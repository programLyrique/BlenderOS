#! /bin/bash

if [[ $UID  != 0 ]] ; then
echo "Are you root ?"
exit 1
fi

if [[ $1  == "mount" ]] ; then
	mkdir /mnt/loopBlenderOS
	mount -o loop -t ext2  floppyA /mnt/loopBlenderOS
elif [[ $1 == "umount" ]] ; then
	umount /mnt/loopBlenderOS 
	rm -r /mnt/loopBlenderOS
else
	echo "USAGE : mount_test mount"
	echo "		 mount_test umount"
fi