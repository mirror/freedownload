#pragma once

/*
********** Author : Mohammed Nisamudheen S.  **********
********** Email  : nizam_clt@rediffmail.com **********
********** Date   : 12.4.2005                **********
********** URL    : www.uslindia.com         **********
*/

//The following structures are taken from iconpro sdk example

#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
	BYTE	bWidth;               // Width of the image
	BYTE	bHeight;              // Height of the image (times 2)
	BYTE	bColorCount;          // Number of colors in image (0 if >=8bpp)
	BYTE	bReserved;            // Reserved
	WORD	wPlanes;              // Color Planes
	WORD	wBitCount;            // Bits per pixel
	DWORD	dwBytesInRes;         // how many bytes in this resource?
	WORD	nID;                  // the ID
} MEMICONDIRENTRY, *LPMEMICONDIRENTRY;
typedef struct
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
	MEMICONDIRENTRY	idEntries [1]; // the entries for each image
} MEMICONDIR, *LPMEMICONDIR;
#pragma pack( pop )

typedef struct
{
	UINT			Width, Height, Colors; // Width, Height and bpp
	LPBYTE			lpBits;                // ptr to DIB bits
	DWORD			dwNumBytes;            // how many bytes?
	LPBITMAPINFO	lpbi;                  // ptr to header
	LPBYTE			lpXOR;                 // ptr to XOR image bits
	LPBYTE			lpAND;                 // ptr to AND image bits
} ICONIMAGE, *LPICONIMAGE;
typedef struct
{
	BOOL		bHasChanged;                     // Has image changed?
	UINT		nNumImages;                      // How many images?
	ICONIMAGE	IconImages [1];                   // Image entries
} ICONRESOURCE, *LPICONRESOURCE;


// These next two structs represent how the icon information is stored
// in an ICO file.
typedef struct
{
	BYTE	bWidth;               // Width of the image
	BYTE	bHeight;              // Height of the image (times 2)
	BYTE	bColorCount;          // Number of colors in image (0 if >=8bpp)
	BYTE	bReserved;            // Reserved
	WORD	wPlanes;              // Color Planes
	WORD	wBitCount;            // Bits per pixel
	DWORD	dwBytesInRes;         // how many bytes in this resource?
	DWORD	dwImageOffset;        // where in the file is this image
} ICONDIRENTRY, *LPICONDIRENTRY;
typedef struct
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
	ICONDIRENTRY	idEntries [1]; // the entries for each image
} ICONDIR, *LPICONDIR;


#define ICON_EXCTRACTOR_WIDTHBYTES(bits)      ((((bits) + 31)>>5)<<2)


class CIconExtractor
{

public:

	/****************************************************************************
*
*     FUNCTION: ExtractIconFromExe
*
*     PURPOSE:  Extracts the specified icon usualy the application icon
*
*     PARAMS:   LPCSTR      SourceEXE    - the source exe
*               LPCSTR      TargetICON   - name of the icon file
*               UINT        IconIndex    - icon index < MAX_ICONS
*
*     RETURNS:  DWORD - Indicates the error code
*
*     History:
*
*               April 2005 - Created
*
\****************************************************************************/

