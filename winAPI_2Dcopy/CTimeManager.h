#pragma once

// ���� ����, ���� ������
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	// LARGE_INTEGER : long long �ڷ����� ����ü, HighPart + LowPart = QuadPart;
	LARGE_INTEGER	m_llCurCnt;			// ���� ī��Ʈ
	LARGE_INTEGER	m_llPrevCnt;		// ���� ī��Ʈ
	LARGE_INTEGER	m_llFrequency;		// �ʴ� ī��Ʈ Ƚ��

	unsigned int	m_uiFPS;			// FPS			: 1�ʴ� �׷��� ȭ�� �� (update�� ��� ȣ�� �ƴ���)
	double			m_dDT;				// Delta Time	: 1�����Ӵ� �Ҹ� �ð� (FPS�� ���� ����)

public:
	void			update();
	void			init();

	unsigned int	getFPS();
	double			getDT();
	
};