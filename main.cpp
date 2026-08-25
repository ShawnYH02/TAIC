#include <iostream>
#include <memory>

#include "ir/TensorType.h"
#include "ir/Value.h"
#include "ir/Operation.h"
#include "ir/Graph.h"
#include "ir/Printer.h"

int main() {
    TensorType a(DType::Float32, {1, 2, 3, 4});
    TensorType b(DType::Float32, {1, 3, 4});
    TensorType c(DType::Float32, {1, 3,  4});
    Value v(0, TensorType(DType::Float32, {2, 4}), nullptr);

    auto result = std::make_unique<Value>(1, TensorType(DType::Float32, {2, 4}), nullptr);

    std::vector<std::unique_ptr<Value>> res;
    res.push_back(std::move(result));

    Operation op(OpKind::MatMul, {&v}, std::move(res));

    Graph g;
    Value *va = g.addInput(TensorType(DType::Float32, {1, 2, 3, 4}));
    Value *vb = g.addInput(TensorType(DType::Float32, {1, 3, 4, 5}));
    Value *vc = g.addBinary(OpKind::Add, va, vb, TensorType(DType::Float32, {2, 3, 4, 5}));

    g.addOutput(vc);

    std::cout << g.operations().size() << std::endl;
    std::cout << g.outputs().size() << std::endl;
    std::cout << vc->id() << std::endl;
    std::cout << (vc->defOp() != nullptr) << std::endl;


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

    printGraph(g, std::cout);
    return 0;
}

