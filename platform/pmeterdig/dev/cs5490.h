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

#ifndef CONTIKI_CS5490_H
#define CONTIKI_CS5490_H

#include "contiki.h"
/*---------------------------------------------------------------------------*/
#define DEBUG 1

#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
/*---------------------------------------------------------------------------*/
//static process_event_t full_msg_in;
static unsigned int ind;
static unsigned int rdata[3];
/*---------------------------------------------------------------------------*/
static void byte2str(uint8_t byte, uint8_t str[]);
static uint16_t ascii2Number(const unsigned char *s, uint8_t index);
static void number2Ascii(uint16_t val, uint8_t *pArray, uint8_t times, uint8_t end_index);
static float dec_val(uint8_t MSB, uint8_t type);
static float sig_dec_val(uint8_t MSB);
unsigned int cs_uart_send(const unsigned char *s, unsigned int len);
int cs_uart_rx(unsigned char c);
//static void spi_init();

#endif //CONTIKI_CS5490_H