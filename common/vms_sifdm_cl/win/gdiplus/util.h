#pragma once

/*
The function GetEncoderClsid in the following example receives the MIME type of an encoder and returns the class identifier (CLSID) of that encoder. The MIME types of the encoders built into Windows GDI+ are as follows:

image/bmp
image/jpeg
image/gif
image/tiff
image/png

The function calls GetImageEncoders to get an array of ImageCodecInfo objects. If one of the ImageCodecInfo objects in that array represents the requested encoder, the function returns the index of the ImageCodecInfo object and copies the CLSID into the variable pointed to by pClsid. If the function fails, it returns –1.

(http://msdn.microsoft.com/en-us/library/windows/desktop/ms533843%28v=vs.85%29.aspx)

(c) Microsoft.
*/
inline int vmsGdipGetEncoderClsid (const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize (&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}


inline Gdiplus::Status vmsGdipSaveBitmapToFile (Gdiplus::Bitmap* bmp, const std::wstring& wstrFile, const std::wstring& formatMIME = L"image/png")
{
	CLSID encoderClsid;
	if (-1 == vmsGdipGetEncoderClsid (formatMIME.c_str (), &encoderClsid))
		return Gdiplus::GenericError;
	return bmp->Save (wstrFile.c_str (), &encoderClsid, nullptr);
}


inline Gdiplus::RectF vmsGdipRectfFromWinRect (const vmsWinRect& rc)
{
	return Gdiplus::RectF ((float)rc.left, (float)rc.top, 
		(float)rc.Width (), (float)rc.Height ());
}


inline Gdiplus::FontFamily* vmsGdipFindFontByName (
	const Gdiplus::PrivateFontCollection& fc, 
	const std::wstring& name)
{
	INT count = fc.GetFamilyCount ();
	assert (count);
	if (!count)
		return nullptr;
	std::unique_ptr <Gdiplus::FontFamily []> ffs (new Gdiplus::FontFamily [count]);
	INT tmp;
	fc.GetFamilies (count, ffs.get (), &tmp);
	assert (tmp == count);
	for (INT i = 0; i < count; ++i)
	{
		WCHAR fn [LF_FACESIZE] = L"";
		ffs [i].GetFamilyName (fn);
		if (!_wcsicmp (name.c_str (), fn))
			return ffs [i].Clone ();
	}
	return nullptr;
}