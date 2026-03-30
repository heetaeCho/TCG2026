#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/NSSCryptoSignBackend.cc"

#include "TestProjects/poppler/poppler/HashAlgorithm.h"



class DigestLengthTest_1794 : public ::testing::Test {

protected:

    // Additional setup can be done here if necessary

};



TEST_F(DigestLengthTest_1794, Sha1DigestLength_1794) {

    EXPECT_EQ(digestLength(HashAlgorithm::Sha1), 20U);

}



TEST_F(DigestLengthTest_1794, Sha256DigestLength_1794) {

    EXPECT_EQ(digestLength(HashAlgorithm::Sha256), 32U);

}



TEST_F(DigestLengthTest_1794, Sha384DigestLength_1794) {

    EXPECT_EQ(digestLength(HashAlgorithm::Sha384), 48U);

}



TEST_F(DigestLengthTest_1794, Sha512DigestLength_1794) {

    EXPECT_EQ(digestLength(HashAlgorithm::Sha512), 64U);

}



TEST_F(DigestLengthTest_1794, UnknownHashAlgorithm_ReturnsZero_1794) {

    EXPECT_EQ(digestLength(HashAlgorithm::Unknown), 0U);

}



TEST_F(DigestLengthTest_1794, InvalidHashAlgorithm_ReturnsZero_1794) {

    EXPECT_EQ(digestLength(static_cast<HashAlgorithm>(8)), 0U); // Assuming 8 is not a valid HashAlgorithm

}
