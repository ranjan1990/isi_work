obj-m+= h1.o
obj-m+=x1.o
obj-m+=trace1.o
x1-objs:=init.o exit.o



all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules


