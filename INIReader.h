#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 
class INIREADER
{
public:
	bool OpenFile(const char* Filepath, int flag = std::fstream::in | std::fstream::out);
	bool SaveFile(const char* Filepath, int flag = std::fstream::in | std::fstream::out);
	int GetGroupCount();
	bool Close();
	bool WriteStrings(std::string AppName, std::vector<std::string>& strings);
	std::vector<std::string> GetStrings(std::string AppName);
	std::string GetString(std::string AppName, std::string KeyName);
	bool WriteString(std::string AppName, std::string KeyName, std::string Value);
	struct AppIndex { std::string Name; int Index = -1; AppIndex(int ind, std::string name) { Name = name, Index = ind; }; };
	std::vector<AppIndex> Applines;
	std::vector<std::string> Lines;
private:
	std::fstream file;
};