#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header or replicate the class definition for testing
namespace Exiv2 {
namespace Internal {

class CanonMakerNote {
public:
    std::ostream& printCsLens(std::ostream& os, const Value& value, const ExifData*);
};

} // namespace Internal
} // namespace Exiv2

// We need to use the actual implementation from canonmn_int.cpp
// For testing purposes, we include the implementation inline
#include <exiv2/types.hpp>

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNotePrintCsLensTest_951 : public ::testing::Test {
protected:
    CanonMakerNote maker_note_;
    std::ostringstream os_;
};

// Test: When value count is less than 3, should output raw value in parentheses
TEST_F(CanonMakerNotePrintCsLensTest_951, CountLessThan3_OutputsRawValueInParentheses_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(100);
    value.value_.push_back(200);
    // count = 2, which is < 3

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When value count is 0 (empty), should output raw value in parentheses
TEST_F(CanonMakerNotePrintCsLensTest_951, EmptyValue_OutputsRawValueInParentheses_951) {
    ValueType<uint16_t> value;
    // count = 0

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When value count is 1, should output raw value in parentheses
TEST_F(CanonMakerNotePrintCsLensTest_951, CountEquals1_OutputsRawValueInParentheses_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(50);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: When typeId is not unsignedShort, should output raw value in parentheses
TEST_F(CanonMakerNotePrintCsLensTest_951, WrongTypeId_OutputsRawValueInParentheses_951) {
    ValueType<int32_t> value;
    value.value_.push_back(100);
    value.value_.push_back(200);
    value.value_.push_back(10);
    // typeId is signedLong, not unsignedShort

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test: When fu (focal unit) is 0, should output raw value without formatting
TEST_F(CanonMakerNotePrintCsLensTest_951, FocalUnitIsZero_OutputsRawValue_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(100);  // long focal length
    value.value_.push_back(50);   // short focal length
    value.value_.push_back(0);    // focal units per mm = 0

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    // Should output value directly (no "mm" suffix expected)
    EXPECT_EQ(result.find("mm"), std::string::npos);
}

// Test: When len1 == len2 (same focal lengths), should output single focal length
TEST_F(CanonMakerNotePrintCsLensTest_951, SameFocalLengths_OutputsSingleValue_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(100);  // long focal length
    value.value_.push_back(100);  // short focal length (same)
    value.value_.push_back(1);    // focal units per mm

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("100.0 mm"), std::string::npos);
    // Should NOT contain " - " range separator
    EXPECT_EQ(result.find(" - "), std::string::npos);
}

// Test: When len1 != len2 (different focal lengths), should output range
TEST_F(CanonMakerNotePrintCsLensTest_951, DifferentFocalLengths_OutputsRange_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(200);  // long focal length
    value.value_.push_back(50);   // short focal length
    value.value_.push_back(1);    // focal units per mm

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("50.0"), std::string::npos);
    EXPECT_NE(result.find("200.0"), std::string::npos);
    EXPECT_NE(result.find(" - "), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Focal unit > 1 should divide properly
TEST_F(CanonMakerNotePrintCsLensTest_951, FocalUnitGreaterThanOne_DividesProperly_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(350);  // long focal length
    value.value_.push_back(70);   // short focal length
    value.value_.push_back(10);   // focal units per mm = 10

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    // len1 = 350/10 = 35.0, len2 = 70/10 = 7.0
    // Output: "7.0 - 35.0 mm"
    EXPECT_NE(result.find("7.0"), std::string::npos);
    EXPECT_NE(result.find("35.0"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Same focal lengths with focal unit > 1
TEST_F(CanonMakerNotePrintCsLensTest_951, SameFocalLengthsWithFocalUnit_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(500);  // long focal length
    value.value_.push_back(500);  // short focal length (same)
    value.value_.push_back(10);   // focal units per mm

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    // len1 = len2 = 500/10 = 50.0
    EXPECT_NE(result.find("50.0 mm"), std::string::npos);
    EXPECT_EQ(result.find(" - "), std::string::npos);
}

// Test: With ExifData pointer as nullptr, should still work
TEST_F(CanonMakerNotePrintCsLensTest_951, NullExifData_StillWorks_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(200);
    value.value_.push_back(100);
    value.value_.push_back(1);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: More than 3 values should still work (only first 3 used)
TEST_F(CanonMakerNotePrintCsLensTest_951, MoreThanThreeValues_UsesFirstThree_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(300);
    value.value_.push_back(100);
    value.value_.push_back(1);
    value.value_.push_back(999);
    value.value_.push_back(888);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("100.0"), std::string::npos);
    EXPECT_NE(result.find("300.0"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Exactly 3 values should work properly
TEST_F(CanonMakerNotePrintCsLensTest_951, ExactlyThreeValues_WorksProperly_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(180);
    value.value_.push_back(18);
    value.value_.push_back(1);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_NE(result.find("18.0"), std::string::npos);
    EXPECT_NE(result.find("180.0"), std::string::npos);
    EXPECT_NE(result.find(" - "), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Return value is reference to same ostream
TEST_F(CanonMakerNotePrintCsLensTest_951, ReturnsReferenceToSameOstream_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(100);
    value.value_.push_back(50);
    value.value_.push_back(1);

    std::ostream& returned = maker_note_.printCsLens(os_, value, nullptr);

    EXPECT_EQ(&returned, &os_);
}

// Test: Return value is same ostream for error case
TEST_F(CanonMakerNotePrintCsLensTest_951, ReturnsReferenceToSameOstream_ErrorCase_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(100);
    // count < 3

    std::ostream& returned = maker_note_.printCsLens(os_, value, nullptr);

    EXPECT_EQ(&returned, &os_);
}

// Test: Focal length with value 1 and focal unit 1
TEST_F(CanonMakerNotePrintCsLensTest_951, SmallFocalLengths_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(1);
    value.value_.push_back(1);
    value.value_.push_back(1);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    // len1 = len2 = 1.0
    EXPECT_NE(result.find("1.0 mm"), std::string::npos);
}

// Test: Range output format has shorter focal length first, then longer
TEST_F(CanonMakerNotePrintCsLensTest_951, RangeFormat_ShorterFirst_951) {
    ValueType<uint16_t> value;
    value.value_.push_back(400);  // long
    value.value_.push_back(70);   // short
    value.value_.push_back(1);

    maker_note_.printCsLens(os_, value, nullptr);

    std::string result = os_.str();
    // Format: "len2 - len1 mm" => "70.0 - 400.0 mm"
    size_t pos70 = result.find("70.0");
    size_t pos400 = result.find("400.0");
    EXPECT_NE(pos70, std::string::npos);
    EXPECT_NE(pos400, std::string::npos);
    EXPECT_LT(pos70, pos400);
}

} // anonymous namespace
