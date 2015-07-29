obj-m += ghost.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	# rmmod ghost
	# insmod ghost.ko
	# lsmod | grep ghost

rmmod:
	# rmmod ghost

show:
	# cat /var/log/syslog | grep ghost
