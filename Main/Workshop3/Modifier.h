#pragma once

#include <string>
#include <functional>

class Modifier {
public:
    using EffectFunction = std::function<void(int&)>;

    Modifier(std::string name, EffectFunction effect);
    virtual ~Modifier();
    std::string getName() const;
    void applyEffect(int& value) const;
private:
    std::string name;
    EffectFunction effect;
};
