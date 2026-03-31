#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

// Include the internal header for OlympusMakerNote
// We need to access the print0x0308 function
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote;
}
}

// Include the actual implementation
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_907 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create an unsignedShort Value with a single value
    std::unique_ptr<Value> makeUShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val));
        return v;
    }

    // Helper to create ExifData with a specific camera model
    ExifData makeExifDataWithModel(const std::string& model) {
        ExifData exifData;
        exifData["Exif.Image.Model"] = model;
        return exifData;
    }
};

// Test: Non-E3/E30 model, value 0 -> "Left (or n/a)"
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value0_LeftOrNA_907) {
    auto value = makeUShortValue(0);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
}

// Test: Non-E3/E30 model, value 1 -> "Center (horizontal)"
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value1_CenterHorizontal_907) {
    auto value = makeUShortValue(1);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
}

// Test: Non-E3/E30 model, value 2 -> "Right"
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value2_Right_907) {
    auto value = makeUShortValue(2);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Right"), std::string::npos);
}

// Test: Non-E3/E30 model, value 3 -> "Center (vertical)"
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value3_CenterVertical_907) {
    auto value = makeUShortValue(3);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (vertical)"), std::string::npos);
}

// Test: Non-E3/E30 model, value 255 -> "None"
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value255_None_907) {
    auto value = makeUShortValue(255);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("None"), std::string::npos);
}

// Test: Non-E3/E30 model, unknown value -> prints numeric value
TEST_F(OlympusMakerNoteTest_907, NonE3Model_UnknownValue_PrintsNumeric_907) {
    auto value = makeUShortValue(42);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "42");
}

// Test: Null metadata, value 0 -> uses non-E3 table
TEST_F(OlympusMakerNoteTest_907, NullMetadata_UsesNonE3Table_907) {
    auto value = makeUShortValue(0);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
}

// Test: E-3 model, value 0x00 -> "None", "Single Target"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0_NoneSingleTarget_907) {
    auto value = makeUShortValue(0x00);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("None"), std::string::npos);
    EXPECT_NE(result.find("Single Target"), std::string::npos);
}

// Test: E-30 model, value 0x06 -> "Center (horizontal)", "Single Target"
TEST_F(OlympusMakerNoteTest_907, E30Model_Value6_CenterHorizontalSingleTarget_907) {
    auto value = makeUShortValue(0x06);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-30 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
    EXPECT_NE(result.find("Single Target"), std::string::npos);
}

// Test: E-3 model, value with 0x40 flag -> "All Target"
TEST_F(OlympusMakerNoteTest_907, E3Model_AllTargetFlag_907) {
    // 0x46 = 0x40 | 0x06 -> afPoint 0x06 = Center (horizontal), All Target
    auto value = makeUShortValue(0x46);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
    EXPECT_NE(result.find("All Target"), std::string::npos);
}

// Test: E-3 model, value with 0x80 flag -> "Dynamic Single Target"
TEST_F(OlympusMakerNoteTest_907, E3Model_DynamicSingleTargetFlag_907) {
    // 0x86 = 0x80 | 0x06 -> afPoint 0x06 = Center (horizontal), Dynamic Single Target
    auto value = makeUShortValue(0x86);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
    EXPECT_NE(result.find("Dynamic Single Target"), std::string::npos);
}

// Test: E-3 model, value 0x01 -> "Top-left (horizontal)"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value1_TopLeftHorizontal_907) {
    auto value = makeUShortValue(0x01);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Top-left (horizontal)"), std::string::npos);
}

// Test: E-3 model, value 0x16 -> "Bottom-right (vertical)"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x16_BottomRightVertical_907) {
    auto value = makeUShortValue(0x16);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Bottom-right (vertical)"), std::string::npos);
}

// Test: E-3 model, unknown AF point (e.g., 0x1f masked) -> prints raw value
TEST_F(OlympusMakerNoteTest_907, E3Model_UnknownAFPoint_PrintsRawValue_907) {
    // 0x1f is not in the E3 table (max is 0x16)
    auto value = makeUShortValue(0x1f);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_EQ(result, "31");
}

// Test: Wrong type (not unsignedShort) -> prints raw value
TEST_F(OlympusMakerNoteTest_907, WrongType_PrintsRawValue_907) {
    auto value = Value::create(asciiString);
    value->read("hello");
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "hello");
}

