#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace ISXParser
{

class MutexQueue
{
public:
	MutexQueue(void);

	void Add(std::string adding);
	std::string Pop();

	bool Empty() const;

private:
	std::queue<std::string> queue_;
	mutable std::mutex mutex_;
	std::condition_variable condvar_;
};

}