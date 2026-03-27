// File: test_tags_int_printxmpversion_1423.cpp
// TEST_ID: 1423

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header where printXmpVersion/printVersion are declared in Exiv2.
// In the Exiv2 codebase this is typically available as:
#include "tags_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::Internal::printVersion;
using Exiv2::Internal::printXmpVersion;

std::string StreamValueInParens(const Value& v) {
  std::ostringstream os;
  os << "(" << v << ")";
  return os.str();
}

std::string CallPrintXmpVersion(const Value& v, const ExifData* exif = nullptr) {
  std::ostringstream os;
  printXmpVersion(os, v, exif);
  return os.str();
}

std::string CallPrintVersion(const std::string& s) {
  std::ostringstream os;
  printVersion(os, s);
  return os.str();
}

Value::UniquePtr MakeValue(TypeId type, const std::string& readSpec) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  // Value::read expects a textual representation; keep it simple and generic.
  v->read(readSpec);
  return v;
}

class PrintXmpVersionTest_1423 : public ::testing::Test {};

}  // namespace

TEST_F(PrintXmpVersionTest_1423, NonXmpTextType_FormatsAsParenthesizedValue_1423) {
  // typeId != xmpText -> must take the "(value)" branch regardless of size.
  auto v = MakeValue(Exiv2::asciiString, "hello");

  const std::string out = CallPrintXmpVersion(*v, nullptr);
  const std::string expected = StreamValueInParens(*v);

  EXPECT_EQ(out, expected);
}

TEST_F(PrintXmpVersionTest_1423, XmpTextButWrongSize_FormatsAsParenthesizedValue_1423) {
  // xmpText but size != 4 -> "(value)" branch.
  auto v = MakeValue(Exiv2::xmpText, "abc");  // intentionally not "4" sized

  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::xmpText);
  ASSERT_NE(v->size(), 4u);  // boundary condition being exercised

  const std::string out = CallPrintXmpVersion(*v, nullptr);
  const std::string expected = StreamValueInParens(*v);

  EXPECT_EQ(out, expected);
}

TEST_F(PrintXmpVersionTest_1423, NonXmpTextButSizeFour_FormatsAsParenthesizedValue_1423) {
  // size == 4 but typeId != xmpText -> still "(value)" branch.
  // Use a numeric type with 4 components.
  auto v = MakeValue(Exiv2::unsignedByte, "1 2 3 4");

  ASSERT_NE(v.get(), nullptr);
  ASSERT_NE(v->typeId(), Exiv2::xmpText);
  ASSERT_EQ(v->size(), 4u);

  const std::string out = CallPrintXmpVersion(*v, nullptr);
  const std::string expected = StreamValueInParens(*v);

  EXPECT_EQ(out, expected);
}

TEST_F(PrintXmpVersionTest_1423, XmpTextSizeFour_DelegatesToPrintVersion_1423) {
  // When size == 4 and type == xmpText, printXmpVersion delegates to printVersion(os, value.toString()).
  auto v = MakeValue(Exiv2::xmpText, "1234");

  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::xmpText);
  ASSERT_EQ(v->size(), 4u);

  const std::string out = CallPrintXmpVersion(*v, nullptr);
  const std::string expected = CallPrintVersion(v->toString());

  EXPECT_EQ(out, expected);
}

TEST_F(PrintXmpVersionTest_1423, ExifDataPointerDoesNotChangeOutput_1423) {
  // The ExifData* is not used by this function; verify null vs non-null yields same output.
  auto v = MakeValue(Exiv2::xmpText, "1234");

  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::xmpText);
  ASSERT_EQ(v->size(), 4u);

  ExifData exif;

  const std::string out_null = CallPrintXmpVersion(*v, nullptr);
  const std::string out_nonnull = CallPrintXmpVersion(*v, &exif);

  EXPECT_EQ(out_null, out_nonnull);
}

TEST_F(PrintXmpVersionTest_1423, EmptyXmpTextValue_FormatsAsParenthesizedValue_1423) {
  auto v = MakeValue(Exiv2::xmpText, "");

  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::xmpText);
  ASSERT_NE(v->size(), 4u);

  const std::string out = CallPrintXmpVersion(*v, nullptr);
  const std::string expected = StreamValueInParens(*v);

  EXPECT_EQ(out, expected);
}