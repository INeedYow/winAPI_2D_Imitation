#pragma once
class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VKEY_SIZE = 0xFF;		// VKŰ�� ����, #define���� �ص� ��

	bool m_arrPrevKey[VKEY_SIZE] = {};
	bool m_arrCurKey[VKEY_SIZE] = {};

public:
	void update();
	void init();

	bool getKeyHold(const int key);		
	bool getKeyOn(const int key);
	bool getKeyOff(const int key);		
	bool getKeyNone(const int key);	
};

