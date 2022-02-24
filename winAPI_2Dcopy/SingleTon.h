#pragma once

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