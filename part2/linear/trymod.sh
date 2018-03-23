make &&
dmesg -C;
insmod linear.ko;
rmmod linear;
dmesg;

