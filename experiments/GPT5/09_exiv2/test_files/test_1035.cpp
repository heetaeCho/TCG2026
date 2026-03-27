// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::Internal::printMinoltaSonySceneMode
// File under test: ./TestProjects/exiv2/src/minoltamn_int.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
class Value;
class ExifData;

namespace Internal {
std::ostream& printMinoltaSonySceneMode(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintMinoltaSonySceneModeTest_1035 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    // Use only the public interface: create + read from string.
    // If parsing fails, ok() may become false; tests using this helper
    // will still observe the black-box behavior via output.
    (void)val->read(std::to_string(static_cast<unsigned int>(v)));
    return val;
  }
};

TEST_F(PrintMinoltaSonySceneModeTest_1035, ReturnsSameStreamReference_1035) {
  auto v = makeUShortValue(0);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
}

TEST_F(PrintMinoltaSonySceneModeTest_1035, PrintsKnownValueStandard_1035) {
  auto v = makeUShortValue(0);

  std::ostringstream oss;
  Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("Standard"), std::string::npos);
}

TEST_F(PrintMinoltaSonySceneModeTest_1035, PrintsKnownValuePortrait_1035) {
  auto v = makeUShortValue(1);

  std::ostringstream oss;
  Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("Portrait"), std::string::npos);
}

TEST_F(PrintMinoltaSonySceneModeTest_1035, PrintsKnownValueHDR_1035) {
  auto v = makeUShortValue(33);

  std::ostringstream oss;
  Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("HDR"), std::string::npos);
}

TEST_F(PrintMinoltaSonySceneModeTest_1035, PrintsBoundaryNAValue_1035) {
  auto v = makeUShortValue(65535);

  std::ostringstream oss;
  Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("n/a"), std::string::npos);
}

TEST_F(PrintMinoltaSonySceneModeTest_1035, WorksWithNonNullMetadataPointer_1035) {
  auto v = makeUShortValue(0);

  Exiv2::ExifData exif;
  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonySceneMode(oss, *v, &exif);

  EXPECT_EQ(&ret, &oss);
  EXPECT_NE(oss.str().find("Standard"), std::string::npos);
}

}  // namespace