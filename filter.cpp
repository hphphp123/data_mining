#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include<iomanip>
using namespace std;

//row 15:SUM_YR_1,row16:SUM_YR_2,29:AVG_DISCOUNT,17:SEG_KM_SUM
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


vector<int> clean_line;//store the number of cleaned lines
void filter(){
	fstream f("hw1air_data.csv");
	string line;
	//attribute line
	getline(f,line,'\n');

	vector<string> attribute_line;
	int attribute_num=split(line,',',attribute_line);

	vector<string> data_line;
	int total = 0;
	float value = 0;
	while (f.good())
	{
		total++;//number of data_line
		data_line.clear();

		getline(f,line,'\n');

		//split the data_line
		split(line,',',data_line);

		//attribute_number!=44 error lines
		if(data_line.size()!=attribute_num){
			clean_line.push_back(total);
			continue;
		}

		float YR_1 = atof(data_line[14].data());
		float YR_2 = atof(data_line[15].data());
		float DISCOUNT = atof(data_line[28].data());
		float SEG = atof(data_line[16].data());

		if((YR_1==0)&&(YR_2==0)){
			if(!DISCOUNT && SEG){
				clean_line.push_back(total);
				continue;
			}
		}	
	}
}

int main(){

	filter();

	//once again
	freopen("cleaned_out.csv","w",stdout);
	fstream f("hw1air_data.csv");
	string line;
	getline(f,line,'\n');
	cout<<line<<endl;

	int curr=0;
	int clean_num=clean_line.size();
	int flag=0;
	while(f.good()){
		curr++;
		getline(f,line,'\n');
		for(int i=0;i<clean_num;i++){
			if(curr == clean_line[i]) {flag = 1;break;}
		}
		if(flag) continue;
		cout<<line<<endl;
	}
	return 0;
}

