#pragma once

#include "vmsSerializationStoreMgr.h"
#include "vmsSerializationStreamBinding.h"

class vmsSerializer 
{
public:

	static inline bool Serialize (vmsSerializable *pObject, vmsSerializationStoreMgr *pSerializationStore, vmsSerializationInputStream *pSerializationStm)
	{
		assert (pObject != NULL);
		assert (pSerializationStore != NULL);
		assert (pSerializationStm != NULL);

		if (!pObject || !pSerializationStore || !pSerializationStm)
			return false;

		// we may fail to load due to stream store absence (i.e. the object was not saved before)
		// this case is not a error
		bool bErrorOccured = false;

		vmsSerializationInputStreamBinding *pSerializationStmBinding = dynamic_cast <vmsSerializationInputStreamBinding*> (pSerializationStm);
		assert (pSerializationStmBinding != NULL);
		if (!pSerializationStmBinding)
			return false;

		auto spStm = pSerializationStore->getPrimaryStreamReadyToLoadObject ();
		if (spStm)
		{
			if (pSerializationStmBinding->BindToStream (spStm))
			{
				bool bResult = pObject->Serialize (pSerializationStm);
				pSerializationStmBinding->BindToStream (NULL);
				if (bResult)
					return true;
			}
			bErrorOccured = true;
		}

		spStm = pSerializationStore->getSecondaryStreamReadyToLoadObject ();
		if (spStm)
		{
			if (pSerializationStmBinding->BindToStream (spStm))
			{
				bool bResult = pObject->Serialize (pSerializationStm);
				pSerializationStmBinding->BindToStream (NULL);
				if (bResult)
					return true;
			}
			bErrorOccured = true;
		}

		return !bErrorOccured;
	}

	static inline bool Serialize (vmsSerializable *pObject, vmsSerializationStoreMgr *pSerializationStore, vmsSerializationOutputStream *pSerializationStm)
	{
		assert (pObject != NULL);
		assert (pSerializationStore != NULL);
		assert (pSerializationStm != NULL);

		if (!pObject || !pSerializationStore || !pSerializationStm)
			return false;

		vmsSerializationOutputStreamBinding *pSerializationStmBinding = dynamic_cast <vmsSerializationOutputStreamBinding*> (pSerializationStm);
		assert (pSerializationStmBinding != NULL);
		if (!pSerializationStmBinding)
			return false;

		bool bSetDirtyOnError = false;

		auto spStm = pSerializationStore->getSecondaryStreamReadyToSaveObject ();
		if (spStm)
		{
			if (pSerializationStmBinding->BindToStream (spStm))
			{
				bSetDirtyOnError = pObject->isDirty ();
				pObject->setDirty (false); // remove dirty flag before save
				// if save will fail - we'll restore it
				// if save will succeed - object will be not dirty or it will in case some modifications were made on object during save
				bool bResult = pObject->Serialize (pSerializationStm) && pSerializationStmBinding->Flush () && 
					pSerializationStore->MoveSecondaryStreamToPrimary (spStm);
				pSerializationStmBinding->BindToStream (NULL);
				if (bResult)
					return true;
			}
		}

		if (bSetDirtyOnError)
			pObject->setDirty (true);

		return false;
	}
};