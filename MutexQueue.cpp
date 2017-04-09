#include "MutexQueue.h"

namespace ISXParser
{

MutexQueue::MutexQueue(void) : queue_(), mutex_(), condvar_()
{
}

void MutexQueue::Add(std::string adding)
{
	std::lock_guard<std::mutex> locker(mutex_);
	queue_.emplace(adding);
	condvar_.notify_one();
}

std::string MutexQueue::Pop()
{
	std::unique_lock<std::mutex> locker(mutex_);

	while (queue_.empty())
	{
		condvar_.wait(locker);
	}
	std::string adding = queue_.front();
	queue_.pop();
	return adding;
}

bool MutexQueue::Empty() const
{
	std::lock_guard<std::mutex> locker(mutex_);
	return queue_.empty();
}

}