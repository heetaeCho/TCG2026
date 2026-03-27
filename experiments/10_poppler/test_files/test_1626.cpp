#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    void md5(const unsigned char *msg, int msgLen, unsigned char *digest);

}



struct MD5State {

public:

    unsigned long a;

    unsigned long b;

    unsigned long c;

    unsigned long d;

    unsigned char buf[64];

    int msgLen;

    unsigned char digest[16];

};



TEST(md5Test_1626, NormalOperation_1626) {

    const unsigned char msg[] = "Hello, World!";

    unsigned char digest[16];

    md5(msg, sizeof(msg) - 1, digest);



    // Expected MD5 hash for "Hello, World!" is "65a8e27d8879283831b664bd8b7f0ad4"

    unsigned char expectedDigest[] = {0x65, 0xa8, 0xe2, 0x7d, 0x88, 0x79, 0x28, 0x38,

                                     0x31, 0xb6, 0x64, 0xbd, 0x8b, 0x7f, 0x0a, 0xd4};



    EXPECT_TRUE(memcmp(digest, expectedDigest, sizeof(expectedDigest)) == 0);

}



TEST(md5Test_1626, ZeroLengthMessage_1626) {

    const unsigned char msg[] = "";

    unsigned char digest[16];

    md5(msg, 0, digest);



    // Expected MD5 hash for an empty string is "d41d8cd98f00b204e9800998ecf8427e"

    unsigned char expectedDigest[] = {0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,

                                     0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e};



    EXPECT_TRUE(memcmp(digest, expectedDigest, sizeof(expectedDigest)) == 0);

}



TEST(md5Test_1626, NegativeLengthMessage_1626) {

    const unsigned char msg[] = "Hello, World!";

    unsigned char digest[16];

    md5(msg, -1, digest);



    // Expect no change to the digest array since negative length should be handled

    for (int i = 0; i < 16; ++i) {

        EXPECT_EQ(digest[i], 0);

    }

}



TEST(md5Test_1626, LargeMessage_1626) {

    const unsigned char msg[] = "This is a very long message that should still be hashed correctly by the md5 function. "

                                "The MD5 algorithm should handle this without any issues.";

    unsigned char digest[16];

    md5(msg, sizeof(msg) - 1, digest);



    // Expected MD5 hash for the large message

    unsigned char expectedDigest[] = {0x8a, 0x9d, 0xe7, 0xb8, 0xf3, 0xc4, 0x1b, 0xa6,

                                     0xcb, 0x2e, 0x5f, 0x8a, 0x75, 0xbe, 0x9d, 0x7c};



    EXPECT_TRUE(memcmp(digest, expectedDigest, sizeof(expectedDigest)) == 0);

}
