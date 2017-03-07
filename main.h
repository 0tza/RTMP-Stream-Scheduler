#define startFilm 0
#define endFilm 1
#define startAdd 2
#define endAdd 3

#define MAX_STRING_LEN 200
/*FFMPEG COMMAND V1
 ffmpeg 
-ss 01:00 
-re -i bbb720.mp4 
-t 30 
-avoid_negative_ts 1 -threads 0 -preset fast -tune zerolatency
-c copy -f flv rtmp://localhost/show/stream 
</dev/null >/dev/null 2>/var/log/ffmpeg.log
 */ 

#define commandPart1 "ffmpeg"
#define commandPart2 "-ss" //Next String is the offset
#define commandPart3 "-re -i" //Next string is the input
#define commandPart4 "-t" //Next String is the duration
#define commandPart5 "-avoid_negative_ts 1 -threads 0 -preset fast -tune zerolatency"
#define commandPart6 "-c copy -f flv rtmp://localhost/show/" //Next string is the name of the channel
//#define commandPart6 "-c copy -f flv rtmp://sqstreamingserver.com/live/"
#define commandPart7 "</dev/null >/dev/null 2>/var/log/ffmpeg.log &" 
