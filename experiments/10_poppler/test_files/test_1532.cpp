#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Decrypt.h"

#include "TestProjects/poppler/poppler/Stream.h"



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

};



class BaseCryptStreamTest_1532 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    unsigned char fileKey[32] = {0};

    Ref ref{0, 0};

    std::unique_ptr<BaseCryptStream> baseCryptStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        baseCryptStream = std::make_unique<BaseCryptStream>(std::move(mockStream), fileKey, cryptRC4, sizeof(fileKey), ref);

    }

};



TEST_F(BaseCryptStreamTest_1532, RewindReturnsTrue_1532) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(baseCryptStream->rewind());

}



TEST_F(BaseCryptStreamTest_1532, RewindReturnsFalse_1532) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(baseCryptStream->rewind());

}



TEST_F(BaseCryptStreamTest_1532, GetCharDelegatesToMockStream_1532) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(42));

    EXPECT_EQ(baseCryptStream->getChar(), 42);

}



TEST_F(BaseCryptStreamTest_1532, LookCharDelegatesToMockStream_1532) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(84));

    EXPECT_EQ(baseCryptStream->lookChar(), 84);

}



TEST_F(BaseCryptStreamTest_1532, GetPosDelegatesToMockStream_1532) {

    EXPECT_CALL(*mockStream, getPos()).WillOnce(::testing::Return(static_cast<Goffset>(100)));

    EXPECT_EQ(baseCryptStream->getPos(), static_cast<Goffset>(100));

}



TEST_F(BaseCryptStreamTest_1532, IsBinaryDelegatesToMockStream_1532) {

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(baseCryptStream->isBinary(true));



    EXPECT_CALL(*mockStream, isBinary(false)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(baseCryptStream->isBinary(false));

}



TEST_F(BaseCryptStreamTest_1532, GetKindReturnsStrCrypt_1532) {

    EXPECT_EQ(baseCryptStream->getKind(), strCrypt);

}



TEST_F(BaseCryptStreamTest_1532, GetUndecodedStreamDelegatesToMockStream_1532) {

    auto* expectedStream = new MockStream();

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(::testing::Return(expectedStream));

    EXPECT_EQ(baseCryptStream->getUndecodedStream(), expectedStream);

}
