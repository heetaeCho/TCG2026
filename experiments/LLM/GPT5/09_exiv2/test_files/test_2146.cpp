// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_slicebase_2146.cpp
//
// Unit tests for Exiv2::Internal::SliceBase (exiv2/slice.hpp)
// TEST_ID: 2146

#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>
#include <type_traits>

#include "exiv2/slice.hpp"

namespace {

using Exiv2::Internal::SliceBase;

// Helper to access protected rangeCheck() without touching internal state.
class SliceBaseTestAdapter : public SliceBase {
 public:
  SliceBaseTestAdapter(size_t begin, size_t end) : SliceBase(begin, end) {}

  void CallRangeCheck(size_t index) const { rangeCheck(index); }
};

class SliceBaseTest_2146 : public ::testing::Test {};

TEST_F(SliceBaseTest_2146, ConstructorValidRangeDoesNotThrow_2146) {
  EXPECT_NO_THROW((SliceBaseTestAdapter{0u, 1u}));
  EXPECT_NO_THROW((SliceBaseTestAdapter{3u, 10u}));
}

TEST_F(SliceBaseTest_2146, ConstructorBeginEqualsEndThrowsOutOfRange_2146) {
  EXPECT_THROW((SliceBaseTestAdapter{0u, 0u}), std::out_of_range);
  EXPECT_THROW((SliceBaseTestAdapter{7u, 7u}), std::out_of_range);
}

TEST_F(SliceBaseTest_2146, ConstructorBeginGreaterThanEndThrowsOutOfRange_2146) {
  EXPECT_THROW((SliceBaseTestAdapter{1u, 0u}), std::out_of_range);
  EXPECT_THROW((SliceBaseTestAdapter{10u, 3u}), std::out_of_range);
}

TEST_F(SliceBaseTest_2146, SizeIsNoexceptAndPositiveForValidRange_2146) {
  static_assert(noexcept(std::declval<const SliceBase&>().size()),
                "SliceBase::size() must be noexcept");

  const SliceBaseTestAdapter s1(0u, 1u);
  const SliceBaseTestAdapter s2(5u, 9u);

  // Minimal observable contract: constructed with begin < end, size should be non-zero.
  EXPECT_GT(s1.size(), 0u);
  EXPECT_GT(s2.size(), 0u);
}

TEST_F(SliceBaseTest_2146, SizeIsDeterministicForSameConstructionParams_2146) {
  const SliceBaseTestAdapter a(2u, 8u);
  const SliceBaseTestAdapter b(2u, 8u);
  EXPECT_EQ(a.size(), b.size());
}

TEST_F(SliceBaseTest_2146, RangeCheckAcceptsIndicesStrictlyLessThanSize_2146) {
  const SliceBaseTestAdapter s(4u, 12u);
  const size_t n = s.size();
  ASSERT_GT(n, 0u);

  EXPECT_NO_THROW(s.CallRangeCheck(0u));
  EXPECT_NO_THROW(s.CallRangeCheck(n - 1u));
}

TEST_F(SliceBaseTest_2146, RangeCheckRejectsIndexEqualToSize_2146) {
  const SliceBaseTestAdapter s(1u, 2u);
  const size_t n = s.size();
  ASSERT_GT(n, 0u);

  EXPECT_THROW(s.CallRangeCheck(n), std::out_of_range);
}

TEST_F(SliceBaseTest_2146, RangeCheckRejectsVeryLargeIndex_2146) {
  const SliceBaseTestAdapter s(0u, 3u);
  EXPECT_THROW(s.CallRangeCheck(static_cast<size_t>(-1)), std::out_of_range);
}

}  // namespace