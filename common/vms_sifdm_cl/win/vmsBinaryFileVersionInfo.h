#pragma once

#include "vmsAppVersion.h"
#include "../vmsStringHelper.h"
#include "../xml/vmsXmlUtil.h"

#pragma comment (lib, "version")

class vmsBinaryFileVersionInfo : public vmsSerializable 
{
public:
	BOOL Retrieve (LPCTSTR pszFile)
	{
		m_tstrProductName = _T ("");
		m_tstrProductVersion = _T ("");
		m_appVersion.clear ();
		m_fileVersion.clear ();

		DWORD dw;
		DWORD dwSize = GetFileVersionInfoSize (pszFile, &dw);
		if (dwSize == 0)
			return FALSE;
		LPVOID pvVer = _alloca (dwSize);
		ZeroMemory (pvVer, dwSize);
		if (FALSE == GetFileVersionInfo (pszFile, 0, dwSize, pvVer))
			return FALSE;
		return ExtractVersionInfo (pvVer, dwSize);
	}

	vmsBinaryFileVersionInfo(LPCTSTR ptszFile = NULL)
	{
		if (ptszFile)
			Retrieve (ptszFile);
	}

	virtual ~vmsBinaryFileVersionInfo()
	{

	}

	tstring m_tstrCompanyName;
	tstring m_tstrFileDescription;
	tstring m_tstrFileVersion;
	tstring m_tstrInternalName;
	tstring m_tstrLegalCopyright;
	tstring m_tstrOriginalFileName;
	tstring m_tstrProductName;
	tstring m_tstrProductVersion;
	tstring m_tstrSpecialBuildDescription;

