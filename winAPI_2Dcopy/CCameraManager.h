#pragma once

class CObject;

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint		m_fpFocus;
	fPoint		m_fpPrevFocus;
	CObject*	m_pTraceObj;

	fPoint		m_fpDiff;

public:
	void update();

	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	fPoint getRenderPos(fPoint pos);

	void calculateDiff();

};

// �� ������Ʈ�� ���󰡰ų� Ư�� ��ǥ�� ����
// ������Ʈ�� ������ ��ǥ �������