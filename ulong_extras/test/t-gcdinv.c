/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int i, result;
   flint_rand_t state;
   
   printf("gcdinv....");
   fflush(stdout);
   
   flint_randinit(state);

   for (i = 0; i < 10000 * flint_test_multiplier(); i++) 
   {
      mp_limb_t a, b, c, g, g2, s, t2, t, bits1, bits2, bits3;
      
      bits1 = n_randint(state, FLINT_BITS-2) + 2;
      bits2 = n_randint(state, bits1) + 1;
      bits3 = n_randint(state, FLINT_BITS - bits1) + 1;

      do
      {
         a = n_randtest_bits(state, bits1);
         b = n_randtest_bits(state, bits2);
      } while ((n_gcd(a, b) != 1UL) || (b >= a));

      c = n_randtest_bits(state, bits3);

      g = n_xgcd(&s, &t, a*c, b*c);
      g2 = n_gcdinv(&t2, b*c, a*c);
      t %= (a*c);
      t = a*c - t;

      result = ((g == g2) && (t == t2));
      if (!result)
      {
         printf("FAIL\n");
         printf("a = %lu, b = %lu, c = %lu, g = %lu, g2 = %lu, t = %ld, t2 = %ld\n", a, b, c, g, g2, t, t2); 
         abort();
      }
   }

   flint_randclear(state);

   printf("PASS\n");
   return 0;
}
