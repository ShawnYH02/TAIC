#include <iostream>
#include "ir/TensorType.h"

int main() {
    TensorType a(DType::Float32, {1, 2, 3, 4});
    TensorType b(DType::Float32, {1, 3, 4});
    TensorType c(DType::Float32, {1, 3,  4});

    std::cout << a.rank() << std::endl;
    std::cout << b.numElements() << std::endl;
    std::cout << (b == c) << std::endl;
    std::cout << (a != b) << std::endl;

    return 0;
}

