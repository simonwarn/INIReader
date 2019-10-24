# INIReader
INI reader that works like GetPrivateProfileString/WritePrivateProfileString but with a lot better performance

file
```
[User1]
Age=31
Name=mikael tratt
[User2]
Age=18
Name=sara larsson
```
Example
```cpp
int main()
{
	INIREADER INI;
	if (INI.SaveFile("C:/Users/Public/test.ini")) // Save to file
	{
		INI.WriteString("User1", "Age", "31");
		INI.WriteString("User1", "Name", "mikael tratt");

		INI.WriteString("User2", "Age", "18");
		INI.WriteString("User2", "Name", "sara larsson");

		INI.Close();
	}

	if (INI.OpenFile("C:/Users/Public/test.ini")) // Load from file
	{
		std::cout << INI.GetString("User1", "Age") << std::endl;
		std::cout << INI.GetString("User1", "Name") << std::endl;

		std::cout << INI.GetString("User2", "Age") << std::endl;
		std::cout << INI.GetString("User2", "Name") << std::endl;

		INI.Close();
	}
}
```
