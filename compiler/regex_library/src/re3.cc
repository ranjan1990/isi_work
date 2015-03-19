#include"re3.h"
#include<stdlib.h>


//This function is used to display a NFA.
void dis_NFA(NFA nfa)
{

	for(int i=0;i<int(nfa.T.size());i++)
	{
//		cout<<nfa.T[i].v1<<"----"<<nfa.T[i].c<<"--->"<<nfa.T[i].v2<<endl;
	}
}


//This function is used to build new NFA by doing concatenation operation on given two NFAs.
NFA concatenation(NFA nfa1,NFA nfa2)
{
	transition T1;
	NFA temp=NFA();
	temp.set_vcount(nfa1.final_state+1+nfa2.final_state+1);
	temp.set_fstate(nfa1.final_state+1+nfa2.final_state+1-1);
	temp.T=nfa1.T;

	temp.set_trans(nfa1.get_fstate(),nfa1.final_state+1,'$');		//$ is a null transition

	for(int i=0;i<int(nfa2.T.size());i++)
	{
		T1=nfa2.T[i];
		temp.set_trans(nfa1.final_state+1+T1.v1,nfa1.final_state+1+T1.v2,T1.c);

	}

	return(temp);	//return new NFA
}



//This function is used to build new NFA by doing closure operation on given a NFA.
NFA closure(NFA nfa)
{
	//see this we need to add  extra  two state --> http://userpages.umbc.edu/~squire/images/re2.gif
	NFA temp=NFA();
	transition T1;
	temp.set_vcount(nfa.final_state+1+2);
	temp.set_fstate(nfa.final_state+1+1);

	nfa.set_trans(nfa.get_fstate(),0,'$');
	for(int i=0;i<(int)nfa.T.size();i++)
	{
		T1=nfa.T[i];
		temp.set_trans(1+T1.v1,1+T1.v2,T1.c);
	}
	temp.set_trans(0,1,'$');
	temp.set_trans(0,temp.get_fstate(),'$');
	temp.set_trans(1+nfa.get_fstate(),temp.get_fstate(),'$');

	return(temp);

}



//This function is used to build new NFA by doing or operation on given two NFAs.
NFA nfa_or(NFA nfa1,NFA nfa2)
{
	int vcount;
	NFA temp=NFA();
	int base=1;
    	vcount = nfa1.final_state+1 + nfa2.final_state+1 + 2;
	temp.set_vcount(vcount);

		for(int j=0;j<(int)nfa1.T.size();j++)
		{
			temp.set_trans(base+nfa1.T[j].v1,base+nfa1.T[j].v2,nfa1.T[j].c);
		}
		temp.set_trans(0,base,'$');
		temp.set_trans(base+nfa1.final_state,vcount-1,'$');
		base = base + nfa1.final_state+1;


		temp.set_trans(0,base,'$');				//new added for bug 
		temp.set_trans(base+nfa2.final_state,vcount-1,'$');	//""

		for(int j=0;j<(int)nfa2.T.size();j++)
		{
			temp.set_trans(base+nfa2.T[j].v1,base+nfa2.T[j].v2,nfa2.T[j].c);
		}
		return temp;

}



//This recursive function is used to traverse the NFA to parse the string.
void traverseNFA(string str,int i,int curr_state , NFA nfa)
{
    if(curr_state == nfa.final_state && i == (int)str.size() )
    {
        parse_status = true;
        return ;
    }

    for(int j = 0 ; j <(int)nfa.T.size(); j++)
    {
        if(nfa.T[j].v1 == curr_state)
        {
            if(nfa.T[j].c == str[i]) // || nfa.T[j].c == '.')
            {
                traverseNFA(str,i+1,nfa.T[j].v2, nfa);
            }
            if (nfa.T[j].c == '$')
            {
                traverseNFA(str,i,nfa.T[j].v2, nfa);
            }
        }

    }

}



//This function is used to parse the string
bool strParse(string str , NFA nfa)
{
    int i = 0,curr_state = 0;
    parse_status = false;
    traverseNFA(str,i,curr_state, nfa);
    return parse_status;
}




//This function convert the regex into appropriate form to process again. 
vector<char> convertRegex(string re)
{
	vector<char> temp;
	int i = 0;
	bool flag = 1;

	while( i < int(re.size()) )
	{
		if(re[i] == '(')
		{
			if(flag!=1)
			{
				
				temp.push_back('*');
			}
			temp.push_back(re[i]);
			flag=1;
		}
		else if(re[i] == ')')
		{
			temp.push_back(re[i]);
			flag = 0;
		}
		else if(re[i] == '|')
		{
			temp.push_back('+');
			flag=1;
		}
		else if(re[i] == '*')
		{
			flag = 1;
			temp.push_back('$');
			
		}
		else
		{
			if(flag != 1)	
			{
				temp.push_back('*');
				flag = 1;
				i--;
			}
			else
			{
				temp.push_back(re[i]);
				flag = 0;
			}		
		}
		i++;
	}	
	return(temp); 
}



//It return the priority of the given operator.It is used in postfix conversion.
int priority(char ch)
{
	if(ch == '(')
		return 4;
	if(ch == '$' )
		return 3;
	else if(ch == '*' )
		return 2;
	else if(ch == '+' )
		return 1;
	else
		return 0;
}




