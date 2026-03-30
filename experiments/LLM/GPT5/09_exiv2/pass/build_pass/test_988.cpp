// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_version_988.cpp
//
// Unit tests for Exiv2::version() from ./TestProjects/exiv2/src/version.cpp
//
// NOTE:
// - Treat implementation as a black box.
// - Only test observable behavior via the public interface.
// - No private state access.
// - No mocks needed (no external collaborators).

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <string>

#include "exiv2/exiv2.hpp"  // provides Exiv2::version() in the real codebase

namespace {

class VersionTest_988 : public ::testing::Test {};

TEST_F(VersionTest_988, ReturnsNonNullPointer_988) {
  const char* v = Exiv2::version();
  ASSERT_NE(v, nullptr);
}

TEST_F(VersionTest_988, ReturnsNonEmptyCString_988) {
  const char* v = Exiv2::version();
  ASSERT_NE(v, nullptr);
  EXPECT_GT(std::strlen(v), 0u);
}

TEST_F(VersionTest_988, ReturnsSamePointerAcrossCalls_988) {
  const char* v1 = Exiv2::version();
  const char* v2 = Exiv2::version();
  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);

  // Observable property: stable pointer identity across calls.
  // This should hold for typical build-time string macros and avoids inferring
  // internal logic beyond what is returned by the interface.
  EXPECT_EQ(v1, v2);
}

TEST_F(VersionTest_988, ReturnedStringIsStableAcrossCalls_988) {
  const char* v1 = Exiv2::version();
  ASSERT_NE(v1, nullptr);
  const std::string s1(v1);

  const char* v2 = Exiv2::version();
  ASSERT_NE(v2, nullptr);
  const std::string s2(v2);

  EXPECT_EQ(s1, s2);
}

TEST_F(VersionTest_988, ReturnedCStringIsNullTerminated_988) {
  const char* v = Exiv2::version();
  ASSERT_NE(v, nullptr);

  // Boundary-style check: ensure there is a '\0' within a reasonable bound.
  // Avoids walking arbitrary memory if something goes wrong.
  constexpr std::size_t kMaxScan = 4096;
  bool found_null = false;
  for (std::size_t i = 0; i < kMaxScan; ++i) {
    if (v[i] == '\0') {
      found_null = true;
      break;
    }
  }
  EXPECT_TRUE(found_null);
}

}  // namespace