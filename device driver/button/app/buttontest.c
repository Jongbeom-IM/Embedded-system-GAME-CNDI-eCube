#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>

// first read input device
#define  INPUT_DEVICE_LIST	"/dev/input/event"

#define  SYS_PATH	"S: Sysfs="
#define  BUTTON_NAME	"ecube-button"

#define  LINE_FEED	0x0A

#define  MAX_BUFF	200
int main(int argc, char *argv[])
{
	int    fp;

	char 	inputfileName[MAX_BUFF+1];

	int		readSize,inputIndex;
	struct input_event  stEvent;

	if (argc != 2)
	{
		printf("Usage : buttontest  <input Number>\n");
		printf("       Firstly read the '/proc/bus/input/devices' file to check <input Number> \n");
		printf("       >cat /proc/bus/input/devices\n");
		
		return 1;
	}
	inputIndex = atoi(argv[1]);

	sprintf(inputfileName,"%s%d",INPUT_DEVICE_LIST,inputIndex);
	printf("read button event:%s\n",inputfileName);
	fp = open(inputfileName, O_RDONLY);
	
	if ( -1 == fp )
	{
		printf("%s file read error.\n",inputfileName);
		return 1;
	}
	while(1)
	{
		readSize = read(fp, &stEvent , sizeof(stEvent));
		if (readSize != sizeof(stEvent))
		{
			continue;
		}
//		printf("type:%d, code:%d, value:%d\n", stEvent.type, stEvent.code, stEvent.value);
		if ( stEvent.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP:
				printf("Volume up key):");
				break;
				case KEY_HOME:
				printf("Home key):");
				break;
				case KEY_SEARCH:
				printf("Search key):");
				break;
				case KEY_BACK:
				printf("Back key):");
				break;
				case KEY_MENU:
				printf("Menu key):");
				break;
				case KEY_VOLUMEDOWN:
				printf("Volume down key):");
				break;
			}
			if ( stEvent.value )
			{
				printf("pressed\n");
			}
			else
			{
				printf("released\n");
			}
		}
		else // EV_SYN
		{
			// do notthing
		}
	}
	close(fp);		
}
