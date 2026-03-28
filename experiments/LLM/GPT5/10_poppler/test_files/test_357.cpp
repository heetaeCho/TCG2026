// TEST_ID: 357
// File: IdentityFunction_test.cpp

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <memory>
#include <type_traits>

#include "poppler/Function.h"

namespace {

class IdentityFunctionTest_357 : public ::testing::Test {
protected:
  IdentityFunction func_;
};

TEST_F(IdentityFunctionTest_357, DefaultConstruction_IsOkReturnsTrue_357) {
  EXPECT_TRUE(func_.isOk());
}

TEST_F(IdentityFunctionTest_357, IsOk_IsStableAcrossMultipleCalls_357) {
  EXPECT_TRUE(func_.isOk());
  EXPECT_TRUE(func_.isOk());
  EXPECT_TRUE(func_.isOk());
}

TEST_F(IdentityFunctionTest_357, Copy_ReturnsNonNullUniquePtr_357) {
  std::unique_ptr<Function> copy = func_.copy();
  EXPECT_NE(copy, nullptr);
}

TEST_F(IdentityFunctionTest_357, Copy_ResultIsOk_357) {
  std::unique_ptr<Function> copy = func_.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->isOk());
}

TEST_F(IdentityFunctionTest_357, Copy_ReturnsDistinctObject_357) {
  std::unique_ptr<Function> copy = func_.copy();
  ASSERT_NE(copy, nullptr);

  // Ensure we didn't just get an alias to the same object.
  EXPECT_NE(copy.get(), static_cast<Function*>(&func_));
}

TEST_F(IdentityFunctionTest_357, GetType_IsStableAcrossCalls_357) {
  const auto t1 = func_.getType();
  const auto t2 = func_.getType();
  EXPECT_EQ(t1, t2);
}

TEST_F(IdentityFunctionTest_357, Copy_PreservesType_357) {
  const auto originalType = func_.getType();
  std::unique_ptr<Function> copy = func_.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->getType(), originalType);
}

TEST_F(IdentityFunctionTest_357, Transform_CanBeCalledWithValidPointers_357) {
  // Black-box safety test: ensure the method is callable with non-null buffers.
  // We do not assume any specific transformation semantics.
  std::array<double, 8> in{{0.0, 1.0, -1.0, 3.14159, 2.71828, 42.0, -0.5, 10.0}};
  std::array<double, 8> out{{-999.0, -999.0, -999.0, -999.0, -999.0, -999.0, -999.0, -999.0}};

  ASSERT_NO_FATAL_FAILURE(func_.transform(in.data(), out.data()));
}

TEST_F(IdentityFunctionTest_357, Transform_RepeatedCallsDoNotCrash_357) {
  std::array<double, 4> in{{1.0, 2.0, 3.0, 4.0}};
  std::array<double, 4> out{{0.0, 0.0, 0.0, 0.0}};

  ASSERT_NO_FATAL_FAILURE(func_.transform(in.data(), out.data()));
  ASSERT_NO_FATAL_FAILURE(func_.transform(in.data(), out.data()));
}

}  // namespace