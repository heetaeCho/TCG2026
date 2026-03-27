// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 793
//
// Unit tests for Exiv2::DataValue::read
// File under test: ./TestProjects/exiv2/src/value.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Try to include the real Exiv2 headers (preferred). Keep this resilient to
// different include layouts in the codebase.
#if __has_include(<exiv2/value.hpp>)
#include <exiv2/value.hpp>
#elif __has_include(<value.hpp>)
#include <value.hpp>
#else
// If your build fails here, adjust includes to match your project.
#error "Cannot find Exiv2 value.hpp header (tried <exiv2/value.hpp> and <value.hpp>)."
#endif

#if __has_include(<exiv2/types.hpp>)
#include <exiv2/types.hpp>
#elif __has_include(<types.hpp>)
#include <types.hpp>
#endif

namespace {

class DataValueTest_793 : public ::testing::Test {
 protected:
  Exiv2::DataValue dv_;
};

TEST_F(DataValueTest_793, ReadReturnsZeroForNonEmptyBuffer_793) {
  const Exiv2::byte buf[] = {0x00, 0x01, 0x7F, 0x80, 0xFF};

  const int rc = dv_.read(buf, sizeof(buf), Exiv2::littleEndian);
  EXPECT_EQ(rc, 0);
}

TEST_F(DataValueTest_793, ReadReturnsZeroForEmptyLenWithNonNullBuffer_793) {
  const Exiv2::byte buf[] = {0xAB};

  const int rc = dv_.read(buf, 0u, Exiv2::bigEndian);
  EXPECT_EQ(rc, 0);
}

TEST_F(DataValueTest_793, ReadReturnsZeroForEmptyLenWithNullptr_793) {
  // Boundary case: zero-length read should be safe even with nullptr.
  const int rc = dv_.read(nullptr, 0u, Exiv2::littleEndian);
  EXPECT_EQ(rc, 0);
}

TEST_F(DataValueTest_793, ReadCanBeCalledMultipleTimes_793) {
  const Exiv2::byte buf1[] = {0x10, 0x20, 0x30};
  const Exiv2::byte buf2[] = {0xAA, 0xBB};

  EXPECT_EQ(dv_.read(buf1, sizeof(buf1), Exiv2::littleEndian), 0);
  EXPECT_EQ(dv_.read(buf2, sizeof(buf2), Exiv2::bigEndian), 0);
  EXPECT_EQ(dv_.read(nullptr, 0u, Exiv2::bigEndian), 0);
}

TEST_F(DataValueTest_793, ReadHandlesLargeBuffer_793) {
  // Boundary-ish: exercise a larger input without assuming any internal storage details.
  std::vector<Exiv2::byte> buf(64 * 1024);
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<Exiv2::byte>(i & 0xFF);
  }

  const int rc = dv_.read(buf.data(), buf.size(), Exiv2::littleEndian);
  EXPECT_EQ(rc, 0);
}

}  // namespace