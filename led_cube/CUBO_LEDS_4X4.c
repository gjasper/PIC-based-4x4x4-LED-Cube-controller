#include "C:\Users\GHJ\Google Drive\Univali\2015-1\Microcontroladores\C_Projects\TrabalhoFA\CUBO_LEDS_4X4.h"
#include <STDLIB.H>

#define level_0_Enable 0b00000001
#define level_1_Enable 0b00000010
#define level_2_Enable 0b00000100
#define level_3_Enable 0b00001000

//To 4MHz PRESCALER 8 

#define timer1_2_hz_Speed  3036
#define timer1_4_hz_Speed  34286
#define timer1_6_hz_Speed  44702
#define timer1_8_hz_Speed  49911
#define timer1_10_hz_Speed 53036


int cubeLevelC0, cubeLevelC1, cubeLevelC2, cubeLevelC3;
int cubeLevelD0, cubeLevelD1, cubeLevelD2, cubeLevelD3;
int levelEnable = 0;


int Mode1_CubeLevelC0[4] = {0b11111111,0b00000000,0b00000000,0b00000000}, 
	Mode1_CubeLevelC1[4] = {0b00000000,0b11111111,0b00000000,0b00000000}, 
	Mode1_CubeLevelC2[4] = {0b00000000,0b00000000,0b11111111,0b00000000}, 
	Mode1_CubeLevelC3[4] = {0b00000000,0b00000000,0b00000000,0b11111111},
    Mode1_CubeLevelD0[4] = {0b11111111,0b00000000,0b00000000,0b00000000}, 
	Mode1_CubeLevelD1[4] = {0b00000000,0b11111111,0b00000000,0b00000000}, 
	Mode1_CubeLevelD2[4] = {0b00000000,0b00000000,0b11111111,0b00000000}, 
	Mode1_CubeLevelD3[4] = {0b00000000,0b00000000,0b00000000,0b11111111};
	
	
int Mode2_CubeLevelC0[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelC1[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelC2[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelC3[4] = {0b00010001,0b00100010,0b01000100,0b10001000},
    Mode2_CubeLevelD0[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelD1[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelD2[4] = {0b00010001,0b00100010,0b01000100,0b10001000}, 
	Mode2_CubeLevelD3[4] = {0b00010001,0b00100010,0b01000100,0b10001000};
	

int speedControl = 0;
int stateControl = 0;
int modeControl = 0;

unsigned int16 timer1StartValue = 0;

#int_RTCC
void  RTCC_isr(void) {

	//output_toggle(PIN_B6);

   
   switch(levelEnable){
      case 0:output_a(level_0_Enable);
          output_c(cubeLevelC0);
             output_d(cubeLevelD0); 
      break;
      case 1:output_a(level_1_Enable);
          output_c(cubeLevelC1);
             output_d(cubeLevelD1);
      break;
      case 2:output_a(level_2_Enable);
          output_c(cubeLevelC2);
             output_d(cubeLevelD2);
      break;
      case 3:output_a(level_3_Enable);
          output_c(cubeLevelC3);
             output_d(cubeLevelD3);
      break;
   }
   
   if (levelEnable == 3){
      levelEnable = 0;
   }else{
       levelEnable++;
   }
   
   output_toggle(PIN_B6);
}

#int_TIMER1
void  TIMER1_isr(void) 
{   
	set_timer1(timer1StartValue);
	//output_toggle(PIN_B7);

	
	
	if(stateControl < 3){
		stateControl++;
	}else{
		stateControl = 0;
	}
	
	
	switch (modeControl){
		case 0:
			cubeLevelC0 = Mode1_CubeLevelC0[stateControl];
			cubeLevelC1 = Mode1_CubeLevelC1[stateControl];
			cubeLevelC2 = Mode1_CubeLevelC2[stateControl];
			cubeLevelC3 = Mode1_CubeLevelC3[stateControl];
			cubeLevelD0 = Mode1_CubeLevelD0[stateControl];
			cubeLevelD1 = Mode1_CubeLevelD1[stateControl];
			cubeLevelD2 = Mode1_CubeLevelD2[stateControl];
			cubeLevelD3 = Mode1_CubeLevelD3[stateControl];

		break;
		
		case 1:
			cubeLevelC0 = Mode2_CubeLevelC0[stateControl];
			cubeLevelC1 = Mode2_CubeLevelC1[stateControl];
			cubeLevelC2 = Mode2_CubeLevelC2[stateControl];
			cubeLevelC3 = Mode2_CubeLevelC3[stateControl];
			cubeLevelD0 = Mode2_CubeLevelD0[stateControl];
			cubeLevelD1 = Mode2_CubeLevelD1[stateControl];
			cubeLevelD2 = Mode2_CubeLevelD2[stateControl];
			cubeLevelD3 = Mode2_CubeLevelD3[stateControl];

		break;
		
		case 2:
			cubeLevelC0 = rand ();
			cubeLevelC1 = rand ();
			cubeLevelC2 = rand ();
			cubeLevelC3 = rand ();
			cubeLevelD0 = rand ();
			cubeLevelD1 = rand ();
			cubeLevelD2 = rand ();
			cubeLevelD3 = rand ();
		break;

	}
	
	output_toggle(PIN_B7);
}


#int_EXT
void  EXT_isr(void) 
{
	if(speedControl < 4){
		speedControl++;
	}else{
		speedControl = 0;
	}
	
	
	switch (speedControl){
		case 0:timer1StartValue = timer1_2_hz_Speed;
		break;                    
		case 1:timer1StartValue = timer1_4_hz_Speed;
		break;                    
		case 2:timer1StartValue = timer1_6_hz_Speed;
		break;                    
		case 3:timer1StartValue = timer1_8_hz_Speed;
		break;                    
	    case 4:timer1StartValue = timer1_10_hz_Speed;
		break;
	}
}

#int_EXT1
void  EXT1_isr(void) 
{
	if(modeControl < 2){
		modeControl++;
	}else{
		modeControl = 0;
	}

}

void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32|RTCC_8_bit);   //RTCC_DIV_32 -> 122 Hz ou 30 Hz por nivel
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(GLOBAL);

   
   set_tris_a (0b11110000);
   set_tris_c (0b00000000);
   set_tris_d (0b00000000);
   
   
   while(1){
	delay_ms(10);
   }

}