// Test: Multiple values (count != 1) -> prints raw value
TEST_F(OlympusMakerNoteTest_907, MultipleValues_PrintsRawValue_907) {
    auto value = Value::create(unsignedShort);
    value->read("1 2");
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    // Should print the raw value representation since count != 1
    EXPECT_FALSE(result.empty());
}

// Test: Metadata exists but no Model key -> uses non-E3 table
TEST_F(OlympusMakerNoteTest_907, MetadataNoModel_UsesNonE3Table_907) {
    auto value = makeUShortValue(0);
    ExifData exifData;
    // No model key added
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
}

// Test: Metadata with non-E3/E30 model -> uses non-E3 table
TEST_F(OlympusMakerNoteTest_907, MetadataNonE3Model_UsesNonE3Table_907) {
    auto value = makeUShortValue(1);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-5");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
}

// Test: E-3 model, value 0x0b -> "Bottom-right (horizontal)"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x0b_BottomRightHorizontal_907) {
    auto value = makeUShortValue(0x0b);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Bottom-right (horizontal)"), std::string::npos);
}

// Test: E-3 model, value 0x11 -> "Center (vertical)"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x11_CenterVertical_907) {
    auto value = makeUShortValue(0x11);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (vertical)"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(OlympusMakerNoteTest_907, ReturnsSameOstream_907) {
    auto value = makeUShortValue(0);
    std::ostream& result = OlympusMakerNote::print0x0308(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: E-3 model with 0x40 flag on AF point 0x00 -> "None", "All Target"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x40_NoneAllTarget_907) {
    auto value = makeUShortValue(0x40);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("None"), std::string::npos);
    EXPECT_NE(result.find("All Target"), std::string::npos);
}

// Test: E-3 model with 0x80 flag on AF point 0x00 -> "None", "Dynamic Single Target"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x80_NoneDynamicSingleTarget_907) {
    auto value = makeUShortValue(0x80);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("None"), std::string::npos);
    EXPECT_NE(result.find("Dynamic Single Target"), std::string::npos);
}

// Test: Non-E3 model, value 4 (not in afPoints table) -> prints numeric
TEST_F(OlympusMakerNoteTest_907, NonE3Model_Value4_NotInTable_PrintsNumeric_907) {
    auto value = makeUShortValue(4);
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "4");
}

// Test: E-30 model, value 0x0c -> "Top-left (vertical)"
TEST_F(OlympusMakerNoteTest_907, E30Model_Value0x0c_TopLeftVertical_907) {
    auto value = makeUShortValue(0x0c);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-30 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Top-left (vertical)"), std::string::npos);
}

// Test: E-3 model, value 0x08 -> "Right (horizontal)"
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x08_RightHorizontal_907) {
    auto value = makeUShortValue(0x08);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Right (horizontal)"), std::string::npos);
}

// Test: E-3 model with both 0x40 and 0x80 -> should match 0x40 first (All Target)
TEST_F(OlympusMakerNoteTest_907, E3Model_BothFlags_AllTargetFirst_907) {
    // 0xC6 = 0x80 | 0x40 | 0x06 -> checks 0x40 first
    auto value = makeUShortValue(0xC6);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("Center (horizontal)"), std::string::npos);
    EXPECT_NE(result.find("All Target"), std::string::npos);
}

// Test: signedShort type (not unsignedShort) -> prints raw value
TEST_F(OlympusMakerNoteTest_907, SignedShortType_PrintsRawValue_907) {
    auto value = Value::create(signedShort);
    value->read("1");
    OlympusMakerNote::print0x0308(os, *value, nullptr);
    std::string result = os.str();
    // typeId is signedShort, not unsignedShort, so should print raw value
    EXPECT_FALSE(result.empty());
}

// Test: E-3 model, value 0x20 flag only (0xe0 = 0x20) -> not matching any flag condition
TEST_F(OlympusMakerNoteTest_907, E3Model_Value0x20_NoMatchingFlag_907) {
    // 0x20 -> afPoint = 0x20 & 0x1f = 0x00 = None, but 0xe0 = 0x20 which is not 0, not 0x40, not 0x80
    // So none of the flag conditions match, falls through to printing v
    auto value = makeUShortValue(0x20);
    ExifData exifData = makeExifDataWithModel("OLYMPUS E-3 ");
    OlympusMakerNote::print0x0308(os, *value, &exifData);
    std::string result = os.str();
    // The afPoint 0x00 matches "None", but flag 0x20 doesn't match any condition
    // So it prints "None, " and then falls to the end printing v=32
    EXPECT_NE(result.find("None"), std::string::npos);
}
