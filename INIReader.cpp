#include "INIReader.h"

bool INIREADER::OpenFile(const char* Filepath, int flag)
{
	file.open(Filepath, flag);
	if (!file.good())
		return false;

	Applines.clear();
	Lines.clear();

	std::string str;
	int index = 0;
	while (std::getline(file, str))
	{
		Lines.insert(Lines.end(), str);
		if (str.size() && str.c_str()[0] == '[')
			Applines.insert(Applines.end(), AppIndex(index, str));
		str.clear();
		index++;
	}
	if (Lines.size() && Applines.size())
		return true;

	Close();
	return false;
}

bool INIREADER::SaveFile(const char* Filepath, int flag)
{
	file.open(Filepath, std::fstream::out);
	if (!file.good())
		return false;

	Applines.clear();
	Lines.clear();

	return true;
}

int INIREADER::GetGroupCount()
{
	return Applines.size();
}

bool INIREADER::Close()
{
	for(std::string str : Lines)
		file << str.c_str() << std::endl;

	file.close();
	Lines.clear();
	Applines.clear();
	return false;
}
bool INIREADER::WriteStrings(std::string AppName, std::vector<std::string>& strings)
{
	for (size_t i = 0; i < strings.size(); i++)
	{
		WriteString(AppName, std::to_string(i), strings.at(i));
	}
	return false;
}
std::vector<std::string> INIREADER::GetStrings(std::string AppName)
{
	std::vector<std::string> temp;
	if (!Lines.size() || !Applines.size())
		return temp;

	for (size_t appname = 0; appname < Applines.size(); appname++)
	{
		std::string str = std::string("[") + AppName.c_str() + "]";
		if (!strcmp(str.c_str(), Applines.at(appname).Name.c_str()))
		{
			for (size_t key = Applines.at(appname).Index + 1; key < Lines.size(); key++)
			{
				std::string full_str_temp = Lines.at(key);
				if (full_str_temp.at(0) == '[')
					return temp;
				int offset = full_str_temp.find('=');
				std::string key_name = full_str_temp.substr(0, offset);
				std::string val = full_str_temp.substr(offset + 1);
				temp.push_back(val);
			}
		}
	}
	return temp;
}

std::string INIREADER::GetString(std::string AppName, std::string KeyName)
{
	if (!Lines.size() || !Applines.size())
		return std::string();

	for (size_t appname = 0; appname < Applines.size(); appname++)
	{
		std::string str = std::string("[") + AppName.c_str() + "]";
		if (!strcmp(str.c_str(), Applines.at(appname).Name.c_str()))
		{
			for (size_t key = Applines.at(appname).Index + 1; key < Lines.size(); key++)
			{
				std::string full_str_temp = Lines.at(key);
				if (full_str_temp.at(0) == '[')
					return std::string();
				int offset = full_str_temp.find('=');
				std::string key_name = full_str_temp.substr(0, offset);
				if (!strcmp(KeyName.c_str(), key_name.c_str()))
					return full_str_temp.substr(offset + 1);
			}
		}
	}
	return std::string();
}

bool INIREADER::WriteString(std::string AppName, std::string KeyName, std::string Value)
{
	for (size_t appname = 0; appname < Applines.size(); appname++)
	{
		std::string str = std::string("[") + AppName.c_str() + "]";
		if (!strcmp(str.c_str(), Applines.at(appname).Name.c_str()))
		{

			for (size_t key = Applines.at(appname).Index + 1; key < Lines.size(); key++)
			{
				std::string full_str_temp = Lines.at(key);
				if (full_str_temp.at(0) == '[')
					break;
				int offset = full_str_temp.find('=');
				std::string key_name = full_str_temp.substr(0, offset);
				if (!strcmp(KeyName.c_str(), key_name.c_str()))
				{
					Lines.at(key) = std::string(KeyName) + "=" + Value.c_str();
					return true;
				}
			}
			std::string val = KeyName + "=" + Value;
			Lines.insert(Lines.begin() + Applines.at(appname).Index + 1, val);

			for (size_t i = appname + 1; i < Applines.size(); i++)
				Applines.at(i).Index++;
			return true;
		}
	}
	Lines.insert(Lines.end(), (std::string("[") + AppName.c_str() + "]").c_str());
	Applines.insert(Applines.end(), AppIndex(Lines.size(), (std::string("[") + AppName.c_str() + "]").c_str()));
	Lines.insert(Lines.end(), std::string(KeyName) + "=" + Value.c_str());
	return false;
}