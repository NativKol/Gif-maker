/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/

#define CV_IGNORE_DEBUG_BUILD_GUARD
#define FIRSTTIME 0
#define NOTFIRSTTIME 1

#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "LINKEDLISTH.h"

int main(void)
{ 
	int choice = 0, count = 0;
	FrameNode* movie = NULL;
	FrameNode* head = NULL;
	startAction(0, FIRSTTIME);
	//infinity loop while not exit
	do
	{
		showMenu();
		scanf("%d", &choice);		//get choice
		getchar();
		startAction(choice, NOTFIRSTTIME);
	} while (choice != 0);
	
	return 0;
}