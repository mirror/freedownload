#pragma once

// PROCESS_ALL_ACCESS may "not work" under Windows XP
// PROCESS_ALL_ACCESS__XP is recommended to use instead
#define PROCESS_ALL_ACCESS__XP  (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF)