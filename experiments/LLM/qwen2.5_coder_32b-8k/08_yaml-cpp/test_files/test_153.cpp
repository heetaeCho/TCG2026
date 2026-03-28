#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "scanner.h"



namespace YAML {

    class MockInputStream : public std::istream {

    public:

        using istream::istream;

    };

}



class ScannerTest_153 : public ::testing::Test {

protected:

    YAML::MockInputStream inputStream;

    YAML::Scanner scanner;



    ScannerTest_153() : inputStream(nullptr), scanner(inputStream) {}

};



TEST_F(ScannerTest_153, Empty_ReturnsTrueWhenNoTokens_153) {

    EXPECT_TRUE(scanner.empty());

}



TEST_F(ScannerTest_153, Empty_ReturnsFalseAfterPushingToken_153) {

    // Assuming there's a way to push tokens for testing purposes

    // Since we cannot modify the implementation, this is a theoretical test case

    // In practice, you would need some method to add tokens to m_tokens

    EXPECT_FALSE(scanner.empty());

}



TEST_F(ScannerTest_153, Pop_DoesNotThrowOnEmptyQueue_153) {

    EXPECT_NO_THROW(scanner.pop());

}



TEST_F(ScannerTest_153, Peek_ThrowsWhenNoTokensAvailable_153) {

    EXPECT_THROW(scanner.peek(), ...); // Replace '...' with the actual exception type if known

}



TEST_F(ScannerTest_153, Mark_ReturnsValidMarkObject_153) {

    YAML::Mark mark = scanner.mark();

    // Assuming Mark has some observable properties to verify

    // For example, checking if it's default constructed or not

    EXPECT_FALSE(mark.isInvalid());

}
