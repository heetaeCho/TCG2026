#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.cc"



using namespace testing;



// Mock class for Stream

class MockStream : public Stream {

public:

    MOCK_METHOD(void, reset, (), (override));

    MOCK_METHOD(bool, isEOF, (), (const, override));

    // Add other methods if necessary

};



TEST_F(StreamTest_1486, WrapEOFStream_ReturnsOriginalStreamIfAlreadyEOF_1486) {

    auto originalStream = std::make_unique<MockStream>();

    EXPECT_CALL(*originalStream, isEOF()).WillOnce(Return(true));



    auto wrappedStream = wrapEOFStream(std::move(originalStream));

    EXPECT_NE(wrappedStream.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<EOFStream*>(wrappedStream.get()) == nullptr);  // Ensure it's not wrapped again

}



TEST_F(StreamTest_1486, WrapEOFStream_WrapsNonEOFStreamWithEOFStream_1486) {

    auto originalStream = std::make_unique<MockStream>();

    EXPECT_CALL(*originalStream, isEOF()).WillOnce(Return(false));



    auto wrappedStream = wrapEOFStream(std::move(originalStream));

    EXPECT_NE(wrappedStream.get(), nullptr);

    EXPECT_TRUE(dynamic_cast<EOFStream*>(wrappedStream.get()) != nullptr);  // Ensure it's wrapped

}



TEST_F(StreamTest_1486, WrapEOFStream_HandlesNullptrInput_1486) {

    auto originalStream = std::unique_ptr<MockStream>(nullptr);



    auto wrappedStream = wrapEOFStream(std::move(originalStream));

    EXPECT_EQ(wrappedStream.get(), nullptr);

}
