﻿#pragma once
#include "dataaccess.h"
#include "../../../YaizuComLib/src/stkwebapp/StkWebAppExec.h"
#include "ApiBase.h"

class ApiGetServerInfo : ApiBase
{
private:
	wchar_t StartTimeUtc[DA_MAXLEN_OF_TIME];
	wchar_t StartTimeLocal[DA_MAXLEN_OF_TIME];

public:
	ApiGetServerInfo();
	StkObject* Execute(StkObject*, int, wchar_t[StkWebAppExec::URL_PATH_LENGTH], int*, wchar_t[3]);
};
