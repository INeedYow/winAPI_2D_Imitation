#pragma once

// 구현 미흡, 제일 부족함
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	// LARGE_INTEGER : long long 자료형의 공용체, HighPart + LowPart = QuadPart;
	LARGE_INTEGER	m_llCurCnt;			// 현재 카운트
	LARGE_INTEGER	m_llPrevCnt;		// 이전 카운트
	LARGE_INTEGER	m_llFrequency;		// 초당 카운트 횟수

	unsigned int	m_uiFPS;			// FPS			: 1초당 그려진 화면 수 (update가 몇번 호출 됐는지)
	double			m_dDT;				// Delta Time	: 1프레임당 소모 시간 (FPS와 역수 관계)

public:
	void			update();
	void			init();

	unsigned int	getFPS();
	double			getDT();
	
};