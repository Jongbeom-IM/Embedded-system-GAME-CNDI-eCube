#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>

#define INPUT_DEVICE_LIST "/dev/input/event"
#define  SYS_PATH	"S: Sysfs="
#define  BUTTON_NAME	"ecube-button"
#define  LINE_FEED	0x0A
#define  MAX_BUFF	200


pthread_t tid;
pthread_mutex_t lock;
int round_num, status,Timer_stat;
int LED_SET[20];

void Setfnd(int num){
    char str[40];
    sprintf(str,"./fndtest c %d",num);
    system(str);
}

void textLCD(int line, char* str){
    char Str_input[40];
    sprintf(Str_input,"./textlcdtest %d '%s'",line,str);
    system(Str_input);
}

void rand_Set(int round_num){
    int i, rand_num;
    for(i=0; i<=round_num; i++){
        rand_num=rand();
        LED_SET[i]=rand_num-(rand_num/6)+1;
    }
}

void SetLED(int round_num){
    int ledpoint, i;
    float _delay;
    char str[40];
    rand_Set(round_num);
    _delay = (round_num<3)? 0.5 :
              (round_num<5)? 0.4 : 0.3;
    system("./ledtest 0xC0");
    sleep(0.3);
    system("./ledtest 0x00");
    sleep(0.5);
    system("./ledtest 0xC0");
    Setfnd(500);
    system("./lestest 0x00");
    sleep(0.5);
    for(i=0; i<=round_num; i++){
        ledpoint = 0b00000000&(1<<LED_SET[i]);
        sprintf(str,"./ledtest %d",ledpoint);
        system(str);
        sleep(_delay);
    }
}

void* Timer(void *arg){
    sleep(5);
    if(status==0) {
        pthread_mutex_lock(&lock);
        round_num=1;
        pthread_mutex_unlock(&lock);
        status=0;
        Timer_stat=0;
    }
    else{
        Timer_stat=1;
        status=0;
    }
    return NULL;
}

int Comp(int BUTTON_INPUT[round_num],int LED_SET[round_num]){
    int count, i;
    count=0;
    for(i=0; i<=round_num; i++){
        if(BUTTON_INPUT[i]==LED_SET[i]) count ++;
    }
    if(count==round_num) return 1;
    else return 0;
}

int main(int argc, char*argv[]){
    int BUTTON_INPUT[20];
    Timer_stat=1;
    round_num=1;
    int    fp, key_set, i;
	char 	inputfileName[MAX_BUFF+1];
	int		readSize,inputIndex;
	struct input_event  stEvent;

    sprintf(inputfileName,"%s%d",INPUT_DEVICE_LIST,inputIndex);
	fp = open(inputfileName, O_RDONLY);
    while(1){
        key_set =0;
        SetLED(round_num);
        Setfnd(300);
        pthread_create(&tid,NULL,&Timer,NULL);
        while(key_set<=round_num && Timer_stat==1){
            key_set++;
            readSize = read(fp, &stEvent , sizeof(stEvent));
            if (readSize != sizeof(stEvent)){
                continue;
            }
            if (stEvent.type == EV_KEY){
                switch(stEvent.code){
                    case KEY_HOME:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 1;
                    break;
                    case KEY_SEARCH:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 2;
                    break;
                    case KEY_BACK:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 3;
                    break;
                    case KEY_MENU:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 4;
                    break;
                    case KEY_VOLUMEUP:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 5;
                    break;
                    case KEY_VOLUMEDOWN:
                    for(i=key_set; i>0; i--){
                        BUTTON_INPUT[i]=BUTTON_INPUT[i-1];
                    }
                    BUTTON_INPUT[0] = 6;
                    break;
                }
            }
            else{}
        }
        pthread_join(tid,NULL);
        if(Comp(BUTTON_INPUT,LED_SET)){
            status=1;
            char roundMSG[10];
            textLCD(2,"CONGRATUATION!");
            sleep(0.5);
            textLCD(2,"NEXT LEVEL");
            round_num ++;
            sprintf(roundMSG,"ROUND : %d",round_num);
            textLCD(1,roundMSG);
        }
        else{
            char roundMSG[10];
            textLCD(2,"BOOM...");
            sleep(0.5);
            textLCD(2,"get back to round 1...");
            round_num=1;
            sprintf(roundMSG,"ROUND : %d",round_num);
            textLCD(1,roundMSG);
        }
    }
	close(fp);		
    return 0;
}