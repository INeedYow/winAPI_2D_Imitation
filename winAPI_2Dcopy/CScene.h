#pragma once

class CObject;		// ������ ������ ����� �� ���漱������ ����ϴ�. (#include ������ �ϴ� �� ����, ������ �ӵ� ���)

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// [] �����ŭ vector����
	wstring m_strName;

public:
	CScene();
	virtual ~CScene();

	void setName(const wstring& strName);
	wstring getName();

	void addObject(CObject* pObj, OBJ objType);

	virtual void update();
	virtual void render(HDC hDC);

	// ȭ����ȯ�� �� �۾�
	virtual void enter() = 0;
	virtual void exit() = 0;

	// �̷��� �ϸ� �� ���� �� ������ ��Ե� �ǰԸ� �ϴٺ���
public:
	vector<CObject*>* getVecArr();	
	// �׳� �� �� ���Ƽ� �õ��ϴٰ� ������ �� ���� �ϴٺ��� �Ǳ�� �ѵ� �Ǵ� ������ �𸣰���
		// �̰ɷ� exit�� ��������
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO : (����) �̰� �³��� ������ .. ��� �����غ��µ� �Ӹ� �ʹ� ���Ŵϴ� �ϸ鼭�� �򰥷���
// 
// Scene�� ���� m_arrObj[] �迭�� �ڷ����� vector<CObject*>�̰�
// 
// m_arrObj�� �迭�� �̸����� ���� �ּҴϱ� *(m_arrObj) �� m_arrObj[0]�̰�
// 
// �׷��� m_arrObj�� return�ϴ� getVecArr()�� ��ȯ Ÿ���� vector<CObject*>* ���� �ϴ� ���̰�
//
// ���� getVecArr()�� ��ȯ �޾Ƽ� �� ������
//
// pVecArr[]�� vector<CObject*>�� �Ǵ� ���̰� pVecArr[(int)OBJ::ENUMCLASS][i]�� �ش� obj�鿡 ������ �� �ִ�....? 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////