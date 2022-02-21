#include "framework.h"
#include "CTimeManager.h"

// ���� ���� �򰥸��� �κ�
	// update�Լ��� ȣ�� Ƚ���� ������� ������ �ӵ��� �����̰� �ϱ� ���ؼ� �ʴ� update�Լ� ȣ�� Ƚ���� ������ �����ָ� �ȴ�.(DT) 
		// Frequency�� �򰥸�
CTimeManager::CTimeManager()
{
	m_llCurCnt= {};
	m_llPrevCnt = {};
	m_llFrequency = {};
	m_uiFPS = 0;
	m_dDT = 0.;
}
CTimeManager::~CTimeManager()
{

}

// DT�� ������ FPS���� double����, ������ ����� �����ɸ��Ƿ� �ٸ� ������� ����
void CTimeManager::update()
{
	// FPS�� �ᱹ update()�� ȣ��� Ƚ���ϱ� ī��Ʈ�� �������� updateCnt
	static unsigned int updateCnt = 0;
	// update()�� �ɸ� �ð� ������ ����
	static double updateOneSec = 0;

	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llCurCnt);

	// DT : 1�����Ӵ� �Ҹ� �ð�
		// �Žü� ���δٰ� ' ��(DT) = ��(curCnt - prevCnt) / ��(cnt/s = frequency) ' �� ����?
	m_dDT = (double)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart) / m_llFrequency.QuadPart;	
	// PrevCnt�� CurCnt�� ����
	m_llPrevCnt = m_llCurCnt;

	++updateCnt;
	updateOneSec += m_dDT;			// �ɸ� �ð� ����

	if (updateOneSec >= 1.0)		//�ɸ� �ð��� 1�ʰ� �Ǹ�
	{	// FPS�� update�Լ� ȣ�� Ƚ��
		m_uiFPS = updateCnt;

		updateCnt = 0;
		updateOneSec = 0;
	}
}

void CTimeManager::init()
{
	// init�Լ��� ȣ��� �� PrevCnt�� �Է�
	QueryPerformanceCounter(&m_llPrevCnt);
	// �ʴ� ī��Ʈ Ƚ�� (�ӵ���� ���� �ǳ�)
	QueryPerformanceFrequency(&m_llFrequency);
}

unsigned int CTimeManager::getFPS()
{
	return m_uiFPS;
}

double CTimeManager::getDT()
{
	return m_dDT;
}
