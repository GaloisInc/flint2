/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/******************************************************************************

 Copyright (C) 2009 William Hart
 
******************************************************************************/

#ifndef FLINT_H
#define FLINT_H

#include <mpir.h>
#include "longlong.h"

#define ulong unsigned long
#define FLINT_BITS 64

#define FLINT_ASSERT(param)

#define FLINT_MAX(zzz1, zzz2) ((zzz1) > (zzz2) ? (zzz1) : (zzz2))
#define FLINT_MIN(zzz1, zzz2) ((zzz1) > (zzz2) ? (zzz2) : (zzz1))
#define FLINT_ABS(zzz) ((long)(zzz) < 0 ? (-zzz) : (zzz))

#define r_shift(in, shift) \
   ((shift == FLINT_BITS) ? 0L : ((in)>>(shift)))

#define l_shift(in, shift) \
   ((shift == FLINT_BITS) ? 0L : ((in)<<(shift)))

static inline 
unsigned int FLINT_BIT_COUNT(mp_limb_t x)
{
   unsigned int zeros = FLINT_BITS;
   if (x) count_leading_zeros(zeros, x);
   return FLINT_BITS - zeros;
}

#endif