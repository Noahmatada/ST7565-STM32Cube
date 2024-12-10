/*
$Id:$

ST7565/ST7565P LCD library!

Copyright (C) 2023 Arsalan Ali Mujtaba

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.

// some of this code was written by <arsalan.mselep@uetpeshawar.edu.pk> originally; it is in the public domain.
// modified 2024 by Noah Adams
*/

#include <stdlib.h>
#include <stdint.h>
#include "ST7565.h"
#include <string.h>

extern const uint8_t font[];
// extern uint8_t displayBuffer[];
uint8_t displayBuffer[1024] = { 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 };

// the memory buffer for the LCD
uint8_t st7565_buffer[1024] = { 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


#define enablePartialUpdate

#ifdef enablePartialUpdate
static uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
#endif



static void ST7565_updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
#ifdef enablePartialUpdate
  if (xmin < xUpdateMin) xUpdateMin = xmin;
  if (xmax > xUpdateMax) xUpdateMax = xmax;
  if (ymin < yUpdateMin) yUpdateMin = ymin;
  if (ymax > yUpdateMax) yUpdateMax = ymax;
#endif
}

void ST7565_drawbitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color)
{
	  unsigned Column_Address=0;
	  unsigned Row_Address=0;
	  unsigned int k,i;

	  ST7565_command(CMD_SET_ADC_NORMAL);
	ST7565_command(CMD_SET_COM_REVERSE);
	  for(k=0; k<8; k++)
	  {
		  ST7565_command(0x40);                                       // Line   Address
		  ST7565_command(0xB0+k+Row_Address);                         // Page   Address
		  ST7565_command(0x10);                                       // Column Address-4-H-bits
		  ST7565_command(0x00);                                       // Column Address-4-L-bits

		  ST7565_command(0x10 + ((Column_Address&0xF0)>>4));          // Column Address-4-H-bits
		  ST7565_command(0x00 +  (Column_Address&0x0F));              // Column Address-4-L-bits

	      for(i=0;i<128; i++)
	      {
	    	  ST7565_data(*bitmap);
	    	  bitmap++;
	      }
	  }
  ST7565_updateBoundingBox(x, y, x+w, y+h);
}

void ST7565_drawstring(uint8_t x, uint8_t line, char *c)
{
  while (c[0] != 0) {
	ST7565_drawchar(x, line, c[0]);
    c++;
    x += 6; // 6 pixels wide
    if (x + 6 >= LCD_WIDTH) {
      x = 0;    // ran out of this line
      line++;
    }
    if (line >= (LCD_HEIGHT/8))
      return;        // ran out of space :(
  }
}



void  ST7565_drawchar(uint8_t x, uint8_t line, char c)
{
  uint8_t i;
  for (i =0; i<5; i++ ) {
	  displayBuffer[x + (line*128) ] = font[((unsigned char)c * 5) + i];
    x++;
  }

 ST7565_updateBoundingBox(x-5, line*8, x-1, line*8 + 8);
}

void ST7565_drawstring_anywhere(uint8_t x, uint8_t y, const char* str)
{
  uint8_t i = 0;
  while (str[i] != '\0') {
	  ST7565_drawchar_anywhere(x, y, str[i]);
    x += 6; // Adjust the x-coordinate to leave space between characters
    i++;
  }
}

void ST7565_drawchar_anywhere(uint8_t x, uint8_t y, char c)
{
  uint8_t i, j;
  for (i = 0; i < 5; i++) {
	uint8_t column = font[(unsigned char)c * 5 + i];
	for (j = 0; j < 8; j++) {
	  if ((y + j) < LCD_HEIGHT) {
		if (column & (1 << j)) {
			ST7565_setpixel(x + i, y + j, BLACK);
		} else {
			ST7565_setpixel(x + i, y + j, WHITE);
		}
	  }
	}
  }
}

void ST7565_drawnum_anywhere(uint8_t x, uint8_t y, char c)
{
  uint8_t i, j;
  for (i = 0; i < 5; i++) {
    uint8_t column = font[(unsigned char)c * 5 + i];
    for (j = 0; j < 8; j++) {
      if ((y + j) < LCD_HEIGHT) {
        if (column & (1 << j)) {
          ST7565_setpixel(x + i, y + j, BLACK);
        } else {
          ST7565_setpixel(x + i, y + j, WHITE);
        }
      }
    }
  }
}



