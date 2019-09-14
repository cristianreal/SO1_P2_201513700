obj-m += memo_201513700.o
obj-m += cpu_201513700.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

ejecutar_modulos:
	dmesg -C
	insmod memo_201513700.ko
	rmmod memo_201513700.ko
	insmod cpu_201513700.ko
	rmmod cpu_201513700.ko
	dmesg
