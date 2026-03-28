#include <gtest/gtest.h>

#include "NSSCryptoSignBackend.cc"

#include "HashAlgorithm.h"



class ConvertHashTypeFromNssTest : public ::testing::Test {

protected:

    // You can add any common setup or teardown here if needed.

};



TEST_F(ConvertHashTypeFromNssTest, PutIncreasesCount_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgMD2), HashAlgorithm::Md2);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertMd5ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgMD5), HashAlgorithm::Md5);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha1ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA1), HashAlgorithm::Sha1);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha256ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA256), HashAlgorithm::Sha256);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha384ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA384), HashAlgorithm::Sha384);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha512ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA512), HashAlgorithm::Sha512);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha224ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA224), HashAlgorithm::Sha224);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertUnknownHashToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgNULL), HashAlgorithm::Unknown);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertTotalHashToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgTOTAL), HashAlgorithm::Unknown);

}



#if NSS_VMAJOR >= 3 && NSS_VMINOR >= 91

TEST_F(ConvertHashTypeFromNssTest, ConvertSha3_224ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA3_224), HashAlgorithm::Unknown);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha3_256ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA3_256), HashAlgorithm::Unknown);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha3_384ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA3_384), HashAlgorithm::Unknown);

}



TEST_F(ConvertHashTypeFromNssTest, ConvertSha3_512ToHashAlgorithm_1793) {

    EXPECT_EQ(ConvertHashTypeFromNss(HASH_AlgSHA3_512), HashAlgorithm::Unknown);

}

#endif
