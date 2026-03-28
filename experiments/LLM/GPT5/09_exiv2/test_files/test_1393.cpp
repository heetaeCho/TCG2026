// File: test_tags_int_print0x0213_1393.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Function under test (defined in src/tags_int.cpp)
std::ostream& print0x0213(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class Print0x0213Test_1393 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    // Use public factory + public read API only (black-box friendly).
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedShort);
    // read() return value is not specified/required by the interface excerpt; ensure we at least call it.
    (void)val->read(std::to_string(v));
    return val;
  }
};

TEST_F(Print0x0213Test_1393, ReturnsSameStreamReference_NullMetadata_1393) {
  auto v = makeUShortValue(1);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x0213(oss, *v, nullptr);

  // Observable behavior: returns an ostream& (should be the same stream passed in).
  EXPECT_EQ(&ret, &oss);
}

TEST_F(Print0x0213Test_1393, PrintsCenteredForValue1_NullMetadata_1393) {
  auto v = makeUShortValue(1);

  std::ostringstream oss;
  Exiv2::Internal::print0x0213(oss, *v, nullptr);
  const std::string out = oss.str();

  // Based on provided TagDetails mapping for exifYCbCrPositioning.
  EXPECT_NE(out.find("Centered"), std::string::npos);
  EXPECT_FALSE(out.empty());
}

TEST_F(Print0x0213Test_1393, PrintsCoSitedForValue2_NullMetadata_1393) {
  auto v = makeUShortValue(2);

  std::ostringstream oss;
  Exiv2::Internal::print0x0213(oss, *v, nullptr);
  const std::string out = oss.str();

  // TagDetails: {2, "Co-sited"}
  EXPECT_NE(out.find("Co-sited"), std::string::npos);
  EXPECT_FALSE(out.empty());
}

TEST_F(Print0x0213Test_1393, AcceptsNonNullMetadataPointer_EmptyExifData_1393) {
  auto v = makeUShortValue(1);
  Exiv2::ExifData md;  // empty metadata; should still be safe to pass

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x0213(oss, *v, &md);

  EXPECT_EQ(&ret, &oss);
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(Print0x0213Test_1393, UnknownValueDoesNotPrintKnownLabels_1393) {
  auto v = makeUShortValue(3);  // boundary/other value not in provided TagDetails

  std::ostringstream oss;
  Exiv2::Internal::print0x0213(oss, *v, nullptr);
  const std::string out = oss.str();

  // Black-box safe checks:
  // - It should produce some output (common for tag printers),
  // - and should not incorrectly map to the provided known labels.
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.find("Centered"), std::string::npos);
  EXPECT_EQ(out.find("Co-sited"), std::string::npos);
}

TEST_F(Print0x0213Test_1393, HandlesDefaultConstructedValueObject_NoThrow_1393) {
  // Boundary-ish: create a Value instance but do not populate it.
  // We only assert it doesn't throw and returns the same stream reference.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::print0x0213(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });
}

}  // namespace