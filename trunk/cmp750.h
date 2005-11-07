/*******************************************************************************
 * Canon MP750 SANE backend
   based on the ma1509 backend

   cmp750.h

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

/* declarations */

#ifndef cmp750_h
#define cmp750_h

enum CMP750_Option
{
  OPT_NUM_OPTS = 0,

  OPT_MODE_GROUP,
  OPT_MODE,
  OPT_RESOLUTION,
  OPT_SOURCE,
  OPT_PREVIEW,

  OPT_GEOMETRY_GROUP,
  OPT_TL_X,			/* top-left x */
  OPT_TL_Y,			/* top-left y */
  OPT_BR_X,			/* bottom-right x */
  OPT_BR_Y,			/* bottom-right y */

  OPT_ENHANCEMENT_GROUP,
  OPT_THRESHOLD,
  OPT_CUSTOM_GAMMA,		/* use custom gamma tables? */
  OPT_GAMMA_VECTOR_R,
  OPT_GAMMA_VECTOR_G,
  OPT_GAMMA_VECTOR_B,
  /* must come last: */
  NUM_OPTIONS
};

typedef struct CMP750_Device
{
  struct CMP750_Device *next;
  SANE_String name;
  SANE_Device sane;
  SANE_Bool has_adf;
  SANE_Range x_range;
  SANE_Range y_range;
  /* values actually used by scanner, not necessarily the desired! */
  SANE_Int bpl, ppl, lines;
}
CMP750_Device;


typedef struct CMP750_Scanner
{
  /* all the state needed to define a scan request: */
  struct CMP750_Scanner *next;

  SANE_Option_Descriptor opt[NUM_OPTIONS];
  Option_Value val[NUM_OPTIONS];

  SANE_Bool scanning;
  SANE_Bool cancelled;
  SANE_Parameters params;

  /* Parsed option values and variables that are valid only during
     actual scanning: */
  int fd;			/* filedescriptor */
  long start_time;		/* at this time the scan started */
  long lamp_time;		/* at this time the lamp was turned on */
  SANE_Word total_bytes;	/* bytes read from scanner */
  SANE_Word read_bytes;		/* bytes transmitted by sane_read */

  SANE_Int red_gamma_table[CMP750_GAMMA_SIZE];
  SANE_Int green_gamma_table[CMP750_GAMMA_SIZE];
  SANE_Int blue_gamma_table[CMP750_GAMMA_SIZE];

  SANE_Byte *buffer, *buffer_start;
  SANE_Int buffer_bytes;
  /* scanner dependent/low-level state: */
  CMP750_Device *hw;
}
CMP750_Scanner;

#endif /* cmp750_h */



