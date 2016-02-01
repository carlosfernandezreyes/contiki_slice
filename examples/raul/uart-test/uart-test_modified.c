/*
 * Copyright (c) 2014, Jelmer Tiete <jelmer@tiete.be>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \addtogroup cc2538
 * @{
 *
 * \defgroup cc2538-examples cc2538 Example Projects
 * @{
 *
 * \defgroup cc2538-uart-demo cc2538 UART Demo Project
 *
 *   Example project demonstrating the cc2538 dual UART functionality
 *
 * @{
 *
 * \file
 *     Example demonstrating the double UART on the cc2538 platform
 */
#include "contiki.h"
#include "sys/etimer.h"
#include "sys/rtimer.h"
#include "dev/leds.h"
#include "dev/uart.h"
#include "dev/cs5490.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL       CLOCK_SECOND
#define LEDS_OFF_HYSTERISIS (RTIMER_SECOND >> 1)
#define LEDS_PERIODIC       LEDS_GREEN
/*---------------------------------------------------------------------------*/
static struct etimer et;//, etimeout;
static struct rtimer rt;
static uint16_t counter;
//static unsigned int ind;
//static unsigned int rdata[3];
//static process_event_t full_msg_in;
/*---------------------------------------------------------------------------*/
PROCESS(cc2538_uart_demo_process, "cc2538 uart demo process");
AUTOSTART_PROCESSES(&cc2538_uart_demo_process);
/*---------------------------------------------------------------------------*/
void
rt_callback(struct rtimer *t, void *ptr)
{
  leds_off(LEDS_PERIODIC);
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(cc2538_uart_demo_process, ev, data)
{
  char string0[25];
  char string1[25];
  int ptoproc;
//  int i;
//  uint8_t MSB=100;
//  uint8_t Medida_MSB[8];

//  byte2str(MSB, Medida_MSB);

  unsigned int addr = 0x323130;
//  unsigned long info = 0x343332;
//  unsigned int instr = 0x00;

  PROCESS_BEGIN();

  counter = 0;

//  uart_set_input(0, uart_rx);
  uart_set_input(0, cs_uart_rx);
  etimer_set(&et, CLOCK_SECOND);

  PRINTF("Before while...");
  while(1) {

    PRINTF("While...");
    PROCESS_YIELD();

    if(ev == PROCESS_EVENT_TIMER) {
      PRINTF("if(ev == PROCESS_EVENT_TIMER)...");
      leds_on(LEDS_PERIODIC);

      sprintf(string0, "Test 0x%02x to UART0\n", counter);
      sprintf(string1, "Test 0x%02x to UART1\n", counter);

      memcpy(string0, "", sizeof(string0));
      memcpy(string0, &addr, sizeof(addr));
//      memcpy(string0, "01234", 5);

//      memcpy(string0+sizeof(addr)-2, &info, sizeof(info));
//      memcpy(string0+sizeof(info)-1, &addr, sizeof(addr));

        printf("string0 to send:%s\n\n", string0);
        PRINTF("string0 to send:%s\n\n", string0);

      cs_uart_send((uint8_t *)string0,sizeof(string0)-1);

      /*uart0_send_bytes((uint8_t *)string0,sizeof(string0)-1);
      uart1_send_bytes((uint8_t *)string1,sizeof(string1)-1);*/


      /*etimer_set(&etimeout, CLOCK_SECOND*1);
      PROCESS_WAIT_UNTIL(ev == full_msg_in || etimer_expired(&etimeout));
      PROCESS_YIELD();
      PRINTF("Data: ");
      for (i=0;i<3;i++)
        PRINTF("%u",rdata[i]);
      PRINTF("\n");*/

//      PROCESS_WAIT_UNTIL(ev == full_msg_in);
//      ptoproc = (int) PROCESS_CURRENT();
//      PRINTF("Pointer to current process:%u\n", ptoproc);



      etimer_set(&et, CLOCK_SECOND*2);
      rtimer_set(&rt, RTIMER_NOW() + LEDS_OFF_HYSTERISIS, 1,
                 rt_callback, NULL);
      counter++;
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 * @}
 */
