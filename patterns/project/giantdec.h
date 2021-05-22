#ifndef GIANT_DECORATOR_H
#define GIANT_DECORATOR_H
#include "decorator.h"

class GiantDec : public Decorator {
public:
	GiantDec(Village* vill);
	void Accept(Visitor* visitor) override;
};

#endif