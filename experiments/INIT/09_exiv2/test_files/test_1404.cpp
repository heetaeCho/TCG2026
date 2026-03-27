// File: test_tags_int_print0x9207_1404.cpp
// TEST_ID: 1404

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in ./src/tags_int.cpp)
std::ostream& print0x9207(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

std::string RenderMeteringMode(int64_t n, const Exiv2::ExifData* md) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  // Use textual read to avoid depending on internal storage/layout.
  const int rc = v->read(std::to_string(n));
  (void)rc;  // Some builds may not guarantee a specific return code contract here.

  std::ostringstream oss;
  Exiv2::Internal::print0x9207(oss, *v, md);
  return oss.str();
}

}  // namespace

TEST(Print0x9207Test_1404, PrintsMappedValue_Unknown0_1404) {
  const std::string out = RenderMeteringMode(0, nullptr);
  EXPECT_NE(out.find("Unknown"), std::string::npos);
}

TEST(Print0x9207Test_1404, PrintsMappedValue_Average1_1404) {
  const std::string out = RenderMeteringMode(1, nullptr);
  EXPECT_NE(out.find("Average"), std::string::npos);
}

TEST(Print0x9207Test_1404, PrintsMappedValue_CenterWeighted2_1404) {
  const std::string out = RenderMeteringMode(2, nullptr);
  EXPECT_NE(out.find("Center weighted average"), std::string::npos);
}

TEST(Print0x9207Test_1404, PrintsMappedValue_Spot3_1404) {
  const std::string out = RenderMeteringMode(3, nullptr);
  EXPECT_NE(out.find("Spot"), std::string::npos);
}

TEST(Print0x9207Test_1404, PrintsMappedValue_Other255_1404) {
  const std::string out = RenderMeteringMode(255, nullptr);
  EXPECT_NE(out.find("Other"), std::string::npos);
}

TEST(Print0x9207Test_1404, NullMetadataAndNonNullMetadataProduceSameText_1404) {
  Exiv2::ExifData exif;
  const std::string out_null = RenderMeteringMode(4, nullptr);
  const std::string out_nonnull = RenderMeteringMode(4, &exif);
  EXPECT_EQ(out_null, out_nonnull);
}

TEST(Print0x9207Test_1404, BoundaryValueDoesNotCrashAndProducesSomeOutput_1404) {
  // Boundary-ish: a value outside the provided TagDetails list (0..6, 255).
  const std::string out = RenderMeteringMode(65535, nullptr);
  EXPECT_FALSE(out.empty());
}