#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> numbers = {
        5, 2, 8, 2, 10, 5, 3, 8
    };

    std::sort(numbers.rbegin(), numbers.rend());

    auto new_end = std::unique(numbers.begin(), numbers.end());

    numbers.erase(new_end, numbers.end());

    for (int i : numbers) {
        std::cout << i << " ";
    }

    return 0;
}