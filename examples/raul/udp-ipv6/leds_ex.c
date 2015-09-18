//
// Created by raulsuarez on 11/09/15.
//

#include "leds_ex.h"
#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ip/resolv.h"

#include <string.h>
#include <stdbool.h>

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"
#include "reg.h"
#include "dev/leds.h"
//#include "dev/gpio.h"


#include "sys/clock.h"
#include "sys/energest.h"

#define SEND_INTERVAL		15 * CLOCK_SECOND
#define MAX_PAYLOAD_LEN		40

#define LEDS_GPIO_PIN_MASK   LEDS_ALL

//static uint8_t blinks;
//static uint8_t i;
static unsigned char leds;
unsigned char ledStatus;
unsigned char portStatus;
/*---------------------------------------------------------------------------*/
static void
fade(unsigned char l)
{
   volatile int i;
   int k, j;
   for(k = 0; k < 800; ++k) {
      j = k > 400 ? 800 - k : k;

      leds_on(l);
      for(i = 0; i < j; ++i) {
         asm("nop");
      }
      leds_off(l);
      for(i = 0; i < 400 - j; ++i) {
         asm("nop");
      }
   }
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PROCESS(leds_ex, "LEDS EX PROCESS");
AUTOSTART_PROCESSES(&leds_ex);
/*---------------------------------------------------------------------------*/


PROCESS_THREAD(leds_ex, ev, data)
{

   PROCESS_BEGIN();
   PRINTF("LEDS EX PROCESS process started\n");

//   leds_on(LEDS_ORANGE);

//   GPIO_SET_OUTPUT(GPIO_C_BASE, LEDS_GPIO_PIN_MASK);
//   GPIO_READ_PIN(GPIO_C_BASE, LEDS_GPIO_PIN_MASK);
//   GPIO_WRITE_PIN(GPIO_C_BASE, LEDS_GPIO_PIN_MASK, 0x01);
//   GPIO_WRITE_PIN(GPIO_B_BASE, 0x02, 1);// SET PB1 TO 1

   /*GPIO_SET_OUTPUT(GPIO_D_BASE, 0x0C);//PD2 to output
   GPIO_CLR_PIN(GPIO_D_BASE, 0x0C);
   portStatus = GPIO_READ_PIN(GPIO_D_BASE, 0x0C);
   printf("portStatus1: %u\n", portStatus);*/
   fade(LEDS_YELLOW);


//   ledStatus=leds_get();
//   printf("ledStatus: %u\n", ledStatus);


   /*GPIO_SET_PIN(GPIO_D_BASE, 0x0C);
   portStatus = GPIO_READ_PIN(GPIO_D_BASE, 0x0C);
   printf("portStatus2: %u\n", portStatus);*/





   while(1){

//      clock_delay_usec(0xFFFF);
//      printf("test1\n");
//      clock_delay_usec(0xFFFF);
//      printf("test2\n");
//      clock_delay_usec(0xFFFF);
//      printf("test3\n");
//      clock_delay_usec(0xFFFF);
//      printf("test4\n");
//      clock_delay_usec(0xFFFF);


//      leds_toggle(LEDS_ALL);
   }

   PROCESS_END();
}
/*---------------------------------------------------------------------------*/