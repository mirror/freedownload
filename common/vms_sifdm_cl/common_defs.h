#pragma once

#ifndef UNUSED
#define UNUSED(arg) (void)arg;
#endif

#define MUST_BE_IMPLEMENTED assert (!"implemented"); #error "this part of the code lacks implementation."


#ifndef _countof
template <typename T, std::size_t N>
char(&COUNTOF_REQUIRES_ARRAY_ARGUMENT(T(&)[N]))[N];
#define _countof(x) sizeof(COUNTOF_REQUIRES_ARRAY_ARGUMENT(x))
#endif
