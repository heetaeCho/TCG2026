#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_257 : public ::testing::Test {

protected:

    XRef* xref;



    void SetUp() override {

        xref = new XRef();

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(XRefTest_257, IsOk_DefaultConstructor_ReturnsTrue_257) {

    EXPECT_TRUE(xref->isOk());

}



TEST_F(XRefTest_257, IsXRefStream_DefaultConstructor_ReturnsFalse_257) {

    EXPECT_FALSE(xref->isXRefStream());

}



TEST_F(XRefTest_257, GetErrorCode_DefaultConstructor_ReturnsZero_257) {

    EXPECT_EQ(0, xref->getErrorCode());

}



TEST_F(XRefTest_257, IsEncrypted_DefaultConstructor_ReturnsFalse_257) {

    EXPECT_FALSE(xref->isEncrypted());

}



TEST_F(XRefTest_257, GetPermFlags_DefaultConstructor_ReturnsZero_257) {

    EXPECT_EQ(0, xref->getPermFlags());

}



TEST_F(XRefTest_257, GetNumObjects_DefaultConstructor_ReturnsZero_257) {

    EXPECT_EQ(0, xref->getNumObjects());

}



TEST_F(XRefTest_257, GetRootNum_DefaultConstructor_ReturnsZero_257) {

    EXPECT_EQ(0, xref->getRootNum());

}



TEST_F(XRefTest_257, GetRootGen_DefaultConstructor_ReturnsZero_257) {

    EXPECT_EQ(0, xref->getRootGen());

}



TEST_F(XRefTest_257, IsModified_DefaultConstructor_ReturnsFalse_257) {

    EXPECT_FALSE(xref->isModified());

}
