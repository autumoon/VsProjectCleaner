//author:autumoon
//mail:autumoon@vip.qq.com

#pragma once

#include <tchar.h>
#include "Defines.h"
#include "SimpleIni.h"
#include "StdStrFile.h"

typedef struct _config_s 
{
	bool bRemPath;
	bool bRealDel;
	int nWindowWidth;
	int nWindowHeight;

	std::vector<_tstring> vInputDirs;

	std::vector<_tstring> vRootDirNames;
	std::vector<_tstring> vAllDirNames;
	std::vector<_tstring> vAllSuffixs;

	_config_s()
	{
		//内部初始化
		bRemPath = true;
		bRealDel = false;

		//根目录
		vRootDirNames.push_back(_T("ipch"));
		vRootDirNames.push_back(_T("x64"));

		//所有目录
		vAllDirNames.push_back(_T(".vs"));
		vAllDirNames.push_back(_T("obj"));
		vAllDirNames.push_back(_T("Debug"));
		vAllDirNames.push_back(_T("Release"));

		//C# 工程常见临时目录（阶段 2 新增）
		vAllDirNames.push_back(_T("TestResults"));
		vAllDirNames.push_back(_T("MigrationBackup"));
		vAllDirNames.push_back(_T(".vscode"));
		vAllDirNames.push_back(_T(".idea"));

		//所有后缀
		vAllSuffixs.push_back(_T(".aps"));
		vAllSuffixs.push_back(_T(".dep"));
		vAllSuffixs.push_back(_T(".exp"));
		vAllSuffixs.push_back(_T(".idb"));
		vAllSuffixs.push_back(_T(".ilk"));
		vAllSuffixs.push_back(_T(".ipch"));
		vAllSuffixs.push_back(_T(".manifest"));
		vAllSuffixs.push_back(_T(".ncb"));
		vAllSuffixs.push_back(_T(".obj"));
		vAllSuffixs.push_back(_T(".pch"));
		vAllSuffixs.push_back(_T(".pdb"));
		vAllSuffixs.push_back(_T(".pd_Thumbs.db"));
		vAllSuffixs.push_back(_T(".sdf"));
		vAllSuffixs.push_back(_T(".suo"));
		vAllSuffixs.push_back(_T(".scc"));
		vAllSuffixs.push_back(_T(".user"));

		//C# 工程常见临时文件后缀（阶段 2 新增）
		vAllSuffixs.push_back(_T(".binlog"));
		vAllSuffixs.push_back(_T(".coverage"));
		vAllSuffixs.push_back(_T(".trx"));
		vAllSuffixs.push_back(_T(".VC.db"));
	}

}config_s;

int ReadIniFile(const _tstring& strIniPath, config_s& _cfg);
int WriteIniFile(const _tstring& strIniPath, const config_s& _cfg);

_tstring VectorToString(const std::vector<_tstring>& vStrings);

//_tstring GetIniPath()
//{
//TCHAR chpath[MAX_PATH];
//GetModuleFileName(NULL, chpath, sizeof(chpath));

//_tstring strModulePath = CMfcStrFile::CString2string(chpath);
//_tstring strIniPath = CStdStr::ReplaceSuffix(strModulePath, _T(".ini"));

//return strIniPath;
//}