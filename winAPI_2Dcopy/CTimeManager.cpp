#include "framework.h"
#include "CTimeManager.h"

// 제일 많이 헷갈리는 부분
	// update함수의 호출 횟수와 상관없이 일정한 속도로 움직이게 하기 위해선 초당 update함수 호출 횟수의 역수를 곱해주면 된다.(DT) 
		// Frequency가 헷갈림
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

// DT의 역수가 FPS지만 double형에, 나눗셈 계산은 오래걸리므로 다른 방법으로 구함
void CTimeManager::update()
{
	// FPS가 결국 update()가 호출된 횟수니까 카운트용 정적변수 updateCnt
	static unsigned int updateCnt = 0;
	// update()당 걸린 시간 누적할 변수
	static double updateOneSec = 0;

	// 현재 카운트
	QueryPerformanceCounter(&m_llCurCnt);

	// DT : 1프레임당 소모 시간
		// 거시속 으로다가 ' 시(DT) = 거(curCnt - prevCnt) / 속(cnt/s = frequency) ' 인 느낌?
	m_dDT = (double)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart) / m_llFrequency.QuadPart;	
	// PrevCnt를 CurCnt로 갱신
	m_llPrevCnt = m_llCurCnt;

	++updateCnt;
	updateOneSec += m_dDT;			// 걸린 시간 누적

	if (updateOneSec >= 1.0)		//걸린 시간이 1초가 되면
	{	// FPS는 update함수 호출 횟수
		m_uiFPS = updateCnt;

		updateCnt = 0;
		updateOneSec = 0;
	}
}

void CTimeManager::init()
{
	// init함수가 호출될 때 PrevCnt에 입력
	QueryPerformanceCounter(&m_llPrevCnt);
	// 초당 카운트 횟수 (속도라고 봐도 되나)
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
