#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "scanner.h"



namespace YAML {

    class MockScanner : public Scanner {

    public:

        using Scanner::Scanner;

        MOCK_METHOD0(empty, bool());

        MOCK_METHOD0(peek, Token&());

        MOCK_CONST_METHOD0(mark, Mark());

    };

}



using namespace YAML;



class ScannerTest_154 : public ::testing::Test {

protected:

    std::istringstream inputStream;

    MockScanner scanner;



    ScannerTest_154() : inputStream(""), scanner(inputStream) {}

};



TEST_F(ScannerTest_154, PopOnEmptyQueue_DoesNothing_154) {

    EXPECT_CALL(scanner, empty()).WillOnce(::testing::Return(true));

    scanner.pop();

}



TEST_F(ScannerTest_154, PopReducesTokenCount_154) {

    Token dummyToken;

    std::queue<Token> tokens;

    tokens.push(dummyToken);



    EXPECT_CALL(scanner, empty()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));

    scanner.pop();

}



TEST_F(ScannerTest_154, PopMultipleTimes_DecreasesQueueSize_154) {

    Token dummyToken1, dummyToken2;

    std::queue<Token> tokens;

    tokens.push(dummyToken1);

    tokens.push(dummyToken2);



    EXPECT_CALL(scanner, empty()).WillOnce(::testing::Return(false))

                                  .WillOnce(::testing::Return(false))

                                  .WillOnce(::testing::Return(true));

    scanner.pop();

    scanner.pop();

}



TEST_F(ScannerTest_154, PopDoesNotThrowException_154) {

    EXPECT_NO_THROW(scanner.pop());

}
