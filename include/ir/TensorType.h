//
// Created by Acer on 8/18/2026.
//

#ifndef TENSORTYPE_H
#define TENSORTYPE_H

#include "DType.h"
#include <vector>

class TensorType {
public:
    TensorType(DType dtype, std::vector<long> shape);
    DType dtype() const;
    const std::vector<long> &shape() const;

    int rank() const;
    long numElements() const;

    bool operator==(const TensorType &other) const;
    bool operator!=(const TensorType &other) const;

    private:
    DType dtype_;
    std::vector<long> shape_;
};



#endif //TENSORTYPE_H
