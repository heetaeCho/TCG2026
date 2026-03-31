#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNotePrint0x0529Test_904 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When value count is not 4, should output parenthesized value
TEST_F(OlympusMakerNotePrint0x0529Test_904, WrongCount_OutputsParenthesizedValue_904) {
    auto value = Value::create(unsignedShort);
    value->read("1 2 3"); // 3 elements, not 4
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count is more than 4, should output parenthesized value
TEST_F(OlympusMakerNotePrint0x0529Test_904, TooManyElements_OutputsParenthesizedValue_904) {
    auto value = Value::create(unsignedShort);
    value->read("1 2 3 4 5"); // 5 elements
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value type is not unsignedShort, should output parenthesized value
TEST_F(OlympusMakerNotePrint0x0529Test_904, WrongType_OutputsParenthesizedValue_904) {
    auto value = Value::create(unsignedLong);
    value->read("1 2 3 4"); // 4 elements but wrong type
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value count is 1, should output parenthesized value
TEST_F(OlympusMakerNotePrint0x0529Test_904, SingleElement_OutputsParenthesizedValue_904) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value 0 (Off) with 4 unsignedShort elements
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterOff_OutputsOff_904) {
    auto value = Value::create(unsignedShort);
    value->read("0 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Off") != std::string::npos);
}

// Test: Value 1 (Soft Focus) with 4 unsignedShort elements
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterSoftFocus_OutputsSoftFocus_904) {
    auto value = Value::create(unsignedShort);
    value->read("1 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Soft Focus") != std::string::npos);
}

// Test: Value 2 (Pop Art) with 4 unsignedShort elements
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterPopArt_OutputsPopArt_904) {
    auto value = Value::create(unsignedShort);
    value->read("2 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Pop Art") != std::string::npos);
}

// Test: Value 20 (Dramatic Tone) with 4 unsignedShort elements
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterDramaticTone_OutputsDramaticTone_904) {
    auto value = Value::create(unsignedShort);
    value->read("20 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Dramatic Tone") != std::string::npos);
}

// Test: Value 39 (Partial Color) should also output position info
TEST_F(OlympusMakerNotePrint0x0529Test_904, PartialColor_OutputsPositionInfo_904) {
    auto value = Value::create(unsignedShort);
    value->read("39 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color") != std::string::npos);
    // Position should be v3 + 1 = 0 + 1 = 1
    EXPECT_TRUE(result.find("1") != std::string::npos);
}

// Test: Value 39 (Partial Color) with position value 5 (v3=5, position=6)
TEST_F(OlympusMakerNotePrint0x0529Test_904, PartialColor_Position6_904) {
    auto value = Value::create(unsignedShort);
    value->read("39 0 0 5");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color") != std::string::npos);
    // Position should be v3 + 1 = 5 + 1 = 6
    EXPECT_TRUE(result.find("6") != std::string::npos);
}

// Test: Value 39 (Partial Color) with position value 2 (v3=2, position=3)
TEST_F(OlympusMakerNotePrint0x0529Test_904, PartialColor_Position3_904) {
    auto value = Value::create(unsignedShort);
    value->read("39 0 0 2");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color") != std::string::npos);
    EXPECT_TRUE(result.find("3") != std::string::npos);
}

// Test: Value 40 (Partial Color II) - should NOT output position info
TEST_F(OlympusMakerNotePrint0x0529Test_904, PartialColorII_NoPositionInfo_904) {
    auto value = Value::create(unsignedShort);
    value->read("40 0 0 5");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color II") != std::string::npos);
    // Should NOT contain "position" since v0 is 40, not 39
    EXPECT_TRUE(result.find("position") == std::string::npos);
}

// Test: Unknown filter value (e.g., 100) should still work (may print numeric)
TEST_F(OlympusMakerNotePrint0x0529Test_904, UnknownFilterValue_904) {
    auto value = Value::create(unsignedShort);
    value->read("100 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    // Should not be empty - it should output something
    EXPECT_FALSE(result.empty());
    // Should NOT contain position info since v0 != 39
    EXPECT_TRUE(result.find("position") == std::string::npos);
}

// Test: With nullptr metadata, should still work
TEST_F(OlympusMakerNotePrint0x0529Test_904, NullMetadata_ValidValue_904) {
    auto value = Value::create(unsignedShort);
    value->read("5 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Pin Hole") != std::string::npos);
}

// Test: Empty value should output parenthesized (count == 0 != 4)
TEST_F(OlympusMakerNotePrint0x0529Test_904, EmptyValue_OutputsParenthesized_904) {
    auto value = Value::create(unsignedShort);
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value 6 (Grainy Film) 
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterGrainyFilm_904) {
    auto value = Value::create(unsignedShort);
    value->read("6 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Grainy Film") != std::string::npos);
}

// Test: Value 9 (Diorama)
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterDiorama_904) {
    auto value = Value::create(unsignedShort);
    value->read("9 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Diorama") != std::string::npos);
}

// Test: Value 36 (Vintage)
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterVintage_904) {
    auto value = Value::create(unsignedShort);
    value->read("36 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Vintage") != std::string::npos);
}

// Test: Value 41 (Partial Color III)
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterPartialColorIII_904) {
    auto value = Value::create(unsignedShort);
    value->read("41 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color III") != std::string::npos);
}

// Test: Returns reference to the same ostream
TEST_F(OlympusMakerNotePrint0x0529Test_904, ReturnsOstreamReference_904) {
    auto value = Value::create(unsignedShort);
    value->read("0 0 0 0");
    std::ostream& ret = OlympusMakerNote::print0x0529(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Returns reference to the same ostream for error case
TEST_F(OlympusMakerNotePrint0x0529Test_904, ReturnsOstreamReferenceOnError_904) {
    auto value = Value::create(unsignedShort);
    value->read("0 0 0"); // count != 4
    std::ostream& ret = OlympusMakerNote::print0x0529(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Returns reference for partial color case
TEST_F(OlympusMakerNotePrint0x0529Test_904, ReturnsOstreamReferencePartialColor_904) {
    auto value = Value::create(unsignedShort);
    value->read("39 0 0 3");
    std::ostream& ret = OlympusMakerNote::print0x0529(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: signedShort type should also fail the type check
TEST_F(OlympusMakerNotePrint0x0529Test_904, SignedShortType_OutputsParenthesized_904) {
    auto value = Value::create(signedShort);
    value->read("0 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value 7 (not in the artFilters table, gap between 6 and 9)
TEST_F(OlympusMakerNotePrint0x0529Test_904, UnknownFilterValue7_904) {
    auto value = Value::create(unsignedShort);
    value->read("7 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    // Value 7 is not in the table, should output something (likely the number)
    EXPECT_FALSE(result.empty());
}

// Test: Value 10 (Cross Process)
TEST_F(OlympusMakerNotePrint0x0529Test_904, FilterCrossProcess_904) {
    auto value = Value::create(unsignedShort);
    value->read("10 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Cross Process") != std::string::npos);
}

// Test: With valid ExifData pointer (non-null)
TEST_F(OlympusMakerNotePrint0x0529Test_904, NonNullMetadata_ValidValue_904) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("3 0 0 0");
    OlympusMakerNote::print0x0529(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Pale & Light Color") != std::string::npos);
}

// Test: Partial color with non-null metadata
TEST_F(OlympusMakerNotePrint0x0529Test_904, PartialColor_NonNullMetadata_904) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("39 0 0 4");
    OlympusMakerNote::print0x0529(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Partial Color") != std::string::npos);
    // Position = 4 + 1 = 5
    EXPECT_TRUE(result.find("5") != std::string::npos);
}
