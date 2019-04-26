#include "dataaccess.h"
#include "../../../YaizuComLib/src/stkpl/StkPl.h"
#include "ApiGetCommandForStatus.h"

StkObject* ApiGetCommandForStatus::Execute(StkObject* ReqObj, int Method, wchar_t UrlPath[StkWebAppExec::URL_PATH_LENGTH], int* ResultCode, wchar_t Locale[3])
{
	int PInterval = 0;
	int SaInterval = 0;
	DataAccess::GetInstance()->GetServerInfo(&PInterval, &SaInterval);
	if (PInterval <= 0) {
		PInterval = 30;
	}
	if (SaInterval <= 0) {
		SaInterval = 300;
	}

	StkObject* TmpObj = new StkObject(L"");
	for (int Loop = 0; Loop < PInterval; Loop++) {
		StkPlSleepMs(1000);
		int Year = 0;
		int Mon = 0;
		int Day = 0;
		int Hour = 0;
		int Min = 0;
		int Sec = 0;
		StkPlGetTime(&Year, &Mon, &Day, &Hour, &Min, &Sec, false);
		if ((SaInterval == 300 && Min % 5 == 0 && Sec == 0) ||
			(SaInterval == 900 && Min % 15 == 0 && Sec == 0) ||
			(SaInterval == 1800 && Min % 30 == 0 && Sec == 0) ||
			(SaInterval == 3600 && Min == 0 && Sec == 0)) {
			TmpObj->AppendChildElement(new StkObject(L"Msg0", L"Execution"));
			*ResultCode = 200;
			return TmpObj;
		}
	}
	TmpObj->AppendChildElement(new StkObject(L"Msg0", L"Timeout"));
	*ResultCode = 200;
	return TmpObj;
}
