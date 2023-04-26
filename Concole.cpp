#include "Console.h"

std::string Console::cin()
{
	std::unique_lock<std::mutex> ul(console);
	std::string input_str;
	std::cin >> input_str;
	return input_str;
}

void Console::out(std::string output_str)
{
	std::unique_lock<std::mutex> ul(console);
	std::cout << output_str;
}

void Console::putString(std::string message)
{
	std::unique_lock<std::mutex> ul(console);
	stack_message.push_back(message);
	if (stack_message.size() > 10) {
		for (auto message : stack_message)
			std::cout << message;

		stack_message.clear();
	}
}

Console::~Console()
{
	stack_message.clear();
}
