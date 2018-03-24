set -e;
make all;
dmesg -C;
insmod dfs.ko;
rmmod dfs;
dmesg;
dmesg > output.txt;
ps -eLf > ps.txt;
make clean;
printf "\n\n\n";	
python matchout.py;