	// version from fixed version info part (non string format)
	vmsAppVersion m_appVersion, m_fileVersion;

protected:
	BOOL ExtractVersionInfo (LPVOID pvVer, DWORD dwSize)
	{
		VS_FIXEDFILEINFO *pFileInfo = NULL;
		UINT u;
		BOOL bOK = FALSE;
		if (VerQueryValue (pvVer, _T ("\\"), (LPVOID*)&pFileInfo, &u))
		{
			m_appVersion.push_back (pFileInfo->dwProductVersionMS >> 16);
			m_appVersion.push_back (pFileInfo->dwProductVersionMS & 0xffff);
			m_appVersion.push_back (pFileInfo->dwProductVersionLS >> 16);
			m_appVersion.push_back (pFileInfo->dwProductVersionLS & 0xffff);
			while (m_appVersion.size () > 2 && m_appVersion [m_appVersion.size () - 1].dwVal == 0)
				m_appVersion.erase (m_appVersion.end () - 1);

			m_fileVersion.push_back (pFileInfo->dwFileVersionMS >> 16);
			m_fileVersion.push_back (pFileInfo->dwFileVersionMS & 0xffff);
			m_fileVersion.push_back (pFileInfo->dwFileVersionLS >> 16);
			m_fileVersion.push_back (pFileInfo->dwFileVersionLS & 0xffff);
			while (m_fileVersion.size () > 2 && m_fileVersion [m_fileVersion.size () - 1].dwVal == 0)
				m_fileVersion.erase (m_fileVersion.end () - 1);

			bOK = TRUE;
		}

		struct LANGANDCODEPAGE
		{
			WORD wLanguage;
			WORD wCodePage;
		} *pTranslate = 0;

		UINT uLen;

		tstring tstrLng;

		if (FALSE == VerQueryValue (pvVer, _T ("\\VarFileInfo\\Translation"), (LPVOID*) &pTranslate, &uLen))
		{
			LPBYTE pb;
			if (FALSE == VerQueryValue (pvVer, _T ("\\"), (LPVOID*)&pb, &uLen))
				return bOK;
			VS_FIXEDFILEINFO *p = (VS_FIXEDFILEINFO*)pb;
			pb += uLen;
			// try to find "StringFileInfo" block
			const auto StringFileInfoLen = wcslen (L"StringFileInfo");
			while (DWORD (pb - (LPBYTE)pvVer) < (dwSize - (DWORD)StringFileInfoLen) && wcsncmp ((LPWSTR)pb, L"StringFileInfo", StringFileInfoLen))
				pb++;
			if (DWORD (pb - (LPBYTE)pvVer) >= (dwSize - (DWORD)StringFileInfoLen))
				return bOK; // not found
			// found, skip the header
			pb += (StringFileInfoLen + 1) * 2;
			// skip child header (https://msdn.microsoft.com/en-us/library/windows/desktop/ms646987%28v=vs.85%29.aspx)
			pb += 3*sizeof (WORD);
			// search for string with locale identifier (e.g. "040904b0")
			const int LocNameKeyLen = 8;
			const auto wcharsRemains = [&pb, &pvVer, &dwSize]()
			{
				return (dwSize - (static_cast<int>(pb - (LPBYTE)pvVer))) / 2;
			};
			const auto stringLen = [&pb, &wcharsRemains] ()
			{
				return wcsnlen ((LPWSTR)pb, wcharsRemains());
			};
			while (wcharsRemains() > LocNameKeyLen && 
				stringLen() < wcharsRemains())
			{
				while (wcharsRemains() > LocNameKeyLen && 
					stringLen() < LocNameKeyLen)
				{
					pb++;
				}
				if (wcharsRemains() <= LocNameKeyLen)
					break;
				// check if the string contains digits and letters only
				LPWSTR pwsz = (LPWSTR)pb;
				while (*pwsz && (isdigit (*pwsz) || isalpha (*pwsz)))
					pwsz++;
				if (*pwsz == 0)
				{
					// yes
					USES_CONVERSION;
					tstrLng = W2T ((LPWSTR)pb);
					break;
				}
				else
				{
					// skip this string
					pb += (stringLen()+1) * 2;
				}
			}
		}

		if (!pTranslate && tstrLng.empty())
			return bOK;

		LPCTSTR atszValueName [] = {
			_T ("ProductVersion"),
			_T ("ProductName"),
			_T ("FileDescription"),
			_T ("CompanyName"),
			_T ("FileVersion"),
			_T ("InternalName"),
			_T ("LegalCopyright"),
			_T ("OriginalFilename"),
			_T ("SpecialBuild"),
		};

		m_tstrCompanyName = _T ("");
		m_tstrFileDescription = _T ("");
		m_tstrFileVersion = _T ("");
		m_tstrInternalName = _T ("");
		m_tstrLegalCopyright = _T ("");
		m_tstrOriginalFileName = _T ("");
		m_tstrProductName = _T ("");
		m_tstrProductVersion = _T ("");
		m_tstrSpecialBuildDescription = _T ("");

		tstring* atstrValues [] = {
			&m_tstrProductVersion, &m_tstrProductName, &m_tstrFileDescription, &m_tstrCompanyName,
			&m_tstrFileVersion, &m_tstrInternalName, &m_tstrLegalCopyright,
			&m_tstrOriginalFileName, &m_tstrSpecialBuildDescription,
		};

		int nLang = 0;

		if (tstrLng.empty ())
		{
			for (int i = 0; i < (int)uLen / (int)sizeof (LANGANDCODEPAGE) ; i++)
			{
				if ((pTranslate [i].wLanguage & 0x3FF) == 9)
				{
					// English
					nLang = i;
					break;
				}
			}
		}

		for (int i = 0; i < sizeof (atszValueName) / sizeof (LPCTSTR); i++)
		{
			TCHAR tsz [200];
			if (tstrLng.empty ())
			{
				swprintf (tsz, _countof (tsz), _T ("\\StringFileInfo\\%04x%04x\\%s"), pTranslate [nLang].wLanguage,
					pTranslate [nLang].wCodePage, atszValueName [i]);
			}
			else
			{
				swprintf (tsz, _countof (tsz), _T ("\\StringFileInfo\\%s\\%s"), tstrLng.c_str (), atszValueName [i]);
			}
			LPVOID pvValue;
			UINT uValLen;
			if (FALSE == VerQueryValue (pvVer, tsz, &pvValue, &uValLen))
			{
				if (tstrLng.empty () && pTranslate [nLang].wLanguage == 0)
				{
					pTranslate [nLang].wLanguage = 0x0409;
					i--;
				}
				continue;
			}

			atstrValues [i]->assign (
				vmsStringHelper::RemoveBadCharacters((LPCTSTR)pvValue).c_str ());
		}

		if (m_tstrProductVersion.empty ())
		{
			m_tstrProductVersion = m_appVersion.ToString ();
		}
		else
		{
			for (size_t i = 0; i < m_tstrProductVersion.length (); i++)
			{
				if (m_tstrProductVersion [i] == ',')
					m_tstrProductVersion [i] = '.';

				if (m_tstrProductVersion [i] == '.')
				{
					while (i+1 < m_tstrProductVersion.length () && m_tstrProductVersion [i+1] == ' ')
						m_tstrProductVersion.erase (m_tstrProductVersion.begin () + i + 1);
				}
			}
		}

		return TRUE;
	}

public:
	virtual bool Serialize (vmsSerializationIoStream *pStm, unsigned flags = 0) override
	{
		std::wstring wstrAppVersion, wstrFileVersion;

		if (pStm->isOutputStream ())
		{
			wstrAppVersion = m_appVersion.ToString ();
			wstrFileVersion = m_fileVersion.ToString ();
		}

		if (!(pStm->SerializeValue (L"ProductName", m_tstrProductName) &&
				pStm->SerializeValue (L"ProductVersion", m_tstrProductVersion) &&
				pStm->SerializeValue (L"ProductVersionDigit", wstrAppVersion) &&
				pStm->SerializeValue (L"FileVersion", m_tstrFileVersion) &&
				pStm->SerializeValue (L"FileVersionDigit", wstrFileVersion) &&
				pStm->SerializeValue (L"FileDescription", m_tstrFileDescription) &&
				pStm->SerializeValue (L"InternalName", m_tstrInternalName) &&
				pStm->SerializeValue (L"LegalCopyright", m_tstrLegalCopyright) &&
				pStm->SerializeValue (L"OriginalFilename", m_tstrOriginalFileName) &&
				pStm->SerializeValue (L"CompanyName", m_tstrCompanyName) &&
				pStm->SerializeValue (L"SpecialBuild", m_tstrSpecialBuildDescription)))
			return false;

		if (pStm->isInputStream ())
		{
			m_appVersion.FromString (wstrAppVersion.c_str ());
			m_fileVersion.FromString (wstrFileVersion.c_str ());
		}

		return true;
	}

