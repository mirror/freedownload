/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

#pragma once
class vmsAppGenericInfo : 
	public vmsSerializable
{
public:
	std::wstring m_appGuid;

	bool Serialize(vmsSerializationIoStream *pStm, 
		unsigned flags = 0) override
	{
		return pStm->SerializeValue(L"appGuid", m_appGuid);
	}
};

