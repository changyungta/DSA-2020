#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring> 
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <iterator>
using namespace std;

class data {
    public:
        data();
        string sale;
        string productPrice;
        string productAge;
        string productGender;
        string productId;
        string userId;
        int clickTime;
};

data::data(){}

bool cmp(const data &a, const data &b)
{
    if(a.userId < b.userId)
        return true;
    else if(a.userId > b.userId)
        return false;
     else
    {
        if(a.productId < b.productId)
            return true;
        else if(a.productId > b.productId)
            return false;
        else
        {
            if(a.clickTime < b.clickTime)
                return true;
            else
                return false;
        }
    }
}
int main(int argc, char *argv[])
{
    string other;
    vector<data> alldata;
    //cout<<argv[1]<<endl;
    ifstream fp(argv[1]); //my input file
    int i;
    string time;
    while(!fp.eof())
    {
        data tmp;
        getline(fp, tmp.sale,'\t');
        for(i=0;i<2;i++)
            getline(fp,other,'\t');
        getline(fp,time,'\t');
        tmp.clickTime=stoi(time);
        getline(fp,other,'\t');
        getline(fp,tmp.productPrice,'\t');
        getline(fp,tmp.productAge,'\t');
        for(i=0;i<2;i++)
            getline(fp,other,'\t');
        getline(fp,tmp.productGender,'\t');
        for(i=0;i<9;i++)
            getline(fp,other,'\t');
        getline(fp,tmp.productId,'\t');
        for(i=0;i<2;i++)
            getline(fp,other,'\t');
        getline(fp,tmp.userId);
        alldata.push_back(tmp);
    }
    sort(alldata.begin(), alldata.end(), cmp);
    unordered_map<string, int> mapdata;
    int m=0;
    string save="0";
    vector<set<string> > allproduct;
    unordered_map<string, int> mapproduct;
    unordered_map<string, int>::iterator it;
    set<string> tmp;
    int count=0;
    while(m < alldata.size())
    {
        if(alldata[m].userId != save){
            mapdata[alldata[m].userId]=m;
            save=alldata[m].userId; 
        }
        it=mapproduct.find(alldata[m].productId);
        if(it == mapproduct.end()){
            mapproduct[alldata[m].productId]=count;
            tmp.clear();
            tmp.insert(alldata[m].userId);
            allproduct.push_back(tmp);
            count++;
        }else{
            int p = mapproduct[alldata[m].productId];
            allproduct[p].insert(alldata[m].userId);
        }

        m++;
    }
    string order;
    int q=0;
    while(!cin.eof())
    {
        getline(cin,order,' ');
        int pos;
        if(order=="get"){
            data test;
            getline(cin, test.userId, ' ');
            getline(cin, test.productId, ' ');
            getline(cin, time);
            test.clickTime=stoi(time);
            auto itr = lower_bound(alldata.begin(),alldata.end(),test,cmp);
            cout<<"********************"<<endl;
            cout<<itr->sale<<endl;
            cout<<"********************"<<endl;
        }
        else if(order=="purchased"){
	    string name;
            getline(cin, name);
            int mapPos=mapdata[name];
            cout<<"********************"<<endl;
            while(alldata[mapPos].userId == name)
            {
                if(alldata[mapPos].sale == "1")
                    cout<<alldata[mapPos].productId<<' '<<alldata[mapPos].clickTime<<' '<<alldata[mapPos].productPrice<<' '
                <<alldata[mapPos].productAge<<' '<<alldata[mapPos].productGender<<endl;
                mapPos++;
            }
            cout<<"********************"<<endl;

        }
        else if(order=="clicked")
        {
            string p1,p2;
            getline(cin, p1, ' ');
            getline(cin, p2);
            set<string> intersect;
            set_intersection(allproduct[mapproduct[p1]].begin(), allproduct[mapproduct[p1]].end(), 
                allproduct[mapproduct[p2]].begin(), allproduct[mapproduct[p2]].end(), inserter(intersect, intersect.begin()));
            cout<<"********************"<<endl;
            for(auto it=intersect.begin(); it!=intersect.end(); ++it)
                cout<<*it<<endl;
            cout<<"********************"<<endl;

        }
        else if(order=="profit")
        {
            string t;
            double theta;
            getline(cin, t, ' ');
	        int targetTime;
            targetTime=stoi(t);
            string th;
            getline(cin, th);
            theta=stod(th);
            int point=0;
            int numSale=0, totalClick=0;
            int outCount=0;
            string prevUser="0";
            double result;
            cout<<"********************"<<endl;
            while(point<alldata.size())
            {
                if(alldata[point].userId != prevUser && point > 0){
                    if(totalClick==0)
                        result=0;
                    else
                        result=(double)numSale/totalClick;

                    if(result >= theta && alldata[point-1].userId != "0" && alldata[point-1].userId != "") {
                        cout<<prevUser<<endl;
                        outCount++;
                    }
                    numSale=0;
                    totalClick=0;
                    prevUser=alldata[point].userId;
                }
                if(alldata[point].clickTime > targetTime && alldata[point].userId != "0" && alldata[point].userId != " "){
                    totalClick++;
                if(alldata[point].sale=="1")
                    numSale++;
            }
            point++;
      		if(outCount>9)
                break;
            }
	    cout<<"********************"<<endl;

        }
        else if(order=="quit")
            break;
    }
    
}

