#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that declares the class
// Since we only have the implementation, we need to declare the class ourselves
// based on the provided partial code

namespace Exiv2 {
namespace Internal {

class MinoltaMakerNote {
public:
    std::ostream& printMinoltaExposureCompensationStd(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_1003 : public ::testing::Test {
protected:
    MinoltaMakerNote makerNote;
    std::ostringstream oss;
};

// Test normal positive value
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationPositive_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(512);  // 512 / 256 = 2
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "2");
}

// Test zero value
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationZero_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);  // 0 / 256 = 0
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test negative value
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationNegative_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-512);  // -512 / 256 = -2
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-2");
}

// Test value less than 256 (integer division truncation)
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationTruncation_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(255);  // 255 / 256 = 0 (integer division)
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test value exactly 256
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationExactly256_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(256);  // 256 / 256 = 1
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "1");
}

// Test negative value with truncation
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationNegativeTruncation_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-255);  // -255 / 256 = 0 (C++ truncation toward zero)
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test large positive value
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationLargePositive_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(256 * 100);  // 25600 / 256 = 100
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "100");
}

// Test large negative value
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationLargeNegative_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-256 * 50);  // -12800 / 256 = -50
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-50");
}

// Test that the function returns the ostream reference
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationReturnsStream_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(256);
    std::ostream& result = makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with value of 1 (less than 256, should truncate to 0)
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationOne_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1);  // 1 / 256 = 0
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test with negative value of -1
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationNegativeOne_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-1);  // -1 / 256 = 0 (truncation toward zero)
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test with value of -256
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationNegative256_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-256);  // -256 / 256 = -1
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-1");
}

// Test with ExifData pointer being nullptr (should still work)
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationNullExifData_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(768);  // 768 / 256 = 3
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "3");
}

// Test with non-null ExifData pointer
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationWithExifData_1003) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1024);  // 1024 / 256 = 4
    makerNote.printMinoltaExposureCompensationStd(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "4");
}

// Test chaining output after the function call
TEST_F(MinoltaMakerNoteTest_1003, PrintExposureCompensationChaining_1003) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(512);
    makerNote.printMinoltaExposureCompensationStd(oss, value, nullptr) << " EV";
    EXPECT_EQ(oss.str(), "2 EV");
}
