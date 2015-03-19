import random
def Connected(G,n):
	connected = False
	queue = [0]
	while(len(queue)>0):
		node = queue.pop()
		for i in range(n):
			if(G[node][i]>0):
				#if(ver[1] == 1):
				if(i==n-1):
					connected = True
					break
				else:
					queue.append(i);

	return connected

def find_augmenting_node(L,n):

	total_f=[0 for i in range(n)];

	minflow=999;
	index=0;

	for i in range(n):		#calculating total min(inflow,outflow) of each node)
		inf=0;
		ouf=0;
		for j in range(n):
			if(L[i][j]>0):
				ouf=ouf+L[i][j];
			if(L[j][i]>0):
				inf=inf+L[j][i];
		if(i==0):
			total_f[i]=ouf;
		elif(i==n-1):
			total_f[i]=inf;
		else:
			total_f[i]=min(ouf,inf);	

	#	print "i=",i,"throughput=",total_f[i]
		if(total_f[i]!=0 and total_f[i]<minflow):
			minflow=total_f[i];
			index=i;

	#print total_f,index
	#
	
	for i in range(n):		#if the node is satuarated 
		if(total_f[i] == 0):
			for j in range(n):
				L[j][i]=0

	return(minflow,index)



def level_graph(G,n,l):

	visited=[]
	L=[]
	for i in range(n):
		visited.append(False);
		L.append([-1 for i in range(n)]);
#	print L
#	print v
	visited[0]=True
	Q=[0];
#	print visited
	while(len(Q)>0):	#BFS
		node=Q[0];
		del Q[0]
		for i in range(n):
			if(G[node][i]>0 and visited[i]==False ):
				if(i<n-1):	#its not the sink
					visited[i]=True
					Q.append(i)
				L[node][i]=G[node][i];
				


		
#	print "level G", L
#	(mxf,index)=find_augmenting_node(L,n)   #finding max flow and index of that node

	return(L);


def push_flow(R,L,m_f,index,n):
	Q=[(index,m_f)]
	while(len(Q)>0):
		x1,x2=Q[0]
		del Q[0]
		for i in range(n):
			if(L[x1][i]>0 and x2>0):	#if there is  a level >0 and flow lavue is >0
				if(x2>=L[x1][i]):
					x2=x2-L[x1][i];			#as flow is  distributed 
					Q.append((i,L[x1][i]))				 	
                                        R[x1][i]=R[x1][i]-L[x1][i]
					R[i][x1]=R[i][x1]+L[x1][i]
					L[x1][i]=0;
					
					#add residual back edge.
				else:
					L[x1][i]=L[x1][i]-x2;		#as L[x1][i]>x2
					R[x1][i]=R[x1][i]-x2;		#remove that flow from residual graph 
					R[i][x1]=R[i][x1]+x2
					#add residual back edge
					Q.append((i,x2))
					x2=0;
					break;				#as all the flow are distributed



def pull_flow(R,L,m_f,index,n):
        Q=[(index,m_f)]
        while(len(Q)>0):
                x1,x2=Q[0]
                del Q[0]
                for i in range(n):
                        if(L[i][x1]>0 and x2>0):        #if there is  a level >0 and flow lavue is >0
                                if(x2>=L[i][x1]):
                                        x2=x2-L[i][x1];                 #as flow is  distributed 
                                        Q.append((i,L[i][x1]));
                                        R[i][x1]=R[i][x1]-L[i][x1]
					R[x1][i]=R[x1][i]+L[i][x1]
                                        L[i][x1]=0;

					#add residual back edge
                                else:
                                        L[i][x1]=L[i][x1]-x2;           #as L[x1][i]>x2
                                        R[i][x1]=R[i][x1]-x2           #remove that flow from residual graph 
					R[x1][i]=R[x1][i]+x2
                                        Q.append((i,x2))
                                        x2=0;
                                        break;                          #as all the flow are distributed
			

