#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class EOFStreamTest_198 : public ::testing::Test {

protected:

    std::unique_ptr<EOFStream> eofStream;



    void SetUp() override {

        // Create a mock Stream for the EOFStream to wrap

        auto mockStream = std::make_unique<NiceMock<MockStream>>();

        eofStream = std::make_unique<EOFStream>(std::move(mockStream));

    }

};



// Mock class for Stream

class MockStream : public Stream {

public:

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

};



// Test normal operation of rewind

TEST_F(EOFStreamTest_198, RewindReturnsTrue_198) {

    EXPECT_TRUE(eofStream->rewind());

}



// Test that getChar returns -1 when EOF is reached

TEST_F(EOFStreamTest_198, GetCharReturnsEOFWhenReached_198) {

    EXPECT_CALL(*static_cast<MockStream*>(eofStream->str.get()), getChar())

        .WillOnce(Return(-1));

    EXPECT_EQ(eofStream->getChar(), -1);

}



// Test that lookChar returns -1 when EOF is reached

TEST_F(EOFStreamTest_198, LookCharReturnsEOFWhenReached_198) {

    EXPECT_CALL(*static_cast<MockStream*>(eofStream->str.get()), lookChar())

        .WillOnce(Return(-1));

    EXPECT_EQ(eofStream->lookChar(), -1);

}



// Test that getPSFilter returns nullopt when no filter is available

TEST_F(EOFStreamTest_198, GetPSFilterReturnsNullopt_198) {

    EXPECT_CALL(*static_cast<MockStream*>(eofStream->str.get()), getPSFilter(_, _))

        .WillOnce(Return(std::nullopt));

    EXPECT_EQ(eofStream->getPSFilter(0, ""), std::nullopt);

}



// Test that isBinary returns false when the stream is not binary

TEST_F(EOFStreamTest_198, IsBinaryReturnsFalse_198) {

    EXPECT_CALL(*static_cast<MockStream*>(eofStream->str.get()), isBinary(_))

        .WillOnce(Return(false));

    EXPECT_FALSE(eofStream->isBinary(true));

}
