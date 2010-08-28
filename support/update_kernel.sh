#! /bin/bash
mount /dev/loop0 /mnt/loop
cp  ../BlenderOS_Kernel /mnt/loop
umount /mnt/loop
