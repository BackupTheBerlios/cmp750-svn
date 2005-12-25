/* sane - Scanner Access Now Easy.

   CANON PIXMA MP750 Backend
   Copyright (C) 2005, 2006 Christopher Albert
   ert@zapo.net - http://see.tang.la

   written using the Lexmark Backend
   as a template

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

   As a special exception, the authors of SANE give permission for
   additional uses of the libraries contained in this release of SANE.

   The exception is that, if you link a SANE library with other files
   to produce an executable, this does not by itself cause the
   resulting executable to be covered by the GNU General Public
   License.  Your use of that executable is in no way restricted on
   account of linking the SANE library code into it.

   This exception does not, however, invalidate any other reasons why
   the executable file might be covered by the GNU General Public
   License.

   If you submit changes to SANE to the maintainers to be included in
   a subsequent release, you agree by submitting the changes that
   those changes may be distributed with this exception intact.

   If you write modifications of your own for SANE, it is your choice
   whether to permit this exception to apply to your modifications.
   If you do not wish that, delete this exception notice.

*/

#include "../include/sane/config.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/time.h>

#include "../include/sane/sane.h"
#include "../include/sane/sanei.h"
#include "../include/sane/saneopts.h"
#include "../include/sane/sanei_config.h"
#include "../include/sane/sanei_usb.h"

#include "cmp750.h"
#include "../include/sane/sanei_backend.h"

/*
 *    TODO
 */
 
SANE_Status sane_init (SANE_Int * version_code, SANE_Auth_Callback authorize)

void sane_exit (void);

SANE_Status sane_get_devices (const SANE_Device *** device_list, 
             SANE_Bool local_only);
             
SANE_Status sane_open (SANE_String_Const devicename,
             SANE_Handle * handle);
             
void sane_close (SANE_Handle handle);

const SANE_Option_Descriptor *
  sane_get_option_descriptor (SANE_Handle handle, SANE_Int option);
  
SANE_Status sane_control_option (SANE_Handle handle, SANE_Int option,
			 SANE_Action action, void *value,
			 SANE_Int * info);
			 
SANE_Status sane_get_parameters (SANE_Handle handle,
			 SANE_Parameters * params);
			 
SANE_Status sane_start (SANE_Handle handle);

SANE_Status sane_read (SANE_Handle handle, SANE_Byte * data,
			 SANE_Int max_length, SANE_Int * length);
			 
void sane_cancel (SANE_Handle handle);

SANE_Status sane_set_io_mode (SANE_Handle handle,
			 SANE_Bool non_blocking);
			 
SANE_Status sane_get_select_fd (SANE_Handle handle,
			 SANE_Int * fd);
			 
SANE_String_Const sane_strstatus (SANE_Status status);

