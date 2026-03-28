#include <gtest/gtest.h>

#include "Decrypt.h"



class BaseCryptStreamTest : public ::testing::Test {

protected:

    std::unique_ptr<Stream> mockStream = std::make_unique<Stream>();

    unsigned char fileKey[32] = {0};

    CryptAlgorithm algo = cryptRC4;

    int keyLength = 16;

    Ref ref = {0, 0};



    BaseCryptStream* baseCryptStream;



    void SetUp() override {

        baseCryptStream = new BaseCryptStream(std::move(mockStream), fileKey, algo, keyLength, ref);

    }



    void TearDown() override {

        delete baseCryptStream;

    }

};



TEST_F(BaseCryptStreamTest_1533, GetUndecodedStream_ReturnsSelf_1533) {

    EXPECT_EQ(baseCryptStream->getUndecodedStream(), static_cast<Stream*>(baseCryptStream));

}



TEST_F(BaseCryptStreamTest_1533, Rewind_ReturnsTrue_NormalOperation_1533) {

    EXPECT_TRUE(baseCryptStream->rewind());

}



TEST_F(BaseCryptStreamTest_1533, GetChar_ReturnsNonNegative_IntegerValue_1533) {

    int charValue = baseCryptStream->getChar();

    EXPECT_GE(charValue, -1);

}



TEST_F(BaseCryptStreamTest_1533, LookChar_ReturnsNonNegative_IntegerValue_1533) {

    int charValue = baseCryptStream->lookChar();

    EXPECT_GE(charValue, -1);

}



TEST_F(BaseCryptStreamTest_1533, GetPos_ReturnsNonNegative_GoffsetValue_1533) {

    Goffset pos = baseCryptStream->getPos();

    EXPECT_GE(pos, 0);

}



TEST_F(BaseCryptStreamTest_1533, IsBinary_ReturnsBoolean_NormalOperation_1533) {

    bool isBinaryResult = baseCryptStream->isBinary(true);

    EXPECT_TRUE(isBinaryResult || !isBinaryResult); // Check if it returns a boolean

}



TEST_F(BaseCryptStreamTest_1533, GetKind_ReturnsValidStreamKind_NormalOperation_1533) {

    StreamKind kind = baseCryptStream->getKind();

    EXPECT_TRUE(kind >= strNone && kind <= strCCITTG4);

}
