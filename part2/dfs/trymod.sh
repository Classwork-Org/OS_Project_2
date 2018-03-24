set -e;
cd ../linear;
printf "1)running linear script\n"
source trymod.sh > /dev/null;
printf "done\n\n"

cd ../dfs;
printf "2)building dfs module\n"
make all;
dmesg -C;
printf "done\n\n"

printf "3)inserting module\n"
insmod dfs.ko;
printf "done\n\n"

printf "4)removing module\n"
rmmod dfs;
printf "done\n\n"

printf "5)kernal output:\n"
dmesg;
printf "done\n\n"

printf "6)redirecting outpus to files\n"
ps -eLf > ps.txt;
dmesg > output.txt;
printf "done\n\n"

printf "7)cleaning up\n"
make clean;
printf "done\n\n"

printf "running match script\n";	
python matchout.py;
printf "trymod complete \n"
