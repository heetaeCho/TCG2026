#include <gtest/gtest.h>

#include "HashAlgorithm.h"

#include "NSSCryptoSignBackend.cc" // Assuming the function is in this file or linked properly



class ConvertHashAlgorithmToNssTest_1792 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertMd2_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Md2), SEC_OID_MD2);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertMd5_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Md5), SEC_OID_MD5);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertSha1_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha1), SEC_OID_SHA1);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertSha256_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha256), SEC_OID_SHA256);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertSha384_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha384), SEC_OID_SHA384);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertSha512_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha512), SEC_OID_SHA512);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertSha224_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Sha224), SEC_OID_SHA224);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, ConvertUnknown_1792) {

    EXPECT_EQ(ConvertHashAlgorithmToNss(HashAlgorithm::Unknown), SEC_OID_UNKNOWN);

}



TEST_F(ConvertHashAlgorithmToNssTest_1792, DefaultCase_1792) {

    HashAlgorithm invalidAlg = static_cast<HashAlgorithm>(-1); // Assuming -1 is not a valid enum value

    EXPECT_EQ(ConvertHashAlgorithmToNss(invalidAlg), SEC_OID_UNKNOWN);

}
