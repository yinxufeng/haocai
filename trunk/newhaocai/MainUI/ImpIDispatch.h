/********************************************************************
	file base:	ImpIDispatch
	author:		郭庆轩
	purpose:	重新实现自动化接口，实现和网页交互
*********************************************************************/

#ifndef _IMPIDISPATCH_H_
#define _IMPIDISPATCH_H_

#include "InterfaceToJS.h"
class CImpIDispatch : public IDispatch
{
protected:
	ULONG			m_cRef;

public:

	InterfaceToJS* m_InterfaceToJs;

	CImpIDispatch(void);
	~CImpIDispatch(void);
	
	STDMETHODIMP QueryInterface(REFIID, void**);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	
	//IDispatch
	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
	STDMETHODIMP GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ ITypeInfo** ppTInfo);
	STDMETHODIMP GetIDsOfNames(
		/* [in] */ REFIID riid,
		/* [size_is][in] */ LPOLESTR* rgszNames,
		/* [in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ DISPID* rgDispId);
	STDMETHODIMP Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
	void DisProperty(WORD wFlag, VARIANT *varResul);
};

#endif
