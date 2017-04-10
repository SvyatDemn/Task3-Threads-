#include "Parser.h"
#include <Windows.h>

namespace ISXParser
{

void Data::ShowData()
{
	std::cout << "All files: " << all_files << std::endl;
	std::cout << "All lines: " << all_lines << std::endl;
	std::cout << "Empty lines: " << empty_lines << std::endl;
	std::cout << "Commented lines: " << comment_lines << std::endl;
	std::cout << "Code lines: " << all_lines - empty_lines - comment_lines << std::endl;
	std::cout << "Parsing time: " << time << std::endl;
}
	
void Data::SaveData()
{
	std::ofstream out("info.txt");
	out << "All files: " << all_files << std::endl;
	out << "All lines: " << all_lines << std::endl;
	out << "Empty lines: " << empty_lines << std::endl;
	out << "Commented lines: " << comment_lines << std::endl;
	out << "Code lines: " << all_lines - empty_lines - comment_lines << std::endl;
	out << "Parsing time: " << time << std::endl;
	out.close();
}

void Data::Searching(fs::path root_folder)
{
	for (fs::recursive_directory_iterator it(root_folder), end; it != end; ++it) 
	{
		if (it->path().extension() == ".cpp" || it->path().extension() == ".c" 
			|| it->path().extension() == ".hpp" || it->path().extension() == ".h")
		{
			files.Add((*it).path().string());
		}
	}
	is_searching = false;
}

void Data::Parsing()
{
	while(is_searching || !files.Empty())
	{
		std::string file_path = files.Pop();
		std::ifstream file;
		file.open(file_path);
		all_files++;
		bool is_multiline = false;
		std:: string line;
		while(std::getline(file,line))
		{
			all_lines++;
			if(line.empty())
		{
			empty_lines++;
		}
		else if(is_multiline)
		{
			comment_lines++;
			if(line.find("*/") != std::string::npos)
			{
				is_multiline = false;
			}
		}
		else if(line.find("//"))
		{
			comment_lines++;
		}
		else if(line.find("/*") == std::string::npos)
		{
			is_multiline = true;
		}
		}
	file.close();
	}
}

}
