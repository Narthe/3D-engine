#include "platform.hpp"
#include <windows.h>

std::string ResourcePath(std::string fileName) {
    char ProjectDir[1024] = {'\0'};
    DWORD charsCopied = GetCurrentDirectoryA(1024, ProjectDir);
	if (charsCopied > 0 && charsCopied < 1024)
	{
		std::string res = std::string(ProjectDir) + "\\..\\res\\" + fileName;
		return res;
	}
    else
        throw std::runtime_error("GetModuleFileName failed a bit");
}

