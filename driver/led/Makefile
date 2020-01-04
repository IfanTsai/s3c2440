KERN_DIR = ~/Embedded/kernel/linux-2.6.22.6

obj-m	+= led.o

all:
	make -C $(KERN_DIR) M=`pwd` modules
	#mount -t nfs -o nolock,vers=2 192.168.8.10:/home/ifantsai/Embedded/nfs/rootfs_2440 /mnt
	cp led.ko /home/ifantsai/Embedded/nfs/rootfs_2440/ -f

.PHONY: clean
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -f Module.symvers
