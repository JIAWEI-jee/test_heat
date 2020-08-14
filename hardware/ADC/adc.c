#include "adc.h"
#include "delay.h"
#include "flash.h"

void adc_init ( void )
{
	P0M3 = 0x01;		//P03����Ϊģ������
	P0M7 = 0x01;        //P07����Ϊģ������
	P0M2 = 0x01;        //P02����Ϊģ������
	ADCC0 = 0x81;		//��ADCת����Դ			 4VΪ�ڲ��ο���ѹ
	//00 VDD
//											01 �ڲ�4V
//											10 �ڲ�3V
//											11 �ڲ�2V
//1�� �ڲ��ο���ѹѡ��Ϊ 2V ʱ�� VDD ��ѹ����� 2.7V��
//    �ڲ��ο���ѹѡ��Ϊ 3V ʱ�� VDD ��ѹ����� 3.5V��
//    �ڲ��ο���ѹѡ��Ϊ 4V ʱ�� VDD ��ѹ�����4.5V��
//2�� ϵͳ�������ģʽǰ�����齫 ADC �ο���ѹѡ��� VDD�����Խ�һ������ϵͳ���ġ�
	delay_us ( 80 );						//��ʱ20us��ȷ��ADCϵͳ�ȶ�

//	ADCC1 = 0x08;						//ѡ��ADCͨ��8
	ADCC2 = 0x49;;						//ת�����12λ���ݣ������Ҷ��룬ADCʱ��4��Ƶ 4M/4 = 1MHz
}

u16 get_adc_val_P07 ( void )
{
	u16 adc_val = 0;
	ADCC1 = 0x07;						//ѡ��ADCͨ��7
	ADCC0 |= 0x40;					//����ADCת��
	while ( ! ( ADCC0&0x20 ) );			//�ȴ�ADCת������
	ADCC0 &=~ 0x20;					//�����־λ
	adc_val = ADCR;					//��ȡADC��ֵ
//	ADCR = 0;
	return adc_val;
}

u16 get_adc_val_P03 ( void )
{
	u16 adc_val = 0;
	ADCC1 = 0x03;						//ѡ��ADCͨ��0
	ADCC0 |= 0x40;					//����ADCת��
	while ( ! ( ADCC0&0x20 ) );			//�ȴ�ADCת������
	ADCC0 &=~ 0x20;					//�����־λ
	adc_val = ADCR;					//��ȡADC��ֵ
//	ADCR = 0;
	return adc_val;
}

u16 get_adc_val_P02 ( void )
{
	u16 adc_val = 0;
	ADCC1 = 0x02;						//ѡ��ADCͨ��2
	ADCC0 |= 0x40;					//����ADCת��
	while ( ! ( ADCC0&0x20 ) );			//�ȴ�ADCת������
	ADCC0 &=~ 0x20;					//�����־λ
	adc_val = ADCR;					//��ȡADC��ֵ
//	ADCR = 0;
	return adc_val;
}

void get_voltage ( u16* u1_voltage,u16* u3_voltage )
{
	u32 temp = 0;
	u8  i = 0;
	
	for ( i=0; i<5; i++ )
	{
		temp+=get_adc_val_P03();
	}
	temp/=5;
	*u1_voltage = temp*4000/4095;
	
	delay_us ( 20 );
	temp = 0;
	for ( i=0; i<5; i++ )
	{
		temp+=get_adc_val_P07();
	}
	temp/=5;
	*u3_voltage = temp*4000/4095;
	
}

u16 Detection_Input_Voltage(void)
{
   
	u32 tep = 0;
	u8 i = 0;

	for ( i = 0; i < 5; i++ )
	{
		tep += get_adc_val_P02();
	}
	tep /= 5;
	tep = tep*4000/4096;	//�Ŵ�1000�� ����С�������λ 4096

	return tep;
}

//u16 get_voltage_val ( void )
//{
//	u32 tep = 0;
//	u8 i = 0;
//
//	for ( i = 0; i < 5; i++ )
//	{
//		tep += get_adc_val();
//	}
//	tep /= 5;
//	tep = tep*4000/4096;	//�Ŵ�1000�� ����С�������λ 4096
//	return tep;
//}




