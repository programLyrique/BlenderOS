#! /bin/bash

pushd .
cd ..
make -j9
popd
./update_kernel.sh
bochs -q
echo Fin
