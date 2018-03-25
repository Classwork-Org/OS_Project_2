set -e;
make;
dmesg -C;
insmod simple.ko;
rmmod simple;
dmesg;
make clean;

