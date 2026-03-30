// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmp_text_value_836.cpp
//
// Unit tests for Exiv2::XmpTextValue (black-box tests)
// TEST_ID: 836

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>

#include "exiv2/value.hpp"

namespace {

class XmpTextValueTest_836 : public ::testing::Test {};

TEST_F(XmpTextValueTest_836, DefaultConstructor_SizeIsZero_836) {
  Exiv2::XmpTextValue v;
  EXPECT_EQ(0u, v.size());
}

TEST_F(XmpTextValueTest_836, BufferConstructor_SizeMatchesInput_836) {
  const std::string buf = "hello xmp";
  Exiv2::XmpTextValue v(buf);
  EXPECT_EQ(buf.size(), v.size());
}

TEST_F(XmpTextValueTest_836, Read_SetsSizeForNonEmptyInput_836) {
  Exiv2::XmpTextValue v;

  const std::string buf = "abc";
  const int rc = v.read(buf);
  (void)rc;  // Return code semantics are not asserted (black-box).
  EXPECT_EQ(buf.size(), v.size());
}

TEST_F(XmpTextValueTest_836, Read_EmptyInput_ResultsInZeroSize_836) {
  Exiv2::XmpTextValue v("non-empty");
  ASSERT_GT(v.size(), 0u);

  const std::string empty;
  const int rc = v.read(empty);
  (void)rc;
  EXPECT_EQ(0u, v.size());
}

TEST_F(XmpTextValueTest_836, Read_WithEmbeddedNulls_SizeAccountsForAllBytes_836) {
  Exiv2::XmpTextValue v;

  std::string buf;
  buf.push_back('A');
  buf.push_back('\0');
  buf.push_back('B');
  ASSERT_EQ(3u, buf.size());

  const int rc = v.read(buf);
  (void)rc;
  EXPECT_EQ(buf.size(), v.size());
}

TEST_F(XmpTextValueTest_836, Clone_PreservesSize_836) {
  const std::string buf = "clone-me";
  Exiv2::XmpTextValue v(buf);

  auto c = v.clone();  // UniquePtr
  ASSERT_NE(nullptr, c.get());
  EXPECT_EQ(v.size(), c->size());
}

TEST_F(XmpTextValueTest_836, Size_IsStableAcrossCalls_836) {
  const std::string buf = "stable";
  Exiv2::XmpTextValue v(buf);

  const auto s1 = v.size();
  const auto s2 = v.size();
  const auto s3 = v.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(XmpTextValueTest_836, LargeInput_ReadAndConstructor_HandleBoundarySize_836) {
  // Boundary-style test using a large buffer (commonly used in fuzz/size regressions).
  const std::size_t kLarge = 1'000'000;
  const std::string large(kLarge, 'x');
  ASSERT_EQ(kLarge, large.size());

  // Constructor path
  Exiv2::XmpTextValue v1(large);
  EXPECT_EQ(kLarge, v1.size());

  // read() path
  Exiv2::XmpTextValue v2;
  const int rc = v2.read(large);
  (void)rc;
  EXPECT_EQ(kLarge, v2.size());
}

TEST_F(XmpTextValueTest_836, Size_DoesNotThrow_836) {
  Exiv2::XmpTextValue v("no-throw");
  EXPECT_NO_THROW((void)v.size());
}

}  // namespace