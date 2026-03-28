#include <gtest/gtest.h>

#include "poppler/Parser.h"

#include "gmock/gmock.h"



using namespace testing;



class MockLexer : public Lexer {

public:

    MOCK_METHOD(Goffset, getPos, (), (const, override));

};



TEST_F(ParserTest_1464, GetPos_ReturnsCurrentPosition_1464) {

    MockLexer mockLexer(nullptr, std::unique_ptr<Stream>(nullptr), false);

    Parser parser(nullptr, std::move(mockLexer), true);



    EXPECT_CALL(mockLexer, getPos()).WillOnce(Return(1024));

    Goffset pos = parser.getPos();



    EXPECT_EQ(pos, 1024);

}



TEST_F(ParserTest_1464, GetPos_ReturnsZeroWhenLexerPositionIsZero_1464) {

    MockLexer mockLexer(nullptr, std::unique_ptr<Stream>(nullptr), false);

    Parser parser(nullptr, std::move(mockLexer), true);



    EXPECT_CALL(mockLexer, getPos()).WillOnce(Return(0));

    Goffset pos = parser.getPos();



    EXPECT_EQ(pos, 0);

}



TEST_F(ParserTest_1464, GetPos_ReturnsLargePositionValue_1464) {

    MockLexer mockLexer(nullptr, std::unique_ptr<Stream>(nullptr), false);

    Parser parser(nullptr, std::move(mockLexer), true);



    EXPECT_CALL(mockLexer, getPos()).WillOnce(Return(9223372036854775807));

    Goffset pos = parser.getPos();



    EXPECT_EQ(pos, 9223372036854775807);

}
