PLUGIN_DIR := $(shell arm-none-eabi-g++ -print-file-name=plugin)

all: nexmon.so

nexmon.so: nexmon.o
	g++ -shared -o $@ $<

nexmon.o: ../gcc-nexmon-plugin/nexmon.c
	g++ -std=c++11 -Wall -fno-rtti -Wno-literal-suffix -fPIC -I$(PLUGIN_DIR)/include -c -o $@ $<

clean:
	rm -f *.o *.so
