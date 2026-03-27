// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tags_int_printGPSDirRef_1420.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& printGPSDirRef(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
  // Use only public factory + public read API (black-box).
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  EXPECT_NE(v.get(), nullptr);
  if (v) {
    (void)v->read(s);
  }
  return v;
}

class PrintGPSDirRefTest_1420 : public ::testing::Test {};

}  // namespace

TEST_F(PrintGPSDirRefTest_1420, ReturnsSameStreamReference_NullMetadata_1420) {
  auto v = makeAsciiValue("T");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printGPSDirRef(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(PrintGPSDirRefTest_1420, PrintsTrueDirectionForT_NullMetadata_1420) {
  auto v = makeAsciiValue("T");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printGPSDirRef(os, *v, nullptr);

  const std::string out = os.str();
  // Observable behavior: should produce some output describing the value.
  EXPECT_FALSE(out.empty());
  // Be tolerant to formatting differences (avoid exact string matching).
  EXPECT_NE(out.find("True"), std::string::npos);
  EXPECT_NE(out.find("direction"), std::string::npos);
}

TEST_F(PrintGPSDirRefTest_1420, PrintsMagneticDirectionForM_NullMetadata_1420) {
  auto v = makeAsciiValue("M");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printGPSDirRef(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Magnetic"), std::string::npos);
  EXPECT_NE(out.find("direction"), std::string::npos);
}

TEST_F(PrintGPSDirRefTest_1420, AcceptsNonNullMetadata_StillReturnsStream_1420) {
  auto v = makeAsciiValue("T");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData exif;  // Empty metadata; interaction is black-box.
  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printGPSDirRef(os, *v, &exif);

  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(PrintGPSDirRefTest_1420, UnknownValueDoesNotCrash_ProducesNonEmptyOutput_1420) {
  auto v = makeAsciiValue("X");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printGPSDirRef(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);

  const std::string out = os.str();
  // For unknown values, exact formatting is unspecified; just ensure something observable happens.
  EXPECT_FALSE(out.empty());
  // Typically the raw value is included somewhere; allow either upper/lower or quoting formats.
  EXPECT_NE(out.find("X"), std::string::npos);
}

TEST_F(PrintGPSDirRefTest_1420, EmptyStringValue_DoesNotCrash_ReturnsStream_1420) {
  auto v = makeAsciiValue("");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printGPSDirRef(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
  // Output may be empty or may contain some placeholder; do not assert specifics.
}