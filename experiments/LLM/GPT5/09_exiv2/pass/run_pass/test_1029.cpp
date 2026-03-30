// File: test_minoltamn_int_printMinoltaSonyAFAreaMode_1029.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Under test (implemented in ./TestProjects/exiv2/src/minoltamn_int.cpp)
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyAFAreaMode(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintMinoltaSonyAFAreaModeTest_1029 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValueFromString(const std::string& s) {
    // Use a numeric type suitable for tag-detail mapping. Treat as black-box: only use public API.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    if (v) {
      // Value::read(std::string) is part of the public interface.
      (void)v->read(s);
    }
    return v;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, v, md);
    return oss.str();
  }
};

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, ReturnsSameStreamReference_1029) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, *v, nullptr);

  // Observable behavior: function returns an std::ostream&; it should be the same stream passed in.
  EXPECT_EQ(&ret, &oss);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, PrintsWideForZero_1029) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Wide"), std::string::npos);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, PrintsLocalForOne_1029) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Local"), std::string::npos);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, PrintsSpotForTwo_1029) {
  auto v = makeUShortValueFromString("2");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Spot"), std::string::npos);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, UnknownValueStillProducesOutput_1029) {
  auto v = makeUShortValueFromString("3");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);

  // Black-box: don't assume exact formatting for unknown values; just ensure it prints something useful.
  EXPECT_FALSE(out.empty());
  // Often printers include the numeric value for unknown enumerations; accept that if present.
  EXPECT_NE(out.find("3"), std::string::npos);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, NonNullMetadataDoesNotCrashAndStillPrints_1029) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData md;  // public type; contents not required for this tag printer
  const std::string out = render(*v, &md);

  EXPECT_FALSE(out.empty());
  // Still expect the mapped label for a known value.
  EXPECT_NE(out.find("Local"), std::string::npos);
}

TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, MalformedValueInputDoesNotCrash_1029) {
  auto v = makeUShortValueFromString("not-a-number");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  // Observable: should not throw/crash and should return stream reference.
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);

  // Output may vary; just ensure stream remains usable.
  EXPECT_TRUE(oss.good());
}

}  // namespace