// bresenham's algorithm - thx wikpedia
void ST7565_drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color, uint8_t width)
{
  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
	swap(x0, y0);
	swap(x1, y1);
  }
  if (x0 > x1) {
	swap(x0, x1);
	swap(y0, y1);
  }
  uint8_t dx = x1 - x0;
  uint8_t dy = abs(y1 - y0);
  int8_t err = dx / 2;
  int8_t ystep;
  if (y0 < y1) {
	ystep = 1;
  } else {
	ystep = -1;
  }
  for (; x0 <= x1; x0++) {
	for (int8_t i = -(width / 2); i <= width / 2; i++) {
	  if (steep) {
		ST7565_setpixel(y0 + i, x0, color);
	  } else {
		if (y0 + i >= 0 && y0 + i < LCD_HEIGHT) {
		  ST7565_setpixel(x0, y0 + i, color);
		}
	  }
	}
	err -= dy;
	if (err < 0) {
	  y0 += ystep;
	  err += dx;
	}
  }
}
// filled rectangle
void ST7565_fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
  uint8_t i, j;

  // stupidest version - just pixels - but fast with internal buffer!
  for (i=x; i<x+w; i++) {
    for (j=y; j<y+h; j++) {
    	ST7565_setpixel(i, j, color);
    }
  }

  ST7565_updateBoundingBox(x, y, x+w, y+h);
}

// draw a rectangle
void ST7565_drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color)
{
  uint8_t i;
  // stupidest version - just pixels - but fast with internal buffer!
  for (i=x; i<x+w; i++) {
	ST7565_setpixel(i, y, color);
	ST7565_setpixel(i, y+h-1, color);
  }
  for (i=y; i<y+h; i++) {
	ST7565_setpixel(x, i, color);
	ST7565_setpixel(x+w-1, i, color);
  } 

  ST7565_updateBoundingBox(x, y, x+w, y+h);
}

// draw a circle outline
void ST7565_drawcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
	ST7565_updateBoundingBox(x0-r, y0-r, x0+r, y0+r);

  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;

  ST7565_setpixel(x0, y0+r, color);
  ST7565_setpixel(x0, y0-r, color);
  ST7565_setpixel(x0+r, y0, color);
  ST7565_setpixel(x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    ST7565_setpixel(x0 + x, y0 + y, color);
    ST7565_setpixel(x0 - x, y0 + y, color);
    ST7565_setpixel(x0 + x, y0 - y, color);
    ST7565_setpixel(x0 - x, y0 - y, color);
    
    ST7565_setpixel(x0 + y, y0 + x, color);
    ST7565_setpixel(x0 - y, y0 + x, color);
    ST7565_setpixel(x0 + y, y0 - x, color);
    ST7565_setpixel(x0 - y, y0 - x, color);
    
  }
}

void ST7565_fillcircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color)
{
  ST7565_updateBoundingBox(x0-r, y0-r, x0+r, y0+r);

  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;
  uint8_t i;

  for (i=y0-r; i<=y0+r; i++) {
	// NA: ST7565_my_setpixel(x0, i, color);
  ST7565_setpixel(x0, i, color);
  }

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    for (i=y0-y; i<=y0+y; i++) {
    	ST7565_setpixel(x0+x, i, color);
    	ST7565_setpixel(x0-x, i, color);
    } 
    for (i=y0-x; i<=y0+x; i++) {
    	ST7565_setpixel(x0+y, i, color);
    	ST7565_setpixel(x0-y, i, color);
    }    
  }
}


// Update the physical display with the contents of the display buffer
void updateDisplay()
{
	ST7565_command(CMD_SET_ADC_NORMAL);
	ST7565_command(CMD_SET_COM_NORMAL);
    ST7565_command(CMD_SET_DISP_START_LINE);
  for (uint8_t page = 0; page < LCD_HEIGHT / 8; page++) {
    // Set the page address
    ST7565_command(CMD_SET_PAGE | page);

    for (uint8_t column = 0; column < LCD_WIDTH; column++) {
      // Set the column address
      ST7565_command(CMD_SET_COLUMN_UPPER | (column >> 4));
      ST7565_command(CMD_SET_COLUMN_LOWER | (column & 0x0F));

      // Send the pixel data
      ST7565_data(displayBuffer[page * LCD_WIDTH + column]);
    }
  }
}

void ST7565_setpixel(uint8_t x, uint8_t y, uint8_t color)
{  // Calculate the index into the display buffer
  uint16_t index = (y / 8) * LCD_WIDTH + x;

  // Set the pixel color in the buffer
  if (color == 1) {
	displayBuffer[index] |= (1 << (y % 8));
  } else {
	displayBuffer[index] &= ~(1 << (y % 8));
  }
}



