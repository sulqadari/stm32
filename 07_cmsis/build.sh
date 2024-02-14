#!bin/shell
export CMSIS_STM32F1=~/develop/STM32_assembly/07_cmsis/CMSIS

rm -rf build > /dev/null
mkdir build && cd build

make

# cmake -GNinja ../
# cmake --build .