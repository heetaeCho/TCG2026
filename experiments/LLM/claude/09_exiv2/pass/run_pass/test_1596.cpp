#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for SonyMakerNote
// Adjust path as needed for the actual build system
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1596 : public ::testing::Test {
protected:
  std::ostringstream os;

  // Helper to create ExifData with a model string
  void setModel(ExifData& exifData, const std::string& model) {
    exifData["Exif.Image.Model"] = model;
  }

  // Helper to set AFAreaModeSetting in ExifData
  void setAFAreaModeSetting(ExifData& exifData, uint32_t val) {
    // The tag for AFAreaModeSetting in Sony maker notes
    // Tag 0x2015 in Sony camera settings or similar
    // We need to set it so getAFAreaModeSetting can find it
    exifData["Exif.Sony2.AFAreaModeSetting"] = static_cast<uint16_t>(val);
  }

  // Create a Value of unsignedByte type with a single byte value
  std::unique_ptr<Value> createUnsignedByteValue(uint8_t val) {
    auto v = Value::create(unsignedByte);
    byte buf[1] = {val};
    v->read(buf, 1, littleEndian);
    return v;
  }

  // Create a Value of unsignedShort type with a single value
  std::unique_ptr<Value> createUnsignedShortValue(uint16_t val) {
    auto v = Value::create(unsignedShort);
    byte buf[2];
    buf[0] = static_cast<byte>(val & 0xFF);
    buf[1] = static_cast<byte>((val >> 8) & 0xFF);
    v->read(buf, 2, littleEndian);
    return v;
  }

  // Create a multi-byte Value
  std::unique_ptr<Value> createMultiByteValue(const std::vector<uint8_t>& vals) {
    auto v = Value::create(unsignedByte);
    v->read(vals.data(), vals.size(), littleEndian);
    return v;
  }
};

