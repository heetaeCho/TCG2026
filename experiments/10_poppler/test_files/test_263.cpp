#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_263 : public ::testing::Test {

protected:

    XRef xref;

};



TEST_F(XRefTest_263, GetRootNum_ReturnsDefaultValue_263) {

    EXPECT_EQ(xref.getRootNum(), 0);

}



// Assuming there could be a scenario where rootNum is set to a specific value

// This test would require a way to set rootNum, which isn't provided in the interface.

// However, if we assume some setup function exists or another way to set it, we could have:

// TEST_F(XRefTest_263, GetRootNum_ReturnsSetValue_263) {

//     // Assuming there's a way to set rootNum

//     xref.setRootNum(42); // Hypothetical function

//     EXPECT_EQ(xref.getRootNum(), 42);

// }



TEST_F(XRefTest_263, GetErrorCode_ReturnsDefaultValue_263) {

    EXPECT_EQ(xref.getErrorCode(), 0);

}



TEST_F(XRefTest_263, IsOk_ReturnsTrueByDefault_263) {

    EXPECT_TRUE(xref.isOk());

}



TEST_F(XRefTest_263, IsXRefStream_ReturnsFalseByDefault_263) {

    EXPECT_FALSE(xref.isXRefStream());

}



TEST_F(XRefTest_263, IsEncrypted_ReturnsFalseByDefault_263) {

    EXPECT_FALSE(xref.isEncrypted());

}



TEST_F(XRefTest_263, GetPermFlags_ReturnsDefaultValue_263) {

    EXPECT_EQ(xref.getPermFlags(), 0);

}



TEST_F(XRefTest_263, GetNumObjects_ReturnsDefaultValue_263) {

    EXPECT_EQ(xref.getNumObjects(), 0);

}



TEST_F(XRefTest_263, GetRootGen_ReturnsDefaultValue_263) {

    EXPECT_EQ(xref.getRootGen(), 0);

}



TEST_F(XRefTest_263, IsModified_ReturnsFalseByDefault_263) {

    EXPECT_FALSE(xref.isModified());

}
