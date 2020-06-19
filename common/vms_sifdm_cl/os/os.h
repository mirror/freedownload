#pragma once

#include "vmsOsVersion.h"
#ifdef _WIN32
#include "../vmsWinOsVersion.h"
typedef vmsWinOsVersion vmsOsVersion;
#endif