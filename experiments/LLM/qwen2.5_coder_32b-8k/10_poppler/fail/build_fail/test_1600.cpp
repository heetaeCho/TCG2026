#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

};



TEST_F(MockStreamTest_1600, NormalOperation_ReadFullBlock_1600) {

    MockStream stream;

    unsigned char buffer[16];

    std::vector<int> chars = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 

                              0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};



    for (int c : chars) {

        EXPECT_CALL(stream, getChar()).WillOnce(Return(c));

    }



    bool result = aesReadBlock(&stream, buffer, false);

    EXPECT_TRUE(result);



    for (size_t i = 0; i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(chars[i]));

    }

}



TEST_F(MockStreamTest_1600, NormalOperation_ReadPartialBlock_AddPadding_1600) {

    MockStream stream;

    unsigned char buffer[16];

    std::vector<int> chars = {0x00, 0x01, 0x02, 0x03, 0x04};



    for (int c : chars) {

        EXPECT_CALL(stream, getChar()).WillOnce(Return(c));

    }

    EXPECT_CALL(stream, getChar()).WillRepeatedly(Return(EOF));



    bool result = aesReadBlock(&stream, buffer, true);

    EXPECT_FALSE(result);



    for (size_t i = 0; i < chars.size(); ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(chars[i]));

    }



    for (size_t i = chars.size(); i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(16 - chars.size()));

    }

}



TEST_F(MockStreamTest_1600, NormalOperation_ReadPartialBlock_NoPadding_1600) {

    MockStream stream;

    unsigned char buffer[16];

    std::vector<int> chars = {0x00, 0x01, 0x02, 0x03, 0x04};



    for (int c : chars) {

        EXPECT_CALL(stream, getChar()).WillOnce(Return(c));

    }

    EXPECT_CALL(stream, getChar()).WillRepeatedly(Return(EOF));



    bool result = aesReadBlock(&stream, buffer, false);

    EXPECT_FALSE(result);



    for (size_t i = 0; i < chars.size(); ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(chars[i]));

    }



    for (size_t i = chars.size(); i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST_F(MockStreamTest_1600, BoundaryCondition_ReadZeroChars_1600) {

    MockStream stream;

    unsigned char buffer[16];

    

    EXPECT_CALL(stream, getChar()).WillOnce(Return(EOF));



    bool result = aesReadBlock(&stream, buffer, false);

    EXPECT_FALSE(result);



    for (size_t i = 0; i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}



TEST_F(MockStreamTest_1600, BoundaryCondition_ReadFullBlock_PaddingIgnored_1600) {

    MockStream stream;

    unsigned char buffer[16];

    std::vector<int> chars = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 

                              0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};



    for (int c : chars) {

        EXPECT_CALL(stream, getChar()).WillOnce(Return(c));

    }



    bool result = aesReadBlock(&stream, buffer, true);

    EXPECT_TRUE(result);



    for (size_t i = 0; i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], static_cast<unsigned char>(chars[i]));

    }

}



TEST_F(MockStreamTest_1600, ExceptionalCase_ReadNegativeChars_1600) {

    MockStream stream;

    unsigned char buffer[16];

    

    EXPECT_CALL(stream, getChar()).WillOnce(Return(-1));



    bool result = aesReadBlock(&stream, buffer, false);

    EXPECT_FALSE(result);



    for (size_t i = 0; i < sizeof(buffer); ++i) {

        EXPECT_EQ(buffer[i], 0);

    }

}
