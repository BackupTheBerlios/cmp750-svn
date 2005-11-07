/*******************************************************************************
 * Canon MP750 SANE backend
   based on the ma1509 backend

   cmp750.c

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.

   ******************************************************************************/

#include "../include/sane/config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>

#include "../include/sane/sane.h"
#include "../include/sane/sanei.h"
#include "../include/sane/saneopts.h"
#include "../include/sane/sanei_usb.h"

#define BACKEND_NAME	cmp750
#include "../include/sane/sanei_backend.h"
#include "../include/sane/sanei_config.h"

#include "cmp750.h"

#ifndef SANE_I18N
#define SANE_I18N(text) text
#endif

/* Debug level from sanei_init_debug */
static SANE_Int debug_level;

static SANE_Int num_devices;
static CMP750_Device *first_dev;
static CMP750_Scanner *first_handle;
static const SANE_Device **devlist = 0;

static int warmup_time = CMP750_WARMUP_TIME;

/* Array of newly attached devices */
static CMP750_Device **new_dev;

/* Length of new_dev array */
static SANE_Int new_dev_len;

/* Number of entries alloced for new_dev */
static SANE_Int new_dev_alloced;

static SANE_String_Const mode_list[] = {
  SANE_I18N ("Lineart"), SANE_I18N ("Gray"), SANE_I18N ("Color"),
  0
};

static void
print_data_buffer (const SANE_Byte * buffer, size_t len)
{
  SANE_Byte buffer_byte_list[50];
  SANE_Byte buffer_byte[5];
  const SANE_Byte *pp;

  buffer_byte_list[0] = '\0';
  for (pp = buffer; pp < (buffer + len); pp++)
    {
      sprintf ((SANE_String) buffer_byte, " %02x", *pp);
      strcat ((SANE_String) buffer_byte_list, (SANE_String) buffer_byte);
      if (((pp - buffer) % 0x10 == 0x0f) || (pp >= (buffer + len - 1)))
	{
	  DBG (5, "buffer: %s\n", buffer_byte_list);
	  buffer_byte_list[0] = '\0';
	}
    }
}
