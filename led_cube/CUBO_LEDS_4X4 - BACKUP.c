#include "C:\Users\GHJ\Google Drive\Univali\2015-1\Microcontroladores\C_Projects\TrabalhoFA\CUBO_LEDS_4X4.h"

#define level_0_Enable 0b00000001
#define level_1_Enable 0b00000010
#define level_2_Enable 0b00000100
#define level_3_Enable 0b00001000


int cubeLevelC0, cubeLevelC1, cubeLevelC2, cubeLevelC3;
int cubeLevelD0, cubeLevelD1, cubeLevelD2, cubeLevelD3;
int levelEnable = 0;

#int_RTCC
void  RTCC_isr(void) {
   
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
     
}

#int_EXT
void  EXT_isr(void) 
{

}

#int_EXT1
void  EXT1_isr(void) 
{

}



void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16|RTCC_8_bit);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(GLOBAL);
   
   set_tris_a (0b11110000);
   set_tris_b (0b00000000);
   set_tris_c (0b00000000);
   
   cubeLevelC0 = 0xFF;
   cubeLevelC1 = 0x00;
   cubeLevelC2 = 0xFF;
   cubeLevelC3 = 0x00;
   
   cubeLevelD0 = 0x00;
   cubeLevelD1 = 0xFF;
   cubeLevelD2 = 0x00;
   cubeLevelD3 = 0xFF;

}