#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include<iomanip>
using namespace std;

int split(const string &src,const char split_char,vector<string>&res){
    //split string by split_char
    int len = src.size();
    string one_split="";
    for(int i=0;i<len;i++){
        if(src[i]==split_char){
            res.push_back(one_split);
            one_split="";
        }else{
            one_split+=src[i];
        }
    }
    //the last part
    if(one_split.size()!=0){
        res.push_back(one_split);
    }
    return res.size();
}

bool isNum(const string &str){
    // string is number or not
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d)){
         return false;
    }
     if (sin >> c){
       return false;
     }
     return true;
}

int explore(string savefile){
    //explore original file,sum null,max,min

    fstream f("hw1air_data.csv");
    string line;
    //the attribute line
    getline(f,line,'\n');

    vector<string> attribute_line;
    int attribute_num=split(line,',',attribute_line);

    cout<<"attrbutes:"<<endl;
    for(int i=0;i<attribute_num;i++){
        cout<<attribute_line[i]<<' ';
    }
    cout<<endl;
    cout <<"attributes num:"<<attribute_num<<endl;

    //sum null,max,min
    vector<int> sum_null;
    vector<float> sum_max;
    vector<float> sum_min;
    //init
    for(int i=0;i<attribute_num;i++){
        sum_null.push_back(0);
        sum_max.push_back(-1);
        sum_min.push_back(10000000);
    }


    vector<string> data_line;
    int total=0;    //total line
    float value=0;
    vector<int> error_line; //error line num
    while(f.good()){
        total++;    //line+1
        data_line.clear();

        getline(f,line,'\n');

        //split line by ,
        split(line,',',data_line);

        //attribute number != 44,error line
        if(data_line.size()!=attribute_num){
            cout<<"error line in"<<' '<<total<<endl;
            error_line.push_back(total);
            continue;
        }

        //traverse all attribute,check value is NULL,MAX,MIN
        for(int i=0;i<attribute_num;i++){
            if(data_line[i]==""){//value is NULL
                sum_null[i]++;
            }
            if(!isNum(data_line[i])) continue;//not a number
            //max min
            value=atof(data_line[i].data());
            if(sum_max[i]<value){
                sum_max[i]=value;
            }
            if(sum_min[i]>value){
                sum_min[i]=value;
            }
        }
    }
    //output
    freopen(savefile.data(), "w", stdout);

    cout<<std::left<<setw(32)<<"attributes"
        <<std::left<<setw(32)<<"null"
        <<std::left<<setw(32)<<"max"
        <<std::left<<setw(32)<<"min"
        <<endl;
    for(int i=0;i<attribute_num;i++){
        cout<<std::left<<setw(32)<<attribute_line[i]
            <<std::left<<setw(32)<<sum_null[i]
            <<std::left<<setw(32)<<sum_max[i]
            <<std::left<<setw(32)<<sum_min[i]
            <<endl;
    }
    cout<<total-1<<' '<<"lines"<<endl;
    cout<<"error lines(attributes != 44):";
    for(int i=0;i<error_line.size();i++){
        cout<<'\t'<<error_line[i];
    }
    freopen("CON","w",stdout);
    cout<<"explore info save in "<<savefile<<endl;

    return 0;
}

int main()
{
    explore("explore.csv");
    return 0;
}

