#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/parser.h>

#include <sstream>



namespace YAML {

    class MockScanner : public Scanner {

    public:

        MOCK_METHOD(bool, empty, (), (override));

        MOCK_METHOD(void, pop, (), (override));

        MOCK_METHOD(Token&, peek, (), (override));

        MOCK_METHOD(Mark, mark, (), (const, override));



        using Scanner::Scanner;

    };

}



using namespace YAML;



class ParserTest_507 : public ::testing::Test {

protected:

    std::unique_ptr<MockScanner> mockScanner;

    Parser parser;



    void SetUp() override {

        mockScanner = std::make_unique<MockScanner>(std::istringstream(""));

        parser.m_pScanner = std::move(mockScanner);

    }

};



TEST_F(ParserTest_507, PrintTokens_EmptyScanner_507) {

    EXPECT_CALL(*mockScanner, empty()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockScanner, pop).Times(0);

    EXPECT_CALL(*mockScanner, peek).Times(0);



    std::ostringstream out;

    parser.PrintTokens(out);

    EXPECT_EQ(out.str(), "");

}



TEST_F(ParserTest_507, PrintTokens_OneToken_507) {

    Token token;

    EXPECT_CALL(*mockScanner, empty()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockScanner, pop).Times(1);

    EXPECT_CALL(*mockScanner, peek()).WillOnce(::testing::ReturnRef(token));



    std::ostringstream out;

    parser.PrintTokens(out);

    // Assuming Token has a valid stream insertion operator that outputs something.

    EXPECT_NE(out.str(), "");

}



TEST_F(ParserTest_507, PrintTokens_MultipleTokens_507) {

    Token token1, token2;

    EXPECT_CALL(*mockScanner, empty()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(false))

                                     .WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockScanner, pop).Times(2);

    EXPECT_CALL(*mockScanner, peek()).WillOnce(::testing::ReturnRef(token1)).WillOnce(::testing::ReturnRef(token2));



    std::ostringstream out;

    parser.PrintTokens(out);

    // Assuming Token has a valid stream insertion operator that outputs something.

    EXPECT_TRUE(out.str().size() > 0); // Multiple tokens should result in non-empty output

}



TEST_F(ParserTest_507, PrintTokens_ExceptionDuringPop_507) {

    Token token;

    EXPECT_CALL(*mockScanner, empty()).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockScanner, pop).WillOnce([]() { throw std::runtime_error("Simulated exception"); });

    EXPECT_CALL(*mockScanner, peek()).WillOnce(::testing::ReturnRef(token));



    std::ostringstream out;

    EXPECT_THROW(parser.PrintTokens(out), std::runtime_error);

}
