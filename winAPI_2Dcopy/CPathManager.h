#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	WCHAR	m_strContentPath[255];	// 윈도우 최대 경로가 255

public:
	void init();

	const wchar_t* getContentPath();
};

