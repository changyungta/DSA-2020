#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

class job{
	public:
		job();
		int job_id;
		int priority;
};
class mmheap{
	public:
		mmheap();
		vector<job> alljob;
		int quota;
};

job::job(){}
mmheap::mmheap(){}

void swap(job& job1, job& job2){
	job tmp;
	tmp=job1;
	job1=job2;
	job2=tmp;
}

void push_down_min(mmheap& printer, int index){
	int size=printer.alljob.size()-1;
	int child_index=2*index+1; //child with smaller index
	if(child_index<=size){
		int m=child_index;
		if(child_index+1<=size && printer.alljob[m].priority > printer.alljob[child_index+1].priority)
			m=child_index+1; //child with bigger index
		if(2*child_index+1<=size && printer.alljob[m].priority > printer.alljob[2*child_index+1].priority)
			m=2*child_index+1; //grandchild by the smaller index child
		if(2*child_index+2<=size && printer.alljob[m].priority > printer.alljob[2*child_index+2].priority)
			m=2*child_index+2;
		if(2*child_index+3<=size && printer.alljob[m].priority > printer.alljob[2*child_index+3].priority)
			m=2*child_index+3;
		if(2*child_index+4<=size && printer.alljob[m].priority > printer.alljob[2*child_index+4].priority)
			m=2*child_index+4;
		if(m-2*child_index>=1 && m-2*child_index<=4){
			if(printer.alljob[m].priority < printer.alljob[index].priority){
				swap(printer.alljob[m], printer.alljob[index]);
				int parent;
				if(m%2==0)
					parent=(m-2)/2;
				else
					parent=(m-1)/2;
				if(printer.alljob[m].priority > printer.alljob[parent].priority)
					swap(printer.alljob[m], printer.alljob[parent]);
				push_down_min(printer, m);
			}
		}else if(printer.alljob[m].priority < printer.alljob[index].priority){
			swap(printer.alljob[m], printer.alljob[index]);
		}
	}
	return;
}
void push_down_max(mmheap& printer, int index){
	int size=printer.alljob.size()-1;
	int child_index=2*index+1; //child with smaller index
	if(child_index<=size){
		int m=child_index;
		if(child_index+1<=size && printer.alljob[m].priority < printer.alljob[child_index+1].priority)
			m=child_index+1; //child with bigger index
		if(2*child_index+1<=size && printer.alljob[m].priority < printer.alljob[2*child_index+1].priority)
			m=2*child_index+1; //grandchild by the smaller index child
		if(2*child_index+2<=size && printer.alljob[m].priority < printer.alljob[2*child_index+2].priority)
			m=2*child_index+2;
		if(2*child_index+3<=size && printer.alljob[m].priority < printer.alljob[2*child_index+3].priority)
			m=2*child_index+3;
		if(2*child_index+4<=size && printer.alljob[m].priority < printer.alljob[2*child_index+4].priority)
			m=2*child_index+4;
		if(m-2*child_index>=1 && m-2*child_index<=4){
			if(printer.alljob[m].priority > printer.alljob[index].priority){
				swap(printer.alljob[m], printer.alljob[index]);
				int parent;
				if(m%2==0)
					parent=(m-2)/2;
				else
					parent=(m-1)/2;
				if(printer.alljob[m].priority < printer.alljob[parent].priority)
					swap(printer.alljob[m], printer.alljob[parent]);
				push_down_max(printer, m);
			}
		}else if(printer.alljob[m].priority > printer.alljob[index].priority){
			swap(printer.alljob[m], printer.alljob[index]);
		}
	}
	return;
}

void push_down(mmheap& printer, int index){
	int level=int(log2(index+1));
	if(level%2==0){
		push_down_min(printer, index);
	}else{
		push_down_max(printer, index);
	}
}

void push_up_min(mmheap& printer, int index){
	int gpindex=index;
	if(gpindex%2==0){
		gpindex=(gpindex-2)/2;
		if(gpindex%2==0)
			gpindex=(gpindex-2)/2;
		else
			gpindex=(gpindex-1)/2;
	}else{
		gpindex=(gpindex-1)/2;
		if(gpindex%2==0)
			gpindex=(gpindex-2)/2;
		else
			gpindex=(gpindex-1)/2;
	}
	if(gpindex>=0 && printer.alljob[index].priority < printer.alljob[gpindex].priority){
		swap(printer.alljob[index], printer.alljob[gpindex]);
		push_up_min(printer, gpindex);
	}
}

void push_up_max(mmheap& printer, int index){
	int gpindex=index;
	if(gpindex%2==0){
		gpindex=(gpindex-2)/2;
		if(gpindex%2==0)
			gpindex=(gpindex-2)/2;
		else
			gpindex=(gpindex-1)/2;
	}else{
		gpindex=(gpindex-1)/2;
		if(gpindex%2==0)
			gpindex=(gpindex-2)/2;
		else
			gpindex=(gpindex-1)/2;
	}
	if(gpindex>=0 && printer.alljob[index].priority > printer.alljob[gpindex].priority){
		swap(printer.alljob[index], printer.alljob[gpindex]);
		push_up_max(printer, gpindex);
	}
}

