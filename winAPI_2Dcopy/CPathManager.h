#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	WCHAR	m_strContentPath[255];	// ������ �ִ� ��ΰ� 255

public:
	void init();

	const wchar_t* getContentPath();
};