	DWORD ExtractIconFromExe (LPCTSTR SourceEXE,
		LPCTSTR TargetICON,
		int IconIndex)
	{
		LPICONRESOURCE      lpIR = NULL;
		HINSTANCE        	hLibrary;
		DWORD               ret;

		//assert(IconIndex < MAX_ICONS);

		// Load the EXE - NOTE: must be a 32bit EXE for this to work
		if ((hLibrary = LoadLibraryEx (SourceEXE, NULL, LOAD_LIBRARY_AS_DATAFILE)) == NULL)
			return GetLastError ();

		HRSRC        	hRsrc = NULL;
		HGLOBAL        	hGlobal = NULL;
		LPMEMICONDIR    lpIcon = NULL;
		//UINT i;

		m_vIconsInfo.clear ();
		ret = EnumResourceNames (hLibrary, RT_GROUP_ICON, EnumResNameProc, (LONG_PTR)this);

		if (!ret)
		{
			ret = GetLastError ();
			FreeLibrary (hLibrary);
			return ret;
		}

		if (IconIndex < 0)
		{
			IconIndex *= -1;

			size_t i = 0;
			for (; i < m_vIconsInfo.size (); i++)
			{
				if (m_vIconsInfo [i].strIconName.empty () && m_vIconsInfo [i].uIconID == IconIndex)
					break;
			}
			if (i != m_vIconsInfo.size ())
				IconIndex = (int)i;
			else
				IconIndex = 0;
		}
		else
		{
			assert (IconIndex < (int)m_vIconsInfo.size ());
			if (IconIndex >= (int)m_vIconsInfo.size ())
				IconIndex = 0;
		}

		if ((int)m_vIconsInfo.size () > IconIndex)
		{
			// Find the group icon resource
			//Finding the resource with the ID first

			if (m_vIconsInfo [IconIndex].strIconName.empty ())
				hRsrc = FindResource (hLibrary, MAKEINTRESOURCE (m_vIconsInfo [IconIndex].uIconID), RT_GROUP_ICON);
			else
				hRsrc = FindResource (hLibrary, m_vIconsInfo [IconIndex].strIconName.c_str (), RT_GROUP_ICON);
		}


		if (hRsrc == NULL)
		{
			ret = GetLastError ();
			FreeLibrary (hLibrary);
			return ret;
		}

		if (SizeofResource (hLibrary, hRsrc) < sizeof (MEMICONDIR))
		{
			FreeLibrary (hLibrary);
			return E_UNEXPECTED;
		}

		if ((hGlobal = LoadResource (hLibrary, hRsrc)) == NULL)
		{
			ret = GetLastError ();
			FreeLibrary (hLibrary);
			return ret;
		}
		if ((lpIcon = (LPMEMICONDIR)LockResource (hGlobal)) == NULL)
		{
			ret = GetLastError ();
			FreeLibrary (hLibrary);
			return ret;
		}

		if (IsBadReadPtr (lpIcon, sizeof (MEMICONDIR)))
		{
			FreeLibrary (hLibrary);
			return E_UNEXPECTED;
		}

		// Allocate enough memory for the images
		if ((lpIR = (LPICONRESOURCE)malloc (sizeof (ICONRESOURCE) + ((lpIcon->idCount - 1) * sizeof (ICONIMAGE)))) == NULL)
		{
			ret = GetLastError ();
			FreeLibrary (hLibrary);
			return ret;
		}


		// Fill in local struct members
		lpIR->nNumImages = lpIcon->idCount;


		// Loop through the images
		for (UINT i = 0; i < lpIR->nNumImages; i++)
		{
			// Get the individual image
			if ((hRsrc = FindResource (hLibrary, MAKEINTRESOURCE (lpIcon->idEntries [i].nID), RT_ICON)) == NULL)
			{
				ret = GetLastError ();
				FreeLibrary (hLibrary);
				free (lpIR);
				return ret;
			}
			if ((hGlobal = LoadResource (hLibrary, hRsrc)) == NULL)
			{
				ret = GetLastError ();
				FreeLibrary (hLibrary);
				free (lpIR);
				return ret;
			}
			// Store a copy of the resource locally
			lpIR->IconImages [i].dwNumBytes = SizeofResource (hLibrary, hRsrc);

			lpIR->IconImages [i].lpBits = (LPBYTE)malloc (lpIR->IconImages [i].dwNumBytes);
			if (lpIR->IconImages [i].lpBits == NULL)
			{
				ret = GetLastError ();
				free (lpIR);
				return ret;
			}

			memcpy (lpIR->IconImages [i].lpBits, LockResource (hGlobal), lpIR->IconImages [i].dwNumBytes);

			// Adjust internal pointers
			if (!AdjustIconImagePointers (&(lpIR->IconImages [i])))
			{
				ret = GetLastError ();
				FreeLibrary (hLibrary);
				free (lpIR);
				return ret;
			}
		}

		FreeLibrary (hLibrary);
		ret = WriteIconToICOFile (lpIR, TargetICON);

		free (lpIR);
		return (ret);
	}

