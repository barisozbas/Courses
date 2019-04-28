obj-m = hello_driver.o
KVERSION=$(shell uname -r)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
	gcc -g -Wall -o hello hello.c
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	$(RM) hello

