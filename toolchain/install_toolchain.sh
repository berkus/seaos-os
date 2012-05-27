#!/bin/sh
test -e built
if [ $? = 0 ]; then
	echo Toolchain already built. Remove library/toolchain/built file to force a rebuild
	exit 1
fi
sudo rm -rf /usr/local/seaos-cross
echo "Installing toolchain..."
test -e build-binutils
if [ $? != 0 ]; then
	make -s extract
fi
make compile_install_tools1
if [ $? != 0 ]; then
	echo "Error binutils install"
	exit 1
fi
export PATH=$PATH:/usr/local/cross-seaos/bin/
make compile_install_tools2
if [ $? != 0 ]; then
	echo "Error in gcc install"
	exit 1
fi
sudo ln /usr/local/cross-seaos/bin/i586-pc-seaos-ranlib /usr/local/bin/i586-pc-seaos-ranlib
make compile_library_full
if [ $? != 0 ]; then
	echo "Error in library compile"
	exit 1
fi
make install_library
if [ $? != 0 ]; then
	echo "Error in library install"
	exit 1
fi

cd build-gcc
make all
sudo make install
cd ..
echo "1" > built
sh ./install_extras.sh

