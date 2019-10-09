/*
  Free Download Manager Copyright (c) 2003-2016 FreeDownloadManager.ORG
*/

 

#pragma warning( disable: 4049 )  

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif 

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif 

#ifndef __Fdm_h__
#define __Fdm_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

 

#ifndef __IWGUrlReceiver_FWD_DEFINED__
#define __IWGUrlReceiver_FWD_DEFINED__
typedef interface IWGUrlReceiver IWGUrlReceiver;

#endif 	

#ifndef __IWGUrlListReceiver_FWD_DEFINED__
#define __IWGUrlListReceiver_FWD_DEFINED__
typedef interface IWGUrlListReceiver IWGUrlListReceiver;

#endif 	

#ifndef __IFdmFlvDownload_FWD_DEFINED__
#define __IFdmFlvDownload_FWD_DEFINED__
typedef interface IFdmFlvDownload IFdmFlvDownload;

#endif 	

#ifndef __IFDM_FWD_DEFINED__
#define __IFDM_FWD_DEFINED__
typedef interface IFDM IFDM;

#endif 	

#ifndef __IFDMDownload_FWD_DEFINED__
#define __IFDMDownload_FWD_DEFINED__
typedef interface IFDMDownload IFDMDownload;

#endif 	

#ifndef __IFDMDownloadsStat_FWD_DEFINED__
#define __IFDMDownloadsStat_FWD_DEFINED__
typedef interface IFDMDownloadsStat IFDMDownloadsStat;

#endif 	

#ifndef __IFdmTorrentFilesRcvr_FWD_DEFINED__
#define __IFdmTorrentFilesRcvr_FWD_DEFINED__
typedef interface IFdmTorrentFilesRcvr IFdmTorrentFilesRcvr;

#endif 	

#ifndef __IFDMFlashVideoDownloads_FWD_DEFINED__
#define __IFDMFlashVideoDownloads_FWD_DEFINED__
typedef interface IFDMFlashVideoDownloads IFDMFlashVideoDownloads;

#endif 	

#ifndef __IFdmUiWindow_FWD_DEFINED__
#define __IFdmUiWindow_FWD_DEFINED__
typedef interface IFdmUiWindow IFdmUiWindow;

#endif 	

#ifndef __WGUrlReceiver_FWD_DEFINED__
#define __WGUrlReceiver_FWD_DEFINED__

#ifdef __cplusplus
typedef class WGUrlReceiver WGUrlReceiver;
#else
typedef struct WGUrlReceiver WGUrlReceiver;
#endif 

#endif 	

#ifndef __WGUrlListReceiver_FWD_DEFINED__
#define __WGUrlListReceiver_FWD_DEFINED__

#ifdef __cplusplus
typedef class WGUrlListReceiver WGUrlListReceiver;
#else
typedef struct WGUrlListReceiver WGUrlListReceiver;
#endif 

#endif 	

#ifndef __FdmFlvDownload_FWD_DEFINED__
#define __FdmFlvDownload_FWD_DEFINED__

#ifdef __cplusplus
typedef class FdmFlvDownload FdmFlvDownload;
#else
typedef struct FdmFlvDownload FdmFlvDownload;
#endif 

#endif 	

#ifndef __FDM_FWD_DEFINED__
#define __FDM_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDM FDM;
#else
typedef struct FDM FDM;
#endif 

#endif 	

#ifndef __FDMDownloadsStat_FWD_DEFINED__
#define __FDMDownloadsStat_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDMDownloadsStat FDMDownloadsStat;
#else
typedef struct FDMDownloadsStat FDMDownloadsStat;
#endif 

#endif 	

#ifndef __FDMDownload_FWD_DEFINED__
#define __FDMDownload_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDMDownload FDMDownload;
#else
typedef struct FDMDownload FDMDownload;
#endif 

#endif 	

#ifndef __FDMUploader_FWD_DEFINED__
#define __FDMUploader_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDMUploader FDMUploader;
#else
typedef struct FDMUploader FDMUploader;
#endif 

#endif 	

#ifndef __FDMUploadPackage_FWD_DEFINED__
#define __FDMUploadPackage_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDMUploadPackage FDMUploadPackage;
#else
typedef struct FDMUploadPackage FDMUploadPackage;
#endif 

#endif 	

#ifndef __FdmTorrentFilesRcvr_FWD_DEFINED__
#define __FdmTorrentFilesRcvr_FWD_DEFINED__

