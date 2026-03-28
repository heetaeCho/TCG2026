#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the MinoltaMakerNote class from the internal namespace
namespace Exiv2 {
namespace Internal {

class MinoltaMakerNote {
public:
    std::ostream& printMinoltaFlashExposureCompStd(std::ostream& os, const Value& value, const ExifData*);
};

} // namespace Internal
} // namespace Exiv2

class MinoltaMakerNoteTest_1007 : public ::testing::Test {
protected:
    Exiv2::Internal::MinoltaMakerNote makerNote;
    std::ostringstream oss;
};

// Test normal case: value = 6 should yield (6-6)/3 = 0
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueSix_ReturnsZero_1007) {
    Exiv2::ULongValue value;
    value.read("6");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("0", oss.str());
}

// Test normal case: value = 9 should yield (9-6)/3 = 1
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueNine_ReturnsOne_1007) {
    Exiv2::ULongValue value;
    value.read("9");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("1", oss.str());
}

// Test normal case: value = 12 should yield (12-6)/3 = 2
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueTwelve_ReturnsTwo_1007) {
    Exiv2::ULongValue value;
    value.read("12");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("2", oss.str());
}

// Test normal case: value = 3 should yield (3-6)/3 = -1
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueThree_ReturnsNegativeOne_1007) {
    Exiv2::LongValue value;
    value.read("3");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("-1", oss.str());
}

// Test normal case: value = 0 should yield (0-6)/3 = -2
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueZero_ReturnsNegativeTwo_1007) {
    Exiv2::LongValue value;
    value.read("0");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("-2", oss.str());
}

// Test boundary: value = 7 should yield (7-6)/3 = 0 (integer division)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueSeven_IntegerDivisionZero_1007) {
    Exiv2::ULongValue value;
    value.read("7");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("0", oss.str());
}

// Test boundary: value = 8 should yield (8-6)/3 = 0 (integer division)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueEight_IntegerDivisionZero_1007) {
    Exiv2::ULongValue value;
    value.read("8");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("0", oss.str());
}

// Test that the function returns the same ostream reference
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ReturnsSameOstream_1007) {
    Exiv2::ULongValue value;
    value.read("6");
    std::ostream& result = makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ(&oss, &result);
}

// Test with nullptr ExifData (should not crash)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_NullExifData_DoesNotCrash_1007) {
    Exiv2::ULongValue value;
    value.read("6");
    EXPECT_NO_THROW(makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr));
}

// Test negative value scenario: value = 1 should yield (1-6)/3 = -1 (integer division toward zero)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueOne_NegativeIntegerDivision_1007) {
    Exiv2::LongValue value;
    value.read("1");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("-1", oss.str());
}

// Test with large positive value: value = 306 should yield (306-6)/3 = 100
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_LargeValue_ReturnsHundred_1007) {
    Exiv2::ULongValue value;
    value.read("306");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("100", oss.str());
}

// Test value = 5 should yield (5-6)/3 = 0 (integer division, -1/3 rounds toward zero)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueFive_IntegerDivisionTowardZero_1007) {
    Exiv2::LongValue value;
    value.read("5");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("0", oss.str());
}

// Test value = 4 should yield (4-6)/3 = 0 (integer division, -2/3 rounds toward zero)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_ValueFour_IntegerDivisionTowardZero_1007) {
    Exiv2::LongValue value;
    value.read("4");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, nullptr);
    EXPECT_EQ("0", oss.str());
}

// Test with ExifData pointer (non-null, should still work since it's unused)
TEST_F(MinoltaMakerNoteTest_1007, FlashExposureCompStd_NonNullExifData_WorksNormally_1007) {
    Exiv2::ExifData exifData;
    Exiv2::ULongValue value;
    value.read("15");
    makerNote.printMinoltaFlashExposureCompStd(oss, value, &exifData);
    EXPECT_EQ("3", oss.str());
}
