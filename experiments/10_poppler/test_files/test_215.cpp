#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

};



class ASCII85EncoderTest : public Test {

protected:

    MockStream mockStream;

    std::unique_ptr<ASCII85Encoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<ASCII85Encoder>(&mockStream);

    }

};



TEST_F(ASCII85EncoderTest_215, RewindReturnsTrue_215) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(ASCII85EncoderTest_215, RewindReturnsFalse_215) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(false));

    EXPECT_FALSE(encoder->rewind());

}



TEST_F(ASCII85EncoderTest_215, GetCharFromEmptyBuffer_215) {

    EXPECT_CALL(mockStream, getChar())

        .Times(1)

        .WillOnce(Return(EOF));

    EXPECT_EQ(encoder->getChar(), EOF);

}



TEST_F(ASCII85EncoderTest_215, GetCharFromNonEmptyBuffer_215) {

    EXPECT_CALL(mockStream, getChar())

        .Times(0);

    encoder->bufPtr = encoder->buf;

    encoder->bufEnd = encoder->buf + 1;

    *encoder->bufPtr = 'A';

    EXPECT_EQ(encoder->getChar(), 'A');

}



TEST_F(ASCII85EncoderTest_215, GetKindReturnsStreamKind_215) {

    StreamKind expectedKind = streamUnknown; // Assuming a default kind for illustration

    EXPECT_CALL(mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(encoder->getKind(), expectedKind);

}



TEST_F(ASCII85EncoderTest_215, LookCharFromEmptyBuffer_215) {

    EXPECT_CALL(mockStream, lookChar())

        .Times(1)

        .WillOnce(Return(EOF));

    EXPECT_EQ(encoder->lookChar(), EOF);

}



TEST_F(ASCII85EncoderTest_215, LookCharFromNonEmptyBuffer_215) {

    EXPECT_CALL(mockStream, lookChar())

        .Times(0);

    encoder->bufPtr = encoder->buf;

    encoder->bufEnd = encoder->buf + 1;

    *encoder->bufPtr = 'A';

    EXPECT_EQ(encoder->lookChar(), 'A');

}



TEST_F(ASCII85EncoderTest_215, GetPSFilterReturnsEmptyOptional_215) {

    EXPECT_CALL(mockStream, getPSFilter(_, _))

        .Times(1)

        .WillOnce(Return(std::nullopt));

    EXPECT_EQ(encoder->getPSFilter(0, ""), std::nullopt);

}



TEST_F(ASCII85EncoderTest_215, GetPSFilterReturnsNonEmptyOptional_215) {

    std::string expectedFilter = "filter";

    EXPECT_CALL(mockStream, getPSFilter(_, _))

        .Times(1)

        .WillOnce(Return(expectedFilter));

    EXPECT_EQ(encoder->getPSFilter(0, ""), expectedFilter);

}



TEST_F(ASCII85EncoderTest_215, IsBinaryReturnsTrue_215) {

    EXPECT_CALL(mockStream, isBinary(_))

        .Times(1)

        .WillOnce(Return(true));

    EXPECT_TRUE(encoder->isBinary(false));

}



TEST_F(ASCII85EncoderTest_215, IsBinaryReturnsFalse_215) {

    EXPECT_CALL(mockStream, isBinary(_))

        .Times(1)

        .WillOnce(Return(false));

    EXPECT_FALSE(encoder->isBinary(true));

}
