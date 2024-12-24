#pragma once

#include "brainfxxk_operations.hpp"
#include "typearray.hpp"

using fizzbuzz = typearray<
    inc, inc, inc, inc, inc, inc, lb, dec, iptr, inc, inc, inc, inc, iptr, iptr,
    inc, iptr, inc, iptr, dec, dptr, dptr, dptr, dptr, dptr, le, iptr, lb, dptr,
    inc, inc, inc, inc, iptr, iptr, inc, inc, inc, iptr, inc, inc, inc, inc,
    iptr, iptr, inc, inc, inc, iptr, inc, inc, inc, inc, inc, iptr, inc, inc,
    inc, inc, inc, iptr, iptr, iptr, iptr, iptr, iptr, inc, inc, iptr, iptr,
    inc, inc, dptr, dptr, dptr, dptr, dptr, dptr, dptr, dptr, dptr, dptr, dptr,
    dptr, dptr, dptr, dec, le, dptr, inc, inc, inc, inc, iptr, inc, inc, inc,
    iptr, dec, dec, iptr, inc, inc, inc, iptr, dec, iptr, iptr, dec, dec, dec,
    iptr, inc, inc, iptr, iptr, iptr, inc, inc, inc, inc, inc, lb, dec, iptr,
    inc, inc, iptr, inc, inc, dptr, dptr, le, dptr, dptr, dptr, dptr, dptr,
    dptr, dptr, dptr, dptr, dptr, lb, dec, iptr, dec, lb, iptr, iptr, iptr,
    iptr, iptr, iptr, iptr, le, iptr, lb, dptr, inc, inc, inc, iptr, out, iptr,
    out, iptr, iptr, iptr, iptr, out, out, iptr, iptr, iptr, inc, dptr, le,
    dptr, dptr, dptr, dptr, dptr, dec, lb, iptr, iptr, iptr, iptr, le, iptr, lb,
    dptr, inc, inc, inc, inc, inc, iptr, out, iptr, out, iptr, out, out, iptr,
    iptr, iptr, inc, dptr, le, iptr, iptr, iptr, iptr, inc, dptr, dec, lb, dptr,
    dptr, dptr, le, dptr, lb, lb, dec, dptr, dptr, inc, iptr, iptr, le, iptr,
    iptr, iptr, inc, iptr, inc, dptr, dptr, dptr, dptr, dptr, dptr, lb, dec,
    iptr, iptr, inc, iptr, inc, iptr, dec, dptr, dptr, dptr, dptr, le, dptr, le,
    iptr, iptr, lb, lb, dec, le, dptr, le, iptr, lb, iptr, iptr, iptr, lb, iptr,
    out, dptr, dptr, out, dptr, dptr, dptr, le, dptr, lb, out, dptr, dptr, dptr,
    dptr, le, iptr, le, iptr, out, dptr, dptr, dptr, dptr, dptr, dptr, dptr,
    dptr, dptr, dptr, dptr, le>;

using hello_world =
    typearray<inc, inc, inc, inc, inc, inc, inc, inc, lb, iptr, inc, inc, inc,
              inc, lb, iptr, inc, inc, iptr, inc, inc, inc, iptr, inc, inc, inc,
              iptr, inc, dptr, dptr, dptr, dptr, dec, le, iptr, inc, iptr, inc,
              iptr, dec, iptr, iptr, inc, lb, dptr, le, dptr, dec, le, iptr,
              iptr, out, iptr, dec, dec, dec, out, inc, inc, inc, inc, inc, inc,
              inc, out, out, inc, inc, inc, out, iptr, iptr, out, dptr, dec,
              out, dptr, out, inc, inc, inc, out, dec, dec, dec, dec, dec, dec,
              out, dec, dec, dec, dec, dec, dec, dec, dec, out, iptr, iptr, inc,
              out, iptr, inc, inc, out>;

using prime02100 = typearray<
    iptr, inc, inc, inc, inc, lb, dptr, inc, inc, inc, inc, inc, inc, inc, inc,
    iptr, dec, le, iptr, inc, inc, inc, inc, inc, inc, inc, inc, lb, dptr, inc,
    inc, inc, inc, inc, inc, iptr, dec, le, dptr, inc, inc, out, dptr, out,
    iptr, inc, out, dptr, out, iptr, inc, inc, out, dptr, out, iptr, inc, inc,
    out, dptr, out, iptr, dec, dec, dec, dec, dec, dec, out, out, dptr, out,
    iptr, out, inc, inc, out, dptr, out, iptr, dec, dec, out, inc, inc, inc,
    inc, inc, inc, out, dptr, out, iptr, dec, dec, dec, dec, dec, dec, out,
    iptr, inc, inc, inc, lb, dptr, inc, inc, inc, iptr, dec, le, dptr, dec, out,
    dptr, out, iptr, dec, dec, dec, dec, dec, dec, dec, out, inc, out, dptr,
    out, iptr, dec, out, inc, inc, inc, inc, inc, inc, inc, out, dptr, out,
    iptr, dec, dec, dec, dec, dec, dec, out, dec, dec, out, dptr, out, iptr,
    inc, inc, out, inc, inc, inc, inc, out, dptr, out, iptr, dec, dec, dec, out,
    dec, dec, dec, out, dptr, out, iptr, inc, inc, inc, out, dec, out, dptr,
    out, iptr, inc, out, inc, inc, inc, out, dptr, out, iptr, dec, dec, out,
    dec, dec, out, dptr, out, iptr, inc, inc, out, inc, inc, inc, inc, out,
    dptr, out, iptr, dec, dec, dec, out, dec, dec, dec, dec, dec, out, dptr,
    out, iptr, inc, inc, inc, inc, inc, out, inc, out, dptr, out, iptr, out,
    dec, dec, dec, dec, dec, dec, out, dptr, out, iptr, inc, inc, inc, inc, inc,
    inc, out, dec, dec, dec, dec, out, dptr, out, iptr, inc, inc, inc, inc, out,
    inc, inc, out, dptr, out, iptr, dec, out, dec, dec, dec, dec, dec, out,
    dptr, out, iptr, inc, inc, inc, inc, inc, out, inc, out, dptr, out, iptr,
    out, dec, dec, out>;

using all_ascii = typearray<out, inc, lb, out, inc, le>;

#define run_this_program(p) using program = p::push_back<end>;
