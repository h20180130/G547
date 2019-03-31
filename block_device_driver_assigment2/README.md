
kernel version is :  4.15.0-46-generic

1: open folder and type $ make all

2: type -->  sudo insmod main.ko

3: verify module loaded by   ---> lsmod

4: for the partition information using cat /proc/partitions also check using ls -l /dev/dof* or sudo fdisk -l

5: Give permission by typing sudo chmod 777 /dev/dof*

6: 2 logical Parititions of the Device (mydisk1 and mydisk2 each of 255.5KB and 256KB)

7: Write into file using use cat > /dev/mydisk ,to check contents use --> xxd /dev/dof1 | less

8: unload module --> sudo rmmod main.ko



