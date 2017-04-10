#pragma once
#include <atomic>
#include <iostream>
#include <fstream>
#include "boost/filesystem/operations.hpp"
#include <boost/filesystem/fstream.hpp>
#include <string>
#include <vector>
#include <thread>
#include "MutexQueue.h"

namespace fs = boost::filesystem;
namespace ISXParser
{

class Data
{
public:
	Data::Data(): files(), is_searching(true), all_files(0), all_lines(0), empty_lines(0), comment_lines(0), time(0)
{
}
	void Searching(fs::path root_folder);
	void Parsing();
	void ShowData();
	void SaveData();
	void SetTime(unsigned int time_) { time = time_; };

private:
	MutexQueue files;
	bool is_searching;
	std::atomic<unsigned int> all_files;
	std::atomic<unsigned int> all_lines;
	std::atomic<unsigned int> empty_lines;
	std::atomic<unsigned int> comment_lines;
	unsigned int time;
	
};

}



