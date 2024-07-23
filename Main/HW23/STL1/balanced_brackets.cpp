#include "balanced_brackets.h"
#include <stack>

bool areBracketsBalanced(const std::string& line) {
    std::stack<char> stack;
    for (char ch : line) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.empty()) {
                return false;
            }
            char top = stack.top();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty();
}
