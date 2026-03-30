#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/types.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffBinaryArray : public TiffBinaryArray {

public:

    MockTiffBinaryArray(uint16_t tag, IfdId group, const ArrayCfg & arrayCfg, const ArrayDef * arrayDef, size_t defSize)

        : TiffBinaryArray(tag, group, arrayCfg, arrayDef, defSize) {}



    MOCK_METHOD(bool, cfg, (), (const));

    MOCK_METHOD(bool, decoded, (), (const));

    MOCK_METHOD(size_t, doSize, (), (const, override));

    MOCK_METHOD(bool, initialize, (TiffComponent*), (override));

    MOCK_METHOD(bool, updOrigDataBuf, (const byte*, size_t), (override));

};



class TiffEncoderTest : public ::testing::Test {

protected:

    void SetUp() override {

        arrayCfg.cryptFct_ = nullptr;

        tiffBinaryArray = std::make_unique<NiceMock<MockTiffBinaryArray>>(1, ifdExif, arrayCfg, &arrayDef, 0);

        encoder = std::make_unique<TiffEncoder>(exifData, iptcData, xmpData, pRoot, false, pPrimaryGroups, &tiffHeaderBase, findEncoderFct);

    }



    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;

    TiffComponent* pRoot = nullptr;

    PrimaryGroups pPrimaryGroups;

    const TiffHeaderBase tiffHeaderBase;

    FindEncoderFct findEncoderFct;



    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    std::unique_ptr<NiceMock<MockTiffBinaryArray>> tiffBinaryArray;

    std::unique_ptr<TiffEncoder> encoder;

};



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_NoConfig_1677) {

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillOnce(testing::Return(false));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_NotDecoded_1677) {

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(false));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_ZeroSize_1677) {

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, doSize()).WillOnce(testing::Return(0));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_InitializeFailed_1677) {

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, doSize()).WillOnce(testing::Return(10));

    EXPECT_CALL(*tiffBinaryArray, initialize(_)).WillOnce(testing::Return(false));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_NoCryptFct_1677) {

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, doSize()).WillOnce(testing::Return(10));

    EXPECT_CALL(*tiffBinaryArray, initialize(_)).WillOnce(testing::Return(true));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_EncryptionFailed_1677) {

    arrayCfg.cryptFct_ = sonyTagDecipher;

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, doSize()).WillOnce(testing::Return(10));

    EXPECT_CALL(*tiffBinaryArray, initialize(_)).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, updOrigDataBuf(_, _)).WillOnce(testing::Return(false));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}



TEST_F(TiffEncoderTest_1677, VisitBinaryArrayEnd_SuccessfulEncryption_1677) {

    arrayCfg.cryptFct_ = sonyTagDecipher;

    EXPECT_CALL(*tiffBinaryArray, cfg()).WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, decoded()).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, doSize()).WillOnce(testing::Return(10));

    EXPECT_CALL(*tiffBinaryArray, initialize(_)).WillOnce(testing::Return(true));

    EXPECT_CALL(*tiffBinaryArray, updOrigDataBuf(_, _)).WillOnce(testing::Return(true));

    encoder->visitBinaryArrayEnd(tiffBinaryArray.get());

}
