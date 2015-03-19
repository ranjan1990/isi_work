from scipy.optimize import minimize
import numpy as np
print "\n****************************************************************problem 1*********************************************"
a=np.array([[108,115],[115,108]])
b=np.array([92,113])
x=np.linalg.solve(a,b)
print "d1=",x[0]," d2=",x[1]

print "\n****************************************************************problem 2***********************************************"


def func(X,sign=1.0):
	Y=sign*(92*X[0]+113*X[1])
	return(Y)

def func_deriv(X,sign=1.0):
	dfx0=sign*(92)
	dfx1=sign*(113)
	return(np.array([dfx0,dfx1]));


cons=({'type':'ineq','fun':lambda X: np.array([108*X[0]+115*X[1]]),'jac':lambda X: np.array([108.0,115.0])},{'type':'ineq','fun':lambda X: np.array([115*X[0]+108*X[1]]),'jac':lambda X: np.array([115.0,108.0])})

res=minimize(func, [-1.0,10.0], args=(1.0,), jac=func_deriv,constraints=cons,method='SLSQP', options={'disp': False})

#print res
if(res.success):
	print "solution exists ",res.x
else:
	print "the equation is unbounded "



cons=({'type':'ineq','fun':lambda X: np.array([108*X[0]+115*X[1]]),'jac':lambda X: np.array([108.0,115.0])},{'type':'ineq','fun':lambda X: np.array([115*X[0]+108*X[1]]),'jac':lambda X: np.array([115.0,108.0])},{'type':'ineq','fun':lambda X: np.array([X[0]+1]),'jac':lambda X: np.array([1.0,0.0])},{'type':'ineq','fun':lambda X: np.array([X[1]+1]),'jac':lambda X: np.array([0.0,1.0])})
res=minimize(func, [-1.0,10.0], args=(1.0,), jac=func_deriv,constraints=cons,method='SLSQP', options={'disp': False})



print"_________________________________________________________________\nafter adding contrain s1>=-1 s2>=-1"
if(res.success):
	print "solution exists ",res.x
	print"min cost=",res.x[0]*92+res.x[1]*113
else:
	print "the equation is unbounded "


print "\n****************************************************************problem 4***********************************************"
  
a=np.array([[108,115],[115,108]])
b=np.array([92,90])
x=np.linalg.solve(a,b)
print "d1=",x[0]," d2=",x[1]


print"_________________________________________________________________\n"

def func1(X,sign=1.0):
	Y=sign*(92*X[0]+90*X[1])
	return(Y)

def func1_deriv(X,sign=1.0):
	dfx0=sign*(92)
	dfx1=sign*(90)
	return(np.array([dfx0,dfx1]));

cons=({'type':'ineq','fun':lambda X: np.array([108*X[0]+115*X[1]]),'jac':lambda X: np.array([108.0,115.0])},{'type':'ineq','fun':lambda X: np.array([115*X[0]+108*X[1]]),'jac':lambda X: np.array([115.0,108.0])},{'type':'ineq','fun':lambda X: np.array([X[0]+1]),'jac':lambda X: np.array([1.0,0.0])},{'type':'ineq','fun':lambda X: np.array([X[1]+1]),'jac':lambda X: np.array([0.0,1.0])})


res=minimize(func1, [-1.0,10.0], args=(1.0,), jac=func1_deriv,constraints=cons,method='SLSQP', options={'disp': False})

#print res
if(res.success):
	print "solution exists: X= ",res.x
	print "cost= ",func1(res.x,1)
else:
	print "unbounded "
	
	
