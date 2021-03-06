#pragma once
#include <mlir/IR/Dialect.h>
#include <mlir/IR/OpDefinition.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>

#include <string>

using namespace mlir;  // NOLINT
namespace cinnrt::dt {

namespace detail {
struct TensorTypeStorage;
}  // namespace detail

enum class TargetType : uint8_t { X86, CUDA };
enum class LayoutType : uint8_t { NCHW, NHWC };
enum class PrecisionType : uint8_t { I32, F32 };

llvm::Optional<TargetType> GetTargetType(mlir::StringRef key);
llvm::Optional<LayoutType> GetLayoutType(mlir::StringRef key);
llvm::Optional<PrecisionType> GetPrecisionType(mlir::StringRef key);

raw_ostream &operator<<(raw_ostream &os, TargetType type);
raw_ostream &operator<<(raw_ostream &os, LayoutType type);
raw_ostream &operator<<(raw_ostream &os, PrecisionType type);

class TensorType : public mlir::Type::TypeBase<TensorType, mlir::Type, detail::TensorTypeStorage> {
 public:
  using Base::Base;
  static TensorType get(TargetType target, LayoutType layout, PrecisionType precision);

  TargetType target();
  LayoutType layout();
  PrecisionType precision();
};

raw_ostream &operator<<(raw_ostream &os, TensorType tensorType);

#include "cinnrt/dialect/dense_tensor_dialect.hpp.inc"

#define GET_OP_CLASSES
#include "cinnrt/dialect/dense_tensor.hpp.inc"

}  // namespace cinnrt::dt
