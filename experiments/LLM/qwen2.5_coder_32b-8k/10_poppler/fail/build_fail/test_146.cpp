#include <gtest/gtest.h>

#include "Stream.h"

#include <gmock/gmock.h>



using ::testing::NiceMock;

using ::testing::Return;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

};



class FilterStreamTest_146 : public ::testing::Test {

protected:

    NiceMock<MockStream> mockStream;

    FilterStream filterStream{&mockStream};

};



TEST_F(FilterStreamTest_146, UnfilteredRewind_DelegatesToBaseStream_146) {

    EXPECT_CALL(mockStream, unfilteredRewind()).WillOnce(Return(true));

    bool result = filterStream.unfilteredRewind();

    EXPECT_TRUE(result);

}



TEST_F(FilterStreamTest_146, UnfilteredRewind_ReturnsFalseIfBaseStreamFails_146) {

    EXPECT_CALL(mockStream, unfilteredRewind()).WillOnce(Return(false));

    bool result = filterStream.unfilteredRewind();

    EXPECT_FALSE(result);

}
