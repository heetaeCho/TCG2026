#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the SonyMakerNote class from the Internal namespace
namespace Exiv2 {
namespace Internal {
class SonyMakerNote {
public:
    std::ostream& printSonyMisc3cSequenceNumber(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

class SonyMakerNoteTest_1620 : public ::testing::Test {
protected:
    Exiv2::Internal::SonyMakerNote sonyMakerNote_;
    std::ostringstream oss_;
};

// Test normal operation: single unsignedLong value, result should be value + 1
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_NormalUnsignedLong_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(0);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1");
}

TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_UnsignedLongValue5_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(5);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "6");
}

TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_UnsignedLongValue99_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(99);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "100");
}

TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_UnsignedLongLargeValue_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(999999);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1000000");
}

// Test boundary: count != 1 (count == 0) should produce parenthesized output
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_EmptyValue_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    // No values pushed, count == 0
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    std::string result = oss_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test boundary: count != 1 (count == 2) should produce parenthesized output
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_MultipleValues_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(10);
    value.value_.push_back(20);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    std::string result = oss_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test error: wrong type (unsignedShort instead of unsignedLong) should produce parenthesized output
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_WrongType_UnsignedShort_1620) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.value_.push_back(42);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    std::string result = oss_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test that nullptr ExifData* is handled fine (normal case)
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_NullExifData_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(0);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1");
}

// Test with a non-null ExifData pointer (should still work the same)
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_NonNullExifData_1620) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(7);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, &exifData);
    EXPECT_EQ(oss_.str(), "8");
}

// Test return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_ReturnsOstream_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(3);
    std::ostream& result = sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(&result, &oss_);
}

// Test boundary: value of 0 gives 1 (minimum sequence number)
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_ZeroGivesOne_1620) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.value_.push_back(0);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1");
}

// Test with wrong type and multiple values (both conditions fail)
TEST_F(SonyMakerNoteTest_1620, PrintSequenceNumber_WrongTypeAndMultipleValues_1620) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.value_.push_back(1);
    value.value_.push_back(2);
    sonyMakerNote_.printSonyMisc3cSequenceNumber(oss_, value, nullptr);
    std::string result = oss_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}
