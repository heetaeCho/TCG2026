#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayTest : public ::testing::Test {

protected:

    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    uint16_t tag = 0x0111;

    IfdId group = ifdExif;



    TiffBinaryArray* tiffBinaryArray;



    void SetUp() override {

        tiffBinaryArray = new TiffBinaryArray(tag, group, arrayCfg, &arrayDef, sizeof(arrayDef));

    }



    void TearDown() override {

        delete tiffBinaryArray;

    }

};



TEST_F(TiffBinaryArrayTest_249, SetDecodedTrue_249) {

    tiffBinaryArray->setDecoded(true);

    EXPECT_TRUE(tiffBinaryArray->decoded());

}



TEST_F(TiffBinaryArrayTest_249, SetDecodedFalse_249) {

    tiffBinaryArray->setDecoded(false);

    EXPECT_FALSE(tiffBinaryArray->decoded());

}



TEST_F(TiffBinaryArrayTest_249, InitializeGroupSuccess_249) {

    bool result = tiffBinaryArray->initialize(group);

    EXPECT_TRUE(result); // Assuming initialize returns true on success

}



TEST_F(TiffBinaryArrayTest_249, InitializeWithTiffComponentSuccess_249) {

    TiffComponent* pRoot = nullptr; // Assuming a valid TiffComponent pointer is passed in practice

    bool result = tiffBinaryArray->initialize(pRoot);

    EXPECT_TRUE(result); // Assuming initialize returns true on success

}



TEST_F(TiffBinaryArrayTest_249, IniOrigDataBufNoException_249) {

    EXPECT_NO_THROW(tiffBinaryArray->iniOrigDataBuf());

}



TEST_F(TiffBinaryArrayTest_249, UpdOrigDataBufSuccess_249) {

    byte data[] = {0x01, 0x02, 0x03};

    bool result = tiffBinaryArray->updOrigDataBuf(data, sizeof(data));

    EXPECT_TRUE(result); // Assuming updOrigDataBuf returns true on success

}



TEST_F(TiffBinaryArrayTest_249, AddElementSuccess_249) {

    size_t idx = 0;

    size_t result = tiffBinaryArray->addElement(idx, arrayDef);

    EXPECT_EQ(result, idx); // Assuming addElement returns the index of the added element

}



TEST_F(TiffBinaryArrayTest_249, GetCfgSuccess_249) {

    const ArrayCfg* cfg = tiffBinaryArray->cfg();

    EXPECT_EQ(cfg, &arrayCfg);

}



TEST_F(TiffBinaryArrayTest_249, GetDefSuccess_249) {

    const ArrayDef* def = tiffBinaryArray->def();

    EXPECT_EQ(def, &arrayDef);

}



TEST_F(TiffBinaryArrayTest_249, GetDefSizeSuccess_249) {

    size_t size = tiffBinaryArray->defSize();

    EXPECT_EQ(size, sizeof(arrayDef));

}
