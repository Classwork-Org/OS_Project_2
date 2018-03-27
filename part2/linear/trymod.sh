set -e;
printf "1)building linear module\n"
make;
printf "done\n\n"
dmesg -C;

printf "2)inserting module\n\n"
insmod linear.ko;

printf "3)removing module\n\n"
rmmod linear;

printf "4)kernal output:\n\n"
dmesg;
printf "done\n\n"

printf "5)redirecting output to text file\n"
dmesg > output.txt;
ps -eLf > ps.txt;
printf "done\n\n"

printf "6)cleaning up\n\n"
make clean;
printf "done\n"

printf "running match script\n";	
python matchout.py;
printf "trymod complete \n"
