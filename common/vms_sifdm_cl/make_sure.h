#pragma once

// crash the app if eval is false
#define make_sure(eval) {auto result = (eval) != 0; assert (result); if (!(result)) {char*p=0;++p;*p=1;}}