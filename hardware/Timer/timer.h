#ifndef __TIMER_H__
#define __TIMER_H__
#include "HC89F3541.H"

#define overrang_time   (60*60*4)
#define Heat_Value      (30*9)         // (60*6)

#define Length          7
#define Temperature_Value         97.84
#define cail_value               (60*2*500)
#define LED_ON_TIME        1500



typedef struct led_info
{
	u8 led_std;
	u16 led_time_cnt;
} led_info;

extern u8 over_rang_time_std;
extern u8 Gap_protect_std;
extern u8 On_stay;
extern u8 Heat_start_std;
extern u8  Open_Heat_Value;
extern u8  heat_step;
void time0_init(void);
void set_time_sec_val(u16 sec);
void set_time_sec(void);
void led_set_on(void);
void led_set_off(void);
#endif

