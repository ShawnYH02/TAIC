//
// Created by Acer on 8/25/2026.
//

#include "ir/Graph.h"

Value *Graph::addInput(const TensorType &type) {
    std::vector<Value*> operands;
    std::vector<std::unique_ptr<Value>> results;
    results.push_back(std::make_unique<Value>(++nextValueId_, type, nullptr));

    auto op = std::make_unique<Operation>(OpKind::Input, std::move(operands), std::move(results));

    Operation *opPtr = op.get();
    opPtr->result(0)->setDefOp(opPtr);

    operations_.push_back(std::move(op));

    return opPtr->result(0);
}

Value *Graph::addUnary(OpKind kind, Value *input, const TensorType &resultType) {
    std::vector<Value*> operands;

    std::vector<std::unique_ptr<Value>> results;
    results.push_back(std::make_unique<Value>(nextValueId_++, resultType, nullptr));

    auto op = std::make_unique<Operation>(kind, std::move(operands), std::move(results));

    Operation *opPtr = op.get();
    opPtr->result(0)->setDefOp(opPtr);

    operations_.push_back(std::move(op));

    return opPtr->result(0);
}

Value *Graph::addBinary(OpKind kind, Value *lhs, Value *rhs, const TensorType &resultType) {
    std::vector<Value*> operands;

    operands.push_back(lhs);
    operands.push_back(rhs);

    std::vector<std::unique_ptr<Value>> results;
    results.push_back(std::make_unique<Value>(nextValueId_++, resultType, nullptr));

    auto op = std::make_unique<Operation>(kind, std::move(operands), std::move(results));

    Operation *opPtr = op.get();
    opPtr->result(0)->setDefOp(opPtr);

    operations_.push_back(std::move(op));

    return opPtr->result(0);
}

void Graph::addOutput(Value *value) {
    outputs_.push_back(value);
}

const std::vector<std::unique_ptr<Operation>> &Graph::operations() const {
    return operations_;
}

const std::vector<Value *> &Graph::outputs() const {
    return outputs_;
}




