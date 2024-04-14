KERNEL_DIR?=./kernel
INCLUDES += -I$(KERNEL_DIR)/include

KERNEL_OBJS:= \
	objs/kernel_info.o \
	objs/kernel_security.o \
	objs/kernel_security_selinux.o \
	objs/kernel_security_apparmor.o \
	objs/kernel_security_seccomp.o

objs/kernel_security.o: $(KERNEL_DIR)/src/security.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/kernel_security_selinux.o: $(KERNEL_DIR)/src/security_selinux.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/kernel_security_apparmor.o: $(KERNEL_DIR)/src/security_apparmor.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/kernel_security_seccomp.o: $(KERNEL_DIR)/src/security_seccomp.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/kernel_info.o: $(KERNEL_DIR)/src/kernel_info.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
