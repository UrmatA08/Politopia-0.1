#ifndef DRAGON_DECORATOR_H
#define DRAGON_DECORATOR_H
#include "decorator.h"

class DragonDec : public Decorator {
public:
	DragonDec(Village* vill);
	void Accept(Visitor* visitor) override;
};

#endif