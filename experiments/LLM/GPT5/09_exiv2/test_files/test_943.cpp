// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 943
//
// Unit tests for Exiv2::Internal::CanonMakerNote::print0x0008
//
// Constraints honored:
// - Treat implementation as black box: verify only observable output to std::ostream
// - No private state access
// - No re-implementation of logic in tests (only input/output expectations)
// - No mocking internal behavior; ExifData pointer is unused by observable behavior here

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths if your build requires different ones)
#include <exiv2/exiv2.hpp>

// The class under test lives in exiv2 internals and is implemented in canonmn_int.cpp.
// In many Exiv2 test setups, including the corresponding internal header is sufficient.
#include "canonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::CanonMakerNote;
using Exiv2::Value;

// Helper: create an ASCII Value (common in Exiv2 for string values)
static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
  auto v = Exiv2::Value::UniquePtr(Exiv2::Value::create(Exiv2::asciiString));
  v->read(s);
  return v;
}

class CanonMakerNotePrint0x0008Test_943 : public ::testing::Test {
 protected:
  CanonMakerNote sut_;
  ExifData exif_;  // passed as pointer; content is irrelevant for observable behavior here
};

TEST_F(CanonMakerNotePrint0x0008Test_943, FormatsValueWithHyphenWhenLengthAtLeast4_943) {
  auto v = makeAsciiValue("1234");

  std::ostringstream os;
  auto& ret = sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), " -1234" == os.str() ? os.str() : ""); // avoid any accidental assumptions
  // The only safe, direct check is the final stream content; check expected concrete output:
  // For "1234", expected " -"? No. We'll assert the exact expected output:
  EXPECT_EQ(os.str(), "-1234");  // prefix part empty, then '-', then last 4
  EXPECT_EQ(&ret, &os);
}

TEST_F(CanonMakerNotePrint0x0008Test_943, FormatsValueBySplittingLastFourCharacters_943) {
  auto v = makeAsciiValue("ABCDEFGH"); // length 8

  std::ostringstream os;
  sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), "ABCD-EFGH");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, ShortValueIsWrappedInParentheses_Length3_943) {
  auto v = makeAsciiValue("ABC"); // length 3 (<4)

  std::ostringstream os;
  sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), "(ABC)");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, EmptyStringIsWrappedInParentheses_943) {
  auto v = makeAsciiValue("");

  std::ostringstream os;
  sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), "()");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, LengthExactly4DoesNotAddParentheses_943) {
  auto v = makeAsciiValue("WXYZ");

  std::ostringstream os;
  sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), "-WXYZ");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, WorksWithNullExifDataPointer_943) {
  auto v = makeAsciiValue("HELLO1234");

  std::ostringstream os;
  sut_.print0x0008(os, *v, /*exifData*/ nullptr);

  EXPECT_EQ(os.str(), "HELLO-1234");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, AppendsToExistingStreamContent_943) {
  auto v = makeAsciiValue("ABCDE"); // length 5

  std::ostringstream os;
  os << "prefix:";
  sut_.print0x0008(os, *v, &exif_);

  EXPECT_EQ(os.str(), "prefix:A-BCDE");
}

TEST_F(CanonMakerNotePrint0x0008Test_943, DoesNotThrowForTypicalStringInput_943) {
  auto v = makeAsciiValue("CanonTest0008");

  std::ostringstream os;
  EXPECT_NO_THROW((void)sut_.print0x0008(os, *v, &exif_));
  EXPECT_FALSE(os.str().empty());
}

}  // namespace