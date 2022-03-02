#include "framework.h"
#include "CScene.h"

CScene::CScene()
{
	m_strName = L"";
}
CScene::~CScene()
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
			delete m_arrObj[i][j];

		/*while (m_arrObj[i].size() > 0)	// 벡터에서 알아서 할 내용인듯
			m_arrObj[i].pop_back();*/
	}
}

void CScene::setName(const wstring& strName)
{
	m_strName = strName;
}

wstring CScene::getName()
{
	return m_strName;
}

void CScene::addObject(CObject* pObj, OBJ objType)
{
	m_arrObj[(int)objType].push_back(pObj);
}

void CScene::update()
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
			m_arrObj[i][j]->update();
	}
}

void CScene::finalUpdate()
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
			m_arrObj[i][j]->finalUpdate();
	}
}

void CScene::render(HDC hDC)
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
			m_arrObj[i][j]->render(hDC);
	}
}

const vector<CObject*>& CScene::getGroupObject(OBJ group)
{
	return m_arrObj[(UINT)group];
}

vector<CObject*>* CScene::getVecArr()
{
	return m_arrObj;
}
