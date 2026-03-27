#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

};



class OrfParserTest : public ::testing::Test {

protected:

    MockBasicIo mockIo;

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

};



TEST_F(OrfParserTest_NormalOperation_1554, EncodeWithNoFilteredIfds_1554) {

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(1);

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_NE(result, wmNone);

}



TEST_F(OrfParserTest_BoundaryConditions_1554, EncodeWithEmptyExifData_1554) {

    exifData.clear();

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(1);

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_NE(result, wmNone);

}



TEST_F(OrfParserTest_BoundaryConditions_1554, EncodeWithEmptyIptcData_1554) {

    iptcData.clear();

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(1);

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_NE(result, wmNone);

}



TEST_F(OrfParserTest_BoundaryConditions_1554, EncodeWithEmptyXmpData_1554) {

    xmpData.clear();

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(1);

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_NE(result, wmNone);

}



TEST_F(OrfParserTest_ErrorHandling_1554, EncodeWithOpenFailure_1554) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(-1));

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_EQ(result, wmNone);

}



TEST_F(OrfParserTest_ErrorHandling_1554, EncodeWithWriteFailure_1554) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).WillOnce(::testing::Return(0));

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_EQ(result, wmNone);

}



TEST_F(OrfParserTest_ErrorHandling_1554, EncodeWithCloseFailure_1554) {

    EXPECT_CALL(mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).WillOnce(::testing::Return(size));

    EXPECT_CALL(mockIo, close()).WillOnce(::testing::Return(-1));

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_EQ(result, wmNone);

}



TEST_F(OrfParserTest_FilteredIfds_1554, EncodeWithFilteredIfdPresent_1554) {

    Exifdatum exifDatum;

    exifDatum.ifdId() = IfdId::panaRawId;

    exifData.add(exifDatum);

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(1);

    WriteMethod result = OrfParser().encode(mockIo, pData, size, byteOrder, exifData, iptcData, xmpData);

    EXPECT_NE(result, wmNone);

    EXPECT_EQ(exifData.count(), 0u);

}
