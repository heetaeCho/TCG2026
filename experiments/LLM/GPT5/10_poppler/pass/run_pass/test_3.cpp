// File: goo_checked_add_test_3.cpp
// Unit tests for checkedAdd() in ./TestProjects/poppler/goo/GooCheckedOps.h
//
// The TEST_ID is 3

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "goo/GooCheckedOps.h"

namespace {

class GooCheckedOpsTest_3 : public ::testing::Test {};

template <typename T>
static void ExpectNoOverflowAndValue_3(T x, T y, T expected)
{
  T out{};
  const bool overflow = checkedAdd<T>(x, y, &out);
  EXPECT_FALSE(overflow);
  EXPECT_EQ(out, expected);
}

template <typename T>
static void ExpectOverflow_3(T x, T y)
{
  T out = static_cast<T>(0x7); // sentinel; value is unspecified on overflow
  const bool overflow = checkedAdd<T>(x, y, &out);
  EXPECT_TRUE(overflow);
}

} // namespace

// --- Normal operation ---

TEST_F(GooCheckedOpsTest_3, AddsPositiveNumbers_Int_3)
{
  ExpectNoOverflowAndValue_3<int>(10, 20, 30);
}

TEST_F(GooCheckedOpsTest_3, AddsNegativeAndPositive_Int_3)
{
  ExpectNoOverflowAndValue_3<int>(-5, 12, 7);
}

TEST_F(GooCheckedOpsTest_3, AddsZero_IsIdentity_LongLong_3)
{
  using T = long long;
  ExpectNoOverflowAndValue_3<T>(123456789LL, 0LL, 123456789LL);
  ExpectNoOverflowAndValue_3<T>(0LL, 987654321LL, 987654321LL);
}

TEST_F(GooCheckedOpsTest_3, AddsUnsigned_NoOverflow_3)
{
  using T = unsigned int;
  ExpectNoOverflowAndValue_3<T>(100u, 23u, 123u);
}

// --- Boundary conditions (no overflow) ---

TEST_F(GooCheckedOpsTest_3, MaxPlusZero_NoOverflow_Int_3)
{
  using T = int;
  const T maxv = std::numeric_limits<T>::max();
  ExpectNoOverflowAndValue_3<T>(maxv, 0, maxv);
}

TEST_F(GooCheckedOpsTest_3, MinPlusZero_NoOverflow_Int_3)
{
  using T = int;
  const T minv = std::numeric_limits<T>::min();
  ExpectNoOverflowAndValue_3<T>(minv, 0, minv);
}

TEST_F(GooCheckedOpsTest_3, NearMaxPlusOne_NoOverflow_Int_3)
{
  using T = int;
  const T maxv = std::numeric_limits<T>::max();
  ExpectNoOverflowAndValue_3<T>(maxv - 1, 1, maxv);
}

TEST_F(GooCheckedOpsTest_3, NearMinPlusMinusOne_NoOverflow_Int_3)
{
  using T = int;
  const T minv = std::numeric_limits<T>::min();
  ExpectNoOverflowAndValue_3<T>(minv + 1, -1, minv);
}

// --- Exceptional / error cases (overflow/underflow observable via return value) ---

TEST_F(GooCheckedOpsTest_3, SignedPositiveOverflow_Int_3)
{
  using T = int;
  const T maxv = std::numeric_limits<T>::max();
  ExpectOverflow_3<T>(maxv, 1);
}

TEST_F(GooCheckedOpsTest_3, SignedNegativeUnderflow_Int_3)
{
  using T = int;
  const T minv = std::numeric_limits<T>::min();
  ExpectOverflow_3<T>(minv, -1);
}

TEST_F(GooCheckedOpsTest_3, UnsignedOverflow_UInt_3)
{
  using T = unsigned int;
  const T maxv = std::numeric_limits<T>::max();
  ExpectOverflow_3<T>(maxv, 1u);
}

TEST_F(GooCheckedOpsTest_3, UnsignedMaxPlusZero_NoOverflow_3)
{
  using T = unsigned int;
  const T maxv = std::numeric_limits<T>::max();
  ExpectNoOverflowAndValue_3<T>(maxv, 0u, maxv);
}

// --- Type-focused coverage ---

TEST_F(GooCheckedOpsTest_3, WorksForSizeT_BasicAdd_3)
{
  using T = size_t;
  ExpectNoOverflowAndValue_3<T>(static_cast<T>(1), static_cast<T>(2), static_cast<T>(3));
}

TEST_F(GooCheckedOpsTest_3, SizeTOverflow_3)
{
  using T = size_t;
  const T maxv = std::numeric_limits<T>::max();
  ExpectOverflow_3<T>(maxv, static_cast<T>(1));
}