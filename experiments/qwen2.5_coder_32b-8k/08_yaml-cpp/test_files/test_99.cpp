#include <gtest/gtest.h>

#include "streamcharsource.h"



// Mock Stream class for testing purposes

class MockStream {

public:

    MOCK_METHOD(bool, operator bool, (), (const));

    MOCK_CONST_METHOD1(operator[], char, (std::size_t i));

};



namespace YAML {



TEST_F(StreamCharSourceTest_99, DefaultConstructor_99) {

    MockStream mockStream;

    StreamCharSource source(mockStream);

    EXPECT_TRUE(static_cast<bool>(source)); // Assuming default constructed stream is valid

}



TEST_F(StreamCharSourceTest_99, CopyConstructor_99) {

    MockStream mockStream;

    StreamCharSource original(mockStream);

    StreamCharSource copy(original);

    EXPECT_EQ(static_cast<bool>(original), static_cast<bool>(copy));

}



TEST_F(StreamCharSourceTest_99, MoveConstructor_99) {

    MockStream mockStream;

    StreamCharSource original(mockStream);

    StreamCharSource moved(std::move(original));

    EXPECT_TRUE(static_cast<bool>(moved)); // Assuming move doesn't invalidate the object

}



TEST_F(StreamCharSourceTest_99, BoolOperatorTrue_99) {

    MockStream mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(::testing::Return(true));

    StreamCharSource source(mockStream);

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_99, BoolOperatorFalse_99) {

    MockStream mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(::testing::Return(false));

    StreamCharSource source(mockStream);

    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_99, NotOperatorTrue_99) {

    MockStream mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(::testing::Return(true));

    StreamCharSource source(mockStream);

    EXPECT_FALSE(!source);

}



TEST_F(StreamCharSourceTest_99, NotOperatorFalse_99) {

    MockStream mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(::testing::Return(false));

    StreamCharSource source(mockStream);

    EXPECT_TRUE(!source);

}



TEST_F(StreamCharSourceTest_99, IndexOperator_99) {

    MockStream mockStream;

    char expectedChar = 'a';

    ON_CALL(mockStream, operator[](0)).WillByDefault(::testing::Return(expectedChar));

    StreamCharSource source(mockStream);

    EXPECT_EQ(source[0], expectedChar);

}



TEST_F(StreamCharSourceTest_99, PlusOperator_99) {

    MockStream mockStream;

    char expectedChar = 'b';

    ON_CALL(mockStream, operator[](1)).WillByDefault(::testing::Return(expectedChar));

    StreamCharSource source(mockStream);

    EXPECT_EQ((source + 1)[0], expectedChar);

}



} // namespace YAML