#ifdef __cplusplus
typedef class FdmTorrentFilesRcvr FdmTorrentFilesRcvr;
#else
typedef struct FdmTorrentFilesRcvr FdmTorrentFilesRcvr;
#endif 

#endif 	

#ifndef __FDMFlashVideoDownloads_FWD_DEFINED__
#define __FDMFlashVideoDownloads_FWD_DEFINED__

#ifdef __cplusplus
typedef class FDMFlashVideoDownloads FDMFlashVideoDownloads;
#else
typedef struct FDMFlashVideoDownloads FDMFlashVideoDownloads;
#endif 

#endif 	

#ifndef __FdmUiWindow_FWD_DEFINED__
#define __FdmUiWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class FdmUiWindow FdmUiWindow;
#else
typedef struct FdmUiWindow FdmUiWindow;
#endif 

#endif 	

#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

#ifndef __IWGUrlReceiver_INTERFACE_DEFINED__
#define __IWGUrlReceiver_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IWGUrlReceiver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("454A4044-16EC-4D64-9069-C5B8832B7B55")
    IWGUrlReceiver : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_Url( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Url( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ShowAddDownloadDialog( void) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ShowAddPageDownloadDialog( void) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Comment( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Comment( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Referer( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Referer( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE AddDownload( void) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_CheckExtension( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_CheckExtension( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_IgnoreSize( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_IgnoreSize( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_UseSkipExtsList( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_UseSkipExtsList( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_UIState( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_ForceSilent( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_ForceSilent( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Cookies( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Cookies( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_PostData( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_PostData( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_ForceSilentEx( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_ForceSilentEx( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_ForceDownloadAutoStart( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_ForceDownloadAutoStart( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_DisableMaliciousChecking( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_DisableMaliciousChecking( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_DisableURLExistsCheck( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_DisableURLExistsCheck( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_FileName( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_FileName( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_FlashVideoDownload( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_FlashVideoDownload( 
             BOOL newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_FileSize( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_FileSize( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_OriginalURL( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_OriginalURL( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_UserAgent( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_UserAgent( 
             BSTR newVal) = 0;
        
    };
    
    
#else 	

    typedef struct IWGUrlReceiverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWGUrlReceiver * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWGUrlReceiver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWGUrlReceiver * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWGUrlReceiver * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWGUrlReceiver * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWGUrlReceiver * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWGUrlReceiver * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *ShowAddDownloadDialog )( 
            IWGUrlReceiver * This);
        
         HRESULT ( STDMETHODCALLTYPE *ShowAddPageDownloadDialog )( 
            IWGUrlReceiver * This);
        
         HRESULT ( STDMETHODCALLTYPE *get_Comment )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Comment )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_Referer )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Referer )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *AddDownload )( 
            IWGUrlReceiver * This);
        
         HRESULT ( STDMETHODCALLTYPE *get_CheckExtension )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_CheckExtension )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_IgnoreSize )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_IgnoreSize )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_UseSkipExtsList )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_UseSkipExtsList )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_UIState )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_ForceSilent )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_ForceSilent )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_Cookies )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Cookies )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_PostData )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_PostData )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_ForceSilentEx )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_ForceSilentEx )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_ForceDownloadAutoStart )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_ForceDownloadAutoStart )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_DisableMaliciousChecking )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_DisableMaliciousChecking )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_DisableURLExistsCheck )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_DisableURLExistsCheck )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_FileName )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_FlashVideoDownload )( 
            IWGUrlReceiver * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_FlashVideoDownload )( 
            IWGUrlReceiver * This,
             BOOL newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_FileSize )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_FileSize )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_OriginalURL )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_OriginalURL )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_UserAgent )( 
            IWGUrlReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_UserAgent )( 
            IWGUrlReceiver * This,
             BSTR newVal);
        
        END_INTERFACE
    } IWGUrlReceiverVtbl;

    interface IWGUrlReceiver
    {
        CONST_VTBL struct IWGUrlReceiverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IWGUrlReceiver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWGUrlReceiver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWGUrlReceiver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IWGUrlReceiver_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWGUrlReceiver_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWGUrlReceiver_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWGUrlReceiver_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IWGUrlReceiver_get_Url(This,pVal)	\
    ( (This)->lpVtbl -> get_Url(This,pVal) ) 

#define IWGUrlReceiver_put_Url(This,newVal)	\
    ( (This)->lpVtbl -> put_Url(This,newVal) ) 

#define IWGUrlReceiver_ShowAddDownloadDialog(This)	\
    ( (This)->lpVtbl -> ShowAddDownloadDialog(This) ) 

#define IWGUrlReceiver_ShowAddPageDownloadDialog(This)	\
    ( (This)->lpVtbl -> ShowAddPageDownloadDialog(This) ) 

#define IWGUrlReceiver_get_Comment(This,pVal)	\
    ( (This)->lpVtbl -> get_Comment(This,pVal) ) 

#define IWGUrlReceiver_put_Comment(This,newVal)	\
    ( (This)->lpVtbl -> put_Comment(This,newVal) ) 

#define IWGUrlReceiver_get_Referer(This,pVal)	\
    ( (This)->lpVtbl -> get_Referer(This,pVal) ) 

#define IWGUrlReceiver_put_Referer(This,newVal)	\
    ( (This)->lpVtbl -> put_Referer(This,newVal) ) 

#define IWGUrlReceiver_AddDownload(This)	\
    ( (This)->lpVtbl -> AddDownload(This) ) 

#define IWGUrlReceiver_get_CheckExtension(This,pVal)	\
    ( (This)->lpVtbl -> get_CheckExtension(This,pVal) ) 

#define IWGUrlReceiver_put_CheckExtension(This,newVal)	\
    ( (This)->lpVtbl -> put_CheckExtension(This,newVal) ) 

#define IWGUrlReceiver_get_IgnoreSize(This,pVal)	\
    ( (This)->lpVtbl -> get_IgnoreSize(This,pVal) ) 

#define IWGUrlReceiver_put_IgnoreSize(This,newVal)	\
    ( (This)->lpVtbl -> put_IgnoreSize(This,newVal) ) 

#define IWGUrlReceiver_get_UseSkipExtsList(This,pVal)	\
    ( (This)->lpVtbl -> get_UseSkipExtsList(This,pVal) ) 

#define IWGUrlReceiver_put_UseSkipExtsList(This,newVal)	\
    ( (This)->lpVtbl -> put_UseSkipExtsList(This,newVal) ) 

#define IWGUrlReceiver_get_UIState(This,pVal)	\
    ( (This)->lpVtbl -> get_UIState(This,pVal) ) 

#define IWGUrlReceiver_get_ForceSilent(This,pVal)	\
    ( (This)->lpVtbl -> get_ForceSilent(This,pVal) ) 

#define IWGUrlReceiver_put_ForceSilent(This,newVal)	\
    ( (This)->lpVtbl -> put_ForceSilent(This,newVal) ) 

#define IWGUrlReceiver_get_Cookies(This,pVal)	\
    ( (This)->lpVtbl -> get_Cookies(This,pVal) ) 

#define IWGUrlReceiver_put_Cookies(This,newVal)	\
    ( (This)->lpVtbl -> put_Cookies(This,newVal) ) 

#define IWGUrlReceiver_get_PostData(This,pVal)	\
    ( (This)->lpVtbl -> get_PostData(This,pVal) ) 

#define IWGUrlReceiver_put_PostData(This,newVal)	\
    ( (This)->lpVtbl -> put_PostData(This,newVal) ) 

#define IWGUrlReceiver_get_ForceSilentEx(This,pVal)	\
    ( (This)->lpVtbl -> get_ForceSilentEx(This,pVal) ) 

#define IWGUrlReceiver_put_ForceSilentEx(This,newVal)	\
    ( (This)->lpVtbl -> put_ForceSilentEx(This,newVal) ) 

#define IWGUrlReceiver_get_ForceDownloadAutoStart(This,pVal)	\
    ( (This)->lpVtbl -> get_ForceDownloadAutoStart(This,pVal) ) 

#define IWGUrlReceiver_put_ForceDownloadAutoStart(This,newVal)	\
    ( (This)->lpVtbl -> put_ForceDownloadAutoStart(This,newVal) ) 

#define IWGUrlReceiver_get_DisableMaliciousChecking(This,pVal)	\
    ( (This)->lpVtbl -> get_DisableMaliciousChecking(This,pVal) ) 

#define IWGUrlReceiver_put_DisableMaliciousChecking(This,newVal)	\
    ( (This)->lpVtbl -> put_DisableMaliciousChecking(This,newVal) ) 

#define IWGUrlReceiver_get_DisableURLExistsCheck(This,pVal)	\
    ( (This)->lpVtbl -> get_DisableURLExistsCheck(This,pVal) ) 

#define IWGUrlReceiver_put_DisableURLExistsCheck(This,newVal)	\
    ( (This)->lpVtbl -> put_DisableURLExistsCheck(This,newVal) ) 

#define IWGUrlReceiver_get_FileName(This,pVal)	\
    ( (This)->lpVtbl -> get_FileName(This,pVal) ) 

#define IWGUrlReceiver_put_FileName(This,newVal)	\
    ( (This)->lpVtbl -> put_FileName(This,newVal) ) 

#define IWGUrlReceiver_get_FlashVideoDownload(This,pVal)	\
    ( (This)->lpVtbl -> get_FlashVideoDownload(This,pVal) ) 

#define IWGUrlReceiver_put_FlashVideoDownload(This,newVal)	\
    ( (This)->lpVtbl -> put_FlashVideoDownload(This,newVal) ) 

#define IWGUrlReceiver_get_FileSize(This,pVal)	\
    ( (This)->lpVtbl -> get_FileSize(This,pVal) ) 

#define IWGUrlReceiver_put_FileSize(This,newVal)	\
    ( (This)->lpVtbl -> put_FileSize(This,newVal) ) 

#define IWGUrlReceiver_get_OriginalURL(This,pVal)	\
    ( (This)->lpVtbl -> get_OriginalURL(This,pVal) ) 

#define IWGUrlReceiver_put_OriginalURL(This,newVal)	\
    ( (This)->lpVtbl -> put_OriginalURL(This,newVal) ) 

#define IWGUrlReceiver_get_UserAgent(This,pVal)	\
    ( (This)->lpVtbl -> get_UserAgent(This,pVal) ) 

#define IWGUrlReceiver_put_UserAgent(This,newVal)	\
    ( (This)->lpVtbl -> put_UserAgent(This,newVal) ) 

#endif 

#endif 	

#endif 	

#ifndef __IWGUrlListReceiver_INTERFACE_DEFINED__
#define __IWGUrlListReceiver_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IWGUrlListReceiver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("42E8D680-A18B-4CAA-ACE0-18EA05E4A056")
    IWGUrlListReceiver : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_Url( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Url( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Comment( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Comment( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Referer( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Referer( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE AddUrlToList( void) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ShowAddUrlListDialog( void) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE GetUrlListFromDocumentSelection( 
             IDispatch *pDispatch) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Cookies( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Cookies( 
             BSTR newVal) = 0;
        
    };
    
    
#else 	

    typedef struct IWGUrlListReceiverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWGUrlListReceiver * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWGUrlListReceiver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWGUrlListReceiver * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWGUrlListReceiver * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWGUrlListReceiver * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWGUrlListReceiver * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWGUrlListReceiver * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            IWGUrlListReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            IWGUrlListReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_Comment )( 
            IWGUrlListReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Comment )( 
            IWGUrlListReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_Referer )( 
            IWGUrlListReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Referer )( 
            IWGUrlListReceiver * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *AddUrlToList )( 
            IWGUrlListReceiver * This);
        
         HRESULT ( STDMETHODCALLTYPE *ShowAddUrlListDialog )( 
            IWGUrlListReceiver * This);
        
         HRESULT ( STDMETHODCALLTYPE *GetUrlListFromDocumentSelection )( 
            IWGUrlListReceiver * This,
             IDispatch *pDispatch);
        
         HRESULT ( STDMETHODCALLTYPE *get_Cookies )( 
            IWGUrlListReceiver * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Cookies )( 
            IWGUrlListReceiver * This,
             BSTR newVal);
        
        END_INTERFACE
    } IWGUrlListReceiverVtbl;

    interface IWGUrlListReceiver
    {
        CONST_VTBL struct IWGUrlListReceiverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IWGUrlListReceiver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWGUrlListReceiver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWGUrlListReceiver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IWGUrlListReceiver_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWGUrlListReceiver_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWGUrlListReceiver_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWGUrlListReceiver_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IWGUrlListReceiver_get_Url(This,pVal)	\
    ( (This)->lpVtbl -> get_Url(This,pVal) ) 

#define IWGUrlListReceiver_put_Url(This,newVal)	\
    ( (This)->lpVtbl -> put_Url(This,newVal) ) 

#define IWGUrlListReceiver_get_Comment(This,pVal)	\
    ( (This)->lpVtbl -> get_Comment(This,pVal) ) 

#define IWGUrlListReceiver_put_Comment(This,newVal)	\
    ( (This)->lpVtbl -> put_Comment(This,newVal) ) 

#define IWGUrlListReceiver_get_Referer(This,pVal)	\
    ( (This)->lpVtbl -> get_Referer(This,pVal) ) 

#define IWGUrlListReceiver_put_Referer(This,newVal)	\
    ( (This)->lpVtbl -> put_Referer(This,newVal) ) 

#define IWGUrlListReceiver_AddUrlToList(This)	\
    ( (This)->lpVtbl -> AddUrlToList(This) ) 

#define IWGUrlListReceiver_ShowAddUrlListDialog(This)	\
    ( (This)->lpVtbl -> ShowAddUrlListDialog(This) ) 

#define IWGUrlListReceiver_GetUrlListFromDocumentSelection(This,pDispatch)	\
    ( (This)->lpVtbl -> GetUrlListFromDocumentSelection(This,pDispatch) ) 

#define IWGUrlListReceiver_get_Cookies(This,pVal)	\
    ( (This)->lpVtbl -> get_Cookies(This,pVal) ) 

#define IWGUrlListReceiver_put_Cookies(This,newVal)	\
    ( (This)->lpVtbl -> put_Cookies(This,newVal) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFdmFlvDownload_INTERFACE_DEFINED__
#define __IFdmFlvDownload_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFdmFlvDownload;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E66B63B0-49F8-47E3-A9BA-799287B59E87")
    IFdmFlvDownload : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_Url( 
             IWGUrlReceiver **pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Url( 
             IWGUrlReceiver *newVal) = 0;
        
    };
    
    
#else 	

    typedef struct IFdmFlvDownloadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFdmFlvDownload * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFdmFlvDownload * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFdmFlvDownload * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFdmFlvDownload * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFdmFlvDownload * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFdmFlvDownload * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFdmFlvDownload * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            IFdmFlvDownload * This,
             IWGUrlReceiver **pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            IFdmFlvDownload * This,
             IWGUrlReceiver *newVal);
        
        END_INTERFACE
    } IFdmFlvDownloadVtbl;

    interface IFdmFlvDownload
    {
        CONST_VTBL struct IFdmFlvDownloadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFdmFlvDownload_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFdmFlvDownload_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFdmFlvDownload_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFdmFlvDownload_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFdmFlvDownload_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFdmFlvDownload_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFdmFlvDownload_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFdmFlvDownload_get_Url(This,pVal)	\
    ( (This)->lpVtbl -> get_Url(This,pVal) ) 

#define IFdmFlvDownload_put_Url(This,newVal)	\
    ( (This)->lpVtbl -> put_Url(This,newVal) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFDM_INTERFACE_DEFINED__
#define __IFDM_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFDM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8FA5B48-B7A2-4BC6-8389-9587643A4660")
    IFDM : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE Shutdown( 
             BOOL bAskUser) = 0;
        
    };
    
    
#else 	

    typedef struct IFDMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFDM * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFDM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFDM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFDM * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFDM * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFDM * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFDM * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *Shutdown )( 
            IFDM * This,
             BOOL bAskUser);
        
        END_INTERFACE
    } IFDMVtbl;

    interface IFDM
    {
        CONST_VTBL struct IFDMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFDM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFDM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFDM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFDM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFDM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFDM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFDM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFDM_Shutdown(This,bAskUser)	\
    ( (This)->lpVtbl -> Shutdown(This,bAskUser) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFDMDownload_INTERFACE_DEFINED__
#define __IFDMDownload_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFDMDownload;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F2B3016-17D4-447A-B207-FFA8957A834A")
    IFDMDownload : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_Url( 
             BSTR *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_Url( 
             BSTR newVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_DownloadText( 
             long nTextIndex,
             BSTR *pVal) = 0;
        
    };
    
    
#else 	

    typedef struct IFDMDownloadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFDMDownload * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFDMDownload * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFDMDownload * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFDMDownload * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFDMDownload * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFDMDownload * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFDMDownload * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_Url )( 
            IFDMDownload * This,
             BSTR *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_Url )( 
            IFDMDownload * This,
             BSTR newVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_DownloadText )( 
            IFDMDownload * This,
             long nTextIndex,
             BSTR *pVal);
        
        END_INTERFACE
    } IFDMDownloadVtbl;

    interface IFDMDownload
    {
        CONST_VTBL struct IFDMDownloadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFDMDownload_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFDMDownload_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFDMDownload_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFDMDownload_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFDMDownload_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFDMDownload_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFDMDownload_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFDMDownload_get_Url(This,pVal)	\
    ( (This)->lpVtbl -> get_Url(This,pVal) ) 

#define IFDMDownload_put_Url(This,newVal)	\
    ( (This)->lpVtbl -> put_Url(This,newVal) ) 

#define IFDMDownload_get_DownloadText(This,nTextIndex,pVal)	\
    ( (This)->lpVtbl -> get_DownloadText(This,nTextIndex,pVal) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFDMDownloadsStat_INTERFACE_DEFINED__
#define __IFDMDownloadsStat_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFDMDownloadsStat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B26E4A2-7F09-4365-9AB8-13E6891E42CB")
    IFDMDownloadsStat : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_DownloadCount( 
             long *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_Download( 
             long nIndex,
             IFDMDownload **pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE BuildListOfDownloads( 
             BOOL bIncludeCompleted,
             BOOL bIncludeRunning) = 0;
        
    };
    
    
#else 	

    typedef struct IFDMDownloadsStatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFDMDownloadsStat * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFDMDownloadsStat * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFDMDownloadsStat * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFDMDownloadsStat * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFDMDownloadsStat * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFDMDownloadsStat * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFDMDownloadsStat * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_DownloadCount )( 
            IFDMDownloadsStat * This,
             long *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *get_Download )( 
            IFDMDownloadsStat * This,
             long nIndex,
             IFDMDownload **pVal);
        
         HRESULT ( STDMETHODCALLTYPE *BuildListOfDownloads )( 
            IFDMDownloadsStat * This,
             BOOL bIncludeCompleted,
             BOOL bIncludeRunning);
        
        END_INTERFACE
    } IFDMDownloadsStatVtbl;

    interface IFDMDownloadsStat
    {
        CONST_VTBL struct IFDMDownloadsStatVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFDMDownloadsStat_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFDMDownloadsStat_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFDMDownloadsStat_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFDMDownloadsStat_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFDMDownloadsStat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFDMDownloadsStat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFDMDownloadsStat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFDMDownloadsStat_get_DownloadCount(This,pVal)	\
    ( (This)->lpVtbl -> get_DownloadCount(This,pVal) ) 

#define IFDMDownloadsStat_get_Download(This,nIndex,pVal)	\
    ( (This)->lpVtbl -> get_Download(This,nIndex,pVal) ) 

#define IFDMDownloadsStat_BuildListOfDownloads(This,bIncludeCompleted,bIncludeRunning)	\
    ( (This)->lpVtbl -> BuildListOfDownloads(This,bIncludeCompleted,bIncludeRunning) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFdmTorrentFilesRcvr_INTERFACE_DEFINED__
#define __IFdmTorrentFilesRcvr_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFdmTorrentFilesRcvr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21402197-BB5B-476C-AA1D-3FFED8ED813A")
    IFdmTorrentFilesRcvr : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE CreateBtDownload( 
             BSTR bstrFile) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE get_ForceSilent( 
             BOOL *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE put_ForceSilent( 
             BOOL newVal) = 0;
        
    };
    
    
#else 	

    typedef struct IFdmTorrentFilesRcvrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFdmTorrentFilesRcvr * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFdmTorrentFilesRcvr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFdmTorrentFilesRcvr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFdmTorrentFilesRcvr * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFdmTorrentFilesRcvr * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFdmTorrentFilesRcvr * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFdmTorrentFilesRcvr * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *CreateBtDownload )( 
            IFdmTorrentFilesRcvr * This,
             BSTR bstrFile);
        
         HRESULT ( STDMETHODCALLTYPE *get_ForceSilent )( 
            IFdmTorrentFilesRcvr * This,
             BOOL *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *put_ForceSilent )( 
            IFdmTorrentFilesRcvr * This,
             BOOL newVal);
        
        END_INTERFACE
    } IFdmTorrentFilesRcvrVtbl;

    interface IFdmTorrentFilesRcvr
    {
        CONST_VTBL struct IFdmTorrentFilesRcvrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFdmTorrentFilesRcvr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFdmTorrentFilesRcvr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFdmTorrentFilesRcvr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFdmTorrentFilesRcvr_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFdmTorrentFilesRcvr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFdmTorrentFilesRcvr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFdmTorrentFilesRcvr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFdmTorrentFilesRcvr_CreateBtDownload(This,bstrFile)	\
    ( (This)->lpVtbl -> CreateBtDownload(This,bstrFile) ) 

#define IFdmTorrentFilesRcvr_get_ForceSilent(This,pVal)	\
    ( (This)->lpVtbl -> get_ForceSilent(This,pVal) ) 

#define IFdmTorrentFilesRcvr_put_ForceSilent(This,newVal)	\
    ( (This)->lpVtbl -> put_ForceSilent(This,newVal) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFDMFlashVideoDownloads_INTERFACE_DEFINED__
#define __IFDMFlashVideoDownloads_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFDMFlashVideoDownloads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0DC81A74-1FBD-4EF6-82B2-DE3FA05E8233")
    IFDMFlashVideoDownloads : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE ProcessIeDocument( 
             IDispatch *pDispatch) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ProcessHtml( 
             BSTR bstrHost,
             BSTR bstrHtml) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE CreateFromUrl( 
             BSTR bstrUrl) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ShowAddDownloadDialog( 
             BSTR bstrSrcWebPageUrl,
             IFdmFlvDownload *pDld) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE ShowAddDownloadsDialog( 
             BSTR bstrSrcWebPageUrl,
             SAFEARRAY * pDownloads) = 0;
        
    };
    
    
#else 	

    typedef struct IFDMFlashVideoDownloadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFDMFlashVideoDownloads * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFDMFlashVideoDownloads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFDMFlashVideoDownloads * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFDMFlashVideoDownloads * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFDMFlashVideoDownloads * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFDMFlashVideoDownloads * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFDMFlashVideoDownloads * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *ProcessIeDocument )( 
            IFDMFlashVideoDownloads * This,
             IDispatch *pDispatch);
        
         HRESULT ( STDMETHODCALLTYPE *ProcessHtml )( 
            IFDMFlashVideoDownloads * This,
             BSTR bstrHost,
             BSTR bstrHtml);
        
         HRESULT ( STDMETHODCALLTYPE *CreateFromUrl )( 
            IFDMFlashVideoDownloads * This,
             BSTR bstrUrl);
        
         HRESULT ( STDMETHODCALLTYPE *ShowAddDownloadDialog )( 
            IFDMFlashVideoDownloads * This,
             BSTR bstrSrcWebPageUrl,
             IFdmFlvDownload *pDld);
        
         HRESULT ( STDMETHODCALLTYPE *ShowAddDownloadsDialog )( 
            IFDMFlashVideoDownloads * This,
             BSTR bstrSrcWebPageUrl,
             SAFEARRAY * pDownloads);
        
        END_INTERFACE
    } IFDMFlashVideoDownloadsVtbl;

    interface IFDMFlashVideoDownloads
    {
        CONST_VTBL struct IFDMFlashVideoDownloadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFDMFlashVideoDownloads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFDMFlashVideoDownloads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFDMFlashVideoDownloads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFDMFlashVideoDownloads_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFDMFlashVideoDownloads_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFDMFlashVideoDownloads_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFDMFlashVideoDownloads_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFDMFlashVideoDownloads_ProcessIeDocument(This,pDispatch)	\
    ( (This)->lpVtbl -> ProcessIeDocument(This,pDispatch) ) 

#define IFDMFlashVideoDownloads_ProcessHtml(This,bstrHost,bstrHtml)	\
    ( (This)->lpVtbl -> ProcessHtml(This,bstrHost,bstrHtml) ) 

#define IFDMFlashVideoDownloads_CreateFromUrl(This,bstrUrl)	\
    ( (This)->lpVtbl -> CreateFromUrl(This,bstrUrl) ) 

#define IFDMFlashVideoDownloads_ShowAddDownloadDialog(This,bstrSrcWebPageUrl,pDld)	\
    ( (This)->lpVtbl -> ShowAddDownloadDialog(This,bstrSrcWebPageUrl,pDld) ) 

#define IFDMFlashVideoDownloads_ShowAddDownloadsDialog(This,bstrSrcWebPageUrl,pDownloads)	\
    ( (This)->lpVtbl -> ShowAddDownloadsDialog(This,bstrSrcWebPageUrl,pDownloads) ) 

#endif 

#endif 	

#endif 	

#ifndef __IFdmUiWindow_INTERFACE_DEFINED__
#define __IFdmUiWindow_INTERFACE_DEFINED__

 

EXTERN_C const IID IID_IFdmUiWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FEB1BAD-35AD-4a08-B6EC-E6D832F1ED4D")
    IFdmUiWindow : public IDispatch
    {
    public:
        virtual  HRESULT STDMETHODCALLTYPE get_Handle( 
             ULONG *pVal) = 0;
        
        virtual  HRESULT STDMETHODCALLTYPE WaitForWindowCreation( 
            LONG uTimeoutMilliseconds) = 0;
        
    };
    
    
#else 	

    typedef struct IFdmUiWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFdmUiWindow * This,
             REFIID riid,
             
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFdmUiWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFdmUiWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFdmUiWindow * This,
             UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFdmUiWindow * This,
             UINT iTInfo,
             LCID lcid,
             ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFdmUiWindow * This,
             REFIID riid,
             LPOLESTR *rgszNames,
             UINT cNames,
             LCID lcid,
             DISPID *rgDispId);
        
         HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFdmUiWindow * This,
             
            _In_  DISPID dispIdMember,
             
            _In_  REFIID riid,
             
            _In_  LCID lcid,
             
            _In_  WORD wFlags,
             
            _In_  DISPPARAMS *pDispParams,
             
            _Out_opt_  VARIANT *pVarResult,
             
            _Out_opt_  EXCEPINFO *pExcepInfo,
             
            _Out_opt_  UINT *puArgErr);
        
         HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            IFdmUiWindow * This,
             ULONG *pVal);
        
         HRESULT ( STDMETHODCALLTYPE *WaitForWindowCreation )( 
            IFdmUiWindow * This,
            LONG uTimeoutMilliseconds);
        
        END_INTERFACE
    } IFdmUiWindowVtbl;

    interface IFdmUiWindow
    {
        CONST_VTBL struct IFdmUiWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS

#define IFdmUiWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFdmUiWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFdmUiWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IFdmUiWindow_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFdmUiWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFdmUiWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFdmUiWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#define IFdmUiWindow_get_Handle(This,pVal)	\
    ( (This)->lpVtbl -> get_Handle(This,pVal) ) 

#define IFdmUiWindow_WaitForWindowCreation(This,uTimeoutMilliseconds)	\
    ( (This)->lpVtbl -> WaitForWindowCreation(This,uTimeoutMilliseconds) ) 

#endif 

#endif 	

#endif 	

#ifndef __FdmLib_LIBRARY_DEFINED__
#define __FdmLib_LIBRARY_DEFINED__

 

EXTERN_C const IID LIBID_FdmLib;

EXTERN_C const CLSID CLSID_WGUrlReceiver;

#ifdef __cplusplus

class DECLSPEC_UUID("959BA0A4-0893-48B4-8B02-BA0DA0A401FE")
WGUrlReceiver;
#endif

EXTERN_C const CLSID CLSID_WGUrlListReceiver;

#ifdef __cplusplus

class DECLSPEC_UUID("83E6F60E-7147-4475-9DF6-5F1E237FE2CE")
WGUrlListReceiver;
#endif

EXTERN_C const CLSID CLSID_FdmFlvDownload;

#ifdef __cplusplus

class DECLSPEC_UUID("42130E6A-0045-4208-A252-71CA12C8FE99")
FdmFlvDownload;
#endif

EXTERN_C const CLSID CLSID_FDM;

#ifdef __cplusplus

class DECLSPEC_UUID("01483019-D8C9-47D8-8E93-AF032EBFADA6")
FDM;
#endif

EXTERN_C const CLSID CLSID_FDMDownloadsStat;

#ifdef __cplusplus

class DECLSPEC_UUID("F01F76EC-3376-4E62-B201-8074C8239376")
FDMDownloadsStat;
#endif

EXTERN_C const CLSID CLSID_FDMDownload;

#ifdef __cplusplus

class DECLSPEC_UUID("DEBBD32E-1D08-4F6A-8A26-E1B3D768A1E5")
FDMDownload;
#endif

EXTERN_C const CLSID CLSID_FDMUploader;

#ifdef __cplusplus

class DECLSPEC_UUID("4D6295C9-2765-49B0-A45B-4136B610954C")
FDMUploader;
#endif

EXTERN_C const CLSID CLSID_FDMUploadPackage;

#ifdef __cplusplus

class DECLSPEC_UUID("56101D38-6A8B-49D6-8C9D-939595AB2D19")
FDMUploadPackage;
#endif

EXTERN_C const CLSID CLSID_FdmTorrentFilesRcvr;

#ifdef __cplusplus

class DECLSPEC_UUID("19CAD08F-0413-47F8-B1D9-5D66826E1E39")
FdmTorrentFilesRcvr;
#endif

EXTERN_C const CLSID CLSID_FDMFlashVideoDownloads;

#ifdef __cplusplus

class DECLSPEC_UUID("D8E9E2ED-846D-4711-A9B8-A29312157DB4")
FDMFlashVideoDownloads;
#endif

EXTERN_C const CLSID CLSID_FdmUiWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("5A810830-B199-4a4c-89CB-928D960A5C04")
FdmUiWindow;
#endif
#endif 

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

#ifdef __cplusplus
}
#endif

#endif

