﻿#include "dataaccess.h"
#include "sample_elem1.h"

StkObject* Sample_Elem1::Execute(StkObject* ReqObj, int Method, wchar_t UrlPath[StkWebAppExec::URL_PATH_LENGTH], int* ResultCode, wchar_t Locale[3])
{
	wchar_t TimeUtc[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_LOGTIME];
	wchar_t TimeLocal[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_LOGTIME];
	wchar_t Msg[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_LOGMSG];
	int Count = DataAccess::GetInstance()->GetLogs(TimeUtc, TimeLocal, Msg);

	StkObject* TmpObj = new StkObject(L"");
	for (int Loop = 0; Loop < Count; Loop++) {
		StkObject* TmpObjC = new StkObject(L"Person");
		TmpObjC->AppendChildElement(new StkObject(L"name", TimeLocal[Loop]));
		TmpObjC->AppendChildElement(new StkObject(L"age", Loop));
		TmpObjC->AppendChildElement(new StkObject(L"address", Msg[Loop]));
		TmpObj->AppendChildElement(TmpObjC);
	}
	*ResultCode = 200;
	return TmpObj;
}
