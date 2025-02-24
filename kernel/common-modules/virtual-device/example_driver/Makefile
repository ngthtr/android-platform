obj-m += example_driver.o
example_driver-objs = src/main.o src/device_file_handler.o src/proc_file_handler.o

all:
	make -C /lib/modules/6.8.0-55-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.8.0-55-generic/build M=$(PWD) clean
