//
// Created by Acer on 8/18/2026.
//

#include "ir/TensorType.h"

TensorType::TensorType(DType dtype, std::vector<int64_t> shape)
    : dtype_(dtype), shape_(shape) {
}

DType TensorType::dtype() const {
    return dtype_;
}

const std::vector<int64_t> &TensorType::shape() const {
    return shape_;
}


int32_t TensorType::rank() const {
    return static_cast<int32_t>(shape_.size());
}

int64_t TensorType::numElements() const {
    int64_t n = 1;
    for (int64_t dim : shape_) {
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
