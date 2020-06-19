#pragma once

// Although an objects supporting vmsSerializable interface can be serialized to any stream
// it can also implement vmsSerializationStoreMgr interface to provide a default way
// to serialize an instance of serializable class (for example, to/from the specified file)

// the manager also supports safe serialization (however, it's optional and depends on implementation of the manager interface)
// Save: we use secondary stream to make serialization process safe
// we serialize to secondary stream and, once succeeded, move contents of the secondary stream
// to the primary stream (here it's required for move operation to be safe; it depends on implementation)
// Load: we first try to load object state from primary stream
// in case of a error we try to load from secondary stream

class vmsSerializationStoreMgr
{
public:
	vmsSerializationStoreMgr ()
	{

	}

	virtual ~vmsSerializationStoreMgr ()
	{

	}

	// Save

	virtual std::shared_ptr <std::ostream> getSecondaryStreamReadyToSaveObject () = NULL;

	// called in case the serialization to secondary stream was successful
	// it's required for move operation to be safe (i.e. neither contents of secondary, nor primary streams could be damaged while moving in case of a failure)
	virtual bool MoveSecondaryStreamToPrimary (std::shared_ptr <std::ostream> spStm)
	{
		// implementation is recommended by not required
		// in this case the serialization goes directly to the primary stream (not safe)
		return true;
	}

	// Load

	virtual std::shared_ptr <std::istream> getPrimaryStreamReadyToLoadObject () = NULL;

	// called in case the serialization from primary stream has failed
	virtual std::shared_ptr <std::istream> getSecondaryStreamReadyToLoadObject ()
	{
		// implementation is recommended by not required
		return NULL;
	}
};


class vmsSerializationFileStoreMgr : public vmsSerializationStoreMgr
{
public:

	vmsSerializationFileStoreMgr (const std::wstring& wstrSerializationFile = L"") : m_wstrSerializationFile (wstrSerializationFile)
	{

	}

	virtual ~vmsSerializationFileStoreMgr ()
	{

	}

	void setSerializationFile (const std::wstring& wstrFile)
	{
		m_wstrSerializationFile = wstrFile;
	}

	virtual std::shared_ptr <std::ostream> getSecondaryStreamReadyToSaveObject ()
	{
		if (m_wstrSerializationFile.empty ())
			return NULL;
		return std::make_shared <std::ofstream> (getSecondarySerializationFile ().c_str (), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	}

	virtual bool MoveSecondaryStreamToPrimary (std::shared_ptr <std::ostream> spStm)
	{
		std::shared_ptr <std::ofstream> spFstm = std::dynamic_pointer_cast <std::ofstream> (spStm);
		assert (spFstm != NULL);
		if (spFstm->is_open ())
			spFstm->close ();
		_wremove (m_wstrSerializationFile.c_str ());
		return !_wrename (getSecondarySerializationFile ().c_str (), m_wstrSerializationFile.c_str ());
	}
	
	virtual std::shared_ptr <std::istream> getPrimaryStreamReadyToLoadObject ()
	{
		auto spStm = std::make_shared <std::ifstream> (m_wstrSerializationFile, std::ios_base::in | std::ios_base::binary);
		if (!spStm->good ())
			return NULL;
		return spStm;
	}

	virtual std::shared_ptr <std::istream> getSecondaryStreamReadyToLoadObject ()
	{
		auto spStm = std::make_shared <std::ifstream> (getSecondarySerializationFile ().c_str (), std::ios_base::in | std::ios_base::binary);
		if (!spStm->good ())
			return NULL;
		return spStm;
	}


protected:
	std::wstring m_wstrSerializationFile;

	std::wstring getSecondarySerializationFile () const 
	{
		return m_wstrSerializationFile + L".tmp";
	}
};