# RTMP-STREAM-SCHEDULER #

RTMP Stream Scheduler is a piece of software that can launch RTMP Streams against an NGINX Server in localhost. It should be used in the same server as the ReStreamer ( Nginx ). It can be very useful to set up a tv channel or an online streaming service like Twitch. FFMPEG is used for pretty much everything.
	
A standard use case : ./schedulerCore [timeToSleep] [Name of Media] [mediaPath] [nameOfChannel] [positionToStartFrom] [durationOfPlay]

## Installation 

### FFMPEG ###
	apt-get install ffmpeg 
	
or

	brew install ffmpeg 
	
## Compile
	gcc main.c -o Scheduler
	
## Nginx Configuration 

In addition to the scheduler, Nginx and it's RTMP Module can be used to restream the RTMP Input into : 
* RTMP 
* HLS ( Apple Devices )
* Dash ( Android and others ). 

The configuration file is an example or how many tv channels in HLS can be set. 


## EXAMPLES ##

	Example : Scheduler 0 playFilm vision.mp4 tvc15 00:30 10 
	Means   : Wait for 0 Second Then Play vision.mp4 on channel tvc15 from the position 00:30 (s) of the video for 10 seconds

Example 2 : 0 playFilm vision.mp4 tvc15 00:30 10 15 playFilm bbb720.mp4 tvc15 00:30 10 25 playFilm vision.mp4 tvc15 00:00 10
