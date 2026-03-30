// File: test_value_data_value_to_int64_799.cpp
#include <gtest/gtest.h>

#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace {

class DataValueToInt64Test_799 : public ::testing::Test {
 protected:
  // Pick a concrete TypeId that should exist in Exiv2's public API.
  // The specific type is not important for these tests; we only exercise toInt64().
  Exiv2::DataValue dv_{Exiv2::unsignedLong};

  void SetUp() override {
    // value_ is public in the provided interface, so it is legal to populate it here.
    dv_.value_.clear();
  }
};

TEST_F(DataValueToInt64Test_799, ReturnsElementAtIndexZero_799) {
  dv_.value_.push_back(static_cast<int64_t>(42));
  dv_.value_.push_back(static_cast<int64_t>(-7));

  EXPECT_EQ(dv_.toInt64(0), 42);
}

TEST_F(DataValueToInt64Test_799, ReturnsElementAtNonZeroIndex_799) {
  dv_.value_.push_back(static_cast<int64_t>(10));
  dv_.value_.push_back(static_cast<int64_t>(20));
  dv_.value_.push_back(static_cast<int64_t>(30));

  EXPECT_EQ(dv_.toInt64(1), 20);
  EXPECT_EQ(dv_.toInt64(2), 30);
}

TEST_F(DataValueToInt64Test_799, Boundary_LastValidIndex_799) {
  dv_.value_.push_back(static_cast<int64_t>(1));
  dv_.value_.push_back(static_cast<int64_t>(2));
  dv_.value_.push_back(static_cast<int64_t>(3));

  const size_t last = dv_.value_.size() - 1;
  EXPECT_EQ(dv_.toInt64(last), 3);
}

TEST_F(DataValueToInt64Test_799, Error_EmptyValueThrowsOnAnyIndex_799) {
  EXPECT_TRUE(dv_.value_.empty());
  EXPECT_THROW((void)dv_.toInt64(0), std::out_of_range);
}

TEST_F(DataValueToInt64Test_799, Error_IndexOutOfRangeThrows_799) {
  dv_.value_.push_back(static_cast<int64_t>(123));

  EXPECT_THROW((void)dv_.toInt64(1), std::out_of_range);
  EXPECT_THROW((void)dv_.toInt64(static_cast<size_t>(-1)), std::out_of_range);
}

TEST_F(DataValueToInt64Test_799, DoesNotMutatePublicValueContainer_799) {
  dv_.value_ = {static_cast<int64_t>(5), static_cast<int64_t>(6), static_cast<int64_t>(7)};
  const auto before = dv_.value_;

  (void)dv_.toInt64(0);
  (void)dv_.toInt64(2);

  EXPECT_EQ(dv_.value_, before);
}

}  // namespace