//This function convert the converted_regex to postfix form.
vector<char> conv_regextoPostfix(vector<char> conv_regex)
{
	stack<char> symbol_stack, char_stack,temp_stack;
    vector<char> postfix_conv_regex;

    for(int i = 0; i <(int) conv_regex.size(); i++)
    {
        if( (conv_regex[i] != '*') && (conv_regex[i] != '$') && (conv_regex[i] != '+') && (conv_regex[i] != '(') && (conv_regex[i] != ')'))
		{
        		char_stack.push(conv_regex[i]);
		}
        else
        {
       		if(conv_regex[i] == '(')
			{
                		symbol_stack.push(conv_regex[i]);
			}
       		else if(conv_regex[i] == ')')
       		{
           		while(symbol_stack.top() != '(' )
           		{
           			char_stack.push(symbol_stack.top());
           			symbol_stack.pop();
           		}
           		symbol_stack.pop();
       		}
       		else if(conv_regex[i] == '+' || conv_regex[i] == '*' )//|| conv_regex[i] == '$' )
       		{
           		while(symbol_stack.size()!=0 && symbol_stack.top() != '(' && priority(symbol_stack.top()) > priority(conv_regex[i]))
           		{
					if(symbol_stack.size()==0)
					{
						cout<<"error in regex"<<endl;
						exit(0);
					}
           			char_stack.push(symbol_stack.top());
           			symbol_stack.pop();
           		}
           		symbol_stack.push(conv_regex[i]);
       		}
			else if(conv_regex[i] == '$')
			{
				char_stack.push(conv_regex[i]);
			}
		}
	}

	while(symbol_stack.size()!=0)
	{
		char_stack.push(symbol_stack.top());
		symbol_stack.pop();
	}

	while(char_stack.size()!=0)
	{
		temp_stack.push(char_stack.top());
		char_stack.pop();
	}

	while(temp_stack.size()!=0)
    {
		postfix_conv_regex.push_back(temp_stack.top());
		temp_stack.pop();
   	}

	return(postfix_conv_regex);
}



//This function build a NFA for a given regex.
NFA  regex_to_nfa(string regex)
{
	vector<char> con_re = convertRegex(regex);
	vector<char> pf_con_re = conv_regextoPostfix(con_re);
	stack<NFA> stack1;  
	NFA nfa1,nfa2;

	for(int i=0;i<(int)con_re.size();i++)
	{
		//cout<<con_re[i];
	}
	//cout<<endl;

	for(int i=0;i<(int)pf_con_re.size();i++)
	{
		//cout<<pf_con_re[i];
	}
	//cout<<endl;

	for(int i=0;i<(int)pf_con_re.size();i++)
	{
		if(pf_con_re[i]!='*' && pf_con_re[i]!='$' && pf_con_re[i]!='+')
		{
			NFA nfa=NFA();
			nfa.set_vcount(2);
			nfa.set_trans(0,1,pf_con_re[i]);
			nfa.set_fstate(1);
			stack1.push(nfa);
		}
		else if(pf_con_re[i]=='$')
		{
			NFA tnfa=stack1.top();
			stack1.pop();
			stack1.push(closure(tnfa));
		}
		else if(pf_con_re[i]=='*')
		{
			nfa1=stack1.top();
			stack1.pop();
			nfa2=stack1.top();
			stack1.pop();
			stack1.push(concatenation(nfa2,nfa1));
		}
		else if(pf_con_re[i]=='+')
		{
			vector<NFA> vnfa;
			nfa1=stack1.top();
			stack1.pop();
			if(stack1.size()==0)
			{
				cout<<"error:regex"<<endl;
				exit(0);
			}

			nfa2=stack1.top();
			stack1.pop();
			stack1.push(nfa_or(nfa1,nfa2));
		}
	}

	while(stack1.size()!=1)
	{
		nfa1=stack1.top();
		stack1.pop();
		nfa2=stack1.top();
		stack1.pop();
		stack1.push(concatenation(nfa2,nfa1));
	}
	return(stack1.top());
}




//This recursive function is used to traverse the NFA to check whether the given string have any substring which match with the regex.
void traverseNFA1(string str,int i,int curr_state , NFA nfa)
{
	if(curr_state == nfa.final_state && i == (int)str.size() )
	{
		parse_status = true;
		return ;
	}
	if(i>(int)str.size())
	{
		return;	
	}

	for(int j = 0 ; j <(int)nfa.T.size(); j++)
	{
		if(nfa.T[j].v1 == curr_state)
		{
			if(nfa.T[j].c == str[i] || nfa.T[j].c == '.')
			{
				traverseNFA1(str,i+1,nfa.T[j].v2, nfa);
			}
			if (nfa.T[j].c == '$')
			{
				traverseNFA1(str,i,nfa.T[j].v2, nfa);
			}
			if (nfa.T[j].c == '#')
			{
				traverseNFA1(str,i+1,nfa.T[j].v2, nfa);
			}
			if (nfa.T[j].c == '?')
			{
				parse_status = true;
				return ;
			}
		}
	}
}

//This function is used to parse the string.
bool strParse1(string str , NFA nfa)
{
	int i = 0,curr_state = 0;
	parse_status = false;
	traverseNFA1(str,i,curr_state, nfa);
	return parse_status;
}

//This function is used to match the string with the given regular expression.
bool regex_match(string regex,string str)
{
	NFA nfa;
	nfa = regex_to_nfa(regex);
	return strParse(str,nfa);
	
}


//This function is used to match any substring of given string with the given regular expression.
bool regex_submatch(string regex,string str)
{
	NFA nfa;
	nfa = regex_to_nfa("#*"+regex+"?*");
	return strParse1(str,nfa);
	
}

