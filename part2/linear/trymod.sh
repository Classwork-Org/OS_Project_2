set -e;
make;
dmesg -C;
insmod linear.ko;
rmmod linear;
dmesg;
make clean;

