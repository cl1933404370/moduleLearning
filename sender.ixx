module;

export module sender;
import Messaging;
using namespace messaging;
export namespace messaging
{
  class sender
  {
    queue* q;
  public:
    sender() : q(nullptr) {}
    explicit sender(queue* q_) : q(q_) {}
    template <typename Message>
    void send(Message const& msg)
    {
      if (q)
        q->push(msg);
    }
  };
};
