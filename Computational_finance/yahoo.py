import pandas.io.data as web
from scipy.stats import norm
import datetime
import numpy as np
import matplotlib.pyplot as plt


print"enter the number of stock"
N=int(raw_input());
SID=[]
for i in range(N):
	SID.append(raw_input("enter STOCK ID (ex:SBIN.NS,SAIL.NS)"))




for i in range(N):
	start = datetime.datetime(2013,8, 1)
	end = datetime.datetime(2014, 12,20)
	f=web.DataReader(SID[i], 'yahoo', start, end)

	#print f
	print "________________________________________________\n"
	#print "DATE    || %change||"
	change=(f.Close-f.Open)*100/f.Open
	#print change
	change.to_csv(SID[i]);
	mean=change.mean()
	std=change.std()
	print "mean=",change.mean()
	print "standrad daviation=",change.std()
	per=norm.ppf(0.05, loc=mean, scale=std)
	print "conf=95% :",per
	per=norm.ppf(0.10, loc=mean, scale=std)
	print "conf=90% :",per
	per=norm.ppf(0.90, loc=mean, scale=std)
	print "conf=10% :",per


	A=[]
	fp=open(SID[i],"r");

	lines=fp.readlines()
	for l in lines:
		l=l.split(",");
		l=float(l[1])
		l=round(l,2)
		A.append(l)
	
	A=np.array(A);
	x = np.arange(-5,5, 0.1);
	l=plt.hist(A);
	plt.xlabel("Percentage Return -->")
	plt.ylabel("Frequency-->")
	plt.show()
	

	range = np.arange(-10, 10, 0.001)
	plt.plot(range, norm.pdf(range,mean,std))
	plt.show()














