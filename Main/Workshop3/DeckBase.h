#pragma once

#include <vector>
#include <memory>
#include <random>
#include <algorithm>

// Template class for generic deck
template <typename T>
class DeckBase {
public:
    DeckBase();
    void addElement(std::unique_ptr<T> element);
    std::unique_ptr<T> generateElement();
    size_t size() const { return elements.size(); }

private:
    std::vector<std::unique_ptr<T>> elements;
};

template <typename T>
DeckBase<T>::DeckBase() = default;

template <typename T>
void DeckBase<T>::addElement(std::unique_ptr<T> element) {
    elements.push_back(std::move(element));
}

template <typename T>
std::unique_ptr<T> DeckBase<T>::generateElement() {
    if (elements.empty()) return nullptr;

    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, elements.size() - 1);

    size_t index = dist(rng);
    std::unique_ptr<T> element = std::move(elements[index]);
    elements.erase(elements.begin() + index);
    return element;
}