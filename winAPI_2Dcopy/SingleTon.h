#pragma once

// 매크로
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

// 클래스
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
//	static T* getInst()		// 없으면 생성 후 반환, 있으면 그냥 반환
//	{
//		if (nullptr == _instance)
//			_instance = new T;
//	}
//	return _instance;
//
//	void release()			// 있으면 해제
//	{
//		if (nullptr != _instance)
//		{
//			delete _instance;
//			_instance = nullptr;
//		}
//	}
//};
//
//// 싱글톤 인스턴스 선언
//template <typename T>
//T* SingleTon<T>::_instance = nullptr;