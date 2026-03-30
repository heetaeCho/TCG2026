#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_266 : public ::testing::Test {

protected:

    XRef* xref;



    void SetUp() override {

        xref = new XRef();

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(XRefTest_266, GetTrailerDict_ReturnsNonNullPointer_266) {

    EXPECT_NE(xref->getTrailerDict(), nullptr);

}



TEST_F(XRefTest_266, GetTrailerDict_ReturnsSameObjectAcrossCalls_266) {

    Object* trailerDict1 = xref->getTrailerDict();

    Object* trailerDict2 = xref->getTrailerDict();

    EXPECT_EQ(trailerDict1, trailerDict2);

}



TEST_F(XRefTest_266, IsOk_ReturnsTrueAfterConstruction_266) {

    EXPECT_TRUE(xref->isOk());

}



TEST_F(XRefTest_266, IsXRefStream_ReturnsFalseByDefault_266) {

    EXPECT_FALSE(xref->isXRefStream());

}



TEST_F(XRefTest_266, GetErrorCode_ReturnsZeroAfterConstruction_266) {

    EXPECT_EQ(xref->getErrorCode(), 0);

}



TEST_F(XRefTest_266, IsEncrypted_ReturnsFalseByDefault_266) {

    EXPECT_FALSE(xref->isEncrypted());

}



TEST_F(XRefTest_266, GetPermFlags_ReturnsZeroAfterConstruction_266) {

    EXPECT_EQ(xref->getPermFlags(), 0);

}



TEST_F(XRefTest_266, GetNumObjects_ReturnsZeroAfterConstruction_266) {

    EXPECT_EQ(xref->getNumObjects(), 0);

}



TEST_F(XRefTest_266, GetRootNum_ReturnsZeroAfterConstruction_266) {

    EXPECT_EQ(xref->getRootNum(), 0);

}



TEST_F(XRefTest_266, GetRootGen_ReturnsZeroAfterConstruction_266) {

    EXPECT_EQ(xref->getRootGen(), 0);

}



TEST_F(XRefTest_266, IsModified_ReturnsFalseByDefault_266) {

    EXPECT_FALSE(xref->isModified());

}
