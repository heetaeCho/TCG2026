#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Stream class for dependency injection

class Stream {

public:

    virtual ~Stream() = default;

    virtual unsigned char getChar() = 0;

};



// MockStream inherits from Stream to mock its behavior

class MockStream : public Stream {

public:

    MOCK_METHOD(unsigned char, getChar, (), (override));

};



// Including the partial implementation of StreamBitReader for testing

#include "Hints.cc"



class StreamBitReaderTest_1979 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        reader = std::make_unique<StreamBitReader>(mockStream.get());

    }



    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<StreamBitReader> reader;

};



// Test: Normal operation, reading 1 bit

TEST_F(StreamBitReaderTest_1979, ReadBits_OneBit_NormalOperation_1979) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(testing::Return(0b10000000));

    ASSERT_EQ(reader->readBits(1), 1);

}



// Test: Normal operation, reading multiple bits

TEST_F(StreamBitReaderTest_1979, ReadBits_MultipleBits_NormalOperation_1979) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(testing::Return(0b11000000));

    ASSERT_EQ(reader->readBits(2), 3);

}



// Test: Boundary condition, reading zero bits

TEST_F(StreamBitReaderTest_1979, ReadBits_ZeroBits_BoundaryCondition_1979) {

    ASSERT_EQ(reader->readBits(0), 0);

}



// Test: Boundary condition, reading one bit with EOF

TEST_F(StreamBitReaderTest_1979, ReadBits_OneBit_EOF_BoundaryCondition_1979) {

    reader->isAtEof = true;

    ASSERT_EQ(reader->readBits(1), -1);

}



// Test: Exceptional case, negative number of bits

TEST_F(StreamBitReaderTest_1979, ReadBits_NegativeBits_ExceptionalCase_1979) {

    ASSERT_EQ(reader->readBits(-1), -1);

}



// Test: Reading multiple bytes with EOF in between

TEST_F(StreamBitReaderTest_1979, ReadBits_MultipleBytesWithEOF_ExceptionalCase_1979) {

    EXPECT_CALL(*mockStream, getChar())

        .WillOnce(testing::Return(0b10000000))

        .WillOnce(testing::Invoke([this]() {

            this->reader->isAtEof = true;

            return 0;

        }));

    ASSERT_EQ(reader->readBits(9), -1);

}
