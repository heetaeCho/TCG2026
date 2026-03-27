// File: gmallocn3_test.cpp
// Unit tests for gmallocn3 (./TestProjects/poppler/goo/gmem.h)

#include <gtest/gtest.h>

#include <climits>
#include <cstddef>
#include <cstring>

// Poppler header under test
#include "goo/gmem.h"

namespace {

class Gmallocn3Test_14 : public ::testing::Test {};

TEST_F(Gmallocn3Test_14, ZeroWidthReturnsNullptr_14) {
  void* p = gmallocn3(0, 10, 1);
  EXPECT_EQ(p, nullptr);
}

TEST_F(Gmallocn3Test_14, ZeroHeightReturnsNullptr_14) {
  void* p = gmallocn3(10, 0, 1);
  EXPECT_EQ(p, nullptr);
}

TEST_F(Gmallocn3Test_14, NormalAllocationReturnsNonNull_14) {
  // 2 * 3 * 4 = 24 bytes
  void* p = gmallocn3(2, 3, 4);
  ASSERT_NE(p, nullptr);

  // Observable behavior: should be usable memory (at least within requested size).
  std::memset(p, 0xAB, 24);

  // gmem.h in poppler typically provides gfree; use it if available.
  gfree(p);
}

TEST_F(Gmallocn3Test_14, NegativeWidthCheckoverflowTrueReturnsNullptrAndPrintsMessage_14) {
  testing::internal::CaptureStderr();
  void* p = gmallocn3(-1, 2, 3, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);
}

TEST_F(Gmallocn3Test_14, NegativeHeightCheckoverflowTrueReturnsNullptrAndPrintsMessage_14) {
  testing::internal::CaptureStderr();
  void* p = gmallocn3(1, -2, 3, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);
}

TEST_F(Gmallocn3Test_14, NonPositiveSizeCheckoverflowTrueReturnsNullptrAndPrintsMessage_14) {
  testing::internal::CaptureStderr();
  void* p = gmallocn3(1, 2, 0, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);
}

TEST_F(Gmallocn3Test_14, OverflowInMultiplicationCheckoverflowTrueReturnsNullptrAndPrintsMessage_14) {
  // Choose values very likely to overflow int multiplication in checkedMultiply.
  testing::internal::CaptureStderr();
  void* p = gmallocn3(INT_MAX, INT_MAX, 2, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);
}

TEST_F(Gmallocn3Test_14, InvalidArgsCheckoverflowFalseAbortsWithMessage_14) {
  // When checkoverflow == false, bogus sizes should abort.
  EXPECT_DEATH(
      (void)gmallocn3(-1, 2, 3, /*checkoverflow=*/false),
      "Bogus memory allocation size");
}

TEST_F(Gmallocn3Test_14, OverflowCheckoverflowFalseAbortsWithMessage_14) {
  EXPECT_DEATH(
      (void)gmallocn3(INT_MAX, INT_MAX, 2, /*checkoverflow=*/false),
      "Bogus memory allocation size");
}

}  // namespace