#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define LEN 50

// Frame struct
typedef struct Frame
{
	char name[LEN];			
	unsigned int duration;	
	char path[LEN];
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

//functions
void showMenu();
void startAction(int num, int first);
void myFgets(char str[], int length);
Frame* input(FrameNode* copy);
void getData(FrameNode** head, char* path);
int checkValid(char file[], int dur, char name[], FrameNode* head);
int checkInput(char name[], FrameNode* head, int move, int count);
Frame* createFrame(char file[], int dur, char name[]);
//actions
void append(FrameNode** head_ref, Frame* new_data);
int deleteFrame(FrameNode** head, char name[]);
void changeFrameIndex(FrameNode** head, char name[], int move);
int changeDuration(FrameNode** head, char name[], int dur);
void changeAllDurations(FrameNode** head, int dur);
void printList(FrameNode* head);
void saveList(FrameNode* head);
#endif