def remove_nodes(L,n,node):
	inf=0;
        ouf=0;
	total_flow=0
        for j in range(n):
	        if(L[node][j]>0):
                	ouf=ouf+L[node][j];
                if(L[j][node]>0):
                	inf=inf+L[j][node];
	if(node==0):
        	total_flow=ouf;
        elif(node==n-1):
        	total_flow=inf;
        else:
               	total_flow=min(ouf,inf);



	if(total_flow==0):
		if(node==0 or node==n-1):
			return
		else:					#if total  throughput is 0 
			for i in range(n):
				if(L[node][i]!=-1):	
					L[node][i]=-1;
					remove_nodes(L,n,i)
				if(L[i][node]!=-1):
					L[i][node]=-1;
					remove_nodes(L,n,i)
			return



def do_it(R,L,n):
	minf=0
	minf,index=find_augmenting_node(L,n);
		
	if(Connected(L,n)==True):
		push_flow(R,L,minf,index);
		pull_flow(R,L,minf,index);
		remove_nodes(L,n,index)
		
	return(R,L,minf,False)

def MPM(G,n):
        R=list(G)
        flow=0
        while(1):
                L=level_graph(R,n,1);
	
                #print "level",L
                #print "residual",R
                if(not Connected(L,n)):
                        break;

                while(1):
                        if(Connected(L,n)):
				print "levelx",L
                                minf,index=find_augmenting_node(L,n);
                                print "minf=",minf,index
                                push_flow(R,L,minf,index,n);#print "level",L
                                pull_flow(R,L,minf,index,n);
                                remove_nodes(L,n,index)
                                flow=flow+minf
                        else:
                                break;
        print flow


def gen(n):
	V1=[]
	V2=[]
	for i in range(1,n+1):
		if(random.randint(0,1)):
			V1.append(i)
		else:
			V2.append(i)

	A=[[0 for i in range(n+2)] for i in range(n+2)]


	for v in V1:
		A[0][v]=1;
	for v in V2:
		A[v][n+1]=1;


	print "V1=",V1
	print "V2=",V2
	

	
	for k in range(len(V1)*len(V2)):
	#	if(random.randint(0,1)):
		i=random.randint(0,len(V1)-1);
		j=random.randint(0,len(V2)-1);
		A[V1[i]][V2[j]]=1;			
	
	#print A
	return(A)



def input_graph(n):
	G=[]
	for i in range(n):
		a=[]
		for i in range(n):
			a.append(int(raw_input()))
		G.append(a);
	return(G);









G = [
	[0,16,13,0,0,0],
	[0,0,4,12,0,0],
	[0,10,0,0,14,0],
	[0,0,9,0,0,20],
	[0,0,0,7,0,4],
	[0,0,0,0,0,0]
	]
G=[[0,10,5,15,0,0,0,0],
[0,0,4,0,9,15,0,0],
[0,0,0,4,0,8,0,0],
[0,0,0,0,0,0,30,0],
[0,0,0,0,0,15,0,10],
[0,0,0,0,0,0,15,10],
[0,0,3,0,0,0,0,10],
[0,0,0,0,0,0,0,0]]
                  
#input_graph(6);	
MPM(G,8)






'''
R=[[0, 4, 9, 0, 0, 0],[12, 0, 4, 0, 0, 0],[4, 10, 0, 0, 10, 0], [0, 12, 9, 0, 0, 8], [0, 0, 4, 7, 0, 0], [0, 0, 0, 12, 4, 0]]
L=level_graph(R,n,1);
minf,index=find_augmenting_node(L,n);

#			print minf
#push_flow(R,L,minf,index);
#print R
pull_flow(R,L,minf,index);
print R
#			remove_nodes(L,n,index)
i'''


#print R






































#while(1):
#	(L,minf,index)=level_graph(R,n,1);     
#	flow=flow+minf
#	if(Connected(L,n)==False):
#		break;
#	while(1):
#		push_flow(R,L,minf,index);
#		pull_flow(R,L,minf,index);
#		remove_nodes(L,n,index)
#		if(Connected(L,n)==False):
#			break;
#		minf,index=find_augmenting_node(L,n);
#		flow=flow+minf;


#(L,minf,index)=level_graph(R,n,1);    
#minf,index=find_augmenting_node(L,n);
#print L
#print  "throughput =",minf,index
#push_flow(R,L,minf,index);
#pull_flow(R,L,minf,index);
#print "after pushing and pulling flow= ",R
#remove_nodes(L,n,index)

#print "LEVEL",L

#minf,index=find_augmenting_node(L,n);
#print minf,index


#print "residual graph ",R
#print "level graph",L
#print "max flow=",flow

