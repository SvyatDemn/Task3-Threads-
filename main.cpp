#include "Parser.h"
namespace fs = boost::filesystem;
using namespace ISXParser;

int main()
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	std::string root_folder = "E:\\boost\\boost_1_63_0\\boost";
	unsigned int threads = std::thread::hardware_concurrency();
	//std::cout<< threads << std::endl;
	Data data;
	std::vector<std::thread> parsing;
	std::thread searching(std::bind(&Data::Searching, std::ref(data), root_folder));
	searching.join();
	for(unsigned int i = 0; i < threads; i++)
		parsing.emplace_back(std::thread(std::bind(&Data::Parsing, std::ref(data))));
	for(unsigned int j = 0; j < parsing.size(); j++)
		parsing[j].join();
	std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
	auto finaltime = std::chrono::duration_cast<std::chrono::seconds>(finish-start).count();
	data.SetTime(finaltime);
	data.ShowData();
	data.SaveData();
	system("pause");
}
