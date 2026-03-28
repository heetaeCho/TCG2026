#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the necessary classes for BaseStreamStream

class MockBaseStream {

public:

    MOCK_CONST_METHOD0(isBinary, bool());

};



class MockStream {

public:

    MOCK_METHOD0(getBaseStream, MockBaseStream*());

};



class TestableBaseStreamStream : public BaseStreamStream {

public:

    TestableBaseStreamStream(MockStream* stream) : str(stream) {}



private:

    MockStream* str;

};



TEST_F(StreamTest_1491, IsBinary_DelegatesToBaseStream_IsBinary_1491) {

    // Arrange

    auto mockStream = new MockStream();

    auto mockBaseStream = new MockBaseStream();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(::testing::Return(mockBaseStream));

    EXPECT_CALL(*mockBaseStream, isBinary()).WillOnce(::testing::Return(true));



    TestableBaseStreamStream testSubject(mockStream);



    // Act

    bool result = testSubject.isBinary();



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(StreamTest_1491, IsBinary_DelegatesToBaseStream_IsNotBinary_1491) {

    // Arrange

    auto mockStream = new MockStream();

    auto mockBaseStream = new MockBaseStream();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(::testing::Return(mockBaseStream));

    EXPECT_CALL(*mockBaseStream, isBinary()).WillOnce(::testing::Return(false));



    TestableBaseStreamStream testSubject(mockStream);



    // Act

    bool result = testSubject.isBinary();



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(StreamTest_1491, IsBinary_DefaultLastParameter_IsIgnored_1491) {

    // Arrange

    auto mockStream = new MockStream();

    auto mockBaseStream = new MockBaseStream();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(::testing::Return(mockBaseStream));

    EXPECT_CALL(*mockBaseStream, isBinary()).WillOnce(::testing::Return(true));



    TestableBaseStreamStream testSubject(mockStream);



    // Act

    bool result = testSubject.isBinary(false);



    // Assert

    EXPECT_TRUE(result);

}
