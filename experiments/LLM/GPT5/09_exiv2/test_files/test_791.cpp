// ============================================================================
// UNIT TESTS for Exiv2::Value (dataArea)
// File: value_test_791.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "exiv2/value.hpp"  // adjust include path if your project uses <exiv2/value.hpp>

namespace {

// --- Small adapter helpers so we can read DataBuf regardless of whether it
//     exposes members (pData_/size_) or methods (data()/size()).

template <typename T>
auto DataPtrImpl(const T& b, int) -> decltype(b.pData_) {
  return b.pData_;
}
template <typename T>
auto DataPtrImpl(const T& b, long) -> decltype(b.data()) {
  return b.data();
}

template <typename T>
auto SizeImpl(const T& b, int) -> decltype(b.size_) {
  return b.size_;
}
template <typename T>
auto SizeImpl(const T& b, long) -> decltype(b.size()) {
  return b.size();
}

template <typename T>
auto DataPtr(const T& b) {
  return DataPtrImpl(b, 0);
}
template <typename T>
auto SizeOf(const T& b) -> std::size_t {
  return static_cast<std::size_t>(SizeImpl(b, 0));
}

// Concrete type to instantiate Value (treating implementation as a black box).
class PublicValue : public Exiv2::Value {
 public:
  explicit PublicValue(Exiv2::TypeId typeId) : Exiv2::Value(typeId) {}
  ~PublicValue() override = default;
};

class ValueDataAreaTest_791 : public ::testing::Test {};

}  // namespace

TEST_F(ValueDataAreaTest_791, DataAreaIsEmptyOnFreshInstance_791) {
  PublicValue v(static_cast<Exiv2::TypeId>(0));

  const auto buf = v.dataArea();

  EXPECT_EQ(DataPtr(buf), nullptr);
  EXPECT_EQ(SizeOf(buf), 0u);
}

TEST_F(ValueDataAreaTest_791, DataAreaWorksThroughConstReference_791) {
  const PublicValue v(static_cast<Exiv2::TypeId>(0));

  const auto buf = v.dataArea();

  EXPECT_EQ(DataPtr(buf), nullptr);
  EXPECT_EQ(SizeOf(buf), 0u);
}

TEST_F(ValueDataAreaTest_791, DataAreaIsIdempotentAcrossCalls_791) {
  PublicValue v(static_cast<Exiv2::TypeId>(0));

  const auto buf1 = v.dataArea();
  const auto buf2 = v.dataArea();

  EXPECT_EQ(DataPtr(buf1), DataPtr(buf2));
  EXPECT_EQ(SizeOf(buf1), SizeOf(buf2));
  EXPECT_EQ(DataPtr(buf1), nullptr);
  EXPECT_EQ(SizeOf(buf1), 0u);
}