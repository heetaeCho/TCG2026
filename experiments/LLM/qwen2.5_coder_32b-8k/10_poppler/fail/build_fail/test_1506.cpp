#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

};



TEST_F(StreamTest_1506, GetCharFromStream_ReturnsExpectedValue_1506) {

    auto mock_stream = std::make_unique<MockStream>();

    int expected_value = 42;

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(Return(expected_value));



    int result = getCharFromStream(mock_stream.get());



    EXPECT_EQ(result, expected_value);

}



TEST_F(StreamTest_1506, GetCharFromStream_ReturnsDifferentValues_1506) {

    auto mock_stream = std::make_unique<MockStream>();

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(Return(42)).WillOnce(Return(84));



    int result1 = getCharFromStream(mock_stream.get());

    int result2 = getCharFromStream(mock_stream.get());



    EXPECT_EQ(result1, 42);

    EXPECT_EQ(result2, 84);

}



TEST_F(StreamTest_1506, GetCharFromStream_ReturnsBoundaryValues_1506) {

    auto mock_stream = std::make_unique<MockStream>();

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(Return(0)).WillOnce(Return(-1));



    int result1 = getCharFromStream(mock_stream.get());

    int result2 = getCharFromStream(mock_stream.get());



    EXPECT_EQ(result1, 0);

    EXPECT_EQ(result2, -1);

}
