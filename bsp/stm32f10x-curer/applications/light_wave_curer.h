/*
 * File      : application.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2013-07-12     aozima       update for auto initial.
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#ifndef LIGHT_WAVE_CURER_H__
#define LIGHT_WAVE_CURER_H__

#include <rtthread.h>
#include <stdint.h>
#include <drivers/lcdht1621b.h>

#define LWC_ACTIVED                         1
#define LWC_INACTIVE                        0

/* The pin NO. on the chip*/
#define PD2_BEEP                        54 
#define PB1_LASER_DRV                   27
#define PB5_IONTHERAPY_SW               57
#define PB12_IONTHERAPY_PWR             33
#define PB13_IONTHERAPY_CRL1            34
#define PB14_IONTHERAPY_CRL2            35
#define PB15_IONTHERAPY_DECT            36

/* the registered device */
#define BUTTON                          "button"
#define LCD                             "lcdht"
#define TIMER3                          "timer3"
#define TIMER4                          "timer4"
#define XTP                             "xtp"


/* define the button value */
#define BUTTON_RL                       0x11
#define BUTTON_DY_DS                    0x12
#define BUTTON_ZL1_INC                  0x14
#define BUTTON_ZL2_INC                  0x18
#define BUTTON_JG                       0x22
#define BUTTON_SD                       0x24
#define BUTTON_LZLF                     0x28
#define BUTTON_JY                       0x31
#define BUTTON_GN                       0x32
#define BUTTON_ZL1_DEC                  0x34
#define BUTTON_ZL2_DEC                  0x38

#define TMR_DELAY_100ms                 100
#define TMR_DELAY_200ms                 200
#define TMR_DELAY_250ms                 250
#define TMR_DELAY_300ms                 300
#define TMR_DELAY_500ms                 500
#define TMR_DELAY_600ms                 600
#define TMR_DELAY_900ms                 900

/* define cure mode */
enum cure_mod
{
    SET_TIMER  = 0x00,  /* ��ʱ */
    LASER_CURE,         /* �������� */
    HEAT_CURE,          /* ���� */
    IONICE_CURE,        /* �����Ʒ� */
    FUNCTION            /* ���� */  
};

enum func_mod
{
    FULL_FUNCTION = 1,   /* ȫ���� */
    MID_FREQUENCY,          /* ��Ƶ */
    ACUPUNCTURE_NEEDLE,     /* ��� */
    PAT_CURE,               /* �Ĵ� */
    NAPRAPATHY,             /* ���� */
    MASSOTHERAPY,           /* ��Ħ */
    CUPPING_THERAPY,        /* �ι� */
    PEDICURE,               /* ���� */
    LOSE_WEIGHT,            /* ���� */
    VOICE_FREQUENCY         /* ��Ƶ */
};


typedef struct lwc_button
{
    uint8_t button_rl; /* ���� */
    uint8_t button_dyds;/* ��Դ��ʱ */   
    uint8_t button_jg;/* ���� */
    uint8_t button_sd;/* ���� */
    uint8_t button_lzlf;/* �����Ʒ� */
    uint8_t button_jy/* ���� */;
    uint8_t button_gn;/*����*/
    uint8_t button_zl1;/* ����1 */
    uint8_t button_zl2;/* ����2 */
   
}lwc_button_t;

typedef struct timer_val
{
    uint8_t tmr_value;
    uint8_t lcd_hbyte;
    uint8_t lcd_lbyte;   
}timer_val_t;

typedef struct lwc_cure_way
{
    uint8_t status;     /* ����״̬ */      
}lwc_cure_way_t;    

typedef struct lwc_cure_force
{
    uint8_t force;      /* ����ǿ�� */
    uint8_t func;           /* ���ܴ��� */
}lwc_cure_force_t;  

typedef struct lwc_data_reg
{   
    lwc_button_t btn;       /* �������� */
    uint8_t    power_ok;    /* ϵͳ�ϵ���*/
    timer_val_t tval;       /* ��ʱ���� */   
}lwc_data_reg_t;

typedef struct lwc_cure_display   
{   
    lwc_data_reg_t lreg;
    lwc_cure_way_t lway[5];     /* ���Ʒ�ʽ */    
    rt_lcd_ramdat_t lcdr[20];   /* ����20����λ */
}lwc_cure_display_t;

typedef struct lwc_cure_control  
{   
    lwc_data_reg_t lreg;
    lwc_cure_way_t lway[5];     /* �������Ʒ�ʽ����ʱ������ */    
    lwc_cure_force_t lcf[4];    /* ����·���*/
}lwc_cure_output_t;


extern struct rt_mailbox mb;
extern char mb_pool[128];

extern lwc_cure_display_t lcd;
extern lwc_cure_output_t lco;

extern rt_uint8_t lwc_button_stack[ 1024 ];
extern struct rt_thread lwc_button_thread;
extern rt_uint8_t lwc_display_stack[ 1024 ];
extern struct rt_thread lwc_display_thread;
extern rt_uint8_t lwc_output_stack[ 1024 ];
extern struct rt_thread lwc_output_thread;

extern void lwc_button_thread_entry(void* parameter);
extern void lwc_display_thread_entry(void* parameter);
extern void lwc_output_thread_entry(void* parameter);

//rt_err_t seglcd_display_time(rt_device_t dev, lwc_cure_t *lc);


#endif

/*@}*/