﻿#include "../../../YaizuComLib/src/stkpl/StkPl.h"
#include "dataaccess.h"
#include "ApiGetLogInfo.h"

StkObject* ApiGetLogInfo::Execute(StkObject* ReqObj, int Method, wchar_t UrlPath[StkWebAppExec::URL_PATH_LENGTH], int* ResultCode, wchar_t Locale[3])
{
	wchar_t TimeUtc[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_TIME];
	wchar_t TimeLocal[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_TIME];
	wchar_t Msg[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_LOGMSG];
	wchar_t MsgJa[DA_MAXNUM_OF_LOGRECORDS][DA_MAXLEN_OF_LOGMSG];
	int Count = DataAccess::GetInstance()->GetLogs(TimeUtc, TimeLocal, Msg, MsgJa);

	StkObject* TmpObj = new StkObject(L"");
	for (int Loop = 0; Loop < Count; Loop++) {
		StkObject* TmpObjC = new StkObject(L"Log");
		TmpObjC->AppendChildElement(new StkObject(L"TimeUtc", TimeUtc[Loop]));
		TmpObjC->AppendChildElement(new StkObject(L"TimeLocal", TimeLocal[Loop]));
		if (Locale != NULL && Locale[2] == '\0' && Locale[0] != '\0' && StkPlWcsCmp(Locale, L"ja") == 0) {
			TmpObjC->AppendChildElement(new StkObject(L"Msg", MsgJa[Loop]));
		} else {
			TmpObjC->AppendChildElement(new StkObject(L"Msg", Msg[Loop]));
		}
		TmpObj->AppendChildElement(TmpObjC);
	}
	TmpObj->AppendChildElement(new StkObject(L"Msg0", L""));
	*ResultCode = 200;
	return TmpObj;
}
