// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_value_790.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// In this simplified test project, the class under test is defined in the .cpp file.
// Including it here allows the test TU to see the public interface without re-implementing it.
#include "TestProjects/exiv2/src/value.cpp"

namespace {

TEST(ValueTest_790, SizeDataAreaReturnsZeroByDefault_790) {
  Exiv2::Value v;
  EXPECT_EQ(v.sizeDataArea(), static_cast<size_t>(0));
}

TEST(ValueTest_790, SizeDataAreaIsConstCallable_790) {
  const Exiv2::Value v;
  EXPECT_EQ(v.sizeDataArea(), static_cast<size_t>(0));
}

TEST(ValueTest_790, SizeDataAreaIsStableAcrossMultipleCalls_790) {
  Exiv2::Value v;

  const auto first = v.sizeDataArea();
  const auto second = v.sizeDataArea();
  const auto third = v.sizeDataArea();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(third, static_cast<size_t>(0));
}

TEST(ValueTest_790, SizeDataAreaConsistentAcrossInstances_790) {
  Exiv2::Value a;
  Exiv2::Value b;

  EXPECT_EQ(a.sizeDataArea(), static_cast<size_t>(0));
  EXPECT_EQ(b.sizeDataArea(), static_cast<size_t>(0));
  EXPECT_EQ(a.sizeDataArea(), b.sizeDataArea());
}

TEST(ValueTest_790, SizeDataAreaReturnTypeIsSizeT_790) {
  Exiv2::Value v;
  using Ret = decltype(v.sizeDataArea());
  EXPECT_TRUE((std::is_same<Ret, size_t>::value));
}

}  // namespace