void push_up(mmheap& printer, int index){
	if(index!=0){
		int level=int(log2(index+1));
		int parent;
		if(index%2==0)
			parent=(index-2)/2;
		else
			parent=(index-1)/2;
		if(level%2==0){
			if(printer.alljob[index].priority > printer.alljob[parent].priority){
				swap(printer.alljob[index], printer.alljob[parent]);
				push_up_max(printer, parent);
			}else{
				push_up_min(printer, index);
			}
		}else{
			if(printer.alljob[index].priority < printer.alljob[parent].priority){
				swap(printer.alljob[index], printer.alljob[parent]);
				push_up_min(printer, parent);
			}else{
				push_up_max(printer, index);
			}
		}
	}
	return;
}
void remove_min(mmheap& printer){
	int last_index=printer.alljob.size()-1;
	printer.alljob[0]=printer.alljob[last_index];
	printer.alljob.erase(printer.alljob.begin()+last_index);
	push_down(printer, 0);
}

void remove_max(mmheap& printer, int max_id){
	int last_index=printer.alljob.size()-1;
	printer.alljob[max_id]=printer.alljob[last_index];
	printer.alljob.erase(printer.alljob.begin()+last_index);
	push_down(printer, max_id);
}

int getmin(mmheap& printer){
	job save=printer.alljob[0];
	remove_min(printer);
	return save.job_id;
}

int getmax(mmheap& printer){
	int max_index;
	job save;
	if(printer.alljob.size()==1){
		save=printer.alljob[0];
		remove_min(printer);
	}
	else if(printer.alljob.size()==2){
		save=printer.alljob[1];
		remove_max(printer, 1);
	}else{
		if(printer.alljob[1].priority < printer.alljob[2].priority)
			max_index=2;
		else
			max_index=1;
		save=printer.alljob[max_index];
		remove_max(printer,max_index);
	}
	return save.job_id;
	
}
void drop(vector<mmheap> &allprinter, int printer_id){
	if(allprinter[printer_id].alljob.size()==0)
		cout<<"no jobs in "<<printer_id<<endl;
	else{
		int job_id=getmin(allprinter[printer_id]);
		cout<<job_id<<" dropped on printer "<<printer_id<<endl;
	}
	return;

}

void print(vector<mmheap> &allprinter, int printer_id){
	if(allprinter[printer_id].alljob.size()==0)
		cout<<"no jobs in "<<printer_id<<endl;
	else{
		int job_id=getmax(allprinter[printer_id]);
		cout<<job_id<<" printed on printer "<<printer_id<<endl;
	}
}

void quotaopr(vector<mmheap> &allprinter, int q, int printer_id){
	if(allprinter[printer_id].alljob.size()<=q){
		allprinter[printer_id].quota=q;
	}
	else{
		int size=allprinter[printer_id].alljob.size();
		size=size-q;
		for(int i=0;i<size;i++){
			drop(allprinter, printer_id);
		}
		allprinter[printer_id].quota=q;
	}
	cout<<"quota "<<q<<" set for "<<printer_id<<endl;
	return;
}

void add(vector<mmheap> &allprinter, int set_job_id, int set_priority, int printer_id){
	if(allprinter[printer_id].alljob.size()==allprinter[printer_id].quota)
		drop(allprinter, printer_id);
	job tmp;
	tmp.job_id=set_job_id;
	tmp.priority=set_priority;
	allprinter[printer_id].alljob.push_back(tmp);
	int index=allprinter[printer_id].alljob.size()-1;
	push_up(allprinter[printer_id], index);
	cout<<set_job_id<<" added to printer "<<printer_id<<" with priority "<<set_priority<<endl;
}

int main(void)
{
	int num_printer, num_instr;
	cin>>num_printer>>num_instr;
	vector<mmheap> allprinter;
	for(int i=0;i<num_instr;i++){
		mmheap tmp;
		tmp.quota=num_instr;
		allprinter.push_back(tmp);
	}
	for(int i=0;i<num_instr;i++){
		string ins;
		cin>>ins;
		if(ins=="add"){
			int add_job_id,add_priority,add_printer_id;
			cin>>add_job_id>>add_priority>>add_printer_id;
			add(allprinter, add_job_id, add_priority, add_printer_id);
		}else if(ins=="quota"){
			int quota_q,quota_printer_id;
			cin>>quota_q>>quota_printer_id;
			quotaopr(allprinter, quota_q, quota_printer_id);
		}else if(ins=="drop"){
			int drop_printer_id;
			cin>>drop_printer_id;
			drop(allprinter, drop_printer_id);
		}else{
			int print_printer_id;
			cin>>print_printer_id;
			print(allprinter, print_printer_id);
		}
	}
}
