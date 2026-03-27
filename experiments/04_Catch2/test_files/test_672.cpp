#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class ParserTest_672 : public ::testing::Test {

protected:

    Parser parser;

};



TEST_F(ParserTest_672, ParseEmptyTokenStream_672) {

    std::string exeName = "test";

    TokenStream tokens;

    auto result = parser.parse(exeName, tokens);

    EXPECT_TRUE(result);

    EXPECT_EQ(result.value().type(), ParseResultType::NoMatch);

}



TEST_F(ParserTest_672, ParseWithSingleToken_672) {

    std::string exeName = "test";

    Token token{TokenType::Unknown, StringRef{"token"}};

    TokenStream tokens{std::vector<Token>{token}};

    auto result = parser.parse(exeName, tokens);

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "Unrecognised token: token");

}



TEST_F(ParserTest_672, ParseWithMultipleTokens_672) {

    std::string exeName = "test";

    Token token1{TokenType::Unknown, StringRef{"token1"}};

    Token token2{TokenType::Unknown, StringRef{"token2"}};

    TokenStream tokens{std::vector<Token>{token1, token2}};

    auto result = parser.parse(exeName, tokens);

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "Unrecognised token: token1");

}



TEST_F(ParserTest_672, ParseShortCircuitAll_672) {

    class MockParser : public ParserBase {

    public:

        MOCK_CONST_METHOD2(parse, InternalParseResult(const std::string&, TokenStream));

        MOCK_CONST_METHOD0(cardinality, size_t());

    };

    

    auto mockParser = std::make_unique<MockParser>();

    EXPECT_CALL(*mockParser, cardinality()).WillRepeatedly(::testing::Return(1));

    EXPECT_CALL(*mockParser, parse(::testing::_, ::testing::_))

        .WillOnce([](const std::string&, TokenStream) {

            return InternalParseResult::ok(ParseState{ParseResultType::ShortCircuitAll, TokenStream{}});

        });



    parser.m_options.push_back(std::move(*mockParser));



    std::string exeName = "test";

    Token token1{TokenType::Unknown, StringRef{"token1"}};

    TokenStream tokens{std::vector<Token>{token1}};

    auto result = parser.parse(exeName, tokens);

    EXPECT_TRUE(result);

    EXPECT_EQ(result.value().type(), ParseResultType::ShortCircuitAll);

}



TEST_F(ParserTest_672, ParseWithMatchingToken_672) {

    class MockParser : public ParserBase {

    public:

        MOCK_CONST_METHOD2(parse, InternalParseResult(const std::string&, TokenStream));

        MOCK_CONST_METHOD0(cardinality, size_t());

    };

    

    auto mockParser = std::make_unique<MockParser>();

    EXPECT_CALL(*mockParser, cardinality()).WillRepeatedly(::testing::Return(1));

    EXPECT_CALL(*mockParser, parse(::testing::_, ::testing::_))

        .WillOnce([](const std::string&, TokenStream) {

            return InternalParseResult::ok(ParseState{ParseResultType::Matched, TokenStream{}});

        });



    parser.m_options.push_back(std::move(*mockParser));



    std::string exeName = "test";

    Token token1{TokenType::Unknown, StringRef{"token1"}};

    TokenStream tokens{std::vector<Token>{token1}};

    auto result = parser.parse(exeName, tokens);

    EXPECT_TRUE(result);

    EXPECT_EQ(result.value().type(), ParseResultType::Matched);

}



TEST_F(ParserTest_672, ParseWithUnmatchedTokens_672) {

    class MockParser : public ParserBase {

    public:

        MOCK_CONST_METHOD2(parse, InternalParseResult(const std::string&, TokenStream));

        MOCK_CONST_METHOD0(cardinality, size_t());

    };

    

    auto mockParser = std::make_unique<MockParser>();

    EXPECT_CALL(*mockParser, cardinality()).WillRepeatedly(::testing::Return(1));

    EXPECT_CALL(*mockParser, parse(::testing::_, ::testing::_))

        .WillOnce([](const std::string&, TokenStream) {

            return InternalParseResult::ok(ParseState{ParseResultType::NoMatch, TokenStream{}});

        });



    parser.m_options.push_back(std::move(*mockParser));



    std::string exeName = "test";

    Token token1{TokenType::Unknown, StringRef{"token1"}};

    TokenStream tokens{std::vector<Token>{token1}};

    auto result = parser.parse(exeName, tokens);

    EXPECT_FALSE(result);

    EXPECT_EQ(result.errorMessage(), "Unrecognised token: token1");

}
