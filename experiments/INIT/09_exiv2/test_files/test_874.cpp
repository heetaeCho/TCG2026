// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/unit/test_timevalue_read_buf.cpp
//
// TEST_ID: 874
//
// Unit tests for Exiv2::TimeValue::read(const byte* buf, size_t len, ByteOrder)
//
// Constraints:
//  - Treat implementation as a black box
//  - Verify only observable behavior through public interface
//  - No private/internal state access

#include <gtest/gtest.h>

#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace {

class TimeValueReadBufTest_874 : public ::testing::Test {
 protected:
  Exiv2::TimeValue tv_;
};

TEST_F(TimeValueReadBufTest_874, ReadBufMatchesReadStringSameBytes_874) {
  // Same bytes -> should behave the same as read(std::string) because the buffer overload
  // constructs a std::string from (buf, len) and forwards.
  const std::string s = "12:34:56";
  const std::vector<Exiv2::byte> buf(s.begin(), s.end());

  const int rc_from_string = tv_.read(s);
  const int rc_from_buf = tv_.read(buf.data(), buf.size(), Exiv2::littleEndian);

  EXPECT_EQ(rc_from_string, rc_from_buf);
}

TEST_F(TimeValueReadBufTest_874, ReadBufWithEmbeddedNullMatchesReadString_874) {
  // The overload uses std::string(ptr, len), so embedded NUL bytes are preserved.
  const std::string s(std::string("12\0:34\0:56", 10));  // includes embedded '\0'
  ASSERT_EQ(10u, s.size());

  std::vector<Exiv2::byte> buf(s.begin(), s.end());

  const int rc_from_string = tv_.read(s);
  const int rc_from_buf = tv_.read(buf.data(), buf.size(), Exiv2::bigEndian);

  EXPECT_EQ(rc_from_string, rc_from_buf);
}

TEST_F(TimeValueReadBufTest_874, ZeroLengthBufferMatchesEmptyString_874) {
  // Avoid passing nullptr even with len==0 to keep the call well-defined.
  const Exiv2::byte dummy = 0;

  const std::string empty;
  const int rc_from_string = tv_.read(empty);
  const int rc_from_buf = tv_.read(&dummy, 0u, Exiv2::littleEndian);

  EXPECT_EQ(rc_from_string, rc_from_buf);
}

TEST_F(TimeValueReadBufTest_874, ByteOrderDoesNotAffectResultForSameInput_874) {
  // The parameter is intentionally unused in the implementation shown. We only assert
  // observable behavior: same input bytes => consistent return across ByteOrder values.
  const std::string s = "23:59:59";
  const std::vector<Exiv2::byte> buf(s.begin(), s.end());

  const int rc_le = tv_.read(buf.data(), buf.size(), Exiv2::littleEndian);
  const int rc_be = tv_.read(buf.data(), buf.size(), Exiv2::bigEndian);

  EXPECT_EQ(rc_le, rc_be);
}

TEST_F(TimeValueReadBufTest_874, DoesNotThrowForTypicalInput_874) {
  const std::string s = "00:00:00";
  const std::vector<Exiv2::byte> buf(s.begin(), s.end());

  EXPECT_NO_THROW({
    (void)tv_.read(buf.data(), buf.size(), Exiv2::littleEndian);
  });
}

}  // namespace