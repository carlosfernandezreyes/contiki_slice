/*
 * Copyright (c) 2015, Edosoft Factory S.L.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EDOSOFT COMPANY AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COMPANY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 */

//
// Created by Raul Suarez on 21/09/15.
//

#include "dev/cs5490.h"
#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ip/resolv.h"
#include "dev/uart.h"
#include "dev/leds.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*/
//static unsigned int ind;
//static unsigned int rdata[3];

/*---------------------------------------------------------------------------*/
static void
byte2str(uint8_t byte, uint8_t str[]){
    static int k;

    for(k=0; k<8; k++){
        if((byte%2)==0) str[k]=0;
        else str[k]=1;
        byte=byte/2;
    }
}
/*--------------------------------------------------------------------------*/
static uint16_t
ascii2Number(const unsigned char *s, uint8_t index)
{
    if(((uint16_t)s[index])<58){
        return((uint16_t)s[index]-48);
    }else{
        return((uint16_t)s[index]-55);
    }
}
/*---------------------------------------------------------------------------*/
static void
number2Ascii(uint16_t val, uint8_t *pArray, uint8_t times, uint8_t end_index)
{
    uint16_t value;
    uint8_t dig;
    //Number cannot be higher than 65535
    value = val & 0xFFFF;
//    PRINTF("\n Received values: %u; Filtered value: %u\n", val, value);
    while (times > 0)
    {
        dig = value & 0x000F;
//        PRINTF("Digit: %u\n", dig);
        if (dig <= 9)
            pArray[end_index] = dig + 48;
        else
            pArray[end_index] = dig + 55;
//        PRINTF("Array content value: %u\n\n", pArray[end_index]);
        times--;
        end_index--;
        value = value >> 4;
    }
}
/*---------------------------------------------------------------------------*/
static float
dec_val(uint8_t MSB, uint8_t type){
    static float bitwt;
    static uint8_t i;
    static float result;
    static uint8_t MSB_val[8];
    byte2str(MSB, MSB_val);
    result=0;
    bitwt=1;
    if(type==1){
        type=0;
        for (i=0; i<7; i++){
            bitwt=bitwt/2;
            result=result+MSB_val[6-i]*bitwt;
        }
    }
    else{
        for (i=0; i<8; i++){
            bitwt=bitwt/2;
            result=result+MSB_val[7-i]*bitwt;
        }
    }
    return result;
}
/*---------------------------------------------------------------------------*/
static float
sig_dec_val(uint8_t MSB){
    static float bitwt;
    static uint8_t i;
    static float result;
    static uint8_t MSB_val[8];
    byte2str(MSB, MSB_val);
    result=0;
    bitwt=1;
    for (i=0; i<8; i++){
        if(i==0){
            result=result-MSB_val[7]*1;
        }
        else{
            bitwt=bitwt/2;
            result=result+MSB_val[7-i]*bitwt;
        }
    }
    return result;
}
/*---------------------------------------------------------------------------*/
unsigned int
cs_uart_send(const unsigned char *s, unsigned int len)
{
    unsigned int i = 0;

    while(s && *s != 0) {
        if(i >= len) {
            break;
        }
        uart_write_byte(0,*s++);
        i++;
    }
    return i;
}
/*---------------------------------------------------------------------------*/
int
cs_uart_rx(unsigned char c)
{
//    rdata[ind++]=c;

    PRINTF("Hex rdata: 0x%02X\n", c);
    /*if(ind==3){
        ind = 0;
        PRINTF("Ok!\n");
        process_post(PROCESS_CURRENT(), full_msg_in, NULL);
//        process_post(PROCESS_BROADCAST, full_msg_in, NULL);
    }*/
    return 1;
}
/*---------------------------------------------------------------------------*/
//static void
//spi_init(){
//
///******** Using UART1 ********/
///******** Alternative 2: USART1 ********/
//    PERCFG |= 0x02;	//Alternative 2
//    //U1CSR &= 0x1F;
//    P1SEL |= 0xE0; 	//PIN 7, 6, 5 peripheral; Master mode has no SS, to be done using IO (P0_6)
//    P0SEL &= ~0x40; //PIN p0_6 = GPIO (SSN); 1 bit complement
//    P0DIR |= 0x40;	//p0_6 as output
//    //P0DIR |= 0xE0;  //???
//
///******** BAUD RATE ********/
////Never to modify this param during a transference (UxCSR.ACTIVE = 1)
////BaudRate to be set in PMeter register at 38400 baudios (default PM = 600)
//    U1BAUD = 0x3B;	//Decimal 59 - Depending on the exponent (BAUD_E) it takes different baud rate values:
//    //10->38400, 11->76800, 4->600
//
///******** MASTER MODE ********/
//    //U1CSR &= ~0xA0;		//SPI as master; the others don't matter
//    U1CSR |= 0x80;		//UART mode; RX not active yet
//
///******** PHASE, POLARITY AND BIT ORDER ********/
//    //U1GCR = 0xEA;	//CPOL=1, CPHA=1, ORDER=1, BAUD_E=10
//    //U1GCR = 0xEB;	//CPOL=1, CPHA=1, ORDER=1, BAUD_E=11(76800bps)
//    //U1GCR = 0x6A;	//CPOL=0, CPHA=1, ORDER=1, BAUD_E=10
//    //U1GCR = 0xAA;	//CPOL=1, CPHA=0, ORDER=1, BAUD_E=10
//    //U1GCR = 0xCA;	//CPOL=1, CPHA=1, ORDER=0(LSB), BAUD_E=10
//    U1GCR = 0x04;	//CPOL=0, CPHA=0, ORDER=0(LSB), BAUD_E=4
//    //U1GCR = 0x24;	//CPOL=0, CPHA=0, ORDER=1(MSB), BAUD_E=4
//}
///*---------------------------------------------------------------------------*/
