#pragma once

//author:autumoon
//2018.01.18
//xcopy /d /y .\src\*.dll $(TargetDir)

#define INI_PRESUFFIX		_T("INI_PRESUFFIX")
#define INI_REMPATH			_T("INI_REMPATH")
#define INI_REALDEL			_T("INI_REALDEL")
#define INI_SRC_DIRS		_T("INI_SRC_DIRS")
#define INI_ALL_DIRS		_T("INI_ALL_DIRS")
#define INI_ROOT_DIRS		_T("INI_ROOT_DIRS")
#define INI_FILE_SUFFIXS	_T("INI_FILE_SUFFIXS")
#define INI_WIN_WIDTH		_T("INI_WIN_WIDTH")
#define INI_WIN_HEIGHT		_T("INI_WIN_HEIGHT")

#ifdef _UNICODE

#ifndef _tstring
#define _tstring std::wstring
#endif // _tstring

#else

#ifndef _tstring
#define _tstring std::string
#endif // _tstring

#endif
