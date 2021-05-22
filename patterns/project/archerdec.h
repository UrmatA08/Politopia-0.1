#ifndef ARCHER_DECORATOR_H
#define ARCHER_DECORATOR_H
#include "decorator.h"

class ArcherDec : public Decorator {
public:
	ArcherDec(Village* vill);
	void Accept(Visitor* visitor) override;
};

#endif