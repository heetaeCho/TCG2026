#include <gtest/gtest.h>

#include "Stream.h"

#include <gmock/gmock.h>



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(Stream *, getUndecodedStream, (), (override));

};



class FilterStreamTest_141 : public Test {

protected:

    NiceMock<MockStream> mockStream;

    FilterStream filterStream{&mockStream};

};



TEST_F(FilterStreamTest_141, GetUndecodedStream_ReturnsCorrectStream_141) {

    Stream* expectedStream = &mockStream;

    EXPECT_CALL(mockStream, getUndecodedStream()).WillOnce(Return(expectedStream));



    Stream* result = filterStream.getUndecodedStream();

    EXPECT_EQ(result, expectedStream);

}



TEST_F(FilterStreamTest_141, GetUndecodedStream_CallsBaseImplementation_141) {

    EXPECT_CALL(mockStream, getUndecodedStream());



    filterStream.getUndecodedStream();

}
