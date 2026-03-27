// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaSonyBoolInverseValue_1028.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <memory>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Declaration should be available from the internal header in the Exiv2 codebase.
#include "minoltamn_int.hpp"

namespace {

std::string trimCopy(std::string s) {
  auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
  s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
  return s;
}

Exiv2::Value::UniquePtr makeUShortValueFromString(const std::string& text) {
  // Use a simple numeric value type that supports Value::read(std::string).
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  EXPECT_NE(v.get(), nullptr);
  if (!v) return v;

  // read() returns int; we don't assume the exact meaning beyond "call succeeds"
  // so we only assert non-negative (common convention in Exiv2 Value readers).
  const int rc = v->read(text);
  EXPECT_GE(rc, 0);
  return v;
}

}  // namespace

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, PrintsOnForZero_1028) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, nullptr);

  EXPECT_EQ(trimCopy(os.str()), "On");
}

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, PrintsOffForOne_1028) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, nullptr);

  EXPECT_EQ(trimCopy(os.str()), "Off");
}

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, ReturnsSameStreamReference_1028) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, nullptr);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
}

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, AcceptsNullMetadata_1028) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, nullptr);
  });

  EXPECT_FALSE(trimCopy(os.str()).empty());
}

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, WorksWithNonNullExifDataPointer_1028) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData exif;  // empty metadata; we only verify pointer is accepted

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, &exif);
  });

  // Should still produce a meaningful output.
  EXPECT_EQ(trimCopy(os.str()), "On");
}

TEST(PrintMinoltaSonyBoolInverseValueTest_1028, HandlesUnknownValueWithoutCrashing_1028) {
  auto v = makeUShortValueFromString("2");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, *v, nullptr);
  });

  // For out-of-range values, exact formatting is implementation-defined.
  // We only require that something observable is written.
  EXPECT_FALSE(trimCopy(os.str()).empty());
}