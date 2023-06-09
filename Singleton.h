#pragma once

template <class T> class Singleton
{
public:
	static T& instance() {
		static T inst;
		return inst;
	}
protected:
	Singleton() {}
	Singleton(const Singleton&) {};
};
