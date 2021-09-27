#include "LINKEDLISTH.h"		//the headers file
#include <stdio.h>
#include "view.h"
#include <string.h>

#define LEN 50
#define FALSE 0
#define TRUE 1


// take input and make frames 
Frame* input(FrameNode* copy)
{
	char path[LEN] = { 0 };			//		E:\gifMaker\photos\img1.jpeg
	int duration = 0;
	char name[LEN] = { 0 };
	Frame* first = NULL;
	int valid = 0;
	printf("Please insert frame path:\n");
	myFgets(path, LEN);		//scan string
	printf("Please insert frame duration(in miliseconds):\n");
	scanf("%d", &duration);
	getchar();
	printf("Please choose a name for that frame:\n");
	myFgets(name, LEN);
	valid = checkValid(path, duration, name, copy);		//check if the input is valid
	if (valid == FALSE)
	{
		return NULL;
	}
	first = createFrame(path, duration, name);		//create the frame with the data
	return first;
}


//take the file and make linked list with the data
void getData(FrameNode** head, char* filePath)
{
	char path[LEN] = { 0 };			
	int duration = 0;
	char name[LEN] = { 0 };
	FILE* openFile = fopen(filePath, "r");
	Frame* first = NULL;

	if (openFile == NULL)
	{
		printf("error with file!\n");
		return 1;
	}

	while (fscanf(openFile, "r") != EOF)		//going throught lines and puts in frame
	{
		fscanf(openFile, "%s\n", name);		
		fscanf(openFile, "%d\n", &duration);
		fscanf(openFile, "%s\n", path);

		first = createFrame(path, duration, name);		//create one frame
		append(head, first);							//add to the movie
	}
}


//check if the name and the file are valid
int checkValid(char file[], int dur, char name[], FrameNode* head)
{
	FrameNode* curr = head;
	FILE* check = NULL;
	//if the name exist
	while (curr != NULL)
	{
		if (strcmp(name, curr->frame->name) == 0)
		{
			printf("This frame name is already exist!\n");
			return FALSE;
		}
		curr = curr->next;
	}
	//if the file path valid
	check = fopen(file, "r");
	if (check == NULL)
	{
		printf("This file path is not exist!\n");
		return FALSE;
	}
	return TRUE;
}

//check the input in option 3
int checkInput(char name[], FrameNode* head, int move, int count)
{
	FrameNode* curr = head;
	//check if the location is valid
	if (move < 1 || move > count)
	{
		printf("This location not exist!\n");
		return FALSE;
	}

	//check if the name is exist
	while (curr != NULL)
	{
		if (strcmp(name, curr->frame->name) == 0)
		{
			return TRUE;
		}
		curr = curr->next;
	}
	printf("This frame name is not exist!\n");
	return FALSE;
}


// craete the frame by the data
Frame* createFrame(char file[], int dur, char name[])
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));
	
	strncpy(newFrame->path, file, LEN);
	newFrame->path[strcspn(newFrame->path, "\n")] = 0;
	newFrame->duration = dur;
	strncpy(newFrame->name, name, LEN);
	newFrame->name[strcspn(newFrame->name, "\n")] = 0;

	
	return newFrame;
}

/*
THE ACTIONS LIST (not includes 7)
*/

//add the FrameNode (1)
void append(FrameNode** head_ref, Frame* new_data)
{
	FrameNode* new_node = (FrameNode*)malloc(sizeof(FrameNode));
	FrameNode* last = *head_ref;  

	//put in the data  
	new_node->frame = new_data;
	new_node->next = NULL;

	//If the Linked List is empty, then make the new node as head 
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	// Else traverse till the last node 
	while (last->next != NULL)
	{
		last = last->next;
	}

	// Change the next of last node 
	last->next = new_node;
	return;
}

//delete frame by name (2)
int deleteFrame(FrameNode** head, char name[])
{
	FrameNode* curr = *head;
	FrameNode* temp = NULL;

	//if that the first 
	if (curr != NULL && strcmp(name, curr->frame->name) == 0)
	{
		*head = (*head)->next;		//reconnect
		free(curr);					//free data
		return TRUE;
	}
	else
	{
		//going through all of the names 
		while (curr && curr->next != NULL)
		{
			if (!strcmp(curr->next->frame->name, name))
			{
				temp = curr->next;
				curr->next = temp->next;
				free(temp);
				curr = NULL;
				return TRUE;
			}
			else
			{
				curr = curr->next;		//reconnect
			}
		}
	}
	printf("The file is not exist!\n");
	return FALSE;

}

//change the location of the file by file name and location (3)
void changeFrameIndex(FrameNode** head, char name[], int move)
{
	FrameNode* copy = NULL;
	FrameNode* curr = NULL;	
	FrameNode* prev = NULL;
	FrameNode* moveNodeIndex = NULL;
	FrameNode* moveNode = NULL;
	FrameNode* realHead = *head;
	FrameNode* temp = NULL;
	curr = *head;
	copy = *head;
	int counter = 1;
	// check the location of the name
	while (curr != NULL && strcmp(curr->frame->name, name))
	{
		counter++;
		prev = curr;
		curr = curr->next;
	}
	moveNodeIndex = counter;	//final location
	moveNode = curr;			//current location

	// if the current and the last lists are null
	if (curr != NULL)
	{
		if (prev != NULL)
		{
			prev->next = moveNode->next;		// one backwords  ( 1 2 3 --> 2 3)
		}
		else
		{
			*head = realHead->next;				// continue foraword (1. 2 3 --> 1 2. 3)
			realHead = *head;	
		}

		curr = *head;
		counter = 1;

		if (move == 1)		//move to first item
		{
			moveNode->next = realHead;
			*head = moveNode;
		}
		else
		{
			while (curr != NULL && counter < move - 1)  //continue until the list ends or you reached the transform
			{
				counter++;
				curr = curr->next;
			}
			//swap
			temp = curr->next;
			curr->next = moveNode;
			moveNode->next = temp;
		}
	}
}

//change duration by name (4)
int changeDuration(FrameNode** head, char name[], int dur)
{
	FrameNode* curr = *head;
	//going through all of the names 
	while (curr != NULL)
	{
		if (strcmp(name, curr->frame->name) == 0)	
		{
			curr->frame->duration = dur;
			return TRUE;
		}
		else
		{
			curr = curr->next;
		}
	}
	
	printf("The file is not exist!\n");
	free(curr);
	return FALSE;
}

//change all durations (5)
void changeAllDurations(FrameNode** head, int dur)
{
	FrameNode* curr = *head;
	//going through all of the frames
	while (curr != NULL)
	{
		curr->frame->duration = dur;
		curr = curr->next;
	}
}


//print the all list (6)
void printList(FrameNode* head)
{
	printf("PRINT LIST:\n");
	FrameNode* curr = head;
	printf("\tName\tDuration    Path \n");
	while (curr != NULL)
	{
		printf("\t%s\t%d ms       %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
}

//option 7 in the file view.c

//save the project (8)
void saveList(FrameNode* head)
{
	char file[LEN] = { 0 };
	FILE* save = NULL;
	printf("Where to save the project? enter a full path and file name\n");
	myFgets(file, LEN);		// scan the string
	save = fopen(file, "w+");		// open text file for saving the project
	FrameNode* curr = head;

	while (curr != NULL)
	{
		fprintf(save, "%s\t%d       %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	fclose(save);		//close file 
}
