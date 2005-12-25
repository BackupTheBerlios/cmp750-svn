/* cmp750.c - SANE backend for the CANON PIXMA MP750 Backend.

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

static CMP750_Device *first_cmp750_device = 0;
static SANE_Int num_cmp750_device = 0;
static const SANE_Device **sane_device_list = NULL;

/*
*    WIP
*/

SANE_Status
attachCMP750 (SANE_String_Const devname)
{
  CMP750_Device *cmp750_device;

  DBG (2, "attachCMP750: devname=%s\n", devname);

  for (cmp750_device = first_cmp750_device; cmp750_device;
       cmp750_device = cmp750_device->next)
    {
      if (strcmp (cmp750_device->sane.name, devname) == 0)
	    return SANE_STATUS_GOOD;
    }

  cmp750_device = (CMP750_Device *) malloc (sizeof (CMP750_Device));
  if (cmp750_device == NULL)
    return SANE_STATUS_NO_MEM;

  cmp750_device->sane.name = strdup (devname);
  cmp750_device->sane.vendor = "CANON";
  cmp750_device->sane.model = "MP750";
  cmp750_device->sane.type = "multi-function peripheral";

  /* Set the default resolution here */
  cmp750_device->x_dpi = 75;
  cmp750_device->y_dpi = 75;

  /* Make the pointer to the read buffer null here */
  cmp750_device->read_buffer = NULL;

  /* Set the default threshold for lineart mode here */
  cmp750_device->threshold = 0x80;

  cmp750_device->next = first_cmp750_device;
  first_cmp750_device = cmp750_device;

  num_cmp750_device++;

  return SANE_STATUS_GOOD;
}

SANE_Status sane_init (SANE_Int * version_code, SANE_Auth_Callback authorize)
{
  FILE *fp;
  SANE_Char line[PATH_MAX];
  const char *lp;
  SANE_Int vendor, product;
  size_t len;
  SANE_Status status;
  SANE_Auth_Callback auth_callback;
  
  DBG_INIT ();
  DBG("Initializing cmp750 backend...");

  sanei_usb_init ();

  fp = sanei_config_open ("cmp750.conf");
  if (!fp)
    {
      return SANE_STATUS_ACCESS_DENIED;
    }

  while (sanei_config_read (line, PATH_MAX, fp))
    {
      /* ignore comments */
      if (line[0] == '#')
	      continue;
      len = strlen (line);

      /* delete newline characters at end */
      if (line[len - 1] == '\n')
	      line[--len] = '\0';

      /* lp = (SANE_String) sanei_config_skip_whitespace (line); */
      lp = sanei_config_skip_whitespace (line);
      /* skip empty lines */
      if (*lp == 0)
	      continue;

      if (sscanf (lp, "usb %i %i", &vendor, &product) == 2)
	      ;
      else if (strncmp ("libusb", lp, 6) == 0)
	      ;
      else if ((strncmp ("usb", lp, 3) == 0) && isspace (lp[3]))
	    {
	      lp += 3;
	      /* lp = (SANE_String) sanei_config_skip_whitespace (lp); */
	      lp = sanei_config_skip_whitespace (lp);
	    }
  
  sanei_usb_attach_matching_devices (lp, attachCMP750)
  
  return SANE_STATUS_GOOD;
}


/*
 *    TODO
 */


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

