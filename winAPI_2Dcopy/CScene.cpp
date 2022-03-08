#include "framework.h"
#include "CScene.h"
#include "CPlayer.h"	// static 함수 사용하려면 필요

CScene::CScene()
{
	m_strName = L"";
}
CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)OBJ::SIZE; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
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
	m_arrObj[(UINT)objType].push_back(pObj);
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)OBJ::SIZE; i++)
	{
		if (CPlayer::getTransformMode() && i != (UINT)OBJ::PLAYER)	// 변신 중이면 플레이어 빼고 continue;
			continue;
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->isDead())				// 유예 중이면 업데이트 x
				m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)OBJ::SIZE; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)OBJ::SIZE; i++)
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

void CScene::deleteObjectGroup(OBJ objGroup)
{
	for (UINT i = 0; i < m_arrObj[(UINT)objGroup].size(); i++)
		delete m_arrObj[(UINT)objGroup][i];

	m_arrObj[(UINT)objGroup].clear();
}

void CScene::deleteObjectAll()
{
	for (UINT i = 0; i < (UINT)OBJ::SIZE; i++)
		deleteObjectGroup((OBJ)i);
}
