//
// Created by Acer on 8/18/2026.
//

#include "ir/Operation.h"

Operation::Operation(OpKind kind, std::vector<Value *> operands, std::vector<std::unique_ptr<Value> > results)
    : kind_(kind), operands_(std::move(operands)), results_(std::move(results)) {
}

OpKind Operation::kind() const {
    return kind_;
}

const std::vector<Value*> &Operation::operands() const {
    return operands_;
}

const std::vector<std::unique_ptr<Value>> &Operation::results() const {
    return results_;
}

Value *Operation::result(int32_t idx) {
    return results_[idx].get();
}


