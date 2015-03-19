from scipy.spatial import ConvexHull
from random import *
from math import sqrt
import numpy as np

def generatepoints(n):
	return(np.random.rand(n,2))

def genpoint(n):
	a=[]
	for i in range(n):
		a.append([uniform(-100,100),uniform(-100,100)]);
	return(a)

def find_cv_point(cv):
	indices = np.unique(cv.simplices.flatten()) #find indices of convex vertices.
	vertices = [p[i] for i in indices]
	return vertices


def dist(p,i,j):
	nop=len(p);
	if(j<i or j-i >=nop):
		return(-1.0)
	if(j>=nop):
		j=j-nop
	return sqrt((p[i][0]-p[j][0])**2+(p[i][1]-p[j][1])**2)


def build_matrix(p):
	print p
	nop=len(p);
	a=[]
	for i in range(nop):
		x=[-1]*nop*2
		a.append(x);
	
	for i in range(nop):
		for j in range(nop*2):
			if(i<=j):
				a[i][j]=dist(p,i,j)
			else:
				#a[i][j]=dist(p,i,j-nop)
				pass	

	
	return(a);		

def red(po,row,col):
	nw_row=list(row);
	nw_col=[]
	
	i=0;j=0
	n=len(nw_row)
	while(len(nw_col)<n):
		if(dist(po,i,j)>=dist(po,i,j+1)):
			if(i<n):
				nw_col.append(j);
				i=i+1;
				j=j+1	
			elif(i==n):
				j=j+1;
		else:
			j=j+1



	return(nw_row,nw_col);
















	

def maxcomp(p,row,col):
	l=len(p)
	(n_r,n_c)=red(p,row,col)

	global index
	if(len(n_r)==1): #if there is only one row .then we are finding max distance of all point.by linear search
		maxd=-1
		for i in col:
			if(dist(p,n_r[0],i)>maxd):
				maxd=dist(p,n_r[0],i);
				index[n_r[0]]=i
		#return((index,maxd));
		return
	
	new_row=[]
	for i in range(0,len(n_r),2):    ##taking the even rows
		new_row.append(n_r[i]);

	new_col=list(n_c);
	maxcomp(p,new_row,new_col);

	for i in range(1,len(row),2):
		l = index[row[i-1]]

		r = index[row[i]];
		if(i+1 < len(row)):
			r = index[row[i+1]];
		mx = dist(p,row[i],row[i-1]);
		for j in range(l,r+1):
			if(dist(p,row[i],j)>mx):
				mx = dist(p,row[i],j)
				index[row[i]] = j;
		







num=int(raw_input("enter number of point"));
p=genpoint(num)

p=[[1,2],[1,6],[6,6],[6,2],[3,4],[3,3],[2,3],[8,9],[4,18],[5,19]]
cv = ConvexHull(p)
ver=find_cv_point(cv)
print ver

n=len(ver)   #number of point
r=[i for i in range(n)]
c=[i for i in range(n*2)]

index=[2*(n-1) for i in range(len(ver))]
maxcomp(ver,r,c)
print index


for i in range(0,len(index)):
	index[i]=index[i]%n;

print "max index array=",index


ind1=-1
dis1=-1
for i in range(len(ver)):
	print "farthest point =",ver[i],ver[index[i]]






