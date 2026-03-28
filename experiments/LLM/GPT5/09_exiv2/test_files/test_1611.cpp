// TEST_ID 1611
// Unit tests for Exiv2::Internal::SonyMakerNote::printFocusMode3

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  EXPECT_TRUE(static_cast<bool>(v));
  // If parsing fails, read() will typically mark the Value as not-ok; tests below
  // only rely on observable output behavior of printFocusMode3 for count/type/metadata gates.
  (void)v->read(text);
  return v;
}

std::string CallPrintFocusMode3(const Value& value, const ExifData* metadata) {
  Exiv2::Internal::SonyMakerNote mn;
  std::ostringstream os;

  // Works whether printFocusMode3 is static or non-static (static can be called via instance too).
  mn.printFocusMode3(os, value, metadata);
  return os.str();
}

}  // namespace

class SonyMakerNotePrintFocusMode3Test_1611 : public ::testing::Test {};

TEST_F(SonyMakerNotePrintFocusMode3Test_1611, NullMetadata_FormatsAsParenthesizedValue_1611) {
  auto v = MakeValue(Exiv2::unsignedShort, "2");
  const std::string out = CallPrintFocusMode3(*v, nullptr);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintFocusMode3Test_1611, WrongType_FormatsAsParenthesizedValue_1611) {
  ExifData md;  // non-null
  auto v = MakeValue(Exiv2::unsignedLong, "2");  // typeId != unsignedShort
  const std::string out = CallPrintFocusMode3(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintFocusMode3Test_1611, CountNotOne_ZeroCount_FormatsAsParenthesizedValue_1611) {
  ExifData md;  // non-null
  auto v = Value::create(Exiv2::unsignedShort);  // leave empty -> commonly count() == 0
  ASSERT_TRUE(static_cast<bool>(v));

  const std::string out = CallPrintFocusMode3(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintFocusMode3Test_1611, CountNotOne_MultipleValues_FormatsAsParenthesizedValue_1611) {
  ExifData md;  // non-null
  auto v = MakeValue(Exiv2::unsignedShort, "2 3");  // intended multiple items
  const std::string out = CallPrintFocusMode3(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintFocusMode3Test_1611, ValidGatesButNoMatchingMetaVersion_PrintsNa_1611) {
  // When gates pass (count==1, type==unsignedShort, metadata != nullptr),
  // observable behavior is either a tag-printed string (if meta version matches)
  // or "n/a" otherwise.
  ExifData md;  // empty metadata -> getMetaVersion(...) is expected to fail or not match
  auto v = MakeValue(Exiv2::unsignedShort, "2");

  const std::string out = CallPrintFocusMode3(*v, &md);

  // Avoid assuming localization details beyond the literal "n/a" used in code.
  EXPECT_NE(out.find("n/a"), std::string::npos);
  // And it should not be in the "(<value>)" error formatting when gates pass.
  EXPECT_TRUE(out.empty() || out.front() != '(');
}