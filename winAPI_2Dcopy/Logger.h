#pragma once

//================================================
//## Logger	(visual studio 출력창에 정보 표시)	##
//================================================

#include <string>

class Logger
{

public:
	static void log(const wchar_t tag[], const wchar_t content[])
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		WCHAR str[30];
		swprintf_s(str, L"%d/%d/%d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		OutputDebugStringW(str);
		OutputDebugStringW(L" ");
		OutputDebugStringW(tag);
		OutputDebugStringW(L" ");
		OutputDebugStringW(content);
		OutputDebugStringW(L"\n");
	}

	static void debug(const wchar_t content[])
	{
		log(L"[DEBUG]", content);
	}

	static void debug(wstring content)
	{
		log(L"[DEBUG]", content.c_str());
	}

	static void info(const wchar_t content[])
	{
		log(L"[ INFO]", content);
	}

	static void info(wstring content)
	{
		log(L"[ INFO]", content.c_str());
	}

	static void warning(const wchar_t content[])
	{
		log(L"[ WARN]", content);
	}

	static void warning(wstring content)
	{
		log(L"[ WARN]", content.c_str());
	}

	static void error(const wchar_t content[])
	{
		log(L"[ERROR]", content);
	}

	static void error(wstring content)
	{
		log(L"[ERROR]", content.c_str());
	}
};
