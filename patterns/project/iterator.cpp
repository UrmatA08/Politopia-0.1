#include "iterator.h"
#include "decorator.h"

Unit* UnitIterator::Next(Decorator* dec, Unit* unit) {
    for (int i = idx_; i < dec->village_->current_number_of_units_; ++i) {
        if (unit->model_ == dec->village_->army_[i]->model_) {
            ++idx_;
            return dec->village_->army_[i];
        }
    }
    return nullptr;
}