#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h> // For Linux	
#include <unistd.h> // For Unix
#include <ctype.h> //For the atoi() function 
#include <string.h>
#include <time.h>
#include <signal.h>

#include "main.h"

/*
	TimeLine : main() -> push() -> fired() -> playVid()	
	Next task : Change strcat to fprintf ( security )
	Next task : Change the link of the nginx streaming server to something new 
	 
*/


int tempID = -1;

void fired(int command, char *hashVid,char *channel,char *offset, char *duration);
void push(int time, int command, char *hashVid,char *channel,char *offset, char *duration);
void playVid (char *hashVid,char *channel,char *offset, char *duration);
char *commandBuilder (char *hashVid, char *channel,char *offset, char *duration);

/*
	05/10/2016
	commandBuilder : Concat the name of the video and the channel with a complete ffmpeg command
	INPUT : Path of Video (local) or location ( HTTP )
	OUTPUT : FFMPEG Command
*/

char *commandBuilder ( char *hashVid, char *channel,char *offset, char *duration) {
	/*
	#define commandPart1 "ffmpeg"
	#define commandPart2 "-ss" //Next String is the offset
	#define commandPart3 "-re -i" //Next string is the input
	#define commandPart4 "-t" //Next String is the duration
	#define commandPart5 "-avoid_negative_ts 1 -threads 0 -preset fast -tune zerolatency"
	#define commandPart6 "-c copy -f flv rtmp://localhost/show/" //Next string is the name of the channel
	#define commandPart7 "</dev/null >/dev/null 2>/var/log/ffmpeg.log &" 
	*/	
	
	char *ffmpegCommand = malloc((strlen(commandPart1) + strlen(commandPart2) + strlen(hashVid) + 2) * sizeof(char));
	//char *offset = "01:00";
	//char *duration = "30";
	
	strcat(ffmpegCommand,commandPart1);
	strcat(ffmpegCommand," ");

	//strcat(ffmpegCommand,hashVid);
	//strcat(ffmpegCommand," ");
	strcat(ffmpegCommand,commandPart2);
	strcat(ffmpegCommand," ");
	strcat(ffmpegCommand,offset);
	strcat(ffmpegCommand," ");
	
	strcat(ffmpegCommand,commandPart3);
	strcat(ffmpegCommand," ");
	strcat(ffmpegCommand,hashVid);
        strcat(ffmpegCommand," ");

	strcat(ffmpegCommand,commandPart4);
	strcat(ffmpegCommand," ");
        strcat(ffmpegCommand,duration);
        strcat(ffmpegCommand," ");

	strcat(ffmpegCommand,commandPart5);
        strcat(ffmpegCommand," ");

	strcat(ffmpegCommand,commandPart6);
        strcat(ffmpegCommand,channel);
        strcat(ffmpegCommand," ");

	strcat(ffmpegCommand,commandPart7);
      
	printf("\n On commandBuilder() : %s",ffmpegCommand);	
	//snprintf(ffmpegCommand,200, "%s %s %s", commandPart1,hashVid,commandPart2);
	return ffmpegCommand;
}
/*
	05/10/2016	
	PUSH : Fork the app to different processes, get them to sleep, and fire a response with the right command
	INPUT : Time to wait ( sleep ) , Command to be executed ( see main.h ) , Path/Adress of the Video, Name of channel 
	OUTPUT : NULL

*/
void push(int time, int command,char *hashVid, char *channel,char *offset, char *duration) {  
				
 				pid_t pID = fork();

 				if ( pID == 0) { // new, child process
						
						printf("\n On Push() :\t %s %s %s %s \n",hashVid,channel,offset,duration);
						sleep(time);
						//printf("\n End of the sleep \n");
						fired(command,hashVid,channel,offset,duration);
        					}
			       else if(pID<0)
						{
							printf("Fork failed 1\n");
						}
			     }
/*
        05/10/2016
        Fired : check which command is sent, create a fork() and execute the appropriate function for the command
        INPUT : Command to be executed , name or location of the video, Name of Channel
        OUTPUT : NULL
*/

void fired(int command, char *hashVid,char *channel, char *offset, char *duration) {
	
	switch(command) {

			case startFilm:
                                        printf("\n Start of Video on Channel");
					tempID = getpid(); //FFMPEG Process PID stored
					//playVid("a"); //TEST
					playVid(hashVid,channel,offset,duration);
                                        exit(0);

			case endFilm:
                                        printf("End of video on Channel");
					if ( tempID > 0 ) {
						//kill(tempID, SIGKILL);
						
						} 
					else {
						printf("Error, No video to kill ");
					}
                                        exit(0);

			case startAdd:
                                        printf("Start of Add on Channel");
                                        exit(0);

			case endAdd:
					printf("End of Add on Channel");
					exit(0);
					
			default: 
			printf("Error Arguments Incorrect");
			exit(-1);	
		}

}

void playVid ( char *hashVid, char *channel,char *offset, char *duration) {
			//Declaration only for testing purposes
			char *cmd;
			printf("\n On PlayVid() :\t %s %s %s %s \n",hashVid,channel,offset,duration);
			cmd = commandBuilder(hashVid,channel,offset,duration);
			printf("\n Da kommand() : %s",cmd);	
			//execl("/usr/bin/ffmpeg",cmd,NULL);
			system(cmd);
			printf("\n PPID :%d ", getpid());
			//printf("%s",commandBuilder("inputTest"));
			
}

/*
	DOC From O.Azil
	26/09/2016
	Every 4* arguments received by the C script are considered as the following (timer,playerCommand,nameOfVideo,nameOfChannel).
	Each i+4 iteration, the arguments are fired back with an ffmpeg streaming command 

*/
int main(int argc, char *argv[]) {
				// char* c_time_string;
				// time_t current_time;	
				int i; 
				//current_time = time(NULL);
    				//c_time_string = ctime(&current_time);
				//printf("Current time is %s **** %d", c_time_string, endAdd);
			  if( argc % 6 == 1 ) {	
				for (i=1; i< argc; i+=6) {
    					int timer = -1;
					int playerCommand = -1;
				        char video[MAX_STRING_LEN];
					char channel[MAX_STRING_LEN];
					char offset[MAX_STRING_LEN];
					char duration[MAX_STRING_LEN];
							
					//char* vidTest = "Vid test";
					//char* channelTest = "Channel test";	
					//printf("\narg%d=%s", i, argv[i]);

					if (isdigit(*argv[i])) {
  							printf("\n Argument String Values : %s,%s %s %s %s %s \n" , argv[i], argv[i+1], argv[i+2],argv[i+3],argv[i+4],argv[i+5] );

							timer = atoi(argv[i]);
    							playerCommand = atoi(argv[i+1]);
								
							strncpy(video, argv[i+2], sizeof(video));
							strncpy(channel, argv[i+3], sizeof(channel));
							strncpy(offset, argv[i+4], sizeof(channel));
							strncpy(duration, argv[i+5], sizeof(channel));
							//printf("-- CHANNEL :  %s -- \n",channel);
							
							//strncpy(S, "Start", 5);
							push(timer,playerCommand,video,channel,offset,duration);
					}
				}
			} 
			else {
				printf("Error : Incorrect Number of arguments. Expecting an even number");
				return -1;
			}
//  else // parent process succeeded forking and now continue running
// {
     
//  }

					return 0;
				}