	virtual bool Serialize (vmsSerializationOutputStream *pStm) 
	{
		pStm->WriteValue (L"ProductName", m_tstrProductName, false);
		pStm->WriteValue (L"ProductVersion", m_tstrProductVersion, false);
		pStm->WriteValue (L"ProductVersionDigit", m_appVersion.ToString (), false);
		pStm->WriteValue (L"FileVersion", m_tstrFileVersion, false);
		pStm->WriteValue (L"FileVersionDigit", m_fileVersion.ToString (), false);
		pStm->WriteValue (L"FileDescription", m_tstrFileDescription, false);
		pStm->WriteValue (L"InternalName", m_tstrInternalName, false);
		pStm->WriteValue (L"LegalCopyright", m_tstrLegalCopyright, false);
		pStm->WriteValue (L"OriginalFilename", m_tstrOriginalFileName, false);
		pStm->WriteValue (L"CompanyName", m_tstrCompanyName, false);
		pStm->WriteValue (L"SpecialBuild", m_tstrSpecialBuildDescription, false);
		return true;
	}

	virtual bool Serialize (vmsSerializationInputStream *pStm) 
	{
		std::wstring wstr;
		pStm->ReadValue (L"ProductName", m_tstrProductName, false);
		pStm->ReadValue (L"ProductVersion", m_tstrProductVersion, false);
		if (pStm->ReadValue (L"ProductVersionDigit", wstr, false))
			m_appVersion.FromString (wstr.c_str ());
		pStm->ReadValue (L"FileVersion", m_tstrFileVersion, false);
		if (pStm->ReadValue (L"FileVersionDigit", wstr, false))
			m_fileVersion.FromString (wstr.c_str ());
		pStm->ReadValue (L"FileDescription", m_tstrFileDescription, false);
		pStm->ReadValue (L"InternalName", m_tstrInternalName, false);
		pStm->ReadValue (L"LegalCopyright", m_tstrLegalCopyright, false);
		pStm->ReadValue (L"OriginalFilename", m_tstrOriginalFileName, false);
		pStm->ReadValue (L"CompanyName", m_tstrCompanyName, false);
		pStm->ReadValue (L"SpecialBuild", m_tstrSpecialBuildDescription, false);

		// compatibility with old versions (older than build 750).
		if (m_appVersion.empty ())
			m_appVersion.FromString (m_tstrProductVersion.c_str ());
		if (m_fileVersion.empty ())
			m_fileVersion.FromString (m_tstrFileVersion.c_str ());

		return true;
	}
};

