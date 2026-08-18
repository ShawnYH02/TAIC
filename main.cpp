#include <iostream>
#include <memory>

#include "ir/TensorType.h"
#include "ir/Value.h"
#include "ir/Operation.h"

int main() {
    TensorType a(DType::Float32, {1, 2, 3, 4});
    TensorType b(DType::Float32, {1, 3, 4});
    TensorType c(DType::Float32, {1, 3,  4});
    Value v(0, TensorType(DType::Float32, {2, 4}), nullptr);

    auto result = std::make_unique<Value>(1, TensorType(DType::Float32, {2, 4}), nullptr);

    std::vector<std::unique_ptr<Value>> res;
    res.push_back(std::move(result));

    Operation op(OpKind::MatMul, {&v}, std::move(res));

    std::cout << a.rank() << std::endl;
    std::cout << b.numElements() << std::endl;
    std::cout << (b == c) << std::endl;
    std::cout << (a != b) << std::endl;

    std::cout << v.id() << std::endl;
    std::cout << v.type().rank() << std::endl;
    std::cout << (v.defOp() == nullptr) << std::endl;

    std::cout << static_cast<int>(op.kind()) << std::endl;
    std::cout << op.operands().size() << std::endl;
    std::cout << op.results().size() << std::endl;
    return 0;
}

