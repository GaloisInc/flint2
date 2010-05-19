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

 Copyright (C) 2010 William Hart
 
******************************************************************************/

#ifndef NMOD_VEC_H
#define NMOD_VEC_H

#include <mpir.h>
#include "longlong.h"
#include "ulong_extras.h"

typedef struct
{
   mp_limb_t n;
   mp_limb_t ninv;
   mp_bitcnt_t norm;
} nmod_t;

#define NMOD_RED2(r, a_hi, a_lo, mod) \
   do { \
      mp_limb_t q0, q1, r1; \
      const mp_limb_t u1 = (a_hi<<mod.norm) + r_shift(a_lo, FLINT_BITS - mod.norm);	\
	  const mp_limb_t u0 = (a_lo<<mod.norm); \
	  const mp_limb_t nxx = (mod.n<<mod.norm); \
      umul_ppmm(q1, q0, mod.ninv, u1); \
	  add_ssaaaa(q1, q0, q1, q0, u1, u0); \
	  r1 = (u0 - (q1 + 1)*nxx); \
      if (r1 >= q0) r1 += nxx; \
	  if (r1 < nxx) r = (r1>>mod.norm); \
	  else r = ((r1 - nxx)>>mod.norm); \
   } while (0)

#define NMOD_RED(r, a, mod) \
   do { \
      NMOD_RED2(r, 0, a, mod); \
   } while (0)

#define NMOD2_RED2(r, a_hi, a_lo, mod) \
	do { \
	   mp_limb_t v_hi;	\
	   NMOD_RED(v_hi, a_hi, mod); \
	   NMOD_RED2(r, v_hi, a_lo, mod); \
	} while (0)

#define NMOD_RED3(r, a_hi, a_me, a_lo, mod) \
	do { \
	   mp_limb_t v_hi;	\
	   NMOD_RED2(v_hi, a_hi, a_lo, mod); \
	   NMOD_RED2(r, v_hi, a_lo, mod); \
	} while (0)

static inline
void nmod_init(nmod_t * mod, mp_limb_t n)
{
   mod->n = n;
   mod->ninv = n_preinvert_limb(n);
   count_leading_zeros(mod->norm, n);
}

static inline
mp_limb_t * nmod_vec_init(ulong length)
{
   return (mp_limb_t *) malloc(length*sizeof(mp_limb_t));
}

static inline
void nmod_vec_free(mp_limb_t * vec)
{
   free(vec);
}

static inline
void _nmod_vec_zero(mp_limb_t * vec, ulong length)
{
   mpn_zero(vec, length);
}

static inline
void _nmod_vec_copy(mp_limb_t * res, mp_limb_t * vec, ulong length)
{
   mpn_copyi(res, vec, length);
}

static inline
int _nmod_vec_equal(mp_limb_t * vec, mp_limb_t * vec2, ulong length)
{
   ulong i;

   for (i = 0; i < length; i++)
      if (vec[i] != vec2[i]) return 0;

   return 1;
}

void _nmod_vec_reduce(mp_limb_t * res, mp_limb_t * vec, ulong len, nmod_t mod);

#endif





