
#WORKS ONLY ON *NIX SYSTEMS
#Give the video to encode in parameter

import os
import subprocess as sp
import sys

print 'THE ARG IS ' + sys.argv[1]

''' NOTES FOR A POSSIBLE V2 : FFMPEG_BIN = "ffmpeg" # on Linux ans Mac OS

commandFF = [ FFMPEG_BIN,
            '-i', 'myHolidays.mp4',
            '-f', 'image2pipe',
            '-pix_fmt', 'rgb24',
            '-vcodec', 'rawvideo', '-']

'''

command = 'ffmpeg -loglevel verbose -i'
command2 = '\
        -codec:v libx264 -profile:v high -preset fast -b:v 145k -maxrate 200k -vf scale="-2:234" -codec:a aac -strict -2 -b:a 32k output_file234p.mp4 \
        -codec:v libx264 -profile:v high -preset fast -b:v 730k -maxrate 800k -vf scale="-2:360" -codec:a aac -strict -2 -b:a 64k output_file360p.mp4 \
        -codec:v libx264 -profile:v high -preset fast -b:v 3000k -maxrate 3300k -vf scale="-2:720" -codec:a aac -strict -2 -b:a 96k output_file720p.mp4'        
        
#pipe = sp.Popen(command, stdout = sp.PIPE, bufsize=10**8)
#print 'command : ' +command+sys.argv[1]+command2
os.system(command+' '+sys.argv[1]+command2)
