G=[]

def input_graph(n):
   for i in range(n):
      arr=raw_input()
      arr=arr.split(" ");
      l=[]
      for j in range(n):
         l.append(int(arr[j]));
      G.append(l);
 

def print_graph():
      for l1 in G:
         i=0
         for l2 in l1:
              i=i+1;
              print(l2),
         print "\n"


def find_augpath_dfs(G,s,t,n):
      STACK=[s];
      P=[-1]*8
      P[0]=0;
      while(len(STACK)!=0):
         print STACK
         v=STACK.pop()
         
         for i in range(n):
            l=G[v][i]
            
            if(i==t and G[v][i]!=0):
               P[i]=v
               temp=t
               L=[t]
               while(P[temp]!=s):
                  L.append(P[temp]);
               L.append(s);
               return(L);

               break;
            if(l!=0):
               P[i]=v
               STACK.append(i);
       
       
input_graph(8)
#print_graph()
L=find_augpath_dfs(G,0,7,8)
print L;



          

	




