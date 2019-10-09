/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             

#include <windows.h>
#include <Shlobj.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <assert.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "../common/vms_sifdm_cl/base.h"
#include "../common/vms_sifdm_cl/thread/vmsCreatesThreads2.h"
#include "../common/vms_sifdm_cl/threadsafe/vmsThreadSafe4.h"
#include "../common/vms_sifdm_cl/inet/http/vmsHttpMessageStore.h"

#include "windivert/windivert.h"
