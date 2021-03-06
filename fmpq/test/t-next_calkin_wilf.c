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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq.h"

int
main(void)
{
    long i;
    fmpq_t r, ans;

    printf("next_calkin_wilf....");
    fflush(stdout);

    fmpq_init(r);
    fmpq_init(ans);

    fmpq_set_si(r, 0, 1);
    fmpq_set_si(ans, 191, 1287);
    for (i = 0; i < 1000000; i++)
        fmpq_next_calkin_wilf(r, r);

    if (!fmpq_equal(r, ans))
    {
        printf("FAIL: enum from 0\n");
        fmpq_print(r);
        printf("\n");
        fmpq_print(ans);
        printf("\n");
        abort();
    }

    fmpq_set_si(r, 0, 1);
    fmpq_set_si(ans, -191, 1096);
    for (i = 0; i < 1000000; i++)
        fmpq_next_signed_calkin_wilf(r, r);

    if (!fmpq_equal(r, ans))
    {
        printf("FAIL: signed enum from 0\n");
        fmpq_print(r);
        printf("\n");
        fmpq_print(ans);
        printf("\n");
        abort();
    }


    fmpz_set_str(fmpq_numref(r), "18446744073709551615", 10);
    fmpz_set_str(fmpq_denref(r), "18446744073709551616", 10);
    fmpz_set_str(fmpq_numref(ans), "18538977794078099355206", 10);
    fmpz_set_str(fmpq_denref(ans), "22062305912156623710275", 10);
    for (i = 0; i < 1000000; i++)
        fmpq_next_calkin_wilf(r, r);

    if (!fmpq_equal(r, ans))
    {
        printf("FAIL: enum from 2^64\n");
        fmpq_print(r);
        printf("\n");
        fmpq_print(ans);
        printf("\n");
        abort();
    }

    fmpz_set_str(fmpq_numref(r), "18446744073709551615", 10);
    fmpz_set_str(fmpq_denref(r), "18446744073709551616", 10);
    fmpz_set_str(fmpq_numref(ans), "15015649675999575000951", 10);
    fmpz_set_str(fmpq_denref(ans), "18538977794078099356211", 10);
    for (i = 0; i < 1000000; i++)
        fmpq_next_signed_calkin_wilf(r, r);

    if (!fmpq_equal(r, ans))
    {
        printf("FAIL: signed enum from 2^64\n");
        fmpq_print(r);
        printf("\n");
        fmpq_print(ans);
        printf("\n");
        abort();
    }


    fmpq_clear(r);
    fmpq_clear(ans);

    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
