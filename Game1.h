#ifndef __GAME1_H__
#define __GAME1_H__
/*                         colorled                         */
#define MAX_SCALE_STEP		7

#define PWM_BASE_SYS_PATH       "/sys/class/pwm/pwmchip"

#define PWM_RED_BASE_SYS_PATH	"/sys/class/pwm/pwmchip0/pwm0/"
#define PWM_GREEN_BASE_SYS_PATH	"/sys/class/pwm/pwmchip1/pwm0/"
#define PWM_BLUE_BASE_SYS_PATH	"/sys/class/pwm/pwmchip2/pwm0/"

#define PWM_SHOW	"1"
#define PWM_HIDE	"0"

#define PWM_ENABLE_NAME		"enable"
#define PWM_FREQUENCY_NAME	"period"
#define PWM_DUTYCYCLE_NAME	"duty_cycle"

#define RED_INDEX	0
#define GREEN_INDEX	1
#define BLUE_INDEX	2

#define TRUE	1
#define FALSE	0

#define  PWM_FREQUENCY		100000

#define  MAX_INPUT_VALUE	100
/*                         button                         */
#define  INPUT_DEVICE_LIST	"/dev/input/event"

#define  SYS_PATH	"S: Sysfs="
#define  BUTTON_NAME	"ecube-button"

#define  LINE_FEED	0x0A

#define  MAX_BUFF	200
/*                         buzzer                         */

#define BUZZER_BASE_SYS_PATH	"/sys/bus/platform/devices/peribuzzer."

#define BUZZER_ENABLE_NAME		"enable"
#define BUZZER_FREQUENCY_NAME	"frequency"
/*                         fnd                         */
#define MAX_FND_NUM			6
#define FND_DATA_BUFF_LEN	(MAX_FND_NUM + 2)


typedef struct FNDWriteDataForm_tag 
{
	char	DataNumeric[FND_DATA_BUFF_LEN];
	char	DataDot[FND_DATA_BUFF_LEN];
	char	DataValid[FND_DATA_BUFF_LEN];	
}stFndWriteForm,*pStFndWriteForm;
/*                         textlcd                         */
#define LED_DRIVER_NAME		"/dev/periled"
#define LINE_NUM			2
#define COLUMN_NUM			16	

#define  LINE_BUFF_NUM 	(COLUMN_NUM + 4)  // for dummy 

#define  MODE_CMD	0
#define  MODE_DATA	1

#define  CMD_DISPLAY_MODE		0x10
	#define  BIT_DISPLAY_MODE_CURSOR_DISP	0x01
	#define  BIT_DISPLAY_MODE_CURSOR_BLINK	0x02
	#define  BIT_DISPLAY_MODE_DISP_ENABLE	0x04

#define  CMD_CURSOR_MOVE_MODE	0x11
	#define CURSOR_MOVE_MODE_ENABLE		0x01
	#define CURSOR_MOVE_MODE_RIGHT_DIR	0x02

#define  CMD_CURSOR_MOVE_POSITION	0x12
	#define  CURSOR_MOVE_X_MASK		0x3F
	#define  CURSOR_MOVE_Y_MASK		0xC0
	
#define  CMD_WRITE_STRING			0x20	
	#define CMD_DATA_WRITE_BOTH_LINE	0
	#define CMD_DATA_WRITE_LINE_1		1
	#define CMD_DATA_WRITE_LINE_2		2
	
#define  CMD_TEST_GPIO_HIGH			0x30
#define  CMD_TEST_GPIO_LOW			0x31


typedef struct TextLCD_tag 
{
	unsigned char cmd; //
	unsigned char cmdData;  
	unsigned char reserved[2];
	
	char	TextData[LINE_NUM][LINE_BUFF_NUM];
}stTextLCD,*pStTextLCD;


#endif //__GAME1_H__