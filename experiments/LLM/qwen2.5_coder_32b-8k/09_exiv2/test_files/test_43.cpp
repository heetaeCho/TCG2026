#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include <vector>



using namespace Exiv2;



// Mock Blob for testing purposes

class MockBlob : public Blob {

public:

    MOCK_METHOD(void, append, (const byte*, size_t), (override));

};



TEST_F(ExifParserTest_43, EncodeWithEmptyData_43) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    ExifParser::encode(blob, nullptr, 0, byteOrder, exifData);



    EXPECT_EQ(blob.size(), 0);

}



TEST_F(ExifParserTest_43, EncodeWithNonEmptyData_43) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    const byte pData[] = {1, 2, 3, 4};

    size_t size = sizeof(pData);



    EXPECT_CALL(mockBlob, append(::testing::NotNull(), ::testing::Eq(size)));



    ExifParser::encode(mockBlob, pData, size, byteOrder, exifData);

}



TEST_F(ExifParserTest_43, EncodeWithEmptyExifData_43) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    ExifParser::encode(blob, nullptr, 0, byteOrder, exifData);



    EXPECT_EQ(blob.size(), 0);

}



TEST_F(ExifParserTest_43, EncodeWithPopulatedExifData_43) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    Exifdatum datum("Exif.Image.Artist", (const Value*)nullptr);

    exifData.add(datum);



    const byte pData[] = {1, 2, 3, 4};

    size_t size = sizeof(pData);



    EXPECT_CALL(mockBlob, append(::testing::NotNull(), ::testing::Eq(size)));



    ExifParser::encode(mockBlob, pData, size, byteOrder, exifData);

}



TEST_F(ExifParserTest_43, EncodeWithLargeSize_43) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    std::vector<byte> largeData(1024 * 1024); // 1 MB of data

    const byte* pData = largeData.data();

    size_t size = largeData.size();



    EXPECT_CALL(mockBlob, append(::testing::NotNull(), ::testing::Eq(size)));



    ExifParser::encode(mockBlob, pData, size, byteOrder, exifData);

}



TEST_F(ExifParserTest_43, EncodeWithZeroSize_43) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    ExifParser::encode(blob, nullptr, 0, byteOrder, exifData);



    EXPECT_EQ(blob.size(), 0);

}



TEST_F(ExifParserTest_43, EncodeWithNullPointerAndNonZeroSize_43) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;

    ExifData exifData;



    EXPECT_THROW({

        ExifParser::encode(blob, nullptr, 10, byteOrder, exifData);

    }, std::exception);

}
