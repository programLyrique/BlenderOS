if [[ $UID != 0 ]] ; then
	echo "Are you root ?"
	exit
fi

if [[ $1 == "-a" ]] ; then
	losetup -o 32256 /dev/loop0 c.img
elif [[ $1 == "-d" ]] ; then
	losetup -d /dev/loop0
else
	echo "USAGE : create_loopdevice.sh -a"
	echo "	      create_loopdevice.sh -d"
	echo "La première crée la loop device, la seconde la supprime"
fi
