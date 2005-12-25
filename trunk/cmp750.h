/* cmp750.h - SANE backend for the CANON PIXMA MP750 Backend.

   Copyright (C) 2005, 2006 Christopher Albert
   ert@zapo.net - http://see.tang.la

   written using the Lexmark Backend as a template

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

*/

#ifndef CMP750_H
#define CMP750_H

/* Force the backend name for all files using this include */
#ifdef BACKEND_NAME
#undef BACKEND_NAME
#define BACKEND_NAME cmp750
#endif

#define DEBUG_NOT_STATIC
#define SANE_NAME_PAPER_SIZE "paper-size"
#define SANE_TITLE_PAPER_SIZE SANE_I18N("Paper size")
#define SANE_DESC_PAPER_SIZE \
SANE_I18N("Selects the size of the area to be scanned.");

typedef enum
{
  OPT_NUM_OPTS = 0,
  OPT_MODE,
/*   OPT_X_DPI, */
/*   OPT_Y_DPI, */
  OPT_RESOLUTION,
  OPT_PREVIEW,
  OPT_SCAN_SIZE,
  OPT_THRESHOLD,
  /* must come last: */
  NUM_OPTIONS
}
CMP750_Options;

typedef enum
{
  RED = 0,
  GREEN,
  BLUE
}
Scan_Regions;

/** @name Option_Value union
 * convenience union to access option values given to the backend
 * @{
 */
#ifndef SANE_OPTION
#define SANE_OPTION 1
typedef union
{
  SANE_Bool b;
  SANE_Word w;
  SANE_Word *wa;		/* word array */
  SANE_String s;
}
Option_Value;
#endif

typedef struct Read_Buffer
{
  SANE_Int gray_offset;
  SANE_Int max_gray_offset;
  SANE_Int region;
  SANE_Int red_offset;
  SANE_Int green_offset;
  SANE_Int blue_offset;
  SANE_Int max_red_offset;
  SANE_Int max_green_offset;
  SANE_Int max_blue_offset;
  SANE_Byte *data;
  SANE_Byte *readptr;
  SANE_Byte *writeptr;
  SANE_Byte *max_writeptr;
  size_t size;
  size_t linesize;
  SANE_Bool empty;
  SANE_Int image_line_no;
  SANE_Int bit_counter;
  SANE_Int max_lineart_offset;
}
Read_Buffer;

typedef struct CMP750_Device
{
  struct CMP750_Device *next;
  
  SANE_Device sane;
  SANE_Option_Descriptor opt[NUM_OPTIONS];
  Option_Value val[NUM_OPTIONS];
  SANE_Parameters params;
  SANE_Int devnum;
  long data_size;
  SANE_Int pixel_height;
  SANE_Int pixel_width;
  SANE_Bool initialized;
  SANE_Bool eof;
  SANE_Int x_dpi;
  SANE_Int y_dpi;
  long data_ctr;
  SANE_Bool device_cancelled;
  SANE_Int cancel_ctr;
  SANE_Byte *transfer_buffer;
  size_t bytes_remaining;
  size_t bytes_in_buffer;
  SANE_Byte *read_pointer;
  Read_Buffer *read_buffer;
  SANE_Byte threshold;
} 
CMP750_Device;

#endif /* CMP750_H */
