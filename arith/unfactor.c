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

    Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "arith.h"


void fmpz_unfactor(fmpz_t n, fmpz_factor_t factor)
{
    long i;
    fmpz_t tmp;

    fmpz_set_si(n, factor->sign);

    fmpz_init(tmp);
    for (i = 0; i < factor->length; i++)
    {
        fmpz_pow_ui(tmp, factor->p + i, fmpz_get_ui(factor->exp + i));
        fmpz_mul(n, n, tmp);
    }

    fmpz_clear(tmp);
}
