//author:autumoon
//mail:autumoon@vip.qq.com
#include "Configure.h"

inline _tstring VectorToString(const std::vector<_tstring>& vStrings)
{
	_tstring strRes;

	const size_t num = vStrings.size();

	if (num > 0)
	{
		for (size_t i = 0; i < num - 1; ++i)
		{
			const _tstring& strCurItems = vStrings[i];
			strRes += strCurItems + _T('|');
		}

		strRes += vStrings[vStrings.size() - 1];
	}

	return strRes;
}

int ReadIniFile(const _tstring& strIniPath, config_s& _cfg)
{
	bool bRes = CStdFile::IfAccessFile(strIniPath.c_str());

	CSimpleIni Ini;
	Ini.SetUnicode();
	if (bRes)
	{
		//读取信息
		Ini.LoadFile(strIniPath.c_str());
		_cfg.bRemPath = Ini.GetBoolValue(INI_PRESUFFIX, INI_REMPATH, _cfg.bRemPath);
		_cfg.bRealDel = Ini.GetBoolValue(INI_PRESUFFIX, INI_REALDEL, _cfg.bRealDel);

		_tstring strInputDirNames = VectorToString(_cfg.vInputDirs);
		strInputDirNames = Ini.GetValue(INI_PRESUFFIX, INI_SRC_DIRS, strInputDirNames.c_str());
		_cfg.vInputDirs = CStdStr::Split(strInputDirNames, _T("|"));

		_tstring strRootDirNames = VectorToString(_cfg.vRootDirNames);
		strRootDirNames = Ini.GetValue(INI_PRESUFFIX, INI_ROOT_DIRS, strRootDirNames.c_str());
		_cfg.vRootDirNames = CStdStr::Split(strRootDirNames, _T("|"));

		_tstring strAllItems = VectorToString(_cfg.vAllDirNames);
		strAllItems = Ini.GetValue(INI_PRESUFFIX, INI_ALL_DIRS, strAllItems.c_str());
		_cfg.vAllDirNames = CStdStr::Split(strAllItems, _T("|"));

		_tstring strSuffixs = VectorToString(_cfg.vAllSuffixs);
		strSuffixs = Ini.GetValue(INI_PRESUFFIX, INI_FILE_SUFFIXS, strSuffixs.c_str());
		_cfg.vAllSuffixs = CStdStr::Split(strSuffixs, _T("|"));

		_tstring strWhiteList = VectorToString(_cfg.vWhiteList);
		strWhiteList = Ini.GetValue(INI_PRESUFFIX, INI_WHITELIST, strWhiteList.c_str());
		_cfg.vWhiteList = CStdStr::Split(strWhiteList, _T("|"));

		_cfg.nWindowWidth = Ini.GetLongValue(INI_PRESUFFIX, INI_WIN_WIDTH, _cfg.nWindowWidth);
		_cfg.nWindowHeight = Ini.GetLongValue(INI_PRESUFFIX, INI_WIN_HEIGHT, _cfg.nWindowHeight);
	}
	else
	{
		WriteIniFile(strIniPath, _cfg);
	}
	Ini.Reset();

	return 0;
}

int WriteIniFile(const _tstring& strIniPath, const config_s& _cfg)
{
	CSimpleIni Ini;
	Ini.SetUnicode();

	Ini.SetBoolValue(INI_PRESUFFIX, INI_REMPATH, _cfg.bRemPath);
	Ini.SetBoolValue(INI_PRESUFFIX, INI_REALDEL, _cfg.bRealDel);
	Ini.SetValue(INI_PRESUFFIX, INI_SRC_DIRS, VectorToString(_cfg.vInputDirs).c_str());
	Ini.SetValue(INI_PRESUFFIX, INI_ROOT_DIRS, VectorToString(_cfg.vRootDirNames).c_str());
	Ini.SetValue(INI_PRESUFFIX, INI_ALL_DIRS, VectorToString(_cfg.vAllDirNames).c_str());
	Ini.SetValue(INI_PRESUFFIX, INI_FILE_SUFFIXS, VectorToString(_cfg.vAllSuffixs).c_str());
	Ini.SetValue(INI_PRESUFFIX, INI_WHITELIST, VectorToString(_cfg.vWhiteList).c_str());
	Ini.SetLongValue(INI_PRESUFFIX, INI_WIN_WIDTH, _cfg.nWindowWidth);
	Ini.SetLongValue(INI_PRESUFFIX, INI_WIN_HEIGHT, _cfg.nWindowHeight);

	Ini.SaveFile(strIniPath.c_str());
	Ini.Reset();

	return 0;
}
