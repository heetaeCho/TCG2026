#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "DCTStream.cc"

#include "Stream.h"



using ::testing::NiceMock;

using ::testing::Return;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

};



class DCTStreamTest_1988 : public ::testing::Test {

protected:

    void SetUp() override {

        stream = std::make_unique<NiceMock<MockStream>>();

        src_mgr.pub.next_input_byte = &src_mgr.buffer;

        src_mgr.pub.bytes_in_buffer = 0;

        cinfo.src = (struct jpeg_source_mgr*)&src_mgr;

        src_mgr.str = stream.get();

        src_mgr.index = 0;

    }



    j_decompress_ptr cinfo;

    struct str_src_mgr src_mgr;

    std::unique_ptr<NiceMock<MockStream>> stream;

};



TEST_F(DCTStreamTest_1988, FirstCallReturnsFF_1988) {

    EXPECT_TRUE(str_fill_input_buffer(&cinfo));

    EXPECT_EQ(src_mgr.buffer, 0xFF);

}



TEST_F(DCTStreamTest_1988, SecondCallReturnsD8_1988) {

    str_fill_input_buffer(&cinfo); // First call

    EXPECT_TRUE(str_fill_input_buffer(&cinfo)); // Second call

    EXPECT_EQ(src_mgr.buffer, 0xD8);

}



TEST_F(DCTStreamTest_1988, ThirdCallDelegatesToGetChar_1988) {

    str_fill_input_buffer(&cinfo); // First call

    str_fill_input_buffer(&cinfo); // Second call

    EXPECT_CALL(*stream, getChar()).WillOnce(Return(0x5A));

    EXPECT_TRUE(str_fill_input_buffer(&cinfo)); // Third call

    EXPECT_EQ(src_mgr.buffer, 0x5A);

}



TEST_F(DCTStreamTest_1988, GetCharReturnsEOF_ReturnsFalse_1988) {

    str_fill_input_buffer(&cinfo); // First call

    str_fill_input_buffer(&cinfo); // Second call

    EXPECT_CALL(*stream, getChar()).WillOnce(Return(EOF));

    EXPECT_FALSE(str_fill_input_buffer(&cinfo)); // Third call

}



TEST_F(DCTStreamTest_1988, BufferAndIndexResetAfterThirdCall_1988) {

    str_fill_input_buffer(&cinfo); // First call

    str_fill_input_buffer(&cinfo); // Second call

    EXPECT_CALL(*stream, getChar()).WillOnce(Return(0x5A));

    str_fill_input_buffer(&cinfo); // Third call

    EXPECT_EQ(src_mgr.buffer, 0x5A);

    EXPECT_EQ(src_mgr.index, 3);

}



TEST_F(DCTStreamTest_1988, MultipleThirdCallsDelegateToGetChar_1988) {

    str_fill_input_buffer(&cinfo); // First call

    str_fill_input_buffer(&cinfo); // Second call



    EXPECT_CALL(*stream, getChar()).WillOnce(Return(0x5A));

    EXPECT_TRUE(str_fill_input_buffer(&cinfo)); // Third call

    EXPECT_EQ(src_mgr.buffer, 0x5A);



    EXPECT_CALL(*stream, getChar()).WillOnce(Return(0x5B));

    EXPECT_TRUE(str_fill_input_buffer(&cinfo)); // Fourth call

    EXPECT_EQ(src_mgr.buffer, 0x5B);

}



TEST_F(DCTStreamTest_1988, ResetIndexAfterEOF_1988) {

    str_fill_input_buffer(&cinfo); // First call

    str_fill_input_buffer(&cinfo); // Second call



    EXPECT_CALL(*stream, getChar()).WillOnce(Return(EOF));

    EXPECT_FALSE(str_fill_input_buffer(&cinfo)); // Third call

    EXPECT_EQ(src_mgr.index, 0);



    EXPECT_TRUE(str_fill_input_buffer(&cinfo)); // First call after EOF

    EXPECT_EQ(src_mgr.buffer, 0xFF);

}
