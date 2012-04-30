#!/bin/sh

echo okay, building extra libraries...
cd extra
tar xjf extra-libs.tar.bz2 
cd termcap-1.3.1
./configure --host=i586-pc-seaos --prefix=/usr/local/cross-seaos/i586-pc-seaos
make CC=i586-pc-seaos-gcc AR=i586-pc-seaos-ar RANLIB=i586-pc-seaos-ranlib
sudo make install

cd ../ncurses-5.9
./configure --host=i586-pc-seaos --enable-termcap --disable-database --prefix=/usr/local/cross-seaos/i586-pc-seaos/ --without-cxx --without-cxx-binding --oldincludedir=/usr/local/cross-seaos/i586-pc-seaos/include --includedir=/usr/local/cross-seaos/i586-pc-seaos/include
make
sudo make install

cd ../readline-6.2
./configure --host=i586-pc-seaos --prefix=/usr/local/cross-seaos/i586-pc-seaos --without-curses --disable-shared
make
sudo make install

cd ../gmp-5.0.4
./configure --host=i586-pc-seaos --prefix=/usr/local/cross-seaos/i586-pc-seaos
make
sudo make install

cd ../mpfr-3.1.0
./configure --host=i586-pc-seaos --prefix=/usr/local/cross-seaos/i586-pc-seaos
make
sudo make install

cd ../mpc-0.9
./configure --host=i586-pc-seaos --prefix=/usr/local/cross-seaos/i586-pc-seaos
make
sudo make install
