#include<iostream>
#include <iomanip>
#include"re3.h"
using namespace std;

int main()
{
	string s1,s2;      //string s1 for regex and s2 for target string.

	cout<<"\n\nString matching:"<<endl;
	for(int i=0;i<15;i++)
	{
		cin>>s1;
		cin>>s2;
	
	    if(regex_match(s1,s2))
        	cout<<left<<setw(15)<<s1<<setw(15)<<s2<<setw(15)<<"Matched"<<endl;
		else
			cout<<left<<setw(15)<<s1<<setw(15)<<s2<<setw(15)<<"Not Matched"<<endl;
	}

	cout<<"\n\nSubstring search:"<<endl;

	for(int i=0;i<15;i++)
	{
		cin>>s1;
		cin>>s2;

	    if(regex_submatch(s1,s2))
			cout<<left<<setw(15)<<s1<<setw(15)<<s2<<setw(15)<<"Substring matched"<<endl;
        else
			cout<<left<<setw(15)<<s1<<setw(15)<<s2<<setw(15)<<"Substring not matched"<<endl;
	}

	return 0;
}



