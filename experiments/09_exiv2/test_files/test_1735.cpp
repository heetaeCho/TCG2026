#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class TiffParserTest : public ::testing::Test {

protected:

    MockBasicIo mockIo;

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    const byte* testData = nullptr;

    size_t dataSize = 0;

    ByteOrder byteOrder = littleEndian;

};



TEST_F(TiffParserTest_1735, EncodeReturnsSuccessForEmptyData_1735) {

    WriteMethod result = TiffParser::encode(mockIo, testData, dataSize, byteOrder, exifData, iptcData, xmpData);

    EXPECT_EQ(result, wmWriteSuccess);

}



TEST_F(TiffParserTest_1735, EncodeCallsWriteOnBasicIo_1735) {

    testData = reinterpret_cast<const byte*>("dummy");

    dataSize = 5;

    EXPECT_CALL(mockIo, write(testing::_, testing::_)).Times(1);

    TiffParser::encode(mockIo, testData, dataSize, byteOrder, exifData, iptcData, xmpData);

}



TEST_F(TiffParserTest_1735, EncodeFiltersPanaRawIdExifData_1735) {

    Exifdatum exifDatum(IfdId::panaRawId, 0x0100); // Example tag for panaRawId

    exifData.add(exifDatum);

    EXPECT_EQ(exifData.count(), 1);



    testData = reinterpret_cast<const byte*>("dummy");

    dataSize = 5;

    TiffParser::encode(mockIo, testData, dataSize, byteOrder, exifData, iptcData, xmpData);



    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(TiffParserTest_1735, EncodeDoesNotFilterOtherExifData_1735) {

    Exifdatum exifDatum(IfdId::exifId, 0x0100); // Example tag for exifId

    exifData.add(exifDatum);

    EXPECT_EQ(exifData.count(), 1);



    testData = reinterpret_cast<const byte*>("dummy");

    dataSize = 5;

    TiffParser::encode(mockIo, testData, dataSize, byteOrder, exifData, iptcData, xmpData);



    EXPECT_EQ(exifData.count(), 1);

}
