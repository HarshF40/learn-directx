#pragma once
#include<windows.h>
#include<unordered_map> //allows for efficient key-value pair storage and retrieval using hash tables
#include<string>

class WindowsMessageMap {
public :
	WindowsMessageMap();
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
	std::unordered_map<DWORD, std::string> map;
};