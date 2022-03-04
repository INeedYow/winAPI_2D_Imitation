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
		{
			if (!m_arrObj[i][j]->isDead())				// 유예 중이면 업데이트 x
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalUpdate()
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render(HDC hDC)
{
	for (int i = 0; i < (int)OBJ::SIZE; i++)
	{
		for (vector<CObject*>::iterator iter = m_arrObj[i].begin(); iter != m_arrObj[i].end();)
		{
			if (!(*iter)->isDead())
				(*iter++)->render(hDC);
			else										// 유예 중이면 erase
				iter = m_arrObj[i].erase(iter);
		}
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
