#pragma once

// ��ũ��
#define SINGLETON(type)					\
										\
public:									\
	static type* getInst()				\
	{									\
		static type _instance;			\
		return &_instance;				\
	}									\
private:								\
	type();								\
	~type();

// Ŭ����
//template <typename T>
//class SingleTon
//{
//protected:
//	static T* _instance;
//
//	SingleTon() {};
//	~SingleTon() {};
//
//public:
//	static T* getInst()		// ������ ���� �� ��ȯ, ������ �׳� ��ȯ
//	{
//		if (nullptr == _instance)
//			_instance = new T;
//	}
//	return _instance;
//
//	void release()			// ������ ����
//	{
//		if (nullptr != _instance)
//		{
//			delete _instance;
//			_instance = nullptr;
//		}
//	}
//};
//
//// �̱��� �ν��Ͻ� ����
//template <typename T>
//T* SingleTon<T>::_instance = nullptr;