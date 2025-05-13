#ifndef _GLOBALS_H 
#define _GLOBALS_H

//--------------------------------------------------------------------
// Include Files
#include "lrun.h"
#include "web_api.h"
#include "lrw_custom_body.h"

//--------------------------------------------------------------------
// Global Variables

int givuser_id=0;  int scid; char *vuser_group;
int time_diff;
double  trans_duration;


int targetedIterationsPerUserPerHour=0; //Iterations per hour per hour
double actualIterationDuration; //Measure vUser ieration duration with lr_start_timer and lr_end_timer
double actualWaitDuration;

//double timecal, pacing;
merc_timer_handle_t timer;

char xURL[100] = "home.ce-perf-a.dsbu.cloud";
 
#endif // _GLOBALS_H
