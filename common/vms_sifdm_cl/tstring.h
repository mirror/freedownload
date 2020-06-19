#pragma once

#ifndef tstring

#include <string>

#if defined (UNICODE) || defined (_UNICODE)
#define tstring std::wstring
#else
#define tstring std::string
#endif

#endif // tstring

#ifndef tstringstream

#include <sstream>

#if defined (UNICODE) || defined (_UNICODE)
#define tstringstream std::wstringstream
#else
#define tstringstream std::stringstream
#endif

#endif // tstring

//////////////////////////////////////////////////////////////////////////
// xstring
// xstring is a string with UNICODE support 
// xstring is a cross platform type
#ifdef WIN32
using xstring = std::wstring;
using xstringstream = std::wstringstream;
#else
using xstring = std::string; // unix uses utf-8 ? 
using xstringstream = std::stringstream;
#endif
//////////////////////////////////////////////////////////////////////////
