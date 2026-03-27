#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class TiffBinaryArrayTest : public ::testing::Test {

protected:

    const uint16_t tag = 0x1234;

    const IfdId group = ifdExif;

    const ArrayCfg arrayCfg = {};

    const ArrayDef arrayDef = {};

    const size_t defSize = 10;



    TiffBinaryArray* tiffBinaryArray;



    void SetUp() override {

        tiffBinaryArray = new TiffBinaryArray(tag, group, arrayCfg, &arrayDef, defSize);

    }



    void TearDown() override {

        delete tiffBinaryArray;

    }

};



TEST_F(TiffBinaryArrayTest_315, IniOrigDataBuf_SetsOrigDataAndSize_315) {

    byte data[20] = {0};

    size_t size = 20;

    tiffBinaryArray->setData(data, size, nullptr);

    tiffBinaryArray->iniOrigDataBuf();

    EXPECT_EQ(tiffBinaryArray->pData(), tiffBinaryArray->origData_);

    EXPECT_EQ(size, tiffBinaryArray->origSize_);

}



TEST_F(TiffBinaryArrayTest_315, IniOrigDataBuf_NoData_SetOrigDataAndSizeToZero_315) {

    tiffBinaryArray->iniOrigDataBuf();

    EXPECT_EQ(nullptr, tiffBinaryArray->origData_);

    EXPECT_EQ(0, tiffBinaryArray->origSize_);

}



TEST_F(TiffBinaryArrayTest_315, IniOrigDataBuf_AfterSetData_CorrectOrigDataAndSize_315) {

    byte data[20] = {0};

    size_t size = 20;

    tiffBinaryArray->setData(data, size, nullptr);

    tiffBinaryArray->iniOrigDataBuf();

    EXPECT_EQ(data, tiffBinaryArray->origData_);

    EXPECT_EQ(size, tiffBinaryArray->origSize_);

}



TEST_F(TiffBinaryArrayTest_315, IniOrigDataBuf_MultipleCalls_SetSameOrigDataAndSize_315) {

    byte data[20] = {0};

    size_t size = 20;

    tiffBinaryArray->setData(data, size, nullptr);

    tiffBinaryArray->iniOrigDataBuf();

    tiffBinaryArray->iniOrigDataBuf();

    EXPECT_EQ(data, tiffBinaryArray->origData_);

    EXPECT_EQ(size, tiffBinaryArray->origSize_);

}
