#include <iostream>
#include "ir/TensorType.h"
#include "ir/Value.h"

int main() {
    TensorType a(DType::Float32, {1, 2, 3, 4});
    TensorType b(DType::Float32, {1, 3, 4});
    TensorType c(DType::Float32, {1, 3,  4});
    Value v(0, TensorType(DType::Float32, {2, 4}), nullptr);

    std::cout << a.rank() << std::endl;
    std::cout << b.numElements() << std::endl;
    std::cout << (b == c) << std::endl;
    std::cout << (a != b) << std::endl;

    std::cout << v.id() << std::endl;
    std::cout << v.type().rank() << std::endl;
    std::cout << (v.defOp() == nullptr) << std::endl;

    return 0;
}

