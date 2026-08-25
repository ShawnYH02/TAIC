//
// Created by Acer on 8/18/2026.
//

#ifndef OPERATION_H
#define OPERATION_H
#include <memory>
#include "ir/Value.h"
#include <vector>

enum OpKind {
    Input,
    Constant,
    Add,
    Mul,
    MatMul,
    Relu
};

class Operation {
public:
    Operation(OpKind kind, std::vector<Value*> operands, std::vector<std::unique_ptr<Value>> results);

    OpKind kind() const;
    const std::vector<Value*> &operands() const;
    const std::vector<std::unique_ptr<Value>> &results() const;

    Value *result(int32_t idx) const;

    private:
    OpKind kind_;
    std::vector<Value*> operands_;
    std::vector<std::unique_ptr<Value>> results_;
};

#endif //OPERATION_H
