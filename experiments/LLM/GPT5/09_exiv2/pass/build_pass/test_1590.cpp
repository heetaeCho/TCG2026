// File: test_sonymn_printMultiBurstSize_1590.cpp
// Unit tests for Exiv2::Internal::SonyMakerNote::printMultiBurstSize
//
// Constraints honored:
// - Black-box tests via public observable behavior (stream output / return reference)
// - No private-state access
// - No re-implementation/simulation of internal behavior beyond interface usage
// - Boundary + error-path (as observable) coverage

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

#include <ostream>
#include <sstream>
#include <string>

// Try common internal header names/paths. Adjust if your build uses a different include layout.
#if __has_include("sonymn_int.hpp")
#include "sonymn_int.hpp"
#elif __has_include("sonymn_int.h")
#include "sonymn_int.h"
#elif __has_include("src/sonymn_int.hpp")
#include "src/sonymn_int.hpp"
#elif __has_include("internal/sonymn_int.hpp")
#include "internal/sonymn_int.hpp"
#else
// If none of the above headers exist in your environment, include the TU-local declaration
// is not appropriate here. The production header should be used by the test build.
#error "Cannot find sonymn_int.hpp (SonyMakerNote declaration). Please add the correct include path."
#endif

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::Internal::SonyMakerNote;

class SonyMakerNoteTest_1590 : public ::testing::Test {
protected:
  static std::string CallPrintMultiBurstSize(const Value& value, const ExifData* exif = nullptr) {
    SonyMakerNote mn;
    std::ostringstream os;
    std::ostream& ret = mn.printMultiBurstSize(os, value, exif);

    // Verify the function returns the same stream reference (observable contract for stream printers).
    EXPECT_EQ(&ret, &os);

    return os.str();
  }

  static std::string ParenthesizedValueString(const Value& value) {
    std::ostringstream os;
    os << "(" << value << ")";
    return os.str();
  }
};

TEST_F(SonyMakerNoteTest_1590, PrintsNumberForUnsignedShortSingleCount_1590) {
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // Single element.
  ASSERT_NO_THROW(v->read("42"));
  ASSERT_EQ(v->count(), 1u);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);

  const std::string out = CallPrintMultiBurstSize(*v, nullptr);
  EXPECT_EQ(out, "42");
}

TEST_F(SonyMakerNoteTest_1590, IgnoresExifDataPointerWhenValid_1590) {
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("7"));
  ASSERT_EQ(v->count(), 1u);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);

  ExifData exif;
  const std::string out_with_exif = CallPrintMultiBurstSize(*v, &exif);
  const std::string out_without_exif = CallPrintMultiBurstSize(*v, nullptr);

  EXPECT_EQ(out_with_exif, "7");
  EXPECT_EQ(out_without_exif, "7");
}

TEST_F(SonyMakerNoteTest_1590, WrapsInParenthesesWhenCountNotOne_1590) {
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // Two elements => observable "error path" output formatting.
  ASSERT_NO_THROW(v->read("1 2"));
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_NE(v->count(), 1u);

  const std::string expected = ParenthesizedValueString(*v);
  const std::string out = CallPrintMultiBurstSize(*v, nullptr);

  EXPECT_EQ(out, expected);
}

TEST_F(SonyMakerNoteTest_1590, WrapsInParenthesesWhenTypeIsNotUnsignedShort_1590) {
  // Pick a different type that supports parsing and streaming.
  Value::UniquePtr v = Value::create(Exiv2::unsignedLong);
  ASSERT_NE(v.get(), nullptr);

  // Single element but wrong type => should be parenthesized.
  ASSERT_NO_THROW(v->read("99"));
  ASSERT_EQ(v->count(), 1u);
  ASSERT_NE(v->typeId(), Exiv2::unsignedShort);

  const std::string expected = ParenthesizedValueString(*v);
  const std::string out = CallPrintMultiBurstSize(*v, nullptr);

  EXPECT_EQ(out, expected);
}

TEST_F(SonyMakerNoteTest_1590, BoundaryCountZeroDoesNotCrashAndIsParenthesized_1590) {
  // Boundary: value with count() == 0 (uninitialized contents).
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // Do not read anything, leaving it empty/zero-count in typical implementations.
  // Regardless of internals, if count != 1 then output should be "(" << value << ")".
  ASSERT_NE(v->count(), 1u);

  const std::string expected = ParenthesizedValueString(*v);
  ASSERT_NO_THROW({
    const std::string out = CallPrintMultiBurstSize(*v, nullptr);
    EXPECT_EQ(out, expected);
  });
}

}  // namespace