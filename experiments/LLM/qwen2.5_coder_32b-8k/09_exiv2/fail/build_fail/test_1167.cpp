#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage_int.hpp"

#include "exif.hpp"

#include "iptc.hpp"

#include "xmp_exiv2.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockFindDecoderFct : public std::function<TiffComponent::UniquePtr(uint16_t, IfdId)> {

public:

    MOCK_CONST_METHOD2(operator(), TiffComponent::UniquePtr(uint16_t, IfdId));

};



class TiffParserWorkerTest_1167 : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    MockFindDecoderFct mockFindDecoderFct;

    std::unique_ptr<TiffHeaderBase> pHeader;



    void SetUp() override {

        pHeader = std::make_unique<TiffHeader>();

    }

};



TEST_F(TiffParserWorkerTest_1167, DecodeWithValidData_1167) {

    const byte tiffData[] = { 0x49, 0x49, 0x2A, 0x00 }; // Little-endian TIFF header

    size_t dataSize = sizeof(tiffData);

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, littleEndian);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithEmptyData_1167) {

    const byte* tiffData = nullptr;

    size_t dataSize = 0;

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, invalidByteOrder);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithBigEndianData_1167) {

    const byte tiffData[] = { 0x4D, 0x4D, 0x00, 0x2A }; // Big-endian TIFF header

    size_t dataSize = sizeof(tiffData);

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, bigEndian);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithInvalidByteOrder_1167) {

    const byte tiffData[] = { 0x49, 0x4D, 0x2A, 0x00 }; // Invalid byte order

    size_t dataSize = sizeof(tiffData);

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, invalidByteOrder);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithProvidedTiffHeader_1167) {

    const byte tiffData[] = { 0x49, 0x49, 0x2A, 0x00 }; // Little-endian TIFF header

    size_t dataSize = sizeof(tiffData);

    TiffHeader providedHeader;

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, &providedHeader);

    EXPECT_EQ(result, littleEndian);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithSmallBuffer_1167) {

    const byte tiffData[] = { 0x49 }; // Incomplete TIFF header

    size_t dataSize = sizeof(tiffData);

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, invalidByteOrder);

}



TEST_F(TiffParserWorkerTest_1167, DecodeWithLargeBuffer_1167) {

    const byte tiffData[] = { 0x49, 0x49, 0x2A, 0x00 }; // Little-endian TIFF header

    size_t dataSize = sizeof(tiffData) * 10; // Larger buffer

    ByteOrder result = TiffParserWorker::decode(exifData, iptcData, xmpData, tiffData, dataSize, 0, mockFindDecoderFct, pHeader.get());

    EXPECT_EQ(result, littleEndian);

}
