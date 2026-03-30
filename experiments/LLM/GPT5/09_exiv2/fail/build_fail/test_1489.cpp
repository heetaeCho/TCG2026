// =================================================================================================
// TEST_ID: 1489
// File: test_samsung_mn_header_1489.cpp
// Target: ./TestProjects/exiv2/src/makernote_int.cpp (Exiv2::Internal::SamsungMnHeader)
// =================================================================================================

#include <gtest/gtest.h>

// Prefer including the public/internal header that declares the class in the real codebase.
#include "makernote_int.hpp"

namespace {

class SamsungMnHeaderTest_1489 : public ::testing::Test {
 protected:
  // Intentionally empty: black-box tests only.
};

TEST_F(SamsungMnHeaderTest_1489, DefaultConstructedSizeIsZero_1489) {
  Exiv2::Internal::SamsungMnHeader h;
  EXPECT_EQ(0u, h.size());
}

TEST_F(SamsungMnHeaderTest_1489, ConstObjectSizeIsZero_1489) {
  const Exiv2::Internal::SamsungMnHeader h;
  EXPECT_EQ(0u, h.size());
}

TEST_F(SamsungMnHeaderTest_1489, CopyConstructedSizeIsZero_1489) {
  Exiv2::Internal::SamsungMnHeader h1;
  Exiv2::Internal::SamsungMnHeader h2(h1);
  EXPECT_EQ(0u, h2.size());
}

TEST_F(SamsungMnHeaderTest_1489, CopyAssignedSizeIsZero_1489) {
  Exiv2::Internal::SamsungMnHeader h1;
  Exiv2::Internal::SamsungMnHeader h2;
  h2 = h1;
  EXPECT_EQ(0u, h2.size());
}

TEST_F(SamsungMnHeaderTest_1489, SizeIsStableAcrossMultipleCalls_1489) {
  Exiv2::Internal::SamsungMnHeader h;
  const auto s1 = h.size();
  const auto s2 = h.size();
  const auto s3 = h.size();
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
  EXPECT_EQ(0u, s1);
}

}  // namespace