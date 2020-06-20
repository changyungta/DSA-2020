#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdbool>
using namespace std;

#define MAX_FEATURE (1024+1)

class treenode
{
	public:
		treenode();
		treenode *leftchild;
		treenode *rightchild;
		treenode *parent;
		int type;
		int result;
		int attr_id;
		double threashold;
};

treenode::treenode(){};

double max_data=0;
int max_depth=0;

double data[MAX_FEATURE][MAX_FEATURE]={0};


double confusion(double a, double b)
{
	return (a>b)? 2*b/(a+b) : 2*a/(a+b);
}

double total_cfs(double c, double d, double e, double f)
{
	return (c+d)/(c+d+e+f)*confusion(c,d)+(e+f)/(c+d+e+f)*confusion(e,f);
}

bool cmp(const double &a, const double &b)
{
	return (a<b);
}

double count_confusion(double threashold, int indice, vector<int> data_id)
{
	int big_yes=0, big_no=0, small_yes=0, small_no=0;
	for(int i=0;i<data_id.size();i++){
		if(data[data_id[i]][indice]>=threashold){
			if(data[data_id[i]][0]==1)
				big_yes++;
			else
				big_no++;
		}else{
			if(data[data_id[i]][0]==1)
				small_yes++;
			else
				small_no++;
		}
	}
	return total_cfs(big_yes, big_no, small_yes, small_no);

}

double find_best_threashold(int id, int data_size, vector<int> data_id) //for a specific indice
{
	vector<double> all_val;
	all_val.clear();
	for(int i=0;i<data_id.size();i++)
		all_val.push_back(data[data_id[i]][id]);
	sort(all_val.begin(),all_val.end(),cmp);
	double curr_num, last_num;
	last_num=all_val[0];
	curr_num=all_val[0];
	int j;
	for(j=1;j<all_val.size();j++){
		if(all_val[j]!=last_num){
			curr_num=all_val[j];
			break;
		}
	}
	if(curr_num==last_num) // check if all data of an id are the same
		return max_data+1;
	double best_threashold=(last_num+curr_num)/2;
	double min_confusion=count_confusion(best_threashold, id, data_id);
	double threashold,confusion;
	for(int i=j;i<all_val.size();i++){
		if(curr_num!=all_val[i]){
			last_num=curr_num;
			curr_num=all_val[i];
			threashold=(curr_num+last_num)/2;
			confusion=count_confusion(threashold, id, data_id);
			if(confusion<min_confusion){
				min_confusion=confusion;
				best_threashold=threashold;
			}
		}
	}
	return best_threashold;
}

void decision_tree(double eps_lim, vector<int> id, int data_size, int id_cnt, int depth)
{
 	if(depth>max_depth)
 		max_depth=depth;
 	if(id.size()==0)
 		return;
 	bool same_example=true;
 	for(int i=0;i<id_cnt;i++){ // check if all data are the same
 		double d=data[id[0]][i+1];
 		for(int j=1;j<id.size();j++){
 			if(data[id[j]][i]!=d){
 				same_example=false;
 				break;
 			}
 		}
 		if(same_example==false)
 			break;
 	}
 	int yes=0, no=0;
 	for(int i=0;i<id.size();i++){
 		if(data[id[i]][0]==1)
 			yes++;
 		else
 			no++;
 	}
 	double conf=confusion(yes,no);
 	if(conf<=eps_lim || same_example==true){
 		if(yes>no){
 			for(int i=0;i<depth-1;i++)
 				cout<<"\t";
 			cout<<"\t"<<"return 1;"<<endl;
 		}
 		else{
 			for(int i=0;i<depth-1;i++)
 				cout<<"\t";
 			cout<<"\t"<<"return -1;"<<endl;
 		}
 		return;
 	}else{
 		vector<double> possible_threashold;
 		possible_threashold.clear();
 		for(int i=0;i<id_cnt;i++){
 			double threashold=find_best_threashold(i+1, data_size, id);
 			possible_threashold.push_back(threashold);
 		} 		
 		double min_confusion;
 		int st;
 		for(st=0;st<id_cnt;st++){
 			if(possible_threashold[st]!=max_data+1){
 				min_confusion=count_confusion(possible_threashold[st], st+1, id);
 				break;
 			}

 		}
 		int min_id=st+1;
 		for(int i=st;i<id_cnt;i++){
 			if(possible_threashold[i]==max_data+1)
 				continue;
 			double confusion=count_confusion(possible_threashold[i], i+1, id);
 			if(confusion<min_confusion){
 				min_confusion=confusion;
 				min_id=i+1;
 			}
 		}
 		vector<int> left_id;
 		vector<int> right_id;
 		for(int i=0;i<data_size;i++){
 			if(data[id[i]][min_id]<possible_threashold[min_id-1])
 				left_id.push_back(id[i]);
 			else
 				right_id.push_back(id[i]);
 		}
 		for(int i=0;i<depth-1;i++)
 			cout<<"\t";
 		cout<<"if(attr["<<min_id<<"]<"<<possible_threashold[min_id-1]<<"){"<<endl;
 		decision_tree(eps_lim, left_id, left_id.size(), id_cnt, depth+1);
 		cout<<"}"<<endl;
 		for(int i=0;i<depth-1;i++)
 			cout<<"\t";
 		cout<<"else{"<<endl;
 		decision_tree(eps_lim, right_id, right_id.size(), id_cnt, depth+1);
 		cout<<"}"<<endl;
 		return;

 	}
 }

int main(int argc, char *argv[])
{
	string fname=argv[1];
	double eps_lim=stod(argv[2]);
	ifstream fp;
	fp.open(fname);
	string istring;
	int max_id=1;
	int total=0;
	while (getline(fp, istring)) {
		total++;
    	char *cstring, *tmp;
    	int label;
		cstring = new char[istring.size() + 1];
    	strncpy(cstring, istring.c_str(), istring.size()+1);

    	tmp =  strtok(cstring, ": ");
    	label = atoi(tmp); //result 1 or -1
    	tmp = strtok(NULL, ": ");

    	while(tmp != NULL) {
      		int id = atoi(tmp);
      		tmp = strtok(NULL, ": ");
      		if(id>max_id)
      			max_id=id;
      		tmp = strtok(NULL, ": ");
    	}

    	delete[] cstring;
 	}
 	fp.close();
 	fp.open(fname);
 	int pos=0;
 	while (getline(fp, istring)) {
    	char *cstring, *tmp;
    	int label;
		cstring = new char[istring.size() + 1];
    	strncpy(cstring, istring.c_str(), istring.size()+1);

    	tmp =  strtok(cstring, ": ");
    	label = atoi(tmp); //result 1 or -1
    	data[pos][0]=label;
    	tmp = strtok(NULL, ": ");

    	while(tmp != NULL) {
      		int id = atoi(tmp);
      		tmp = strtok(NULL, ": ");
      		if(atof(tmp)>max_data)
      			max_data=atof(tmp);
      		data[pos][id]=atof(tmp);
      		tmp = strtok(NULL, ": ");
    	}
    	pos++;
    	delete[] cstring;
 	}
 	fp.close();
 	vector<int> all_id;
 	for(int i=0;i<pos;i++)
 		all_id.push_back(i);
 	cout<<"int tree_predict(double *attr){"<<endl;
 	decision_tree(eps_lim, all_id, pos, max_id, 1);
 	cout<<"}"<<endl;
}