	CIconExtractor ()
	{
	}


protected:
	BOOL AddResource (LPCTSTR lpszType, LPTSTR lpszName)
	{
		if (lpszType == RT_GROUP_ICON)
		{
			__inc_IconInfo icon;

			if ((ULONG)lpszName < 65536)//ID
				icon.uIconID = (ULONG)lpszName;
			else //NAME
				icon.strIconName = lpszName;

			m_vIconsInfo.push_back (icon);
		}

		return TRUE;
	}

private:
	DWORD WriteIconToICOFile (LPICONRESOURCE lpIR, LPCTSTR szFileName)
	{
		HANDLE    	hFile;
		UINT        i;
		DWORD    	dwBytesWritten;
		DWORD		ret = 0;

		// open the file
		if ((hFile = CreateFile (szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
			return GetLastError ();

		// Write the header
		if (WriteICOHeader (hFile, lpIR->nNumImages))
		{
			ret = GetLastError ();
			CloseHandle (hFile);
			return ret;
		}
		// Write the ICONDIRENTRY's
		for (i = 0; i < lpIR->nNumImages; i++)
		{
			ICONDIRENTRY    ide;

			// Convert internal format to ICONDIRENTRY
			ide.bWidth = lpIR->IconImages [i].Width;
			ide.bHeight = lpIR->IconImages [i].Height;
			ide.bReserved = 0;
			ide.wPlanes = lpIR->IconImages [i].lpbi->bmiHeader.biPlanes;
			ide.wBitCount = lpIR->IconImages [i].lpbi->bmiHeader.biBitCount;
			if ((ide.wPlanes * ide.wBitCount) >= 8)
				ide.bColorCount = 0;
			else
				ide.bColorCount = 1 << (ide.wPlanes * ide.wBitCount);
			ide.dwBytesInRes = lpIR->IconImages [i].dwNumBytes;
			ide.dwImageOffset = CalculateImageOffset (lpIR, i);

			// Write the ICONDIRENTRY out to disk
			if (!WriteFile (hFile, &ide, sizeof (ICONDIRENTRY), &dwBytesWritten, NULL))
				return GetLastError ();

			// Did we write a full ICONDIRENTRY ?
			if (dwBytesWritten != sizeof (ICONDIRENTRY))
				return GetLastError ();
		}
		// Write the image bits for each image
		for (i = 0; i < lpIR->nNumImages; i++)
		{
			DWORD dwTemp = lpIR->IconImages [i].lpbi->bmiHeader.biSizeImage;

			// Set the sizeimage member to zero
			lpIR->IconImages [i].lpbi->bmiHeader.biSizeImage = 0;
			// Write the image bits to file
			if (!WriteFile (hFile, lpIR->IconImages [i].lpBits, lpIR->IconImages [i].dwNumBytes, &dwBytesWritten, NULL))
				return GetLastError ();

			if (dwBytesWritten != lpIR->IconImages [i].dwNumBytes)
				return GetLastError ();

			// set it back
			lpIR->IconImages [i].lpbi->bmiHeader.biSizeImage = dwTemp;
		}
		CloseHandle (hFile);
		return NO_ERROR;
	}

	BOOL AdjustIconImagePointers (LPICONIMAGE lpImage)
	{
		// Sanity check
		if (lpImage == NULL)
			return FALSE;
		// BITMAPINFO is at beginning of bits
		lpImage->lpbi = (LPBITMAPINFO)lpImage->lpBits;
		// Width - simple enough
		lpImage->Width = lpImage->lpbi->bmiHeader.biWidth;
		// Icons are stored in funky format where height is doubled - account for it
		lpImage->Height = (lpImage->lpbi->bmiHeader.biHeight) / 2;
		// How many colors?
		lpImage->Colors = lpImage->lpbi->bmiHeader.biPlanes * lpImage->lpbi->bmiHeader.biBitCount;
		// XOR bits follow the header and color table
		lpImage->lpXOR = (PBYTE)FindDIBBits ((LPSTR)lpImage->lpbi);
		// AND bits follow the XOR bits
		lpImage->lpAND = lpImage->lpXOR + (lpImage->Height*BytesPerLine ((LPBITMAPINFOHEADER)(lpImage->lpbi)));
		return TRUE;
	}

	LPSTR FindDIBBits (LPSTR lpbi)
	{
		return ( lpbi + *(LPDWORD)lpbi + PaletteSize( lpbi ) );
	}

	WORD DIBNumColors (LPSTR lpbi)
	{
		WORD wBitCount;
		DWORD dwClrUsed;

		dwClrUsed = ((LPBITMAPINFOHEADER)lpbi)->biClrUsed;

		if (dwClrUsed)
			return (WORD)dwClrUsed;

		wBitCount = ((LPBITMAPINFOHEADER)lpbi)->biBitCount;

		switch (wBitCount)
		{
		case 1: return 2;
		case 4: return 16;
		case 8:	return 256;
		default:return 0;
		}
		return 0;
	}

	WORD PaletteSize (LPSTR lpbi)
	{
		return ( DIBNumColors( lpbi ) * sizeof( RGBQUAD ) );
	}

	DWORD BytesPerLine (LPBITMAPINFOHEADER lpBMIH)
	{
		return ICON_EXCTRACTOR_WIDTHBYTES(lpBMIH->biWidth * lpBMIH->biPlanes * lpBMIH->biBitCount);
	}

	DWORD WriteICOHeader (HANDLE hFile, UINT nNumEntries)
	{
		WORD    Output;
		DWORD	dwBytesWritten;

		// Write 'reserved' WORD
		Output = 0;
		if (!WriteFile (hFile, &Output, sizeof (WORD), &dwBytesWritten, NULL))
			return GetLastError ();
		// Did we write a WORD?
		if (dwBytesWritten != sizeof (WORD))
			return GetLastError ();
		// Write 'type' WORD (1)
		Output = 1;
		if (!WriteFile (hFile, &Output, sizeof (WORD), &dwBytesWritten, NULL))
			return GetLastError ();
		// Did we write a WORD?
		if (dwBytesWritten != sizeof (WORD))
			return GetLastError ();
		// Write Number of Entries
		Output = (WORD)nNumEntries;
		if (!WriteFile (hFile, &Output, sizeof (WORD), &dwBytesWritten, NULL))
			return GetLastError ();
		// Did we write a WORD?
		if (dwBytesWritten != sizeof (WORD))
			return GetLastError ();

		return NO_ERROR;
	}

	DWORD CalculateImageOffset (LPICONRESOURCE lpIR, UINT nIndex)
	{
		DWORD	dwSize;
		UINT    i;

		// Calculate the ICO header size
		dwSize = 3 * sizeof (WORD);
		// Add the ICONDIRENTRY's
		dwSize += lpIR->nNumImages * sizeof (ICONDIRENTRY);
		// Add the sizes of the previous images
		for (i = 0; i < nIndex; i++)
			dwSize += lpIR->IconImages [i].dwNumBytes;
		// we're there - return the number
		return dwSize;
	}

	struct __inc_IconInfo {
		ULONG uIconID; //valid if icon name is empty
		std::wstring strIconName;
	};
	std::vector <__inc_IconInfo> m_vIconsInfo;

	BOOL static CALLBACK EnumResNameProc (
		HMODULE hModule,   // module handle
		LPCTSTR lpszType,  // resource type
		LPTSTR lpszName,   // resource name
		LONG_PTR lParam)    // application-defined parameter
	{
		CIconExtractor *ptr = (CIconExtractor*)lParam;
		return ptr->AddResource (lpszType, lpszName);
	}
};
