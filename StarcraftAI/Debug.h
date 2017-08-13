
#pragma once

#include <string>

namespace Debug
{

	void Log(int Out);
	void Log(float Out);
	void Log(bool Out);
	void Log(char Out[]);
	void Log(std::string Out);
	void Log(uint32_t Out);
	void Prompt();

}