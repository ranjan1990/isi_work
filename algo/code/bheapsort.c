#include<iostream>
#include<time.h>
#include<stdlib.h>
#include"bheapsort.h"
using namespace std;

void swap(int *a,int *b)
{
	 int t=*a;
	*a=*b;
	*b=t;
}

	
int left(int i)
{
 return(2*i+1);
}

int right(int j)
{
	return(2*(j+1));
}

int  parent(int i)
{
	return((i-1)/2);

}
void display(int *a,int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<" "<<a[i];
	}
	cout<<endl;
}
void input(int *a,int *b,int n)
{
 	for(int i=0;i<n;i++)
 	{
		b[i]=a[i]=rand()%10000;
	}
}

		













void heapify(int *a,int i,int n)
{
	int l=left(i);
	int largest=i;
	if(l<=n-1&&a[l]>a[largest])
	{
		largest=l;
	}
	if(l+1<=n-1 && a[largest]<a[l+1])		//l+1 = largest 
	{
		largest=l+1;
	}
	if(i!=largest)
	{
		a[i]=a[i]^a[largest];
		a[largest]=a[i]^a[largest];
		a[i]=a[i]^a[largest]; 
//		swap(&a[i],&a[largest]);
		heapify(a,largest,n);
	}

}
	
void makeheap(int *a,int n)
{
	for(int i=n/2;i>=0;i--)
	{
		heapify(a,i,n);
	}

}		

	



void heapSort(int *a,int n)
{	
	makeheap(a,n);

	for(int i=n-1;i>=0;i--)
	{
/*		a[0]=a[i]^a[0];
		a[i]=a[0]^a[i];
		a[0]=a[0]^a[i];*/
		swap(&a[i],&a[0]);
		heapify(a,0,i);

	}


	
}

int  leafSearch(int *a,int i,int n)
{
	int l,r;
	l=left(i);
	while(l<n-1)
	{
		if(a[l]>a[l+1])
		{
			i=l;
		}
		else
		{
			i=l+1;
		}
		l=left(i);
	}
	if(l==n-1)
	{
		i=l;
	}


	return(i);
}



int bupsearch(int *a,int i,int j)
{
	while(a[i]>a[j])
	{
		j=parent(j);
	}
	return(j);
}

void bureheap(int *a,int i,int j)
{
	int temp;
	int x=a[j];
	a[j]=a[i];
	while(j>i)
	{
		j=parent(j);
		temp=a[j];
		a[j]=x;
		x=temp;
	}


 	
}


void buheapsort(int *a,int n)
{
	int j;
	makeheap(a,n);
//	display(a,n);
	for(int i=n-1;i>=0;i--)
	{
		swap(&a[i],&a[0]);
		j=leafSearch(a,0,i);
	//	cout<<"leaf="<<a[j]<<endl;
		j=bupsearch(a,0,j);
		bureheap(a,0,j);	
	}
}




main()
{

        int n=100000;
	int *A=(int *)malloc(sizeof(int)*n);

	int *B=(int *)malloc(sizeof(int)*n);
	if(A==NULL||B==NULL)
	{
		cout<<"not enough mem"<<endl;
	}
	
	clock_t t;
	double t1=0,t2=0;
	for(int i=0;i<1000;i++)
	{

	        input(A,B,n);
	
		t = clock(); 	
		heapSort(A,n);
		t=clock()-t;
		t1=t1+(double(t)/CLOCKS_PER_SEC);

		t = clock(); 	
		buheapsort(B,n);
		t=clock()-t;
		t2=t2+(double(t)/CLOCKS_PER_SEC);
		//display(B,n);
		cout<<" "<<t1<<"  "<<t2<<endl;
	}       



}




