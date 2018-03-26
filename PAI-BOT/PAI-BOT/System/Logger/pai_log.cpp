//
//  pai_log.cpp
//  PAI-BOT
//
//  Created by Tamir Fridman on 26/03/2018.
//  Copyright © 2018 PAI Technologies. All rights reserved.
//

#include "pai_log.hpp"


#include <sys/time.h>
#include <time.h>
#include <math.h>

#define LOG_DATE_TIME_FORMAT  "%M:%S" // full = "%Y:%m:%d %H:%M:%S"
#define PAI_LOG_TO_CONSOLE 1

struct timeval last_op;


long timevaldiff(struct timeval *starttime, struct timeval *finishtime)
{
    long msec;
    msec=(finishtime->tv_sec-starttime->tv_sec)*1000;
    msec+=(finishtime->tv_usec-starttime->tv_usec)/1000;
    return msec;
}

void pai_log (const char msg[1000])
{
#if PAI_LOG_TO_CONSOLE
    printf ("π:] %s \n", msg);
#endif
}

//log to screen with time difference
void pai_log(const char msg[1000],bool display_diff)
{
#if PAI_LOG_TO_CONSOLE
    
    char buffer[26];
    long millisec;
    struct tm* tm_info;
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec>=1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }
    
    tm_info = localtime(&tv.tv_sec);
    
    strftime(buffer, 26, LOG_DATE_TIME_FORMAT, tm_info);
    
    if(display_diff)
    {
        long diff =  timevaldiff(&last_op, &tv);
        printf ("π:] [%s.%03ld +%04ld] %s  \n", buffer,millisec,diff,msg);
        
    }
    else
    {
        printf ("π:] [%s.%03ld] %s  \n", buffer,millisec,msg);
    }
    
    last_op = tv;
#endif
}
