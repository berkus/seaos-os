# Makefile for the toolchain

INSTALL_LOC=/usr/local/cross-seaos/
PREFIX=$(INSTALL_LOC)
TARGET=i586-pc-seaos

install_tools:
	@./install_toolchain.sh

extract:
	@echo "Extracting tools..."
	@-tar xjf seaos-cross.tar.bz2 
	@-tar xjf seaos-cross-lib.tar.bz2 
	@mkdir build-newlib build-gcc build-binutils

compile_install_tools1:
	@echo -n "Configuring binutils... "
	@cd build-binutils; sh ../binutils-2.22/configure --target=$(TARGET) --prefix=$(PREFIX) --disable-werror
	@echo done!
	@echo -n "Compiling binutils... "
	@cd build-binutils; make MAKEINFO=makeinfo
	@echo done!
	@echo -n "Installing binutils... "
	@cd build-binutils; sudo make install

compile_install_tools2:
	@echo -e -n "\nOkay, time to do gcc. Configuring... "
	@cd build-gcc; sh ../gcc-4.7.0/configure --target=$(TARGET) --prefix=$(PREFIX) --disable-nls --enable-languages=c
	@echo done!
	@echo -n "Compiling gcc... "
	@cd build-gcc; make all-gcc
	@echo done!
	@echo -n "Installing gcc... "
	@cd build-gcc; sudo make install-gcc
	@echo done!
	@echo Tools have been installed!

compile_library_full:
	@echo -n -e "Configuring newlib... "
	@cd build-newlib; ../newlib-1.20.0/configure -q --target=$(TARGET) --prefix=$(PREFIX)
	@echo done!
	@make -s compile_library

compile_library:
	@echo -n "Compiling newlib... "
	@cd build-newlib; make
	@echo done!

compile_ncurses:
	@echo "Compiling ncurses..."
	@cd ncurses-5.9/build; ../configure --host=$(TARGET) --target=$(TARGET) --prefix=$(PREFIX)/$(TARGET) --host=$(TARGET) --without-ada --without-cxx-binding --with-terminfo-dirs=/usr/share/terminfo --with-default-terminfo-dir=/usr/share/terminfo
	@cd ncurses-5.9/build; make

install_ncurses:
	@echo "Installing ncurses..."
	@cd ncurses-5.9/build; su -c "make install"
	@su -c "cp /usr/local/cross-seaos/i586-pc-seaos/include/ncurses/* /usr/local/cross-seaos/i586-pc-seaos/include/"
	
install_library:
	@echo -n "Installing newlib... "
	@cd build-newlib; su -c "make install"
	@echo done!

clean:
	@-rm -rf build-gcc build-newlib build-binutils
	@-mkdir build-binutils build-gcc build-newlib
