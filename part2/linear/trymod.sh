make;
dmesg -C;
insmod linear.ko;
rmmod linear;
dmesg;
dmesg > output.txt;
make clean;

