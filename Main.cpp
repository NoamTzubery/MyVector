#include <iostream>
#include "Vector.hpp" 

template<typename T>
void print_vector(const Vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    Vector<int> vec;

    // Test push_back and size
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "Size after pushing back 3 elements: " << vec.size() << std::endl;
    std::cout << "Vector contents: ";
    print_vector(vec);

    // Test pop_back
    vec.pop_back();
    std::cout << "Size after popping back one element: " << vec.size() << std::endl;
    std::cout << "Vector contents: ";
    print_vector(vec);

    // Test insert
    vec.insert(1, 42);
    std::cout << "Size after inserting one element: " << vec.size() << std::endl;
    std::cout << "Vector contents: ";
    print_vector(vec);

    // Test empty
    std::cout << "Is the vector empty? " << (vec.empty() ? "Yes" : "No") << std::endl;

    // Test reverse
    std::cout << "Vector before reversing: ";
    print_vector(vec);
    vec.reverse();
    std::cout << "Vector after reversing: ";
    print_vector(vec);
    std::cout << "Size after reversing: " << vec.size() << std::endl;

    return 0;
}
