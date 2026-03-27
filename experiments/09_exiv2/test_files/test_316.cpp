#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::Eq;



class TiffBinaryArrayTest_316 : public ::testing::Test {

protected:

    TiffBinaryArrayTest_316() 

        : arrayCfg({}),

          arrayDef(nullptr),

          defSize(0),

          tag(0x1234),

          group(IfdId::ifdExif),

          tiffBinaryArray(tag, group, arrayCfg, arrayDef, defSize) {}



    ArrayCfg arrayCfg;

    const ArrayDef* arrayDef;

    size_t defSize;

    uint16_t tag;

    IfdId group;

    TiffBinaryArray tiffBinaryArray;

};



TEST_F(TiffBinaryArrayTest_316, UpdOrigDataBuf_SamePointerAndSize_ReturnsTrue_316) {

    byte data[5] = {0};

    tiffBinaryArray.iniOrigDataBuf();

    tiffBinaryArray.updOrigDataBuf(data, sizeof(data));

    EXPECT_TRUE(tiffBinaryArray.updOrigDataBuf(data, sizeof(data)));

}



TEST_F(TiffBinaryArrayTest_316, UpdOrigDataBuf_DifferentPointerSameSize_ReturnsTrue_316) {

    byte data1[5] = {0};

    byte data2[5] = {0};

    tiffBinaryArray.iniOrigDataBuf();

    tiffBinaryArray.updOrigDataBuf(data1, sizeof(data1));

    EXPECT_TRUE(tiffBinaryArray.updOrigDataBuf(data2, sizeof(data2)));

}



TEST_F(TiffBinaryArrayTest_316, UpdOrigDataBuf_DifferentSize_ReturnsFalse_316) {

    byte data[5] = {0};

    tiffBinaryArray.iniOrigDataBuf();

    EXPECT_FALSE(tiffBinaryArray.updOrigDataBuf(data, sizeof(data) + 1));

}



TEST_F(TiffBinaryArrayTest_316, UpdOrigDataBuf_Uninitialized_ReturnsFalse_316) {

    byte data[5] = {0};

    EXPECT_FALSE(tiffBinaryArray.updOrigDataBuf(data, sizeof(data)));

}
