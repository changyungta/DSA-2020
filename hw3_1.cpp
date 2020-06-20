#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

class data {
    public:
        data();
        string content;
        int prec;
};

data::data(){
	content="";
	prec=-3;
}

int main(void)
{
	unordered_map<string, int> map_prec;
	map_prec["("]=10;
	map_prec[")"]=-2;
	map_prec["u+"]=0;
	map_prec["u-"]=0;
	map_prec["!"]=0;
	map_prec["~"]=0;
	map_prec["*"]=1;
	map_prec["/"]=1;
	map_prec["%"]=1;
	map_prec["b+"]=2;
	map_prec["b-"]=2;
	map_prec["<<"]=3;
	map_prec[">>"]=3;
	map_prec["=="]=4;
	map_prec["!="]=4;
	map_prec["&"]=5;
	map_prec["^"]=6;
	map_prec["|"]=7;
	map_prec["&&"]=8;
	map_prec["||"]=9;

	string input;
	while(cin>>input){
		if(input=="")
			break;
		vector<data> process;
		process.clear();
		int len=input.length();
		data cut;
		cut.content="";
		int i=0;
		for(i=0;i<len;i++){
			if(input[i]>='0'&& input[i]<='9')
				cut.content=cut.content+input[i];
			else if(input[i]=='+'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i>0 && (input[i-1]==')' || (input[i-1]>='0' && input[i-1]<='9'))){
					cut.content="b+";
					cut.prec=map_prec["b+"];
				}
				else{
					cut.content="u+";
					cut.prec=map_prec["u+"];
				}
				process.push_back(cut);
				cut.content="";
			}
			else if(input[i]=='-'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i>0 && (input[i-1]==')' || (input[i-1]>='0' && input[i-1]<='9'))){
					cut.content="b-";
					cut.prec=map_prec["b-"];
				}
				else{
					cut.content="u-";
					cut.prec=map_prec["u-"];
				}
				process.push_back(cut);
				cut.content="";
			}
			else if(input[i]=='!'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i!=(len-1) && input[i+1]=='='){
					cut.content="!=";
					cut.prec=map_prec["!="];
					process.push_back(cut);
					i++;
					cut.content="";
				}else{
					cut.content="!";
					cut.prec=map_prec["!"];
					process.push_back(cut);
					cut.content="";
				}
			}
			else if(input[i]=='='){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i!=(len-1) && input[i+1]=='='){
					cut.content="==";
					cut.prec=map_prec["=="];
					process.push_back(cut);
					i++;
					cut.content="";
				}
			}
			else if(input[i]=='<'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i != len-1 && input[i+1]=='<'){
					cut.content="<<";
					cut.prec=map_prec["<<"];
					process.push_back(cut);
					i++;
					cut.content="";
				}
			}
			else if(input[i]=='>'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i != len-1 && input[i+1]=='>'){
					cut.content=">>";
					cut.prec=map_prec[">>"];
					process.push_back(cut);
					i++;
					cut.content="";
				}
			}
			else if(input[i]=='&'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i!=(len-1) && input[i+1]=='&'){
					cut.content="&&";
					cut.prec=map_prec["&&"];
					process.push_back(cut);
					i++;
					cut.content="";
				}else{
					cut.content="&";
					cut.prec=map_prec["&"];
					process.push_back(cut);
					cut.content="";
				}

			}
			else if(input[i]=='|'){
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				if(i!=(len-1)&&input[i+1]=='|'){
					cut.content="||";
					cut.prec=map_prec["||"];
					process.push_back(cut);
					i++;
					cut.content="";
				}else{
					cut.content="|";
					cut.prec=map_prec["|"];
					process.push_back(cut);
					cut.content="";
				}
			}
			else{
				if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
				cut.content=input[i];
				string tmp="";
				tmp=tmp+input[i];
				cut.prec=map_prec[tmp];
				process.push_back(cut);
				cut.content="";
			}

		}
		if(input[i-1]>='0' && input[i-1]<='9'){
			cut.prec=-1;
			process.push_back(cut);
		}
		//cout<<"finish input"<<endl;
		int len_proc=process.size();
		int max_prec=-3;
		vector<data> postfix;
		postfix.clear();
		stack<data> opr_post;
		for(i=0;i<len_proc;i++){
			if(process[i].prec == -1)
				postfix.push_back(process[i]);
			else if(process[i].content=="("){
				max_prec=map_prec["("];
				opr_post.push(process[i]);
			}
			else if(process[i].content==")"){
				while(opr_post.top().content != "("){
					postfix.push_back(opr_post.top());
					opr_post.pop();
				}
				opr_post.pop();
				if(opr_post.size()>0)
					max_prec=opr_post.top().prec;
				else
					max_prec=-3;
				
			}
			else if(opr_post.size()>0 && process[i].prec==0 && opr_post.top().prec==0){
				opr_post.push(process[i]);
			}
			else{
				if(opr_post.empty() || max_prec==10){
					max_prec=process[i].prec;
					opr_post.push(process[i]);
				}
				else if(max_prec <= process[i].prec){
					while(true){
						if(opr_post.size()==0)
							break;
						else{
							if(opr_post.top().prec <= process[i].prec){
								postfix.push_back(opr_post.top());
								opr_post.pop();
							}
							else
								break;
						}
					}
					max_prec=process[i].prec;
					opr_post.push(process[i]);
				}
				else{
					max_prec=process[i].prec;
					opr_post.push(process[i]);
				}
			}
		}
		if(!opr_post.empty()){
			while(true){
				postfix.push_back(opr_post.top());
				if(opr_post.size()>1)
					opr_post.pop();
				else if(opr_post.size()==1){
					opr_post.pop();
					break;
				}
			}
		}
		//cout<<"finish postfix"<<endl;
		int len_post=postfix.size();
		stack<int> num;
		for(i=0;i<len_post;i++){
			if(postfix[i].prec==-1)
				num.push(stoi(postfix[i].content));
			else if(postfix[i].prec==0){
				int numa=num.top();
				num.pop();
				if(postfix[i].content=="u+"){
					numa=numa*1;
					num.push(numa);
				}else if(postfix[i].content=="u-"){
					numa=(-1)*numa;
					num.push(numa);
				}else if(postfix[i].content=="!"){
					numa=!numa;
					num.push(numa);
				}else{
					numa=~numa;
					num.push(numa);
				
				}
			}
			else{
				int num1=num.top();
				num.pop();
				int num2=num.top();
				num.pop();
				if(postfix[i].content=="*"){
					num2=num1*num2;
					num.push(num2);
				}else if(postfix[i].content=="/"){
					if(num1==0)
						num2=0;
					else
						num2=num2/num1;
					num.push(num2);
				}else if(postfix[i].content=="%"){
					if(num1==0)
						num2=0;
					else
						num2=num2%num1;
					num.push(num2);
				}else if(postfix[i].content=="b+"){
					num2=num2+num1;
					num.push(num2);
				}else if(postfix[i].content=="b-"){
					num2=num2-num1;
					num.push(num2);
				}else if(postfix[i].content=="<<"){
					num2=num2<<num1;
					num.push(num2);
				}else if(postfix[i].content==">>"){
					num2=num2>>num1;
					num.push(num2);
				}else if(postfix[i].content=="=="){
					num2=(num2==num1);
					num.push(num2);
				}else if(postfix[i].content=="!="){
					num2=(num2!=num1);
					num.push(num2);
				}else if(postfix[i].content=="&"){
					num2=num2&num1;
					num.push(num2);
				}else if(postfix[i].content=="^"){
					num2=num2^num1;
					num.push(num2);
				}else if(postfix[i].content=="|"){
					num2=num2|num1;
					num.push(num2);
				}else if(postfix[i].content=="&&"){
					num2=num2&&num1;
					num.push(num2);
				}else{
					num2=num2||num1;
					num.push(num2);
				}
			}
		}
		int ans=num.top();
		cout<<"RESULT: "<<int(ans)<<endl;

	
	}

	
}