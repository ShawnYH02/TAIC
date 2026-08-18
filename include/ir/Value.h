//
// Created by Acer on 8/18/2026.
//

#ifndef VALUE_H
#define VALUE_H

#include "TensorType.h"

class Operation;


class Value {
    public:
    Value(int32_t id, TensorType type, Operation *defOp);

    int32_t id() const;
    const TensorType &type() const;
    Operation *defOp() const;

private:
    int32_t id_;
    TensorType type_;
    Operation *defOp_;
};

#endif //VALUE_H
