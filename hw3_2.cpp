#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>
#include <fstream>
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
    map_prec["u+"]=1;
    map_prec["u-"]=1;
    map_prec["*"]=2;
    map_prec["b+"]=3;
    map_prec["b-"]=3;
    map_prec["sin"]=0;
    map_prec["cos"]=0;
    map_prec["exp"]=0;
    map_prec["log"]=0;
    map_prec["pow"]=0;
    map_prec["sqrt"]=0;
    map_prec["fabs"]=0;
    map_prec["("]=10;
	map_prec[")"]=-2;

    string input;
    while(cin>>input){
        vector<data> process;
        process.clear();
        int len=input.length();
        data cut;
		cut.content="";
		int i=0;
        for(i=0;i<len;i++){
            if(input[i]>='0'&& input[i]<='9')
				cut.content=cut.content+input[i];
            else if(input[i]=='.'){
                cut.content=cut.content+input[i];
            }
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
            else if(input[i]=='*'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="*";
                cut.prec=map_prec["*"];
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='s' && input[i+1]=='i' && input[i+2]=='n'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="sin";
                cut.prec=map_prec["sin"];
                i=i+2;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='c' && input[i+1]=='o' && input[i+2]=='s'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="cos";
                cut.prec=map_prec["cos"];
                i=i+2;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='e' && input[i+1]=='x' && input[i+2]=='p'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="exp";
                cut.prec=map_prec["exp"];
                i=i+2;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='l' && input[i+1]=='o' && input[i+2]=='g'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="log";
                cut.prec=map_prec["log"];
                i=i+2;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='p' && input[i+1]=='o' && input[i+2]=='w'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="pow";
                cut.prec=map_prec["pow"];
                i=i+2;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='s' && input[i+1]=='q' && input[i+2]=='r' && input[i+3]=='t'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="sqrt";
                cut.prec=map_prec["sqrt"];
                i=i+3;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]=='f' && input[i+1]=='a' && input[i+2]=='b' && input[i+3]=='s'){
                if(input[i-1]>='0' && input[i-1]<='9'){
					cut.prec=-1;
					process.push_back(cut);
				}
                cut.content="fabs";
                cut.prec=map_prec["fabs"];
                i=i+3;
                process.push_back(cut);
                cut.content="";
            }
            else if(input[i]==','){
                if(cut.content != ""){
                    cut.prec=-1;
                    process.push_back(cut);
                }
                cut.content=",";
                cut.prec=8;
                process.push_back(cut);
                cut.content="";
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
        stack<data> opr_post;
        for(i=0;i<len_proc;i++){
            if(process[i].prec==-1)
                postfix.push_back(process[i]);
            else if(process[i].content=="("){
                if(i>0 && (process[i-1].content=="sin" || process[i-1].content=="cos" || 
                    process[i-1].content=="log" || process[i-1].content=="exp" || 
                    process[i-1].content=="sqrt" || process[i-1].content=="pow" || process[i-1].content=="fabs")){
                    process[i].prec=11;
                    max_prec=11;
                    opr_post.push(process[i]);
                }else{
                    max_prec=map_prec["("];
                    opr_post.push(process[i]);
                }
            }
            else if(process[i].content==")"){
                while(opr_post.top().content != "("){
                    postfix.push_back(opr_post.top());
                    opr_post.pop();
                }
                if(opr_post.top().prec==11){
                    opr_post.pop();
                    postfix.push_back(opr_post.top());
                    opr_post.pop();
                }
                else
                    opr_post.pop();
                if(opr_post.size()>0)
                    max_prec=opr_post.top().prec;
                else
                    max_prec=-3;
            }
            else if(opr_post.size()>0 && process[i].prec==1 && opr_post.top().prec==1){
                opr_post.push(process[i]);
            }
            else if(process[i].content==","){
                while(opr_post.top().content != "("){
                    postfix.push_back(opr_post.top());
                    opr_post.pop();
                }
            }
            else{
                if(opr_post.empty() || max_prec==10 || max_prec==11){
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
        int len_post=postfix.size();
        stack<double> num;
        for(i=0;i<len_post;i++){
            if(postfix[i].prec==-1)
                num.push(stod(postfix[i].content));
            else if(postfix[i].prec==0){
                double numa=num.top();
                num.pop();
                if(postfix[i].content=="sin"){
                    numa=sin(numa);
                    num.push(numa);
                }else if(postfix[i].content=="cos"){
                    numa=cos(numa);
                    num.push(numa);
                }else if(postfix[i].content=="exp"){
                    numa=exp(numa);
                    num.push(numa);
                }else if(postfix[i].content=="log"){
                    if(numa<0)
                        numa=0;
                    else
                        numa=log(numa);
                    num.push(numa);
                }else if(postfix[i].content=="sqrt"){
                    if(numa<0)
                        numa=0;
                    else
                        numa=sqrt(numa);
                    num.push(numa);
                }else if(postfix[i].content=="fabs"){
                    numa=fabs(numa);
                    num.push(numa);
                }else{
                    double numb=num.top();
                    num.pop();
                    numb=pow(numb, numa);
                    num.push(numb);
                }
            }
            else if(postfix[i].prec==1){
                double num1=num.top();
                num.pop();
                if(postfix[i].content=="u+"){
                    num1=num1*1;
                    num.push(num1);
                }else{
                    num1=num1*(-1);
                    num.push(num1);
                }
            }else if(postfix[i].content=="*"){
                double multi_num1=num.top();
                num.pop();
                double multi_num2=num.top();
                num.pop();
                multi_num1=multi_num1*multi_num2;
                num.push(multi_num1);
            }
            else{
                double nump=num.top();
                num.pop();
                double numq=num.top();
                num.pop();
                if(postfix[i].content=="b+"){
                    nump=nump+numq;
                    num.push(nump);
                }else{
                    numq=numq-nump;
                    num.push(numq);
                }
            }
        }
        double ans=num.top();
        printf("RESULT: %.6f\n",ans);

    }
}