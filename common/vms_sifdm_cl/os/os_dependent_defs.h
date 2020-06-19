#pragma once

#ifdef WIN32
#include "components/clipboard/vmsWinOsClipboard.h"
typedef vmsWinOsClipboard vmsOsClipboard;
#endif