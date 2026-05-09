#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>
class WindowsMessageMap
{
public:
	WindowsMessageMap();
	std::wstring operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
	std::unordered_map<DWORD, std::wstring> map;
};