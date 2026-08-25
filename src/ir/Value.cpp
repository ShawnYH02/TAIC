//
// Created by Acer on 8/18/2026.
//

#include "ir/Value.h"

Value::Value(int32_t id, TensorType type, Operation *defOp)
    : id_(id), type_(type), defOp_(defOp) {
}

int32_t Value::id() const {
    return id_;
}

const TensorType &Value::type() const {
    return type_;
}

Operation *Value::defOp() const {
    return defOp_;
}

void Value::setDefOp(Operation *defOp) {
    defOp_ = defOp;
}


