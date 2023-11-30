#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Board;

enum class SubscriptionType {All};

class Observer {
 public:
  virtual void notify(Board &cb) = 0;  
  virtual SubscriptionType subType() = 0;
  virtual ~Observer() = default;
};
#endif
