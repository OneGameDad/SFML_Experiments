#pragma once

#include <string>

class APropertyAnimator
{
private:
    std::string type_;
public:
    APropertyAnimator();
    APropertyAnimator(std::string type);
    virtual ~APropertyAnimator();

    std::string getType() const;
};