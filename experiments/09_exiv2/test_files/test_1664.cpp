#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffBinaryArray : public TiffBinaryArray {

public:

    MockTiffBinaryArray(uint16_t tag, IfdId group, const ArrayCfg & arrayCfg, const ArrayDef * arrayDef, size_t defSize)

        : TiffBinaryArray(tag, group, arrayCfg, arrayDef, defSize) {}



    MOCK_CONST_METHOD0(cfg, const ArrayCfg*());

    MOCK_CONST_METHOD0(decoded, bool());

};



class TiffDecoderTest_1664 : public ::testing::Test {

protected:

    NiceMock<MockTiffBinaryArray> mock_binary_array;

    TiffDecoder decoder{ExifData(), IptcData(), XmpData(), nullptr, nullptr};

};



TEST_F(TiffDecoderTest_1664, VisitBinaryArray_DecodedTrue_1664) {

    EXPECT_CALL(mock_binary_array, cfg()).WillOnce(::testing::Return(nullptr));

    mock_binary_array.setDecoded(true);

    EXPECT_CALL(mock_binary_array, decoded()).WillRepeatedly(::testing::Return(true));



    decoder.visitBinaryArray(&mock_binary_array);

}



TEST_F(TiffDecoderTest_1664, VisitBinaryArray_CfgNull_DecodedFalse_1664) {

    EXPECT_CALL(mock_binary_array, cfg()).WillOnce(::testing::Return(nullptr));

    mock_binary_array.setDecoded(false);

    EXPECT_CALL(mock_binary_array, decoded()).WillRepeatedly(::testing::Return(false));



    decoder.visitBinaryArray(&mock_binary_array);

}



TEST_F(TiffDecoderTest_1664, VisitBinaryArray_CfgNotNull_DecodedFalse_1664) {

    ArrayCfg mock_array_cfg;

    EXPECT_CALL(mock_binary_array, cfg()).WillOnce(::testing::Return(&mock_array_cfg));

    mock_binary_array.setDecoded(false);

    EXPECT_CALL(mock_binary_array, decoded()).WillRepeatedly(::testing::Return(false));



    decoder.visitBinaryArray(&mock_binary_array);

}



TEST_F(TiffDecoderTest_1664, VisitBinaryArray_CfgNotNull_DecodedTrue_1664) {

    ArrayCfg mock_array_cfg;

    EXPECT_CALL(mock_binary_array, cfg()).WillOnce(::testing::Return(&mock_array_cfg));

    mock_binary_array.setDecoded(true);

    EXPECT_CALL(mock_binary_array, decoded()).WillRepeatedly(::testing::Return(true));



    decoder.visitBinaryArray(&mock_binary_array);

}
