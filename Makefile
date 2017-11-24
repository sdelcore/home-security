all: home-security

home-security: main.o devicehandler.o motionhandler.o ping.o homesecurity.o backupprocess.o cameraprocess.o
	g++ main.o devicehandler.o motionhandler.o ping.o homesecurity.o backupprocess.o cameraprocess.o -o home-security

main.o: main.cpp
	g++ -c main.cpp

devicehandler.o: devicehandler.cpp
	g++ -c devicehandler.cpp

motionhandler.o: motionhandler.cpp
	g++ -c motionhandler.cpp

ping.o: ping.cpp
	g++ -c ping.cpp
	
homesecurity.o: homesecurity.cpp
	g++ -c homesecurity.cpp
	
cameraprocess.o: cameraprocess.cpp
	g++ -c cameraprocess.cpp
	
backupprocess.o: backupprocess.cpp
	g++ -c backupprocess.cpp

clean:
	rm *o home-security
	
install:
	su -c "chmod 755 homesecurityd"
	su -c "cp home-security /usr/sbin/"
	su -c "cp homesecurityd /etc/init.d/"
	su -c "ln -s /etc/init.d/homesecurityd /etc/rc2.d/S01homesecurityd"
	#su -c "cp home-security-config /etc/sysconfig/"
	#su -c "ssh-keygen"
	#su -c "ssh-copy-id pi@192.168.0.11"
	
uninstall:
	su -c "rm /usr/sbin/home-security"
	su -c "rm /etc/init.d/homesecurityd"
	su -c "rm /etc/rc2.d/S01homesecurityd"
	#su -c "rm /etc/sysconfig/home-security-config"
	
	
