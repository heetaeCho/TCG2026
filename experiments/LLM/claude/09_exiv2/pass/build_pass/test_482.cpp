#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal namespace
namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
public:
    std::ostream& printFlashFocalLength(std::ostream& os, const Value& value, const ExifData*);
};

} // namespace Internal
} // namespace Exiv2

// Include the actual implementation
// Since we have the code inline, we rely on linking with the actual library

class Nikon3MakerNoteTest_482 : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote maker_;
    std::ostringstream os_;
};

// Test: Normal value (non-zero, non-255) should print focal length in mm
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_NormalValue_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 50;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    // Should contain "50" and "mm"
    EXPECT_NE(result.find("50"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Value of 0 should print "n/a"
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_ZeroValue_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 0;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    // Should contain "n/a"
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Value of 255 should print "n/a"
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_Value255_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 255;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Value of 1 (boundary, just above 0) should print focal length
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_Value1_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 1;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Value of 254 (boundary, just below 255) should print focal length
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_Value254_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 254;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    EXPECT_NE(result.find("254"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Wrong count (more than 1 byte) should print parenthesized value
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_WrongCount_482) {
    Exiv2::DataBuf buf(2);
    buf.data()[0] = 50;
    buf.data()[1] = 60;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 2, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    // Should be wrapped in parentheses
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Wrong type (not unsignedByte) should print parenthesized value
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_WrongType_482) {
    Exiv2::ValueType<uint16_t> value;
    value.value_.push_back(50);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    // Should be wrapped in parentheses since type is unsignedShort, not unsignedByte
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Value of 128 (mid-range) should print focal length
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_MidRangeValue_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 128;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    maker_.printFlashFocalLength(os_, value, nullptr);
    std::string result = os_.str();

    EXPECT_NE(result.find("128"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Nullptr ExifData should still work (not crash)
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_NullExifData_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 100;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    EXPECT_NO_THROW(maker_.printFlashFocalLength(os_, value, nullptr));
    std::string result = os_.str();
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Return value should be reference to the same ostream
TEST_F(Nikon3MakerNoteTest_482, PrintFlashFocalLength_ReturnsSameStream_482) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 50;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), 1, Exiv2::invalidByteOrder);

    std::ostream& result = maker_.printFlashFocalLength(os_, value, nullptr);
    EXPECT_EQ(&result, &os_);
}
