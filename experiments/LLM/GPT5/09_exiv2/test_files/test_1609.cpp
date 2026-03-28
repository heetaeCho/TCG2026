// File: test_sonymn_int_printFocusMode_1609.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

std::string CallPrintFocusMode(const Value& value, const ExifData* md, std::ostream** ret_os = nullptr) {
  SonyMakerNote sut;
  std::ostringstream oss;
  std::ostream& ret = sut.printFocusMode(oss, value, md);
  if (ret_os) *ret_os = &ret;
  return oss.str();
}

Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  // Treat as black-box: use public API to populate the value.
  v->read(text);
  return v;
}

}  // namespace

class SonyMakerNotePrintFocusModeTest_1609 : public ::testing::Test {};

// Normal/error case: metadata is null => prints "(<value>)"
TEST_F(SonyMakerNotePrintFocusModeTest_1609, NullMetadata_PrintsParenthesizedValue_1609) {
  auto v = MakeValue(Exiv2::unsignedShort, "1");

  std::ostream* ret_stream = nullptr;
  const std::string out = CallPrintFocusMode(*v, /*md=*/nullptr, &ret_stream);

  ASSERT_NE(ret_stream, nullptr);
  // Returned stream should be the same stream passed in (observable behavior).
  // (We can't directly compare to the local ostringstream here, but we can ensure it's non-null and
  // that something was written.)
  EXPECT_FALSE(out.empty());

  EXPECT_NE(out.find("("), std::string::npos);
  EXPECT_NE(out.find(")"), std::string::npos);
}

// Boundary/error case: value.count() != 1 => prints "(<value>)"
TEST_F(SonyMakerNotePrintFocusModeTest_1609, CountIsZero_PrintsParenthesizedValue_1609) {
  // Create an unsignedShort value but do not populate it -> commonly yields count() == 0.
  auto v = Value::create(Exiv2::unsignedShort);

  const std::string out = CallPrintFocusMode(*v, /*md=*/nullptr /* still exercises same early return */);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("("), std::string::npos);
  EXPECT_NE(out.find(")"), std::string::npos);
}

// Boundary/error case: value has wrong TypeId => prints "(<value>)"
TEST_F(SonyMakerNotePrintFocusModeTest_1609, WrongType_PrintsParenthesizedValue_1609) {
  auto v = MakeValue(Exiv2::asciiString, "1");

  ExifData md;  // non-null metadata pointer, but wrong type should short-circuit first.
  const std::string out = CallPrintFocusMode(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("("), std::string::npos);
  EXPECT_NE(out.find(")"), std::string::npos);
}

// Normal operation: unsignedShort count==1 with metadata present should map known focus mode codes.
TEST_F(SonyMakerNotePrintFocusModeTest_1609, KnownCodes_MapToHumanReadableStrings_1609) {
  ExifData md;  // Empty metadata is still a non-null pointer.

  {
    auto v = MakeValue(Exiv2::unsignedShort, "1");
    const std::string out = CallPrintFocusMode(*v, &md);
    EXPECT_NE(out.find("AF-S"), std::string::npos);
  }
  {
    auto v = MakeValue(Exiv2::unsignedShort, "2");
    const std::string out = CallPrintFocusMode(*v, &md);
    EXPECT_NE(out.find("AF-C"), std::string::npos);
  }
  {
    auto v = MakeValue(Exiv2::unsignedShort, "4");
    const std::string out = CallPrintFocusMode(*v, &md);
    EXPECT_NE(out.find("Permanent-AF"), std::string::npos);
  }
  {
    auto v = MakeValue(Exiv2::unsignedShort, "65535");
    const std::string out = CallPrintFocusMode(*v, &md);
    // Tag table includes 65535 -> "n/a"
    EXPECT_NE(out.find("n/a"), std::string::npos);
  }
}

// Boundary/robustness: unknown code should still produce some non-empty output (typically numeric or fallback).
TEST_F(SonyMakerNotePrintFocusModeTest_1609, UnknownCode_ProducesNonEmptyOutput_1609) {
  ExifData md;

  auto v = MakeValue(Exiv2::unsignedShort, "3");  // Not in the provided table.
  const std::string out = CallPrintFocusMode(*v, &md);

  EXPECT_FALSE(out.empty());
  // For an unknown enum value, a reasonable observable expectation is that the numeric value appears.
  // (We don't assume exact formatting.)
  EXPECT_NE(out.find("3"), std::string::npos);
}