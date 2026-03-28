// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_value_ascii_write_814.cpp
//
// Unit tests for Exiv2::AsciiValue::write (black-box via public interface).
//
// Constraints followed:
// - No re-implementation/inference beyond observable behavior via public API.
// - No private-state access.
// - Uses only public constructors/read/write and std::ostream output.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 public header
#include <exiv2/value.hpp>

namespace {

class AsciiValueWriteTest_814 : public ::testing::Test {};

TEST_F(AsciiValueWriteTest_814, WriteEmptyString_814) {
  Exiv2::AsciiValue v(std::string{});

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteSimpleAscii_814) {
  Exiv2::AsciiValue v(std::string("Hello"));

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("Hello", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteStopsAtFirstNullByte_814) {
  // Boundary/behavioral: embedded '\0' should truncate output at first null.
  std::string s = std::string("ABC") + '\0' + "DEF";
  Exiv2::AsciiValue v(s);

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("ABC", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteWithLeadingNullByteOutputsEmpty_814) {
  // Boundary: first character is '\0' => output should be empty.
  std::string s;
  s.push_back('\0');
  s += "XYZ";
  Exiv2::AsciiValue v(s);

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteWithTrailingNullByteOmitsNull_814) {
  // Boundary: trailing '\0' should not appear in output.
  std::string s = "TRAIL";
  s.push_back('\0');
  Exiv2::AsciiValue v(s);

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("TRAIL", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteMultipleNullBytesStopsAtFirst_814) {
  // Boundary: multiple embedded nulls => stop at first.
  std::string s = std::string("ONE") + '\0' + "TWO" + '\0' + "THREE";
  Exiv2::AsciiValue v(s);

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("ONE", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteToNonEmptyStreamAppends_814) {
  // Observable stream interaction: operator<< appends to existing content.
  Exiv2::AsciiValue v(std::string("DATA"));

  std::ostringstream oss;
  oss << "PREFIX:";
  v.write(oss);

  EXPECT_EQ("PREFIX:DATA", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteReturnsSameStreamReference_814) {
  // External interaction: verify returned ostream reference is the same object.
  Exiv2::AsciiValue v(std::string("X"));

  std::ostringstream oss;
  std::ostream& ret = v.write(oss);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
  EXPECT_EQ("X", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteAfterReadReflectsReadBuffer_814) {
  // Normal operation through another public API: read(string) then write(os).
  Exiv2::AsciiValue v;

  ASSERT_EQ(0, v.read(std::string("ReadMe")));

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("ReadMe", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteAfterReadWithEmbeddedNullTruncates_814) {
  // Boundary via read(string): embedded null should truncate written output.
  Exiv2::AsciiValue v;

  std::string s = std::string("LEFT") + '\0' + "RIGHT";
  ASSERT_EQ(0, v.read(s));

  std::ostringstream oss;
  v.write(oss);

  EXPECT_EQ("LEFT", oss.str());
}

TEST_F(AsciiValueWriteTest_814, WriteWithVeryLongStringDoesNotThrow_814) {
  // Boundary: very long input; only verify it completes and preserves content
  // when no embedded null exists.
  std::string longStr(10000, 'a');
  Exiv2::AsciiValue v(longStr);

  std::ostringstream oss;
  EXPECT_NO_THROW(v.write(oss));
  EXPECT_EQ(longStr, oss.str());
}

}  // namespace