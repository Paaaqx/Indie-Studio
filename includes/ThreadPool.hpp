//
// ThreadPool.hpp for ThreadPool.hpp in /home/anthony/Documents/Tek2/C++/cpp_indie_studio
//
// Made by Anthony
// Login   <anthony.mercadal@epitech.eu>
//
// Started on  Wed May 10 11:24:09 2017 Anthony
// Last update Tue Aug 15 10:32:35 2017 Paqx
//

#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

# include <iostream>
# include <vector>
# include <thread>
# include <mutex>
# include <deque>
# include <condition_variable>
# include  <functional>
# include "IEntity.hpp"

class					ThreadPool
{
public:
  ThreadPool(int nbThread);
  ~ThreadPool();

public:
  void					putInQueue(std::function<void()> toPutInQueue);
  static void				funcPool(ThreadPool *pool);

public:
  std::vector<std::thread>		_pool;
  std::deque<std::function<void()>>	_tasks;
  std::mutex				_mutex;
  std::condition_variable		_cond;
  bool					_end;
  int					_nbThread;
};

#endif /* !THREADPOOL_HPP_ */
