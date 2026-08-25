//
// Created by Acer on 8/18/2026.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "Operation.h"
#include "TensorType.h"
#include "Value.h"

class Graph {
    public:
    Value *addInput(const TensorType &type);
    Value *addUnary(OpKind kind, Value *input, const TensorType &resultType);
    Value *addBinary(OpKind kind, Value *lhs, Value *rhs, const TensorType &resultType);

    void addOutput(Value *value);

    const std::vector<std::unique_ptr<Operation>> &operations() const;
    const std::vector<Value*> &outputs() const;

    private:
    int32_t nextValueId_ = 0;
    std::vector<std::unique_ptr<Operation>> operations_;
    std::vector<Value*> outputs_;
};

#endif //GRAPH_H
