//
// Created by Acer on 8/18/2026.
//

#include <string>

#include "ir/Printer.h"

static std::string dtypeToString(DType dtype) {
    switch (dtype) {
        case DType::Float32:
            return "f32";
    }
    return "Unsupported dtype";
}


static std::string opKindtoString(OpKind kind) {
    switch (kind) {
        case OpKind::Input:
            return "Input";
        case OpKind::Constant:
            return "Constant";
        case OpKind::Add:
            return "Add";
        case OpKind::Mul:
            return "Mul";
        case OpKind::MatMul:
            return "MatMul";
        case OpKind::Relu:
            return "Relu";
    }
    return "Unsupported kind";
}

static void printTensorType(const TensorType &type, std::ostream &os) {
    os << "tensor<";

    const auto &shape = type.shape();
    for (size_t i = 0; i < shape.size(); i++) {
        if (i > 0) {
            os << "x";
        }
        os << shape[i];
    }

    os << "x" << dtypeToString(type.dtype()) << ">";
}


static void printValue(Value *value, std::ostream &os) {
    os << "%" << value->id();
}

void printGraph(const Graph &graph, std::ostream &os) {
    for (const auto &opPtr : graph.operations()) {
        Operation *op = opPtr.get();

        Value *result = op->result(0);
        printValue(result, os);

        os << " = " << opKindtoString(op->kind());

        for (Value *operand : op->operands()) {
            os << " ";
            printValue(operand, os);
        }

        os << " : ";
        printTensorType(result->type(), os);
        os << "\n";
    }

    os << "return";

    for (Value *output : graph.outputs()) {
        os << " ";
        printValue(output, os);
    }

    os << "\n";
}