// Test: Null metadata pointer should output "(value)"
TEST_F(SonyMakerNoteTest_1596, NullMetadata_1596) {
  auto value = createUnsignedByteValue(5);
  SonyMakerNote::printAFPointSelected(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value count != 1 should output "(value)"
TEST_F(SonyMakerNoteTest_1596, MultipleValueCount_1596) {
  auto value = createMultiByteValue({1, 2});
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Wrong type (not unsignedByte) should output "(value)"
TEST_F(SonyMakerNoteTest_1596, WrongValueType_1596) {
  auto value = createUnsignedShortValue(5);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: No model in metadata should output "(value)"
TEST_F(SonyMakerNoteTest_1596, NoModel_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  // Don't set any model
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: SLT- model should use Set1 lookup - value 0 = "Auto"
TEST_F(SonyMakerNoteTest_1596, SLTModelAutoPoint_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Auto") != std::string::npos);
}

// Test: SLT- model should use Set1 lookup - value 1 = "Center"
TEST_F(SonyMakerNoteTest_1596, SLTModelCenterPoint_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: HV- model should use Set1 lookup
TEST_F(SonyMakerNoteTest_1596, HVModelSet1_1596) {
  auto value = createUnsignedByteValue(2);
  ExifData exifData;
  setModel(exifData, "HV-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Top") != std::string::npos);
}

// Test: SLT- model value that maps to "Right"
TEST_F(SonyMakerNoteTest_1596, SLTModelRightPoint_1596) {
  auto value = createUnsignedByteValue(4);
  ExifData exifData;
  setModel(exifData, "SLT-A99");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Right") != std::string::npos);
}

// Test: NEX- model should use Set5
TEST_F(SonyMakerNoteTest_1596, NEXModelSet5_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  setModel(exifData, "NEX-7");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Center Zone") != std::string::npos);
}

// Test: NEX- model value 0 = "n/a" in Set5
TEST_F(SonyMakerNoteTest_1596, NEXModelNAPoint_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "NEX-5");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: ILCE- model with AFAreaModeSetting == 4 should use Set1
TEST_F(SonyMakerNoteTest_1596, ILCEModelAFAreaMode4Set1_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  setAFAreaModeSetting(exifData, 4);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Should use Set1 which maps 1 to "Center"
  EXPECT_TRUE(result.find("Center") != std::string::npos);
}

// Test: ILCE- model without AFAreaModeSetting == 4 should use Set5
TEST_F(SonyMakerNoteTest_1596, ILCEModelOtherAFAreaModeSet5_1596) {
  auto value = createUnsignedByteValue(2);
  ExifData exifData;
  setModel(exifData, "ILCE-7M3");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Should fall through to Set5 which maps 2 to "Top Zone"
  EXPECT_TRUE(result.find("Top Zone") != std::string::npos);
}

// Test: ILCA-68 model with AFAreaModeSetting != 8 should use Set2
TEST_F(SonyMakerNoteTest_1596, ILCA68Set2_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Auto") != std::string::npos);
}

// Test: ILCA-77M2 model with AFAreaModeSetting != 8 should use Set2
TEST_F(SonyMakerNoteTest_1596, ILCA77M2Set2_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  setModel(exifData, "ILCA-77M2");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Set2 maps 1 to "A6"
  EXPECT_TRUE(result.find("A6") != std::string::npos);
}

// Test: ILCA-68 model with AFAreaModeSetting == 8 should use Set4
TEST_F(SonyMakerNoteTest_1596, ILCA68AFAreaMode8Set4_1596) {
  auto value = createUnsignedByteValue(5);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  setAFAreaModeSetting(exifData, 8);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Set4 maps 5 to "Center Zone"
  EXPECT_TRUE(result.find("Center Zone") != std::string::npos);
}

// Test: ILCA-99M2 model with AFAreaModeSetting != 8 should use Set3
TEST_F(SonyMakerNoteTest_1596, ILCA99M2Set3_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "ILCA-99M2");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Set3 maps 0 to "Auto"
  EXPECT_TRUE(result.find("Auto") != std::string::npos);
}

// Test: ILCA-99M2 model with AFAreaModeSetting == 8 should use Set4
TEST_F(SonyMakerNoteTest_1596, ILCA99M2AFAreaMode8Set4_1596) {
  auto value = createUnsignedByteValue(1);
  ExifData exifData;
  setModel(exifData, "ILCA-99M2");
  setAFAreaModeSetting(exifData, 8);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Set4 maps 1 to "Top Left Zone"
  EXPECT_TRUE(result.find("Top Left Zone") != std::string::npos);
}

// Test: ILME- model with AFAreaModeSetting == 4 should use Set1
TEST_F(SonyMakerNoteTest_1596, ILMEModelAFAreaMode4Set1_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "ILME-FX3");
  setAFAreaModeSetting(exifData, 4);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Auto") != std::string::npos);
}

// Test: ILME- model with other AFAreaModeSetting should use Set5
TEST_F(SonyMakerNoteTest_1596, ILMEModelOtherAFAreaModeSet5_1596) {
  auto value = createUnsignedByteValue(3);
  ExifData exifData;
  setModel(exifData, "ILME-FX3");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  // Set5 maps 3 to "Right Zone"
  EXPECT_TRUE(result.find("Right Zone") != std::string::npos);
}

// Test: Unknown model should output "n/a"
TEST_F(SonyMakerNoteTest_1596, UnknownModelNA_1596) {
  auto value = createUnsignedByteValue(5);
  ExifData exifData;
  setModel(exifData, "DSC-RX100");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: SLT model with boundary value 19 (Upper Far Left)
TEST_F(SonyMakerNoteTest_1596, SLTModelBoundaryValue19_1596) {
  auto value = createUnsignedByteValue(19);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Upper Far Left") != std::string::npos);
}

// Test: Set4 value 0 = "n/a"
TEST_F(SonyMakerNoteTest_1596, ILCA68AFAreaMode8Value0_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  setAFAreaModeSetting(exifData, 8);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("n/a") != std::string::npos);
}

// Test: Set4 value 9 = "Bottom Right Zone"
TEST_F(SonyMakerNoteTest_1596, Set4BottomRightZone_1596) {
  auto value = createUnsignedByteValue(9);
  ExifData exifData;
  setModel(exifData, "ILCA-77M2");
  setAFAreaModeSetting(exifData, 8);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Bottom Right Zone") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1596, ReturnsSameOstream_1596) {
  auto value = createUnsignedByteValue(0);
  ExifData exifData;
  setModel(exifData, "SLT-A77");
  std::ostream& ret = SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for null metadata
TEST_F(SonyMakerNoteTest_1596, ReturnsSameOstreamNull_1596) {
  auto value = createUnsignedByteValue(0);
  std::ostream& ret = SonyMakerNote::printAFPointSelected(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: NEX model Set5 value 5 = "Bottom Zone"
TEST_F(SonyMakerNoteTest_1596, NEXBottomZone_1596) {
  auto value = createUnsignedByteValue(5);
  ExifData exifData;
  setModel(exifData, "NEX-6");
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Bottom Zone") != std::string::npos);
}

// Test: Set2 value with Auto (128)
TEST_F(SonyMakerNoteTest_1596, Set2AutoValue128_1596) {
  auto value = createUnsignedByteValue(128);
  ExifData exifData;
  setModel(exifData, "ILCA-68");
  setAFAreaModeSetting(exifData, 0);
  SonyMakerNote::printAFPointSelected(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_TRUE(result.find("Auto") != std::string::npos);
}
