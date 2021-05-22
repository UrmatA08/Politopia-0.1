#ifndef DECORATOR_H
#define DECORATOR_H
#include "village.h"

class Visitor;

class Decorator {
public:
	std::vector<Unit*> squad_;
	Village* village_;

	virtual void Accept(Visitor* visitor) = 0;
	virtual ~Decorator() = default;
};

#endif