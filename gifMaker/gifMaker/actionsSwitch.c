#include "LINKEDLISTH.h"		//the headers file
#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include <string.h>

#define LEN 100
#define FALSE 0
#define TRUE 1

//INITIALIZE
FrameNode* movie = NULL;
FrameNode* copy = NULL;
FrameNode* head = NULL;
int count = 0;

//scan the strings
void myFgets(char str[], int length)
{
	fgets(str, length, stdin);
	str[strcspn(str, "\n")] = 0;
}

//print the menu of the actions
void showMenu()
{
	printf("What would you like to do?\n ");
	printf(" [0] Exit\n ");
	printf(" [1] Add new Frame\n ");
	printf(" [2] Remove a Frame\n ");
	printf(" [3] Change frame index\n ");
	printf(" [4] Change frame duration\n ");
	printf(" [5] Change duration of all frames\n ");
	printf(" [6] List frames\n ");
	printf(" [7] Play movie\n ");
	printf(" [8] Save project\n ");
}

int startMenu()
{
	int num = 0;
	do
	{
		printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
		printf(" [0] Create a new project\n");
		printf(" [1] Load existing project\n");
		scanf("%d", &num);
		getchar();
	} while (num != 0 && num != 1);
	
	return num;
}

//start the action that the usr chose
void startAction(int num, int first)
{
	Frame* pic = NULL;
	char name[LEN] = { 0 };
	int move = 0, duration = 0;
	int valid = FALSE;
	int choice = 3;
	char path[LEN] = { 0 };
	char line[LEN];
	char ch = ' ';
	FILE* saved = NULL;
	int i = 0, lines = 0, j = 0;

	if (first == 0)
	{
		choice = startMenu();			//get the choice of the user
	}
	
	if (choice == 0)
	{
		printf("Create new project...\n");
		return;
	}
	else if (choice == 1)
	{
		printf("Enter the path of the project (including project name): ");		//E:\gifmaker\projects\project2.txt
		myFgets(path, LEN);		//scan the string 	
		
		getData(&copy, path);
		return;
	}

	switch (num)
	{
	case 0:					//exit
		printf("Bye!\n");
		break;
	case 1:
		//printf("the count: %d\n", *count);
		printf("*** Creating new frame ***\n");
		count += 1;
		printf("count: %d\n", count);
		while (pic == NULL)
		{
			pic = input(copy);
		}
		append(&copy, pic);
		break;
	case 2:
		printf("Enter the name of the frame you wish to earse\n");
		myFgets(name, LEN);
		deleteFrame(&copy, name);
		count -= 1;
		break;
	case 3:
		do {	//thake the input until its valid
			printf("Enter the name of the frame \n");
			myFgets(name, LEN);
			printf("Enter the new index in the movie you wish to place the frame\n");
			scanf("%d", &move);
			getchar();
			valid = checkInput(name, copy, move, count);
		} while ((valid == FALSE));
		changeFrameIndex(&copy, name, move);
		break;
	case 4:
		printf("Enter the name of the frame you want to change his duration\n");
		myFgets(name, LEN);
		printf("Enter the duration for the frames\n");
		scanf("%d", &duration);
		getchar();
		changeDuration(&copy, name, duration);
		break;
	case 5:
		printf("Enter the duration for the frames\n");
		scanf("%d", &duration);
		getchar();
		changeAllDurations(&copy, duration);
		break;
	case 6:
		printList(copy);
		break;
	case 7:
		play(copy);
		break;
	case 8:
		saveList(copy);
		break;
	default:		//not valid choice
		printf("You must choose number between 0-8!\n ");
		break;
	}
}