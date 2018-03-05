# home-security
This project uses [motion](https://github.com/Motion-Project/motion)
There are two branches, master & pin_devices

The master branch contains a python websocket server, that accepts commands to start/stop the motion daemon, a cron job is used to sync the output pictures/images to dropbox.

ping_devices pings the ip addresses of specified devices to determine if people are home. This was abandoned due to the fact that iPhone devices disconnect from the internet temperarily while the screen is off.

## Python setup
`sudo pip install git+https://github.com/dpallot/simple-websocket-server.git`
The python script runs on port 8081 for the websocket server.

## Set up motion
https://www.raspberrypi.org/forums/viewtopic.php?t=18314

## Set up Dropbox-Uploader
http://raspi.tv/2013/how-to-use-dropbox-with-raspberry-pi

## Cronjob
run `crontab -e` and add:
`* * * * * /home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload /home/pi/motion / >/dev/null 2>&1`
# To-Do
 - add a check for the ip address that is connected so only certain devices can arm/disarm
