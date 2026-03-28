// SPDX-License-Identifier: GPL-2.0-or-later
// File: nikonmn_int_test_506.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 includes (internal + value types)
#include "nikonmn_int.hpp"
#include "value.hpp"
#include "exif.hpp"

namespace {

using Exiv2::AsciiValue;
using Exiv2::ExifData;
using Exiv2::Internal::Nikon3MakerNote;
using Exiv2::UShortValue;

class Nikon3MakerNoteTest_506 : public ::testing::Test {
 protected:
  static std::string DirectStream(const Exiv2::Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  static std::string Print0x009e(const Exiv2::Value& v, const ExifData* ed = nullptr) {
    std::ostringstream os;
    Nikon3MakerNote mn;
    auto& ret = mn.print0x009e(os, v, ed);
    EXPECT_EQ(&ret, &os);  // should return the same stream reference
    return os.str();
  }
};

TEST_F(Nikon3MakerNoteTest_506, CountNotTen_FallsBackToOperatorStream_506) {
  // count != 10 => should behave exactly like streaming the Value directly.
  UShortValue v;
  ASSERT_EQ(0, v.read("1 2 3 4 5 6 7 8 9"));  // 9 entries

  const std::string expected = DirectStream(v);
  const std::string actual = Print0x009e(v, nullptr);

  EXPECT_EQ(expected, actual);
}

TEST_F(Nikon3MakerNoteTest_506, TypeNotUnsignedShort_FallsBackToOperatorStream_506) {
  // typeId != unsignedShort => should behave exactly like streaming the Value directly.
  AsciiValue v;
  ASSERT_EQ(0, v.read("not-a-ushort"));

  const std::string expected = DirectStream(v);
  const std::string actual = Print0x009e(v, nullptr);

  EXPECT_EQ(expected, actual);
}

TEST_F(Nikon3MakerNoteTest_506, ValidCountAndType_FormatsAsHistoryList_506) {
  // count == 10 and type == unsignedShort => special formatting path.
  // We choose values that should cause >= 2 emitted entries after trimming, so we can check separators.
  //
  // Indices are accessed via toInt64(i) for i=9..0. With typical Value parsing, the first number
  // corresponds to index 0, the last number to index 9.
  //
  // Put 999 at index 1, and 0 at index 0, rest 0:
  // Expected output should contain both "999" and "0" and include a "; " separator.
  UShortValue v;
  ASSERT_EQ(0, v.read("0 999 0 0 0 0 0 0 0 0"));

  const std::string actual = Print0x009e(v, nullptr);

  // Special formatting joins entries using "; " (as opposed to plain numeric streaming).
  EXPECT_NE(std::string::npos, actual.find("; "));
  EXPECT_NE(std::string::npos, actual.find("999"));
  EXPECT_NE(std::string::npos, actual.find("0"));

  // Ensure the "999" appears before the trailing "0" entry in the output (order: i=1 then i=0).
  const auto pos999 = actual.find("999");
  const auto pos0 = actual.rfind("0");
  ASSERT_NE(std::string::npos, pos999);
  ASSERT_NE(std::string::npos, pos0);
  EXPECT_LT(pos999, pos0);
}

TEST_F(Nikon3MakerNoteTest_506, ValidCountAndType_AllLeadingZerosTrimmed_EmitsAtLeastOneEntry_506) {
  // If all entries are zero, loop should skip i=9..1 and still emit i=0 (at least one entry).
  UShortValue v;
  ASSERT_EQ(0, v.read("0 0 0 0 0 0 0 0 0 0"));

  const std::string actual = Print0x009e(v, nullptr);

  // Should not be empty, and should mention "0" somewhere (as value/unknown code).
  EXPECT_FALSE(actual.empty());
  EXPECT_NE(std::string::npos, actual.find("0"));
}

}  // namespace