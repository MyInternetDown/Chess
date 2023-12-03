#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Board;

enum class SubscriptionType {All};

class Observer {
 public:
  virtual void notify(char board[8][8]) = 0;  
  virtual SubscriptionType subType() = 0;
  virtual ~Observer() {};
};
#endif
