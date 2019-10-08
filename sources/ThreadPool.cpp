//
// ThreadPool.cpp for ThreadPool.cpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
//
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
//
// Started on  Wed May 10 11:23:57 2017 Anthony
// Last update Jan Jun 18 16:14:18 2017 Anthony Mercadal
//

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int nbThread)
{
  _nbThread = nbThread;
  _end = false;
  while (nbThread > 0)
    {
      _pool.push_back(std::thread(funcPool, this));
      --nbThread;
    }
}

ThreadPool::~ThreadPool()
{
  _end = true;
  _cond.notify_all();
  for (auto& it : _pool)
    it.join();
}

void				ThreadPool::putInQueue(std::function<void()> toPutInQueue)
{
  std::unique_lock<std::mutex>	lock(_mutex);

  _tasks.push_back(toPutInQueue);
  _cond.notify_one();
}

void			ThreadPool::funcPool(ThreadPool *pool)
{
  std::function<void()>	task;

  while (1)
    {
      std::unique_lock<std::mutex> lock(pool->_mutex);
      while (pool->_end != true && (pool->_tasks).empty())
	(pool->_cond).wait(lock);
      if (pool->_end == true)
	break;
      task = (pool->_tasks).front();
      (pool->_tasks).pop_front();
      task();
    }
}
