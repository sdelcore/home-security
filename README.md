#home-security
The python script runs on port 8081 for the websocket server.

##Python setup
`sudo pip install git+https://github.com/dpallot/simple-websocket-server.git`

##Set up motion
https://www.raspberrypi.org/forums/viewtopic.php?t=18314

##Set up Dropbox-Uploader
http://raspi.tv/2013/how-to-use-dropbox-with-raspberry-pi

#Cronjob
run `crontab -e` and add:
`* * * * * /home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload /home/pi/motion / >/dev/null 2>&1`


