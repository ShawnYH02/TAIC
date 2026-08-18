//
// Created by Acer on 8/18/2026.
//

#ifndef TENSORTYPE_H
#define TENSORTYPE_H

#include "DType.h"
#include <vector>
#include <cstdint>

class TensorType {
public:
    TensorType(DType dtype, std::vector<int64_t> shape);
    DType dtype() const;
    const std::vector<int64_t> &shape() const;

    int32_t rank() const;
    int64_t numElements() const;

    bool operator==(const TensorType &other) const;
    bool operator!=(const TensorType &other) const;

    private:
    DType dtype_;
    std::vector<int64_t> shape_;
};



#endif //TENSORTYPE_H
