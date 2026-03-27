#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayTest_294 : public ::testing::Test {

protected:

    TiffBinaryArrayTest_294() :

        arrayCfg({}),

        arrayDef(nullptr),

        defSize(0),

        tiffBinaryArray(1, IfdId::EXIF_IFD, arrayCfg, arrayDef, defSize) {}



    ArrayCfg arrayCfg;

    const ArrayDef* arrayDef;

    size_t defSize;

    TiffBinaryArray tiffBinaryArray;

};



TEST_F(TiffBinaryArrayTest_294, DoClone_ReturnsNewInstance_294) {

    TiffBinaryArray* cloned = tiffBinaryArray.doClone();

    EXPECT_NE(&tiffBinaryArray, cloned);

    delete cloned;

}



TEST_F(TiffBinaryArrayTest_294, Initialize_Group_Success_294) {

    bool result = tiffBinaryArray.initialize(IfdId::EXIF_IFD);

    EXPECT_TRUE(result);

}



TEST_F(TiffBinaryArrayTest_294, Initialize_PRoot_Success_294) {

    TiffComponent* pRoot = nullptr; // Assuming a valid TiffComponent pointer would be passed in real use

    bool result = tiffBinaryArray.initialize(pRoot);

    EXPECT_TRUE(result);

}



TEST_F(TiffBinaryArrayTest_294, IniOrigDataBuf_Success_294) {

    tiffBinaryArray.iniOrigDataBuf();

    // No observable behavior to assert here, just checking for no crash

}



TEST_F(TiffBinaryArrayTest_294, UpdOrigDataBuf_ValidData_Success_294) {

    byte data[] = {1, 2, 3};

    size_t size = sizeof(data);

    bool result = tiffBinaryArray.updOrigDataBuf(data, size);

    EXPECT_TRUE(result);

}



TEST_F(TiffBinaryArrayTest_294, AddElement_ValidDef_Success_294) {

    ArrayDef def;

    size_t idx = 0;

    size_t result = tiffBinaryArray.addElement(idx, def);

    EXPECT_EQ(1u, result); // Assuming addElement returns the new count

}



TEST_F(TiffBinaryArrayTest_294, SetDecoded_SetTrue_Success_294) {

    tiffBinaryArray.setDecoded(true);

    EXPECT_TRUE(tiffBinaryArray.decoded());

}



TEST_F(TiffBinaryArrayTest_294, Config_ReturnsCorrectConfig_294) {

    const ArrayCfg* cfg = tiffBinaryArray.cfg();

    EXPECT_EQ(&arrayCfg, cfg);

}



TEST_F(TiffBinaryArrayTest_294, Def_ReturnsCorrectDef_294) {

    const ArrayDef* def = tiffBinaryArray.def();

    EXPECT_EQ(arrayDef, def);

}



TEST_F(TiffBinaryArrayTest_294, DefSize_ReturnsCorrectDefSize_294) {

    size_t size = tiffBinaryArray.defSize();

    EXPECT_EQ(defSize, size);

}
