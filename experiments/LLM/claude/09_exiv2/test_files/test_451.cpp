#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "exiv2/exiv2.hpp"
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon1MakerNoteTest_451 : public ::testing::Test {
protected:
    std::ostringstream os;

    void SetUp() override {
        os.str("");
        os.clear();
    }
};

// Test printBarValue with null ExifData pointer
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_NullExifData_ReturnsUndefined_451) {
    auto value = Value::create(unsignedByte);
    std::string buf = "0 1 2 3 4 5 6 7 8 9";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "undefined");
}

// Test printBarValue with value count less than 9
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_CountLessThan9_ReturnsEmptyStream_451) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    // Only 8 elements (indices 0-7), count < 9
    std::string buf = "0 1 2 3 4 5 6 7";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "");
}

// Test printBarValue with exactly 9 elements and little endian byte order
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_Count9_LittleEndian_451) {
    ExifData exifData;
    // Set byte order to "II" (little endian) - anything other than "MM"
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    // We need at least 10 elements (indices 0-9, we access 6,7,8,9)
    std::string buf = "0 0 0 0 0 0 1 0 0 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    // bytes: p[0]=1, p[1]=0, p[2]=0, p[3]=0 in little endian = 1
    EXPECT_EQ(os.str(), "1");
}

// Test printBarValue with exactly 9 elements and big endian byte order
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_Count9_BigEndian_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "MM";

    auto value = Value::create(unsignedByte);
    // indices 6,7,8,9 => p[0]=0, p[1]=0, p[2]=0, p[3]=1
    // big endian: 0x00000001 = 1
    std::string buf = "0 0 0 0 0 0 0 0 0 1";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "1");
}

// Test printBarValue with more than 9 elements
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_CountMoreThan9_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    std::string buf = "0 0 0 0 0 0 0 0 0 0 0 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    // All zeros => 0
    EXPECT_EQ(os.str(), "0");
}

// Test printBarValue with all zeros in little endian
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_AllZeros_LittleEndian_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    std::string buf = "0 0 0 0 0 0 0 0 0 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "0");
}

// Test printBarValue with specific byte pattern in big endian
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_SpecificPattern_BigEndian_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "MM";

    auto value = Value::create(unsignedByte);
    // indices 6,7,8,9 => p[0]=0, p[1]=0, p[2]=1, p[3]=0
    // big endian: 0x00000100 = 256
    std::string buf = "0 0 0 0 0 0 0 0 1 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "256");
}

// Test printBarValue with specific byte pattern in little endian
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_SpecificPattern_LittleEndian_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    // indices 6,7,8,9 => p[0]=0, p[1]=0, p[2]=1, p[3]=0
    // little endian: 0x00010000 = 65536
    std::string buf = "0 0 0 0 0 0 0 0 1 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "65536");
}

// Test printBarValue with empty value (count = 0)
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_EmptyValue_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    // Empty - don't read anything

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "");
}

// Test printBarValue with exactly 8 elements (boundary, should not print)
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_Exactly8Elements_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    std::string buf = "1 2 3 4 5 6 7 8";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    // count is 8, which is < 9, so nothing printed
    EXPECT_EQ(os.str(), "");
}

// Test printBarValue with max byte values
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_MaxByteValues_LittleEndian_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    // indices 6,7,8,9 => p[0]=255, p[1]=255, p[2]=255, p[3]=255
    // little endian: 0xFFFFFFFF = 4294967295
    std::string buf = "0 0 0 0 0 0 255 255 255 255";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_FALSE(os.str().empty());
}

// Test printBarValue with byte order key not present in ExifData
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_NoByteOrderKey_DefaultsToLittleEndian_451) {
    ExifData exifData;
    // Don't set Exif.MakerNote.ByteOrder - it won't be "MM" so should default to littleEndian

    auto value = Value::create(unsignedByte);
    // indices 6,7,8,9 => p[0]=1, p[1]=0, p[2]=0, p[3]=0
    // little endian: 1
    std::string buf = "0 0 0 0 0 0 1 0 0 0";
    value->read(buf);

    Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "1");
}

// Test that the function returns the ostream reference
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ReturnsOstreamReference_451) {
    auto value = Value::create(unsignedByte);
    std::string buf = "0 1 2 3 4 5 6 7 8 9";
    value->read(buf);

    std::ostream& result = Nikon1MakerNote::printBarValue(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test that the function returns ostream reference with valid data
TEST_F(Nikon1MakerNoteTest_451, PrintBarValue_ReturnsOstreamReferenceWithData_451) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";

    auto value = Value::create(unsignedByte);
    std::string buf = "0 0 0 0 0 0 0 0 0 0";
    value->read(buf);

    std::ostream& result = Nikon1MakerNote::printBarValue(os, *value, &exifData);
    EXPECT_EQ(&result, &os);
}
