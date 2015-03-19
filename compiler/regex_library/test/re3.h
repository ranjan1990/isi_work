#ifndef _RE3_H_
#define _RE3_H_

#include<vector>
#include<stack>

using namespace std;

bool parse_status;

typedef struct transition
{
        char c;        									//transiton symbol;
        int v1,v2;      								//v1---c--->v2  format
        int flag;       								//flag=1 to track null transition or not ;
}Transitionstr;	


class NFA
{

        public:
                int start_state;						//start state of the NFA
				int final_state;						//final state of the NFA
                vector<transition> T;   				//set of transition
                NFA()									//constructor
				{
					start_state=0;
				};                          			//constructor
                void set_vcount(int n); 				//set number of vertex to n  in the transition graph;
                void set_trans(int v1,int v2,char c1);  //set transition v1----c---->v2 with char c
                void set_fstate(int x);                 //set single final state single_fs to x;
                int get_fstate(void);
};



//This method is used to set the final_state.
void NFA::set_vcount(int n)
{
	/*
	*code whould be added here 
	*when the extended version
	*whould be written.
	*/
	
	set_fstate(n-1);
}



//This method is used to set the final_state.
void NFA::set_fstate(int x)
{
	final_state = x;
}



//This method is used to get the final_state.
int NFA::get_fstate(void)
{
	 return(final_state);
}




//This method is used to set a transition.
void NFA::set_trans(int x1,int x2,char c1)
{
	transition *temp=new transition;
	temp->v1=x1;
	temp->c=c1;
	temp->v2=x2;
	T.push_back(*temp);
}



extern NFA regex_to_nfa(string re);
extern void dis_NFA(NFA nfa);
extern bool strParse(string str , NFA nfa);
extern vector<char> convertRegex(string re);
extern vector<char> conv_regextoPostfix(vector<char>);
extern bool strParse1(string str , NFA nfa);
extern bool regex_match(string regex,string str);
extern bool regex_submatch(string regex,string str);

#endif


