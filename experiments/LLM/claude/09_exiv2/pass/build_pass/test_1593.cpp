#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal header for SonyMakerNote
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteFocusMode2Test_1593 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to set model in ExifData
    void setModel(ExifData& exifData, const std::string& model) {
        exifData["Exif.Image.Model"] = model;
    }

    // Helper to create a Value with unsignedByte type and a single byte
    std::unique_ptr<Value> createUnsignedByteValue(uint8_t val) {
        auto v = Value::create(unsignedByte);
        byte buf[1] = {val};
        v->read(buf, 1, littleEndian);
        return v;
    }

    // Helper to create a Value with unsignedShort type (wrong type)
    std::unique_ptr<Value> createUnsignedShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        byte buf[2];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        v->read(buf, 2, littleEndian);
        return v;
    }

    // Helper to create a multi-count unsignedByte value
    std::unique_ptr<Value> createMultiByteValue(uint8_t v1, uint8_t v2) {
        auto v = Value::create(unsignedByte);
        byte buf[2] = {v1, v2};
        v->read(buf, 2, littleEndian);
        return v;
    }
};

// Test: null metadata should output raw value in parentheses
TEST_F(SonyMakerNoteFocusMode2Test_1593, NullMetadata_1593) {
    auto value = createUnsignedByteValue(2);
    SonyMakerNote::printFocusMode2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: wrong type (not unsignedByte) should output raw value in parentheses
TEST_F(SonyMakerNoteFocusMode2Test_1593, WrongTypeId_1593) {
    auto value = createUnsignedShortValue(2);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: multi-count value should output raw value in parentheses
TEST_F(SonyMakerNoteFocusMode2Test_1593, MultiCountValue_1593) {
    auto value = createMultiByteValue(2, 3);
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: non-DSC model (e.g., ILCE-7M3) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, NonDSCModel_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(2); // AF-S
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-S");
}

// Test: DSC-RX10M4 model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX10M4Model_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(0); // Manual
    ExifData exifData;
    setModel(exifData, "DSC-RX10M4");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Manual");
}

// Test: DSC-RX100M6 model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX100M6Model_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(3); // AF-C
    ExifData exifData;
    setModel(exifData, "DSC-RX100M6");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-C");
}

// Test: DSC-RX100M7 model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX100M7Model_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(4); // AF-A
    ExifData exifData;
    setModel(exifData, "DSC-RX100M7");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-A");
}

// Test: DSC-RX100M5A model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX100M5AModel_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(6); // DMF
    ExifData exifData;
    setModel(exifData, "DSC-RX100M5A");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "DMF");
}

// Test: DSC-HX99 model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCHX99Model_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(7); // AF-D
    ExifData exifData;
    setModel(exifData, "DSC-HX99");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-D");
}

// Test: DSC-RX0M2 model (in the exception list) should use tag lookup
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX0M2Model_PrintsTagValue_1593) {
    auto value = createUnsignedByteValue(2); // AF-S
    ExifData exifData;
    setModel(exifData, "DSC-RX0M2");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-S");
}

// Test: DSC model NOT in the exception list should output "n/a"
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCModelNotInList_PrintsNA_1593) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    setModel(exifData, "DSC-W800");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: Another DSC model NOT in the list
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRXOtherModel_PrintsNA_1593) {
    auto value = createUnsignedByteValue(0);
    ExifData exifData;
    setModel(exifData, "DSC-RX100M3");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: DSC-HX300 (DSC model not in exception list) should output n/a
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCHX300Model_PrintsNA_1593) {
    auto value = createUnsignedByteValue(3);
    ExifData exifData;
    setModel(exifData, "DSC-HX300");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: Unknown value for tag lookup on non-DSC model
TEST_F(SonyMakerNoteFocusMode2Test_1593, NonDSCModel_UnknownTagValue_1593) {
    auto value = createUnsignedByteValue(255); // Not in the tag table
    ExifData exifData;
    setModel(exifData, "ILCE-9");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    // Unknown values typically get printed with some format, just check it doesn't crash
    EXPECT_FALSE(result.empty());
}

// Test: Value 0 (Manual) for non-DSC model
TEST_F(SonyMakerNoteFocusMode2Test_1593, NonDSCModel_ManualFocus_1593) {
    auto value = createUnsignedByteValue(0);
    ExifData exifData;
    setModel(exifData, "SLT-A77");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "Manual");
}

// Test: Empty ExifData (no model key) should output raw value in parentheses
TEST_F(SonyMakerNoteFocusMode2Test_1593, EmptyExifData_NoModel_1593) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    // Don't set any model
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: DSC-RX100M5 (not DSC-RX100M5A) should print n/a
TEST_F(SonyMakerNoteFocusMode2Test_1593, DSCRX100M5_NotM5A_PrintsNA_1593) {
    auto value = createUnsignedByteValue(2);
    ExifData exifData;
    setModel(exifData, "DSC-RX100M5");
    SonyMakerNote::printFocusMode2(os, *value, &exifData);
    std::string result = os.str();
    // DSC-RX100M5 starts with "DSC-RX100M5A"? No, "DSC-RX100M5" does NOT start with "DSC-RX100M5A"
    // But "DSC-RX100M5A" starts_with "DSC-RX100M5" is irrelevant - the check is model.starts_with(m)
    // model="DSC-RX100M5", m="DSC-RX100M5A" => "DSC-RX100M5".starts_with("DSC-RX100M5A") = false
    // So this DSC model is not in the exception list => n/a
    EXPECT_EQ(result, "n/a");
}

// Test: Verify all known focus mode values with a non-DSC model
TEST_F(SonyMakerNoteFocusMode2Test_1593, AllKnownFocusModes_NonDSC_1593) {
    ExifData exifData;
    setModel(exifData, "ILCE-7M3");

    struct FocusModeEntry {
        uint8_t value;
        std::string expected;
    };

    std::vector<FocusModeEntry> entries = {
        {0, "Manual"},
        {2, "AF-S"},
        {3, "AF-C"},
        {4, "AF-A"},
        {6, "DMF"},
        {7, "AF-D"},
    };

    for (const auto& entry : entries) {
        std::ostringstream oss;
        auto value = createUnsignedByteValue(entry.value);
        SonyMakerNote::printFocusMode2(oss, *value, &exifData);
        EXPECT_EQ(oss.str(), entry.expected) << "Failed for value " << static_cast<int>(entry.value);
    }
}
