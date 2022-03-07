#pragma once

class CObject;

struct tEvent
{
	EVENT		eEvent;
	DWORD_PTR	lParam;		// WM_PAINT���� �ô� �� // �̺�Ʈ ������ ���� �ʿ��� �Ķ���� �ٸ��� ������
	DWORD_PTR	wParam;			// DWORD_PTR(�������ڷ���)���� ���� �� ����� �� ���� �ڷ������� ����ȯ�ؼ� ����ؾ� �Ѵ�.
};

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent>	 m_vecEvent;
	vector<CObject*> m_vecDead;

	void execute(const tEvent& _event);
	void addEvent(const tEvent& _event);

public:
	//void init();				// init()������ ���� �ʿ����

	void update();

	void eventCreateObject(CObject* pObj, OBJ group);
	void eventDeleteObject(CObject* pObj);
	void eventChangeScene(SCENE scn);
};

// �� ������ ���� �߻��� �̺�Ʈ(������Ʈ ����, ����, ����ȯ ��)�� 
// ������ ������ �ƴ϶� �� �������� ������ ���� ������ ���� ó��
	// ������ ����ȭ