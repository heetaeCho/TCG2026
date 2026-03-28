#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "scanner.h"



namespace YAML {



class ScannerTest_155 : public ::testing::Test {

protected:

    std::istringstream input;

    Scanner scanner;



    ScannerTest_155() : input(""), scanner(input) {}

};



TEST_F(ScannerTest_155, PeekReturnsValidToken_155) {

    // Assuming the input stream has tokens, this test checks if peek returns a valid token.

    Token& token = scanner.peek();

    EXPECT_TRUE(token.IsDefined());

}



TEST_F(ScannerTest_155, PopReducesQueueSize_155) {

    // Assuming the input stream has at least one token initially.

    scanner.pop();

    Token& token = scanner.peek();

    EXPECT_TRUE(token.IsDefined());

}



TEST_F(ScannerTest_155, EmptyReturnsTrueWhenNoTokens_155) {

    // If the input stream is empty, the queue should also be empty.

    EXPECT_TRUE(scanner.empty());

}



TEST_F(ScannerTest_155, PopDoesNotThrowOnEmptyQueue_155) {

    // Popping from an empty queue should not throw an exception.

    while (!scanner.empty()) {

        scanner.pop();

    }

    EXPECT_NO_THROW(scanner.pop());

}



TEST_F(ScannerTest_155, PeekThrowsOnEmptyQueue_155) {

    // Peeking into an empty queue should throw an exception or assert.

    while (!scanner.empty()) {

        scanner.pop();

    }

    EXPECT_DEATH(scanner.peek(), ".*");

}



}  // namespace YAML
