#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_260 : public ::testing::Test {

protected:

    XRef* xref;



    void SetUp() override {

        xref = new XRef();

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(XRefTest_260, IsEncrypted_ReturnsFalse_WhenNotEncrypted_260) {

    EXPECT_FALSE(xref->isEncrypted());

}



// Assuming there's a way to set the encrypted state to true externally

// If not, this test case cannot be implemented based on the provided interface.

// TEST_F(XRefTest_260, IsEncrypted_ReturnsTrue_WhenEncrypted_260) {

//     xref->setEncryption(...); // Assuming there's a way to set encryption

//     EXPECT_TRUE(xref->isEncrypted());

// }



TEST_F(XRefTest_260, GetErrorCode_ReturnsZero_ByDefault_260) {

    EXPECT_EQ(0, xref->getErrorCode());

}



TEST_F(XRefTest_260, IsXRefStream_ReturnsFalse_ByDefault_260) {

    EXPECT_FALSE(xref->isXRefStream());

}



TEST_F(XRefTest_260, GetPermFlags_ReturnsZero_ByDefault_260) {

    EXPECT_EQ(0, xref->getPermFlags());

}



TEST_F(XRefTest_260, GetNumObjects_ReturnsZero_ByDefault_260) {

    EXPECT_EQ(0, xref->getNumObjects());

}



TEST_F(XRefTest_260, GetRootNum_ReturnsZero_ByDefault_260) {

    EXPECT_EQ(0, xref->getRootNum());

}



TEST_F(XRefTest_260, GetRootGen_ReturnsZero_ByDefault_260) {

    EXPECT_EQ(0, xref->getRootGen());

}



TEST_F(XRefTest_260, IsModified_ReturnsFalse_ByDefault_260) {

    EXPECT_FALSE(xref->isModified());

}