void ST7565_init(void)
{

	pin_config();                       // configure I/O pins
	HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(cog_port, cog_RST, GPIO_PIN_SET);
	HAL_Delay(500);          // Software Reset Sequence
	HAL_GPIO_WritePin(cog_port, cog_RST, GPIO_PIN_RESET);
	HAL_Delay(500);          // Software Reset Sequence
	HAL_GPIO_WritePin(cog_port, cog_RST, GPIO_PIN_SET);

	// LCD bias select
	ST7565_command(CMD_SET_BIAS_7);
	// ADC select
	ST7565_command(CMD_SET_ADC_REVERSE);
	// SHL select
	ST7565_command(CMD_SET_COM_REVERSE);
	// Initial display line
	ST7565_command(CMD_SET_DISP_START_LINE);

	// turn on voltage converter (VC=1, VR=0, VF=0)
	ST7565_command(CMD_SET_POWER_CONTROL | 0x4);
	// wait for 50% rising
	HAL_Delay(50);          // Software Reset Sequence

	// turn on voltage regulator (VC=1, VR=1, VF=0)
	ST7565_command(CMD_SET_POWER_CONTROL | 0x6);
	// wait >=50ms
	HAL_Delay(50);          // Software Reset Sequence

	// turn on voltage follower (VC=1, VR=1, VF=1)
	ST7565_command(CMD_SET_POWER_CONTROL | 0x7);
	// wait
	HAL_Delay(10);          // Software Reset Sequence

	// set lcd operating voltage (regulator resistor, ref voltage resistor)
	// ST7565_command(CMD_SET_RESISTOR_RATIO | 0x6); // 11yrs
	ST7565_command(CMD_SET_RESISTOR_RATIO | 0x4);


	ST7565_command(CMD_DISPLAY_ON);
	// ADC select
	ST7565_command(CMD_SET_ALLPTS_NORMAL);
	// SHL select
	ST7565_command(CMD_SET_COM_REVERSE);


	// NA: ST7565_st7565_set_brightness(0xff);
	ST7565_set_brightness(0x11);


	memset(displayBuffer, 0, sizeof(displayBuffer)); // for clearing the display buffer

	ST7565_updateBoundingBox(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);
}


uint8_t ST7565_command(uint8_t c) {
	uint8_t ret;
    HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_RESET);               // Following contents are Commands
    HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_RESET);           // COG Chip selected

	HAL_SPI_TransmitReceive(&SPI_PORT, &c, &ret, 1, 100);

    HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_SET);           // chip de-selected until further transaction
    HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_SET);
    return ret;
}

uint8_t ST7565_data(uint8_t c) {
	uint8_t ret;
    HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_SET);               // Following contents are Commands
    HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_RESET);           // COG Chip selected

	HAL_SPI_TransmitReceive(&SPI_PORT, &c, &ret, 1, 100);

    HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_SET);           // chip de-selected until further transaction
    HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_RESET);
    return ret;
}
void ST7565_set_brightness(uint8_t val) {
	ST7565_command(CMD_SET_VOLUME_FIRST);
    ST7565_command(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

// clear everything
void ST7565_clear(void) {
    int page_index=0;
    int column_index=0;

    for(page_index=0; page_index<8; page_index++)
    {
    	ST7565_command(0x40);                   // Line   Address
    	ST7565_command(0xB0 + page_index);      // Page   Address
    	ST7565_command(0x10);                   // Column Address-4-H-bits
    	ST7565_command(0x00);                   // Column Address-4-L-bits

        for(column_index=0; column_index<132; column_index++)
        {
        	ST7565_data(0x00);
        	ST7565_data(0x00);
        }
    }
}

void pin_config()
{
	// check for this portion first if lcd is not working becuase the initializations are here for control pins
	
//++++++++++++++++++++++++++
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	COG_GPIO_CLK_ENABLE();
	HAL_GPIO_WritePin(cog_port, cog_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(cog_port, cog_RST, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(cog_port, cog_CS, GPIO_PIN_RESET);

	/*Configure GPIO pin : Register Select (RS/A0) */
	GPIO_InitStruct.Pin = cog_RS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

	/*Configure GPIO pin : Reset (RST) */
	GPIO_InitStruct.Pin = cog_RST;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

	/*Configure GPIO pin : Chip Select (CS) */
	GPIO_InitStruct.Pin = cog_CS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

}

// void pin_config()
// {
// 	// check for this portion first if lcd is not working becuase the initializations are here for control pins
	
// //++++++++++++++++++++++++++
// 	GPIO_InitTypeDef GPIO_InitStruct = {0};
// 	__HAL_RCC_GPIOD_CLK_ENABLE();
// 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

// 	/*Configure GPIO pin : PD8 */
// 	GPIO_InitStruct.Pin = GPIO_PIN_9;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

// 	/*Configure GPIO pin : PD9 */
// 	GPIO_InitStruct.Pin = GPIO_PIN_10;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

// 	/*Configure GPIO pin : PD10 */
// 	GPIO_InitStruct.Pin = GPIO_PIN_8;
// 	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
// 	GPIO_InitStruct.Pull = GPIO_NOPULL;
// 	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
// 	HAL_GPIO_Init(cog_port, &GPIO_InitStruct);

// }
