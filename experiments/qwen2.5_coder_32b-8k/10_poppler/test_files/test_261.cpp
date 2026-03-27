#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_261 : public ::testing::Test {

protected:

    XRef* xref;



    void SetUp() override {

        xref = new XRef();

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(XRefTest_261, GetPermFlags_DefaultValue_261) {

    EXPECT_EQ(xref->getPermFlags(), 0);

}



TEST_F(XRefTest_261, SetEncryptionAndGetPermFlags_NormalOperation_261) {

    xref->setEncryption(42, false, nullptr, 0, 0, 0, CryptAlgorithm::cryptNone);

    EXPECT_EQ(xref->getPermFlags(), 42);

}



TEST_F(XRefTest_261, SetEncryptionAndGetPermFlags_ZeroValue_261) {

    xref->setEncryption(0, false, nullptr, 0, 0, 0, CryptAlgorithm::cryptNone);

    EXPECT_EQ(xref->getPermFlags(), 0);

}



TEST_F(XRefTest_261, SetEncryptionAndGetPermFlags_MaxValue_261) {

    xref->setEncryption(0xFFFFFFFF, false, nullptr, 0, 0, 0, CryptAlgorithm::cryptNone);

    EXPECT_EQ(xref->getPermFlags(), 0xFFFFFFFF);

}



TEST_F(XRefTest_261, IsEncrypted_DefaultValue_261) {

    EXPECT_FALSE(xref->isEncrypted());

}



TEST_F(XRefTest_261, SetEncryptionAndGetIsEncrypted_NormalOperation_261) {

    xref->setEncryption(42, false, nullptr, 0, 0, 0, CryptAlgorithm::cryptNone);

    EXPECT_TRUE(xref->isEncrypted());

}



TEST_F(XRefTest_261, MarkUnencrypted_IsEncrypted_ReturnsFalse_261) {

    xref->setEncryption(42, false, nullptr, 0, 0, 0, CryptAlgorithm::cryptNone);

    xref->markUnencrypted();

    EXPECT_FALSE(xref->isEncrypted());

}



TEST_F(XRefTest_261, GetErrorCode_DefaultValue_261) {

    EXPECT_EQ(xref->getErrorCode(), 0);

}



TEST_F(XRefTest_261, IsOk_DefaultValue_261) {

    EXPECT_TRUE(xref->isOk());

}
