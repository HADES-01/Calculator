@echo off
pushd ..
make
pushd bin
echo ==== Running Calculator ====
Calculator
popd
popd
