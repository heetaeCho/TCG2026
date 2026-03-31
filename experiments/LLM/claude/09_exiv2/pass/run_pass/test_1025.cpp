#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exiv2.hpp"

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyLensID(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyLensIDTest_1025 : public ::testing::Test {
protected:
  std::ostringstream os;

  // Helper to create a UShortValue with a given value
  std::unique_ptr<Exiv2::Value> makeUInt32Value(uint32_t val) {
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    std::string s = std::to_string(val);
    v->read(s);
    return v;
  }

  std::unique_ptr<Exiv2::Value> makeUShortValue(uint16_t val) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    std::string s = std::to_string(val);
    v->read(s);
    return v;
  }
};

// Test that a known lens ID (0) returns the expected lens name
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_0_ReturnsMinoltaAF28_85_1025) {
  auto value = makeUInt32Value(0);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Minolta AF 28-85mm F3.5-4.5"), std::string::npos)
      << "Got: " << result;
}

// Test that a known lens ID (1) returns the expected lens name
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_1_ReturnsMinoltaAF80_200_1025) {
  auto value = makeUInt32Value(1);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Minolta AF 80-200mm F2.8 HS-APO G"), std::string::npos)
      << "Got: " << result;
}

// Test that known lens ID 4 returns "Minolta AF 85mm F1.4G"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_4_ReturnsMinoltaAF85_1025) {
  auto value = makeUInt32Value(4);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Minolta AF 85mm F1.4G"), std::string::npos)
      << "Got: " << result;
}

// Test that known lens ID 25500 returns "Minolta AF 50mm F1.7"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_25500_ReturnsMinoltaAF50_1025) {
  auto value = makeUInt32Value(25500);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Minolta AF 50mm F1.7"), std::string::npos)
      << "Got: " << result;
}

// Test that known lens ID 65280 returns "Sigma 16mm F2.8 Filtermatic Fisheye"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_65280_ReturnsSigma16mm_1025) {
  auto value = makeUInt32Value(65280);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Sigma 16mm F2.8 Filtermatic Fisheye"), std::string::npos)
      << "Got: " << result;
}

// Test an unknown lens ID that doesn't exist in the table
TEST_F(PrintMinoltaSonyLensIDTest_1025, UnknownLensID_ReturnsNumericOrUnknown_1025) {
  auto value = makeUInt32Value(99999);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  // Should output something (either "99999" or "(99999)")
  EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata for index 0x0080 (128) - a lens ID that has special resolution function
// Without metadata, it should fall through to the tag table lookup
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_128_NullMetadata_FallsThrough_1025) {
  auto value = makeUInt32Value(128);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  // Should still produce output (from the tag table since metadata is null)
  EXPECT_FALSE(result.empty());
  // Index 128 exists in the tag table
  EXPECT_NE(result.find("Sigma"), std::string::npos) << "Got: " << result;
}

// Test with metadata for index 0x0080 (128) - special resolution function with metadata
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_128_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(128);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  // With empty metadata, the resolve function should still produce some output
  EXPECT_FALSE(result.empty());
}

// Test with metadata for index 0x00ff (255) - another special resolution function
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_255_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(255);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with metadata for index 0xffff (65535) - another special resolution function
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_65535_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(65535);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with metadata for index 0x001c (28) - special resolution function
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_28_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(28);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with metadata for index 0x0029 (41) - special resolution function
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_41_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(41);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test with metadata for index 0x0034 (52) - special resolution function
TEST_F(PrintMinoltaSonyLensIDTest_1025, LensID_52_WithMetadata_CallsResolveLens_1025) {
  auto value = makeUInt32Value(52);
  Exiv2::ExifData metadata;
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, &metadata);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test that output stream is returned correctly (chaining)
TEST_F(PrintMinoltaSonyLensIDTest_1025, ReturnedStreamIsSameAsInput_1025) {
  auto value = makeUInt32Value(0);
  std::ostream& returned = Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

// Test known lens ID 20 - "Minolta/Sony 135mm F2.8 [T4.5] STF"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_20_ReturnsSTF_1025) {
  auto value = makeUInt32Value(20);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("135mm F2.8"), std::string::npos)
      << "Got: " << result;
}

// Test known lens ID 43 - "Sony 35mm F1.4 G (SAL35F14G)"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_43_ReturnsSony35mm_1025) {
  auto value = makeUInt32Value(43);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Sony 35mm F1.4 G"), std::string::npos)
      << "Got: " << result;
}

// Test known lens ID 193 - "Minolta AF 1.4x APO II"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_193_ReturnsTeleconverter_1025) {
  auto value = makeUInt32Value(193);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Minolta AF 1.4x APO II"), std::string::npos)
      << "Got: " << result;
}

// Test a value that is not in the special function table but is in the tag details
// Lens ID 2 (no special function needed) - "Minolta AF 28-70mm F2.8 G"
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_2_NoSpecialFunction_1025) {
  auto value = makeUInt32Value(2);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Minolta AF 28-70mm F2.8 G"), std::string::npos)
      << "Got: " << result;
}

// Test with UShort value type as well
TEST_F(PrintMinoltaSonyLensIDTest_1025, UShortValue_KnownLensID_1025) {
  auto value = makeUShortValue(3);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Minolta AF 28-80mm F4-5.6"), std::string::npos)
      << "Got: " << result;
}

// Test lens ID 70 - last regular entry before gap
TEST_F(PrintMinoltaSonyLensIDTest_1025, KnownLensID_70_ReturnsSonyPlanar_1025) {
  auto value = makeUInt32Value(70);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Planar"), std::string::npos)
      << "Got: " << result;
}

// Test that an index value not matching special functions and not in table produces output
TEST_F(PrintMinoltaSonyLensIDTest_1025, NonExistentLensID_50000_1025) {
  auto value = makeUInt32Value(50000);
  Exiv2::Internal::printMinoltaSonyLensID(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
