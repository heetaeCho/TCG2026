#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that contains CanonMakerNote
// Since we only have the cpp file, we need to declare the class interface
namespace Exiv2 {
namespace Internal {
class CanonMakerNote {
public:
    std::ostream& printSi0x0018(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_964 : public ::testing::Test {
protected:
    CanonMakerNote makerNote;
    std::ostringstream oss;
};

// Test normal positive value division by 10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_PositiveValue_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(100);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "10");
}

// Test zero value
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ZeroValue_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test negative value division by 10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NegativeValue_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-100);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-10");
}

// Test value smaller than 10 (integer division truncation)
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ValueSmallerThan10_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(5);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test value not evenly divisible by 10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ValueNotEvenlyDivisible_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(123);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "12");
}

// Test negative value not evenly divisible by 10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NegativeNotEvenlyDivisible_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-7);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test large positive value
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_LargePositiveValue_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1000000);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "100000");
}

// Test large negative value
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_LargeNegativeValue_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-1000000);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-100000");
}

// Test with exactly 10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ExactlyTen_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(10);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "1");
}

// Test with exactly -10
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ExactlyNegativeTen_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-10);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "-1");
}

// Test with value 1
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ValueOne_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test with value -1
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ValueNegativeOne_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-1);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test that the function returns the same ostream reference
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ReturnsSameStream_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(50);
    std::ostream& result = makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with nullptr ExifData (should still work)
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NullExifData_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(200);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "20");
}

// Test with value 9 (boundary just below 10)
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_BoundaryNine_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(9);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test with value -9 (negative boundary just above -10)
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_BoundaryNegativeNine_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-9);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "0");
}

// Test with value 11 (boundary just above 10)
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_BoundaryEleven_964) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(11);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "1");
}

// Test using unsigned short value type
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_UnsignedShortValue_964) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.value_.push_back(250);
    makerNote.printSi0x0018(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "25");
}
