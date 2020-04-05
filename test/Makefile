OBJO = usb-manager
CC = gcc
OBJO:main.c
	$(CC) main.c -I /usr/include -I ../usr -L /usr/lib -L ../usr -lusbmanager -o $(OBJO)
.PHONY:clean
clean:
	rm -rf $(OBJO)

	
