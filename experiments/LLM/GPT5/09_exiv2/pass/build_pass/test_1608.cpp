// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printImageSize_1608.cpp
//
// Unit tests for:
//   Exiv2::Internal::SonyMakerNote::printImageSize(std::ostream&, const Value&, const ExifData*)
//
// Constraints honored:
// - Treat implementation as a black box (test only observable outputs).
// - No access to private state.
// - No re-implementation/inference beyond interface behavior.
// - Mocking not needed (no external collaborator interactions exposed).

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 includes (adjust include paths if your test target uses different ones)
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Header that declares Exiv2::Internal::SonyMakerNote (adjust if needed)
#include "sonymn_int.hpp"

namespace {

// Helper: capture stream output for the call under test.
static std::string CallPrintImageSize(Exiv2::Internal::SonyMakerNote& mn,
                                      const Exiv2::Value& value,
                                      const Exiv2::ExifData* exif = nullptr) {
  std::ostringstream os;
  mn.printImageSize(os, value, exif);
  return os.str();
}

}  // namespace

namespace Exiv2 {
namespace Internal {

class SonyMakerNotePrintImageSizeTest_1608 : public ::testing::Test {
 protected:
  SonyMakerNote mn_;
};

TEST_F(SonyMakerNotePrintImageSizeTest_1608, FormatsAsHeightXWidthWhenTwoUnsignedLong_1608) {
  // Normal operation: value.count()==2 and typeId()==unsignedLong -> "toString(1) x toString(0)"
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  // Use two distinct numbers so order is observable.
  v->read("640 480");  // tokenization rules are handled by Exiv2::Value

  const std::string out = CallPrintImageSize(mn_, *v);
  EXPECT_EQ(out, std::string("480 x 640"));
}

TEST_F(SonyMakerNotePrintImageSizeTest_1608, IgnoresExifDataPointerAndStillFormats_1608) {
  // Boundary / robustness: exif pointer is unused by the interface behavior we can observe.
  Exiv2::ExifData dummyExif;
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  v->read("1 2");
  const std::string out = CallPrintImageSize(mn_, *v, &dummyExif);
  EXPECT_EQ(out, std::string("2 x 1"));
}

TEST_F(SonyMakerNotePrintImageSizeTest_1608, FallsBackToParenthesizedValueWhenCountIsNotTwo_1608) {
  // Boundary: count != 2 => "(" << value << ")"
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  v->read("123");  // count should be 1
  const std::string out = CallPrintImageSize(mn_, *v);

  // Observable behavior: output is wrapped in parentheses and contains the value's stream form.
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  // Ensure the numeric payload appears somewhere.
  EXPECT_NE(out.find("123"), std::string::npos);
}

TEST_F(SonyMakerNotePrintImageSizeTest_1608, FallsBackToParenthesizedValueWhenTypeIsNotUnsignedLong_1608) {
  // Error/exceptional (observable): typeId != unsignedLong => "(" << value << ")"
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);

  v->read("640 480");
  const std::string out = CallPrintImageSize(mn_, *v);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  // Ensure some content from the value appears.
  EXPECT_NE(out.find("640"), std::string::npos);
}

TEST_F(SonyMakerNotePrintImageSizeTest_1608, AppendsToExistingStreamContent_1608) {
  // Boundary: verify it writes to the provided stream without clearing it.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);
  v->read("10 20");

  std::ostringstream os;
  os << "prefix:";
  mn_.printImageSize(os, *v, nullptr);

  EXPECT_EQ(os.str(), std::string("prefix:20 x 10"));
}

}  // namespace Internal
}  // namespace Exiv2