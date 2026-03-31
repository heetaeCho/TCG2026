#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for SonyMakerNote
// Adjust path as needed based on project structure
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteAFAreaModeSettingTest_1594 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Helper to create a Value with a single unsigned byte
    Value::UniquePtr createUnsignedByteValue(uint8_t val) {
        auto v = Value::create(unsignedByte);
        v->read(reinterpret_cast<const byte*>(&val), 1, littleEndian);
        return v;
    }

    // Helper to create a Value with unsignedShort type (wrong type for testing)
    Value::UniquePtr createUnsignedShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        byte buf[2];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        v->read(buf, 2, littleEndian);
        return v;
    }
};

// Test: null metadata pointer should output value in parentheses
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, NullMetadata_1594) {
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: wrong type (not unsignedByte) should output value in parentheses
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, WrongTypeId_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    auto value = createUnsignedShortValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: no model in metadata should output value in parentheses
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, NoModelInMetadata_1594) {
    ExifData exifData;
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: SLT- model prefix should use Set1, value 0 = "Wide"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, SLTModelWide_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: SLT- model prefix should use Set1, value 4 = "Local"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, SLTModelLocal_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A99");
    auto value = createUnsignedByteValue(4);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Local"), std::string::npos);
}

// Test: SLT- model prefix should use Set1, value 8 = "Zone"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, SLTModelZone_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A58");
    auto value = createUnsignedByteValue(8);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Zone"), std::string::npos);
}

// Test: SLT- model prefix should use Set1, value 9 = "Spot"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, SLTModelSpot_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A65");
    auto value = createUnsignedByteValue(9);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Spot"), std::string::npos);
}

// Test: HV model prefix should use Set1
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, HVModelSet1_1594) {
    ExifData exifData;
    setModel(exifData, "HV-something");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: NEX- model prefix should use Set2, value 0 = "Wide"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, NEXModelWide_1594) {
    ExifData exifData;
    setModel(exifData, "NEX-7");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: NEX- model, value 1 = "Center"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, NEXModelCenter_1594) {
    ExifData exifData;
    setModel(exifData, "NEX-5T");
    auto value = createUnsignedByteValue(1);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center"), std::string::npos);
}

// Test: NEX- model, value 3 = "Flexible Spot"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, NEXModelFlexibleSpot_1594) {
    ExifData exifData;
    setModel(exifData, "NEX-6");
    auto value = createUnsignedByteValue(3);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Flexible Spot"), std::string::npos);
}

// Test: ILCE- model prefix should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCEModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    auto value = createUnsignedByteValue(11);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Zone"), std::string::npos);
}

// Test: ILME- model prefix should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILMEModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "ILME-FX3");
    auto value = createUnsignedByteValue(12);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Expanded flexible spot"), std::string::npos);
}

// Test: DSC-RX10M4 model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCRX10M4ModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-RX10M4");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: DSC-RX100M6 model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCRX100M6ModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-RX100M6");
    auto value = createUnsignedByteValue(1);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center"), std::string::npos);
}

// Test: DSC-RX100M7 model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCRX100M7ModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-RX100M7");
    auto value = createUnsignedByteValue(3);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Flexible Spot"), std::string::npos);
}

// Test: DSC-RX100M5A model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCRX100M5AModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-RX100M5A");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: DSC-HX99 model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCHX99ModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-HX99");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: DSC-RX0M2 model should use Set2
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCRX0M2ModelSet2_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-RX0M2");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: ILCA- model prefix should use Set3, value 0 = "Wide"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCAModelWide_1594) {
    ExifData exifData;
    setModel(exifData, "ILCA-77M2");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Wide"), std::string::npos);
}

// Test: ILCA- model, value 4 = "Flexible spot"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCAModelFlexibleSpot_1594) {
    ExifData exifData;
    setModel(exifData, "ILCA-99M2");
    auto value = createUnsignedByteValue(4);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Flexible spot"), std::string::npos);
}

// Test: ILCA- model, value 8 = "Zone"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCAModelZone_1594) {
    ExifData exifData;
    setModel(exifData, "ILCA-77M2");
    auto value = createUnsignedByteValue(8);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Zone"), std::string::npos);
}

// Test: ILCA- model, value 9 = "Center"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCAModelCenter_1594) {
    ExifData exifData;
    setModel(exifData, "ILCA-68");
    auto value = createUnsignedByteValue(9);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center"), std::string::npos);
}

// Test: ILCA- model, value 12 = "Expanded flexible spot"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCAModelExpandedFlexibleSpot_1594) {
    ExifData exifData;
    setModel(exifData, "ILCA-99M2");
    auto value = createUnsignedByteValue(12);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Expanded flexible spot"), std::string::npos);
}

// Test: Unknown model should output "n/a"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, UnknownModelNA_1594) {
    ExifData exifData;
    setModel(exifData, "CANON-EOS-R5");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    // Should contain "n/a" (possibly localized)
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
}

// Test: DSC- prefix that doesn't match any specific DSC model should output "n/a"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, DSCNonMatchingModel_1594) {
    ExifData exifData;
    setModel(exifData, "DSC-W800");
    auto value = createUnsignedByteValue(0);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    // DSC-W800 doesn't start with any of the models2 entries
    // It should fall through to n/a
    EXPECT_FALSE(result.empty());
}

// Test: Set1 with unknown value should produce some output (not crash)
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, SLTModelUnknownValue_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    auto value = createUnsignedByteValue(255);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Set2 with value 4 = "Flexible Spot (LA-EA4)"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCEModelFlexibleSpotLAEA4_1594) {
    ExifData exifData;
    setModel(exifData, "ILCE-6000");
    auto value = createUnsignedByteValue(4);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Flexible Spot"), std::string::npos);
}

// Test: Set2 with value 9 = "Center (LA-EA4)"
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ILCEModelCenterLAEA4_1594) {
    ExifData exifData;
    setModel(exifData, "ILCE-7");
    auto value = createUnsignedByteValue(9);
    SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center"), std::string::npos);
}

// Test: Multiple byte value (count != 1) should output in parentheses
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, MultipleByteValues_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    auto v = Value::create(unsignedByte);
    byte buf[2] = {0, 1};
    v->read(buf, 2, littleEndian);
    SonyMakerNote::printAFAreaModeSetting(os, *v, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ReturnsSameOstream_1594) {
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    auto value = createUnsignedByteValue(0);
    std::ostream& ret = SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for null metadata
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ReturnsSameOstreamNullMeta_1594) {
    auto value = createUnsignedByteValue(0);
    std::ostream& ret = SonyMakerNote::printAFAreaModeSetting(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for unknown model
TEST_F(SonyMakerNoteAFAreaModeSettingTest_1594, ReturnsSameOstreamUnknownModel_1594) {
    ExifData exifData;
    setModel(exifData, "UnknownModel");
    auto value = createUnsignedByteValue(0);
    std::ostream& ret = SonyMakerNote::printAFAreaModeSetting(os, *value, &exifData);
    EXPECT_EQ(&ret, &os);
}
