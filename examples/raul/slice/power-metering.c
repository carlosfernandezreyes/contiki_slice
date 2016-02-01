//
// Created by Edosoft Factory on 28/12/15.
//

#include "power-metering.h"
#include "contiki.h"
//#include "contiki-lib.h"
//#include "contiki-net.h"

//#include <string.h>

#include "dev/uart.h"
#include "dev/leds.h"
#include "dev/cs5490.h"
//#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "sys/rtimer.h"

#include "net/ip/uip-debug.h"

/*---------------------------------------------------------------------------*/
static struct etimer et, et2, et6;
/*---------------------------------------------------------------------------*/
PROCESS(powermetering, "power-metering process");
AUTOSTART_PROCESSES(&powermetering);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(powermetering, ev, data)
{
  PROCESS_BEGIN();
  uart_set_input(0, cs_uart_rx);
  //Wait for 100ms (just 60 ms needed) until PM oscillator starts working
  etimer_set(&et, CLOCK_SECOND/10);
  PROCESS_WAIT_UNTIL(etimer_expired(&et));

  // ==== POWER METER CONFIG (NOT DETAILED -> BY DEFAULT) ==== //
  //SW reset to PM
//  uart_write_byte(0, 0xC1);

  etimer_set(&et2, CLOCK_SECOND);	//Esperamos 1s para que el PM ejecute el reset
  PROCESS_WAIT_UNTIL(etimer_expired(&et2));

  etimer_set(&et, CLOCK_SECOND/10);	//Esperamos 100 ms (60) para que el oscilador del PM comience a funcionar
  PROCESS_WAIT_UNTIL(etimer_expired(&et));
  etimer_set(&et, CLOCK_SECOND*3);	//Ciclo de refresco de la info

  //Check if Vref is OK!
  PRINTF("Checking Vref (reg. should show 0x0C0008)...\n");
  etimer_set(&et6, CLOCK_SECOND);
  uart_write_byte(0, 0x80);
  uart_write_byte(0, 0x1E);

  PROCESS_WAIT_UNTIL(etimer_expired(&et6));
  //    ind = 0;
  //    PRINTF("0x%02X\n", rdata[0]);
  //    PRINTF("0x%02X\n", rdata[1]);
  //    PRINTF("0x%02X\n", rdata[2]);

  //Workaround for Vref voltage error
  PRINTF("Workaround for Vref voltage error!!\n");
  uart_write_byte(0, 0x80); //page 0
  uart_write_byte(0, 0x5C); //addr 28
  uart_write_byte(0, 0x16); //LSB -
  uart_write_byte(0, 0x00); //Med -
  uart_write_byte(0, 0x00); //MSB -

  uart_write_byte(0, 0x80); //page 0
  uart_write_byte(0, 0x5E); //addr 28
  uart_write_byte(0, 0x08); //LSB -
  uart_write_byte(0, 0x00); //Med -
  uart_write_byte(0, 0x0C); //MSB -

  uart_write_byte(0, 0x80); //page 0
  uart_write_byte(0, 0x5C); //addr 28
  uart_write_byte(0, 0x00); //LSB -
  uart_write_byte(0, 0x00); //Med -
  uart_write_byte(0, 0x00); //MSB -

  etimer_set(&et, CLOCK_SECOND*3);	//Ciclo de refresco de la info
  while(1){
    PROCESS_WAIT_UNTIL(etimer_expired(&et));

//    etimer_set(&et6, CLOCK_SECOND);
//    uart_write_byte(0, 0x80);
//    uart_write_byte(0, 0x19);
//    PROCESS_WAIT_UNTIL(etimer_expired(&et6));

    //Check if Vref is OK!
    PRINTF("Checking Vref (reg. should show 0x0C0008)...\n");
    etimer_set(&et6, CLOCK_SECOND);
    uart_write_byte(0, 0x80); //page 0
    uart_write_byte(0, 0x1E); //addr 30
    PROCESS_WAIT_UNTIL(etimer_expired(&et6));
//    ind = 0;
//    PRINTF("0x%02X\n", rdata[0]);
//    PRINTF("0x%02X\n", rdata[1]);
//    PRINTF("0x%02X\n", rdata[2]);

    etimer_restart(&et);
  }

  PROCESS_END();
}