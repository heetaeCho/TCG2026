#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



class TiffReaderTest_1708 : public ::testing::Test {

protected:

    void SetUp() override {

        pData = new byte[bufferSize];

        pRoot = std::make_unique<TiffComponent>(0, ifdExif);

        reader = std::make_unique<TiffReader>(pData, bufferSize, pRoot.get(), TiffRwState());

    }



    void TearDown() override {

        delete[] pData;

    }



    static const size_t bufferSize = 1024;

    byte* pData;

    std::unique_ptr<TiffComponent> pRoot;

    std::unique_ptr<TiffReader> reader;

};



TEST_F(TiffReaderTest_1708, VisitBinaryArray_PostProcFalse_1708) {

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*binaryArray.get(), initialize(pRoot.get())).Times(1);



    reader->visitBinaryArray(binaryArray.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_PostProcTrue_NoDuplicateTag_1708) {

    reader->postProc_ = true;

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    TiffFinder finder(binaryArray->tag(), binaryArray->group());

    pRoot->accept(finder);



    EXPECT_CALL(*binaryArray.get(), initialize(pRoot.get())).Times(1);

    reader->visitBinaryArray(binaryArray.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_PostProcTrue_DuplicateTag_1708) {

    reader->postProc_ = true;

    auto binaryArray1 = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    auto binaryArray2 = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);



    TiffFinder finder(binaryArray1->tag(), binaryArray1->group());

    pRoot->accept(finder);

    EXPECT_CALL(*binaryArray1.get(), initialize(pRoot.get())).Times(1);

    reader->visitBinaryArray(binaryArray1.get());



    finder.init(binaryArray2->tag(), binaryArray2->group());

    pRoot->accept(finder);

    EXPECT_CALL(*binaryArray2.get(), setDecoded(false)).Times(1);

    reader->visitBinaryArray(binaryArray2.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_ZeroSize_1708) {

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*binaryArray.get(), doSize()).WillOnce(testing::Return(0));



    reader->visitBinaryArray(binaryArray.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_NoConfig_1708) {

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*binaryArray.get(), initialize(pRoot.get())).WillOnce(testing::Return(true));

    EXPECT_CALL(*binaryArray.get(), cfg()).WillOnce(testing::Return(nullptr));



    reader->visitBinaryArray(binaryArray.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_CryptFunction_1708) {

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, ArrayCfg(), nullptr, 0);

    EXPECT_CALL(*binaryArray.get(), initialize(pRoot.get())).WillOnce(testing::Return(true));

    EXPECT_CALL(*binaryArray.get(), cfg()).WillRepeatedly(testing::Return(&arrayCfg));



    arrayCfg.cryptFct_ = [](uint16_t /*tag*/, const byte* pData, size_t size, TiffComponent* /*pRoot*/) {

        return std::make_shared<DataBuf>(pData, size);

    };

    EXPECT_CALL(*binaryArray.get(), setData(testing::_)).Times(1);



    reader->visitBinaryArray(binaryArray.get());

}



TEST_F(TiffReaderTest_1708, VisitBinaryArray_AddElement_1708) {

    auto binaryArray = std::make_unique<TiffBinaryArray>(0x0001, ifdExif, arrayCfg, nullptr, 0);

    EXPECT_CALL(*binaryArray.get(), initialize(pRoot.get())).WillOnce(testing::Return(true));

    EXPECT_CALL(*binaryArray.get(), cfg()).WillRepeatedly(testing::Return(&arrayCfg));

    EXPECT_CALL(*binaryArray.get(), addElement(0, testing::_)).Times(1);



    reader->visitBinaryArray(binaryArray.get());

}



static ArrayCfg arrayCfg = {

    ttUnsignedByte,

    nullptr,

    false,

    false,

    false,

    { 0, 1 }

};
