module;

export module receiver;
import Messaging;
import dispatcher;
import sender;
using namespace messaging;
export namespace messaging
{
  class receiver
  {
    queue q;
  public:
    operator sender()
    {
      return sender(&q);
    }
    dispatcher wait()
    {
      return dispatcher(&q);
    }
  };
};