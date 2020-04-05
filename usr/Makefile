OBJS = libusbmanager.so
OBJO = usbmanager.o
CC = gcc
OGJS:$(OBJO)
	$(CC) $(OBJO) -I /usr/include -L /usr/lib -shared -o $(OBJS)
$(OBJO):usb_manager.c usb_manager.h
	$(CC) usb_manager.c -I ./ -I /usr/include -L /usr/lib -fPIC -c -o $(OBJO)

.PHONY:clean
clean:
	rm -rf *.o *.so
