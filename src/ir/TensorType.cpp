//
// Created by Acer on 8/18/2026.
//

#include "ir/TensorType.h"

TensorType::TensorType(DType dtype, std::vector<long> shape)
    : dtype_(dtype), shape_(shape) {
}

DType TensorType::dtype() const {
    return dtype_;
}

const std::vector<long> &TensorType::shape() const {
    return shape_;
}


int TensorType::rank() const {
    return static_cast<int>(shape_.size());
}

long TensorType::numElements() const {
    long n = 1;
    for (long dim : shape_) {
        n *= dim;
    }

    return n;
}

bool TensorType::operator==(const TensorType &other) const {
    return dtype_ == other.dtype_ && shape_ == other.shape_;
}

bool TensorType::operator!=(const TensorType &other) const {
    return !(*this == other);
}
