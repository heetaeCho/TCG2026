#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

};



class EmbedStreamTest_178 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    EmbedStream* embedStream;



    void SetUp() override {

        mockStream = std::make_unique<NiceMock<MockStream>>();

        embedStream = new EmbedStream(mockStream.get(), Object(), true, 0, true);

    }



    void TearDown() override {

        delete embedStream;

    }

};



TEST_F(EmbedStreamTest_178, UnfilteredRewind_DelegatesToBaseStream_178) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));

    bool result = embedStream->unfilteredRewind();

    EXPECT_TRUE(result);

}



TEST_F(EmbedStreamTest_178, UnfilteredRewind_ReturnsFalseWhenBaseStreamFails_178) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(false));

    bool result = embedStream->unfilteredRewind();

    EXPECT_FALSE(result);

}
