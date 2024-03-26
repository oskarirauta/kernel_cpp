KERNEL_DIR?=kernel
INCLUDES += -I./$(KERNEL_DIR)/include
KERNEL_OBJS:= \
	objs/kernel_info.o

objs/kernel_info.o: $(KERNEL_DIR)/src/kernel_info.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
