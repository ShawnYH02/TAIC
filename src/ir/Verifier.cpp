//
// Created by Acer on 8/18/2026.
//
#include "ir/Verifier.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>


static bool check(bool condition, std::ostream &os, const std::string &msg) {
    if (!condition) {
        os << "verification error: " << msg << std::endl;
        return false;
    }
    return true;
}

static bool verifyAdd(Operation *op, std::ostream &os) {
    bool valid = true;

    valid &= check(op->operands().size() == 2, os, "Add must have exactly 2 operands");
    valid &= check(op->results().size() == 1, os, "Add must have exactly 1 result");

    if (!valid) {
        return false;
    }

    Value *lhs = op->operands()[0];
    Value *rhs = op->operands()[1];
    Value *res = op->result(0);

    valid &= check(lhs != nullptr, os, "Add lhs operand is null");
    valid &= check(rhs != nullptr, os, "Add rhs operand is null");
    valid &= check(res != nullptr, os, "Add result operand is null");

    if (!valid) {
        return false;
    }

    valid &= check(lhs->type() == rhs->type(), os, "Add operand type mismatch");
    valid &= check(res->type() == lhs->type(), os, "Add result type mismatch");

    return valid;
}

static bool verifyMul(Operation *op, std::ostream &os) {
    bool valid = true;

    valid &= check(op->operands().size() == 2, os, "Mul must have exactly 2 operands");
    valid &= check(op->results().size() == 1, os, "Mul must have exactly 1 result");

    if (!valid) {
        return false;
    }

    Value *lhs = op->operands()[0];
    Value *rhs = op->operands()[1];
    Value *res = op->result(0);

    valid &= check(lhs != nullptr, os, "Mul lhs operand is null");
    valid &= check(rhs != nullptr, os, "Mul rhs operand is null");
    valid &= check(res != nullptr, os, "Mul result operand is null");

    if (!valid) {
        return false;
    }

    valid &= check(lhs->type() == rhs->type(), os, "Mul operand type mismatch");
    valid &= check(res->type() == lhs->type(), os, "Mul result type mismatch");

    return valid;
}

  static bool verifyMatMul(Operation *op, std::ostream &os) {
      bool valid = true;

      valid &= check(op->operands().size() == 2, os, "Matmul must have exactly 2 operands");
      valid &= check(op->results().size() == 1, os, "Matmul must have exactly 1 result");

      if (!valid) {
          return false;
      }

      Value *lhs = op->operands()[0];
      Value *rhs = op->operands()[1];
      Value *res = op->result(0);

      valid &= check(lhs != nullptr, os, "Matmul lhs operand is null");
      valid &= check(rhs != nullptr, os, "Matmul rhs operand is null");
      valid &= check(res != nullptr, os, "Matmul result operand is null");

      if (!valid) {
          return false;
      }

      valid &= check(lhs->type().dtype() == rhs->type().dtype(), os, "Matmul operand dtype mismatch");
      valid &= check(res->type().dtype() == lhs->type().dtype(), os, "Matmul result dtype mismatch");
      valid &= check(lhs->type().rank() >= 2 && rhs->type().rank() >= 2, os, "Either shape is not a matrix");
      valid &= check(res->type().rank() >= 2, os, "Matmul result rank must be at least 2");

      if (!valid) {
          return false;
      }

      const auto &rhsShape = rhs->type().shape();
      const auto &lhsShape = lhs->type().shape();
      const auto &resShape = res->type().shape();

      auto verifyBatchBroadCast = [](const auto &va, const auto &vb) {
          int32_t ra = static_cast<int32_t>(va.size()) - 2;
          int32_t rb = static_cast<int32_t>(vb.size()) - 2;

          int32_t r = std::max(ra, rb);

          auto canBroadcast = [](int64_t a, int64_t b) {
              return a == b || a == 1 || b == 1;
          };

          for (int32_t i = 0; i < r; ++i) {
              int32_t ia = ra - i - 1;
              int32_t ib = rb - i - 1;

              int64_t da = (ia >= 0) ? va[ia] : 1;
              int64_t db = (ib >= 0) ? vb[ib] : 1;

              if (!canBroadcast(da, db)) {
                  return false;
              }
          }

          return true;
      };

      auto matmulShape = [](const auto &va, const auto &vb) -> std::vector<int64_t> {
          std::vector<int64_t> out;

          int32_t ra = static_cast<int32_t>(va.size()) - 2;
          int32_t rb = static_cast<int32_t>(vb.size()) - 2;

          int32_t r = std::max(ra, rb);

          for (int32_t i = r - 1; i >= 0; --i) {
              int32_t ia = i - (r - ra);
              int32_t ib = i - (r - rb);

              int64_t da = (ia >= 0) ? va[ia] : 1;
              int64_t db = (ib >= 0) ? vb[ib] : 1;

              out.push_back(std::max(da, db));
          }

          out.push_back(va[va.size() - 2]);
          out.push_back(vb[vb.size() - 1]);

          return out;
      };

      valid &= check(verifyBatchBroadCast(lhsShape, rhsShape), os, "Cannot broadcast");
      valid &= check(lhsShape.back() == rhsShape[rhsShape.size() - 2], os, "Matrix shape mismatch");
      valid &= check(resShape == matmulShape(lhsShape, rhsShape), os, "Output shape mismatch");

      return valid;
}


static bool verifyRelu(Operation *op, std::ostream &os) {
    bool valid = true;

    valid &= check(op->operands().size() == 1, os, "Add must have exactly 1 operands");
    valid &= check(op->results().size() == 1, os, "Add must have exactly 1 result");

    if (!valid) {
        return false;
    }

    Value *lhs = op->operands()[0];
    Value *res = op->result(0);

    valid &= check(lhs != nullptr, os, "Add lhs operand is null");
    valid &= check(res != nullptr, os, "Add result operand is null");

    if (!valid) {
        return false;
    }

    valid &= check(res->type() == lhs->type(), os, "Add result type mismatch");

    return valid;

}

static bool verifyInput(Operation *op, std::ostream &os) {
    bool valid = true;

    valid &= check(op->operands().empty(), os, "Input must have exactly 0 operands");
    valid &= check(op->results().size() == 1, os, "Input must have exactly 1 result");

    return valid;
}


static bool verifyOperation(Operation *op, std::ostream &os) {
    bool valid = true;

    valid &= check(op != nullptr, os, "Operation is null");

    if (!valid) {
        return false;
    }

    for (auto &res : op->results()) {
        valid &= check(res != nullptr, os, "Operation has null result");
        if (res != nullptr) {
            valid &= check(res->defOp() == op, os, "result defining operation is incorrect");
        }
    }

    switch (op->kind()) {
        case OpKind::Add: {
            valid &= verifyAdd(op, os);
            break;
        }
        case OpKind::Mul: {
            valid &= verifyMul(op, os);
            break;
        }
        case OpKind::Relu: {
            valid &= verifyRelu(op, os);
            break;
        }
        case OpKind::MatMul: {
            valid &= verifyMatMul(op, os);
            break;
        }
        case OpKind::Input: {
            valid &= verifyInput(op, os);
            break;
        }

        default: break;
    }
    return valid;
}


bool verifyGraph(const Graph &graph, std::ostream &os) {
    bool valid = true;

    for (auto &opPtr : graph.operations()) {
        valid &= check(opPtr != nullptr, os, "graph contains null operation");

        if (opPtr != nullptr) {
            valid &= verifyOperation(opPtr.get(), os);
        }
    }

    for (Value *output : graph.outputs()) {
        valid &= check(output != nullptr, os, "graph output is null");
    }

    return valid;
}