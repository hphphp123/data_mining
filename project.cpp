#include <iostream> 
#include <string>
#include <vector>
#include<fstream> 
using namespace std;
int  splitString(const string & strSrc, const std::string& strDelims, vector<string>& strDest)  
{  
	typedef std::string::size_type ST;  
	string delims = strDelims;  
	std::string STR;  
	if(delims.empty()) delims = "/n/r";  
	ST pos=0, LEN = strSrc.size();  
	while(pos < LEN ){  
		STR="";   
		while( (delims.find(strSrc[pos]) != std::string::npos) && (pos < LEN) ) ++pos;  
		if(pos==LEN) return strDest.size();  
		while( (delims.find(strSrc[pos]) == std::string::npos) && (pos < LEN) ) STR += strSrc[pos++];  
		if( ! STR.empty() ) strDest.push_back(STR);  
	}  
	return strDest.size();  
}  


int main(int argc, char* argv[])
{
	ifstream file ( "hw1air_data.csv" ); // declare file stream: 					http://www.cplusplus.com/reference/iostream/ifstream/
	string value;
	while ( file.good() )
	{
		getline(file,value,'\n'); // read a string until next comma: 		http://www.cplusplus.com/reference/string/getline/
		cout << string( value, 0, value.length() )<<endl; // display value removing the first and the last character from it
		vector<string> splitStrs; //�ѷָ����ַ�������vector����
		splitString(value,",", splitStrs); //�����Զ���ķָ��  
		//��ʾ�ָ����ַ�������(��vector�洢)  
		vector<string>::iterator iter;  
		for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {  
			cout  << *iter<<endl ;  
		}
		
		
	}
}