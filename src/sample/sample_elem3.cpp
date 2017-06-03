#include <tchar.h>
#include "sample_elem3.h"

StkObject* Sample_Elem3::Execute(StkObject* ReqObj, int Method, TCHAR UrlPath[128], int* ResultCode, TCHAR Locale[3])
{
	int ErrCode;
	StkObject* TmpObj;
	if (lstrcmp(Locale, _T("ja")) == 0) {
		TmpObj = StkObject::CreateObjectFromJson(_T("{ \"hello2\" : \"����ɂ���!!\" }"), &ErrCode);
	} else {
		TmpObj = StkObject::CreateObjectFromJson(_T("{ \"hello2\" : \"hello, world!!\" }"), &ErrCode);
	}
	*ResultCode = 200;
	return TmpObj;
}
