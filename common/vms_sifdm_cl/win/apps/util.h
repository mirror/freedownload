#pragma once

#include <atlbase.h>
#include "../vmsCommandLine.h"

inline bool vmsGetOpenAppCmdline(
        const std::wstring &app,
        vmsCommandLine &cl)
{
    assert(!app.empty());
    if (app.empty())
        return false;
    std::wstring kn = L"Applications\\";
    kn += app;
    kn += L"\\shell\\open\\command";
    CRegKey key;
    if (ERROR_SUCCESS != key.Open(
                HKEY_CLASSES_ROOT,
                kn.c_str(),
                KEY_READ))
    {
        return false;
    }
    WCHAR wsz[10000] = {0};
    ULONG ul = _countof(wsz);
    if (ERROR_SUCCESS != key.QueryStringValue(nullptr, wsz, &ul) ||
            !*wsz)
    {
        return false;
    }
    cl.fromString(wsz);
    return true;
}

inline std::wstring vmsGetAppAbsolutePath(
        const std::wstring &app)
{
    assert(!app.empty());
    if (app.empty())
        return std::wstring();
    std::wstring kn = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\";
    kn += app;
    CRegKey key;
    if (ERROR_SUCCESS != key.Open(
                HKEY_LOCAL_MACHINE,
                kn.c_str(),
                KEY_READ))
    {
        return std::wstring();
    }
    WCHAR wsz[10000] = {0};
    ULONG ul = _countof(wsz);
    key.QueryStringValue(nullptr, wsz, &ul);
    if (!*wsz)
        return std::wstring();
    vmsCommandLine cl(wsz);
    return cl.getExe();
}
