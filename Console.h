#pragma once

#include <iostream>
#include <string.h>
#include <mutex>
#include <vector>

#include "Singleton.h"

class Console : public Singleton<Console>
{
public:
	std::string cin();
	void out(std::string);
	void putString(std::string message);
	~Console();
private:
	static Console* m_instance;
	std::mutex console;
	std::vector<std::string> stack_message;
};
