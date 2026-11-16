#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> values = {
        3, 12, 7, 20, 15, 4, 18
    };

    int threshold = 10;

    int above_threshold = std::count_if(
        values.begin(), 
        values.end(), 
        [threshold](int n) { 
            return n > threshold; 
        }
    );

    std::cout << "Above " << threshold << ": " << above_threshold << " numbers." << std::endl; 
}