#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/types.hpp"

#include "TestProjects/exiv2/src/crwimage_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PackIfdIdTest_1799 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(PackIfdIdTest_1799, EmptyExifData_ReturnsEmptyBuffer_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    DataBuf result = packIfdId(exifData, ifdId, byteOrder);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(PackIfdIdTest_1799, SingleExifEntry_ReturnsCorrectBufferSize_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), new StringValue("Artist"));

    exifData.add(exifDatum);

    DataBuf result = packIfdId(exifData, ifdId, byteOrder);

    EXPECT_EQ(result.size(), exifDatum.tag() * 2 + exifDatum.size());

}



TEST_F(PackIfdIdTest_1799, MultipleExifEntries_ReturnsCorrectBufferSize_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    Exifdatum exifDatum1(ExifKey("Exif.Image.Artist"), new StringValue("Artist"));

    Exifdatum exifDatum2(ExifKey("Exif.Image.Copyright"), new StringValue("Copyright"));

    exifData.add(exifDatum1);

    exifData.add(exifDatum2);

    DataBuf result = packIfdId(exifData, ifdId, byteOrder);

    EXPECT_EQ(result.size(), std::max(exifDatum1.tag() * 2 + exifDatum1.size(), exifDatum2.tag() * 2 + exifDatum2.size()));

}



TEST_F(PackIfdIdTest_1799, NonMatchingIfdId_ReturnsEmptyBuffer_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), new StringValue("Artist"));

    exifDatum.setIfdId(0x8825); // Set a different IFD ID

    exifData.add(exifDatum);

    DataBuf result = packIfdId(exifData, ifdId, byteOrder);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(PackIfdIdTest_1799, ExceedingBufferSize_LogsError_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    std::ostringstream logStream;

    LogMsg::setHandler([&logStream](int level, const char* s) { logStream << s; });

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), new StringValue(std::string(1024, 'A')));

    exifData.add(exifDatum);

    packIfdId(exifData, ifdId, byteOrder);

    EXPECT_THAT(logStream.str(), testing::HasSubstr("packIfdId out-of-bounds error"));

}



TEST_F(PackIfdIdTest_1799, BoundaryCondition_MaxSize_ReturnsCorrectBuffer_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    std::string maxString(508, 'A'); // Max size that fits in buffer without exceeding bounds

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), new StringValue(maxString));

    exifData.add(exifDatum);

    DataBuf result = packIfdId(exifData, ifdId, byteOrder);

    EXPECT_EQ(result.size(), 2 + maxString.size()); // Tag ID (2 bytes) + string size

}



TEST_F(PackIfdIdTest_1799, BoundaryCondition_ExceedsMaxSize_LogsError_1799) {

    IfdId ifdId = 0x8769; // Example IFD ID

    ByteOrder byteOrder = littleEndian;

    std::ostringstream logStream;

    LogMsg::setHandler([&logStream](int level, const char* s) { logStream << s; });

    std::string maxString(512, 'A'); // Size that exceeds buffer limit

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), new StringValue(maxString));

    exifData.add(exifDatum);

    packIfdId(exifData, ifdId, byteOrder);

    EXPECT_THAT(logStream.str(), testing::HasSubstr("packIfdId out-of-bounds error"));

}
