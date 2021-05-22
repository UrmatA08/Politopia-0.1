#ifndef RIDER_DECORATOR_H
#define RIDER_DECORATOR_H
#include "decorator.h"

class RiderDec : public Decorator {
public:
	RiderDec(Village* vill);
	void Accept(Visitor* visitor) override;
};

#endif