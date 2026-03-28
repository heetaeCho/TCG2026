// SPDX-License-Identifier: GPL-2.0-or-later
// File: fujimn_int_test_624.cpp
//
// Unit tests for:
//   Exiv2::Internal::printFujiMonochromaticColor(std::ostream&, const Value&, const ExifData*)
//
// Notes:
// - The function has internal linkage (static) in fujimn_int.cpp.
// - To test it as a black box without re-implementing logic, we include the .cpp directly
//   so the function is available in this translation unit.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

// Include the implementation file to access the TU-local (static) function.
#include "fujimn_int.cpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

static Value::UniquePtr makeSByteValueFromText(const std::string& text) {
  // Exiv2 TypeId enum values are typically in namespace Exiv2 (e.g., Exiv2::signedByte).
  auto v = Value::create(Exiv2::signedByte);
  EXPECT_NE(v.get(), nullptr);
  // read() is part of the Value interface; this sets the components from a textual form.
  EXPECT_NO_THROW(v->read(text));
  return v;
}

static std::string streamValue(const Value& value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

static std::string callPrint(const Value& value, const ExifData* exif = nullptr) {
  std::ostringstream oss;
  // Function under test (included from fujimn_int.cpp).
  Exiv2::Internal::printFujiMonochromaticColor(oss, value, exif);
  return oss.str();
}

class FujiMnIntTest_624 : public ::testing::Test {};

}  // namespace

TEST_F(FujiMnIntTest_624, PrintsPlusSignForPositiveSingleComponent_624) {
  auto v = makeSByteValueFromText("1");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "+1");
}

TEST_F(FujiMnIntTest_624, DoesNotPrintPlusSignForZeroSingleComponent_624) {
  auto v = makeSByteValueFromText("0");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "0");
}

TEST_F(FujiMnIntTest_624, PrintsNegativeValueWithoutPlusSign_624) {
  auto v = makeSByteValueFromText("-1");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "-1");
}

TEST_F(FujiMnIntTest_624, HandlesInt8MaxBoundary_624) {
  auto v = makeSByteValueFromText("127");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "+127");
}

TEST_F(FujiMnIntTest_624, HandlesInt8MinBoundary_624) {
  // Boundary for int8_t minimum.
  auto v = makeSByteValueFromText("-128");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "-128");
}

TEST_F(FujiMnIntTest_624, WrapsNonSingleComponentValueInParentheses_624) {
  auto v = makeSByteValueFromText("1 2");
  ASSERT_NE(v->size(), 1U);

  const std::string inner = streamValue(*v);
  EXPECT_EQ(callPrint(*v, nullptr), "(" + inner + ")");
}

TEST_F(FujiMnIntTest_624, WrapsEmptyValueInParenthesesIfNotSingleComponent_624) {
  // An empty value is not a "single component" (size != 1), so it should be wrapped.
  auto v = makeSByteValueFromText("");
  ASSERT_NE(v->size(), 1U);

  const std::string inner = streamValue(*v);
  EXPECT_EQ(callPrint(*v, nullptr), "(" + inner + ")");
}

TEST_F(FujiMnIntTest_624, AcceptsNonNullExifDataPointer_624) {
  // The ExifData* parameter is part of the interface; ensure passing a valid pointer
  // does not change the observable output for the same Value.
  ExifData exif;

  auto v = makeSByteValueFromText("5");
  ASSERT_EQ(v->size(), 1U);

  EXPECT_EQ(callPrint(*v, nullptr), "+5");
  EXPECT_EQ(callPrint(*v, &exif), "+5");
}