#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace ::testing;



class ASCII85StreamTest : public Test {

protected:

    std::unique_ptr<Stream> mockStream = nullptr;

    ASCII85Stream* ascii85Stream = nullptr;



    void SetUp() override {

        mockStream = std::make_unique<StrictMock<MockStream>>();

        ascii85Stream = new ASCII85Stream(std::move(mockStream));

    }



    void TearDown() override {

        delete ascii85Stream;

    }

};



TEST_F(ASCII85StreamTest_181, GetKindReturnsASCII85_181) {

    EXPECT_EQ(ascii85Stream->getKind(), strASCII85);

}



TEST_F(ASCII85StreamTest_181, RewindCallsBaseRewind_181) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(ascii85Stream->rewind());

}



TEST_F(ASCII85StreamTest_181, LookCharCallsBaseLookChar_181) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return('A'));

    EXPECT_EQ(ascii85Stream->lookChar(), 'A');

}



TEST_F(ASCII85StreamTest_181, GetPSFilterCallsBaseGetPSFilter_181) {

    EXPECT_CALL(*mockStream, getPSFilter(PSLevel::LEVEL2, "")).WillOnce(Return(std::optional<std::string>{"filter"}));

    auto result = ascii85Stream->getPSFilter(PSLevel::LEVEL2, "");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "filter");

}



TEST_F(ASCII85StreamTest_181, IsBinaryCallsBaseIsBinary_181) {

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(Return(false));

    EXPECT_FALSE(ascii85Stream->isBinary(true));

}



TEST_F(ASCII85StreamTest_181, GetCharCallsBaseGetChar_181) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return('A'));

    EXPECT_EQ(ascii85Stream->getChar(), 'A');

}
