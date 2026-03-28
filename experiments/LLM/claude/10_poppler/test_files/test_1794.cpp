#include <gtest/gtest.h>
#include "HashAlgorithm.h"

// Declaration of the function under test (it's a static function in the .cc file,
// so we need to either include the .cc or declare it extern for testing purposes)
// Since it's static, we include the .cc file directly to access it in tests.
#include "NSSCryptoSignBackend.cc"

class DigestLengthTest_1794 : public ::testing::Test {
protected:
};

TEST_F(DigestLengthTest_1794, Sha1Returns20_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha1), 20u);
}

TEST_F(DigestLengthTest_1794, Sha256Returns32_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha256), 32u);
}

TEST_F(DigestLengthTest_1794, Sha384Returns48_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha384), 48u);
}

TEST_F(DigestLengthTest_1794, Sha512Returns64_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha512), 64u);
}

TEST_F(DigestLengthTest_1794, UnknownReturns0_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Unknown), 0u);
}

TEST_F(DigestLengthTest_1794, Md2Returns0_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Md2), 0u);
}

TEST_F(DigestLengthTest_1794, Md5Returns0_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Md5), 0u);
}

TEST_F(DigestLengthTest_1794, Sha224Returns0_1794) {
    EXPECT_EQ(digestLength(HashAlgorithm::Sha224), 0u);
}

TEST_F(DigestLengthTest_1794, InvalidEnumValueReturns0_1794) {
    // Test with a cast integer that doesn't correspond to any valid enum value
    EXPECT_EQ(digestLength(static_cast<HashAlgorithm>(99)), 0u);
}

TEST_F(DigestLengthTest_1794, NegativeEnumValueReturns0_1794) {
    EXPECT_EQ(digestLength(static_cast<HashAlgorithm>(-1)), 0u);
}
