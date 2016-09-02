/*
  PIM for Quagga
  Copyright (C) 2008  Everton da Silva Marques

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; see the file COPYING; if not, write to the
  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
  MA 02110-1301 USA
  
*/

#include <zebra.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "log.h"

#include "pim_str.h"

void pim_addr_dump (const char *onfail, struct prefix *p, char *buf, int buf_size)
{
  int save_errno = errno;

  if (!inet_ntop(p->family, &p->u.prefix, buf, buf_size)) {
    zlog_warn("pim_addr_dump: inet_ntop(buf_size=%d): errno=%d: %s",
	      buf_size, errno, safe_strerror(errno));
    if (onfail)
      snprintf(buf, buf_size, "%s", onfail);
  }

  errno = save_errno;
}

void pim_inet4_dump(const char *onfail, struct in_addr addr, char *buf, int buf_size)
{
  int save_errno = errno;

  if (!inet_ntop(AF_INET, &addr, buf, buf_size)) {
    zlog_warn("pim_inet4_dump: inet_ntop(AF_INET,buf_size=%d): errno=%d: %s",
	      buf_size, errno, safe_strerror(errno));
    if (onfail)
      snprintf(buf, buf_size, "%s", onfail);
  }

  errno = save_errno;
}

char *
pim_str_sg_dump (const struct prefix_sg *sg)
{
  char src_str[100];
  char grp_str[100];
  static char sg_str[200];

  pim_inet4_dump ("<src?>", sg->src, src_str, sizeof(src_str));
  pim_inet4_dump ("<grp?>", sg->grp, grp_str, sizeof(grp_str));
  snprintf (sg_str, 200, "(%s,%s)", src_str, grp_str);
  return sg_str;
}
