module;

export module Messaging;

import <mutex>;
import <condition_variable>;
import <memory>;
import <queue>;

export namespace messaging
{
  struct message_base
  {
    virtual ~message_base() {};
  };

  template <typename Msg>
  struct wrapped_message : message_base
  {
    Msg contents;
    explicit wrapped_message(Msg const& contents_) : contents(contents_) {}
  };

  class queue
  {
    std::mutex m;
    std::condition_variable c;
    std::deque<std::shared_ptr<message_base>> q;
  public:
    template <typename T>
    void push(T const& msg)
    {
      std::scoped_lock<std::mutex> lk(m);
      q.push_back(std::make_shared<wrapped_message<T>>(msg));
      c.notify_all();
    }

    std::shared_ptr<message_base> wait_and_pop()
    {
      std::unique_lock<std::mutex> lk(m);
      c.wait(lk, [&] { return !q.empty(); });
      auto res = q.front();
      q.pop_front();
      return res;
    }
  };
};

