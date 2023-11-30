#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class ChessPiece;

enum class SubscriptionType {All};

class Observer {
 public:
  virtual void notify(ChessPiece &cp) = 0;  
  virtual SubscriptionType subType() = 0;
  virtual ~Observer() = default;
};
#endif
