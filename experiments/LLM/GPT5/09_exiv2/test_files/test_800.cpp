// -----------------------------------------------------------------------------
// TEST_ID 800 - Unit tests for Exiv2::DataValue::toUint32(size_t)
// File: test_value_datavalue_touint32_800.cpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include <exiv2/value.hpp>

namespace {

// Small SFINAE helper to append into DataValue::value_ without assuming the exact
// container type beyond “it can store a uint32_t”.
template <int N>
struct prio : prio<N - 1> {};
template <>
struct prio<0> {};

template <typename C>
auto AppendImpl(C& c, uint32_t v, prio<2>) -> decltype(c.push_back(v), void()) {
  c.push_back(v);
}

template <typename C>
auto AppendImpl(C& c, uint32_t v, prio<1>) -> decltype(c.emplace_back(v), void()) {
  c.emplace_back(v);
}

template <typename C>
auto AppendImpl(C& c, uint32_t v, prio<0>) -> decltype(c.insert(c.end(), v), void()) {
  c.insert(c.end(), v);
}

template <typename C>
void AppendValue(C& c, uint32_t v) {
  AppendImpl(c, v, prio<2>{});
}

class DataValueToUint32Test_800 : public ::testing::Test {
 protected:
  static Exiv2::TypeId AnyTypeId() {
    // Avoid depending on specific TypeId enumerator names; constructor only needs a value.
    return static_cast<Exiv2::TypeId>(0);
  }
};

}  // namespace

TEST_F(DataValueToUint32Test_800, ReturnsElementAtGivenIndex_800) {
  Exiv2::DataValue dv(AnyTypeId());

  dv.value_.clear();
  AppendValue(dv.value_, static_cast<uint32_t>(10));
  AppendValue(dv.value_, static_cast<uint32_t>(20));
  AppendValue(dv.value_, static_cast<uint32_t>(30));

  EXPECT_EQ(dv.toUint32(0), static_cast<uint32_t>(10));
  EXPECT_EQ(dv.toUint32(1), static_cast<uint32_t>(20));
  EXPECT_EQ(dv.toUint32(2), static_cast<uint32_t>(30));
}

TEST_F(DataValueToUint32Test_800, Boundary_LastElementIsReadable_800) {
  Exiv2::DataValue dv(AnyTypeId());

  dv.value_.clear();
  AppendValue(dv.value_, static_cast<uint32_t>(1));
  AppendValue(dv.value_, static_cast<uint32_t>(2));

  // Boundary: last valid index.
  EXPECT_EQ(dv.toUint32(1), static_cast<uint32_t>(2));
}

TEST_F(DataValueToUint32Test_800, ThrowsWhenEmpty_800) {
  Exiv2::DataValue dv(AnyTypeId());

  dv.value_.clear();

  // Observable error case: accessing element when there are none.
  EXPECT_ANY_THROW((void)dv.toUint32(0));
}

TEST_F(DataValueToUint32Test_800, ThrowsWhenIndexPastEnd_800) {
  Exiv2::DataValue dv(AnyTypeId());

  dv.value_.clear();
  AppendValue(dv.value_, static_cast<uint32_t>(123));

  // Observable error case: index is out of range.
  EXPECT_ANY_THROW((void)dv.toUint32(1));
}

TEST_F(DataValueToUint32Test_800, OkIsTrueAfterSuccessfulCall_800) {
  Exiv2::DataValue dv(AnyTypeId());

  dv.value_.clear();
  AppendValue(dv.value_, static_cast<uint32_t>(42));

  (void)dv.toUint32(0);

  // Observable via public interface on Value.
  EXPECT_TRUE(dv.ok());
}