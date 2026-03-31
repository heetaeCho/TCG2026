#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1615 : public ::testing::Test {
 protected:
  std::ostringstream os;

  // Helper to set the camera model in ExifData
  void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
  }

  // Helper to create a Value with a single integer
  std::unique_ptr<Value> createUShortValue(uint16_t val) {
    auto v = Value::create(unsignedShort);
    std::string s = std::to_string(val);
    v->read(s);
    return v;
  }

  // Helper to create a Value with multiple integers
  std::unique_ptr<Value> createMultiUShortValue(const std::vector<uint16_t>& vals) {
    auto v = Value::create(unsignedShort);
    std::string s;
    for (size_t i = 0; i < vals.size(); i++) {
      if (i > 0) s += " ";
      s += std::to_string(vals[i]);
    }
    v->read(s);
    return v;
  }

  std::unique_ptr<Value> createUByteValue(uint8_t val) {
    auto v = Value::create(unsignedByte);
    std::string s = std::to_string(val);
    v->read(s);
    return v;
  }

  std::unique_ptr<Value> createMultiUByteValue(const std::vector<uint8_t>& vals) {
    auto v = Value::create(unsignedByte);
    std::string s;
    for (size_t i = 0; i < vals.size(); i++) {
      if (i > 0) s += " ";
      s += std::to_string(vals[i]);
    }
    v->read(s);
    return v;
  }
};

// Test: printSony2FpFocusPosition2 with null metadata returns value in parentheses
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_NullMetadata_1615) {
  auto val = createUByteValue(100);
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with count != 1 returns value in parentheses
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_MultipleValues_1615) {
  auto val = createMultiUByteValue({100, 200});
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with DSC- model prefix returns "n/a"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_DSCModel_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  setModel(exifData, "DSC-RX100");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with Stellar model prefix returns "n/a"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_StellarModel_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  setModel(exifData, "Stellar");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with value 255 returns "Infinity"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_Infinity_1615) {
  auto val = createUByteValue(255);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Infinity") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with normal value returns the numeric value
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_NormalValue_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "100");
}

// Test: printSony2FpFocusPosition2 with value 0 returns "0"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_ZeroValue_1615) {
  auto val = createUByteValue(0);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "0");
}

// Test: printSony2FpFocusPosition2 with value 254 (boundary near 255) returns numeric
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_BoundaryValue254_1615) {
  auto val = createUByteValue(254);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "254");
}

// Test: printSony2FpFocusPosition2 with value 1 returns "1"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_ValueOne_1615) {
  auto val = createUByteValue(1);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "1");
}

// Test: printSony2FpFocusPosition2 with no model in metadata returns parenthesized value
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_NoModelInMetadata_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  // Do not set any model
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with DSC- model and value 255 still returns "n/a"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_DSCModelInfinity_1615) {
  auto val = createUByteValue(255);
  ExifData exifData;
  setModel(exifData, "DSC-HX90V");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with SLT model (non-DSC, non-Stellar) returns value
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_SLTModel_1615) {
  auto val = createUByteValue(50);
  ExifData exifData;
  setModel(exifData, "SLT-A77V");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_EQ(result, "50");
}

// Test: Verify the return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_ReturnsSameStream_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  std::ostream& ret = SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  EXPECT_EQ(&ret, &os);
}

// Test: printSony2FpFocusPosition2 with "StellarXYZ" model returns "n/a" (starts_with "Stellar")
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_StellarExtendedModel_1615) {
  auto val = createUByteValue(100);
  ExifData exifData;
  setModel(exifData, "StellarXYZ");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: printSony2FpFocusPosition2 with "DSC-" exact model returns "n/a"
TEST_F(SonyMakerNoteTest_1615, FocusPosition2_DSCExactPrefix_1615) {
  auto val = createUByteValue(42);
  ExifData exifData;
  setModel(exifData, "DSC-");
  SonyMakerNote::printSony2FpFocusPosition2(os, *val, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}
