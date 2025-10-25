#include "APropertyAnimator.h"

APropertyAnimator::APropertyAnimator() : type_("")
{}

APropertyAnimator::APropertyAnimator(std::string type) : type_(type)
{}

APropertyAnimator::~APropertyAnimator(){}

std::string APropertyAnimator::getType() const { return (type_); }