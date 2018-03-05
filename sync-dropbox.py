from subprocess import call 

photofile = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload /home/pi/motion /"   
call ([photofile], shell=True)  
