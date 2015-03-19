from scipy.optimize import minimize
import numpy as np

def func(X,sign=1.0):
	Y=sign*(60*X[0]+100*X[1]+100*X[2])
	return(Y)

def func_deriv(X,sign=1.0):
	dfx0=sign*(60)
	dfx1=sign*(100)
	dfx2=sign*(100)

	return(np.array([dfx0,dfx1,dfx2]));


cons=({'type':'ineq','fun':lambda X: np.array([50*X[0]+90*X[1]+110*X[2]]),'jac':lambda X: np.array([50.0,90.0,110])},{'type':'ineq','fun':lambda X: np.array([60*X[0]+110*X[1]+110*X[2]]),'jac':lambda X: np.array([60.0,110.0,110.0])},{'type':'ineq','fun':lambda X: np.array([80*X[0]+130*X[1]+110*X[2]]),'jac':lambda X: np.array([80.0,130.0,110.0])},{'type':'ineq','fun':lambda X: np.array([X[0]+2]),'jac':lambda X: np.array([1.0,0,0])},{'type':'ineq','fun':lambda X: np.array([X[1]+2]),'jac':lambda X: np.array([0,1.0,0])})



res=minimize(func, [-1.0,10.0,32], args=(1.0,), jac=func_deriv,constraints=cons,method='SLSQP', options={'disp': True})

print res

