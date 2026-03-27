#include <gtest/gtest.h>

#include "Lexer.h"

#include "Stream.h"

#include "Object.h"



class LexerTest : public ::testing::Test {

protected:

    XRef* xref = nullptr;

    std::unique_ptr<Stream> stream = std::make_unique<Stream>();

    Lexer lexer{xref, std::move(stream)};



    Goffset initialPosition = 0; // Assuming the initial position is 0 for simplicity

};



TEST_F(LexerTest_1459, GetPos_ReturnsCorrectInitialPosition_1459) {

    EXPECT_EQ(lexer.getPos(), initialPosition);

}



TEST_F(LexerTest_1459, SetPosAndGetPosition_Consistent_1459) {

    Goffset newPosition = 123;

    lexer.setPos(newPosition);

    EXPECT_EQ(lexer.getPos(), newPosition);

}



TEST_F(LexerTest_1459, GetPos_ReturnsMinusOneIfNotStream_1459) {

    Lexer nonStreamLexer{xref, nullptr};

    EXPECT_EQ(nonStreamLexer.getPos(), -1);

}



// Additional test cases for boundary conditions

TEST_F(LexerTest_1459, SetAndGetLargePosition_Consistent_1459) {

    Goffset largePosition = std::numeric_limits<Goffset>::max();

    lexer.setPos(largePosition);

    EXPECT_EQ(lexer.getPos(), largePosition);

}



TEST_F(LexerTest_1459, SetAndGetZeroPosition_Consistent_1459) {

    Goffset zeroPosition = 0;

    lexer.setPos(zeroPosition);

    EXPECT_EQ(lexer.getPos(), zeroPosition);

}



// Additional test cases for exceptional or error cases (if observable through the interface)

TEST_F(LexerTest_1459, SetAndGetNegativePosition_Consistent_1459) {

    Goffset negativePosition = -10;

    lexer.setPos(negativePosition);

    EXPECT_EQ(lexer.getPos(), negativePosition); // Assuming setPos allows setting to a negative value

}
