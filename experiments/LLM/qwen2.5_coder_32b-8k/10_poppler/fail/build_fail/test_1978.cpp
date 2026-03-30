#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include "Hints.cc"



using ::testing::Return;

using ::testing::_;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

};



class StreamBitReaderTest_1978 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mock_stream_;

    std::unique_ptr<StreamBitReader> bit_reader_;



    void SetUp() override {

        mock_stream_ = std::make_unique<MockStream>();

        bit_reader_ = std::make_unique<StreamBitReader>(mock_stream_.get());

    }

};



TEST_F(StreamBitReaderTest_1978, ReadBitReturns0WhenFirstCharIs0x00_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(0x00));

    EXPECT_EQ(bit_reader_->readBit(), 0);

}



TEST_F(StreamBitReaderTest_1978, ReadBitReturns1WhenFirstCharIs0xFF_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(0xFF));

    EXPECT_EQ(bit_reader_->readBit(), 1);

}



TEST_F(StreamBitReaderTest_1978, ReadBitsReturnsCorrectValueForTwoBits_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(0b10101010));

    EXPECT_EQ(bit_reader_->readBits(2), 2);

}



TEST_F(StreamBitReaderTest_1978, ReadBitsHandlesEOFProperly_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(EOF));

    EXPECT_EQ(bit_reader_->readBits(1), (unsigned int)-1);

}



TEST_F(StreamBitReaderTest_1978, ReadBitResetsAfterReadingAllBits_1978) {

    EXPECT_CALL(*mock_stream_, getChar())

        .WillOnce(Return(0b10000000))

        .WillOnce(Return(0b01000000));

    EXPECT_EQ(bit_reader_->readBit(), 1);

    EXPECT_EQ(bit_reader_->readBit(), 0);

}



TEST_F(StreamBitReaderTest_1978, ReadBitsReturnsMultipleBitsCorrectly_1978) {

    EXPECT_CALL(*mock_stream_, getChar())

        .WillOnce(Return(0b10101010))

        .WillOnce(Return(0b01010101));

    EXPECT_EQ(bit_reader_->readBits(4), 0b1010);

    EXPECT_EQ(bit_reader_->readBits(4), 0b1010);

}



TEST_F(StreamBitReaderTest_1978, AtEOFReturnsFalseInitially_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(0x00));

    EXPECT_FALSE(bit_reader_->atEOF());

}



TEST_F(StreamBitReaderTest_1978, AtEOFReturnsTrueAfterReadingEOF_1978) {

    EXPECT_CALL(*mock_stream_, getChar()).WillOnce(Return(EOF));

    bit_reader_->readBit();

    EXPECT_TRUE(bit_reader_->atEOF());

}
