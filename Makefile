all:
	cd usr && make
	cd test && make
.PHONY:clean
clean:
	rm -rf ./usr/*.so ./usr/*.o
	rm -rf ./test/usb-manager
