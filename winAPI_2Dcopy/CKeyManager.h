#pragma once
class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VKEY_SIZE = 0xFF;		// VK키의 개수, #define으로 해도 됨

	bool m_arrPrevKey[VKEY_SIZE] = {};
	bool m_arrCurKey[VKEY_SIZE] = {};

public:
	void update();
	void init();

	bool getKeyPress(const int key);		// 누르고 있으면 계속 처리함
	bool getKeyOn(const int key);			// 누르고 있어도 한 번만
	bool getKeyOff(const int key);			// 떼는 순간 한 번
};

