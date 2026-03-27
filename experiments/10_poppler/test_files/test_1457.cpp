#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Lexer.h"

#include <gmock/gmock.h>



using ::testing::_;

using ::testing::NiceMock;



class MockStream : public Stream {

public:

    MOCK_METHOD(void, reset, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

};



class LexerTest_1457 : public ::testing::Test {

protected:

    XRef* mockXref = nullptr;

    std::unique_ptr<NiceMock<MockStream>> mockStreamPtr;

    Lexer* lexer;



    void SetUp() override {

        mockXref = new XRef();

        mockStreamPtr = std::make_unique<NiceMock<MockStream>>();

        lexer = new Lexer(mockXref, std::move(mockStreamPtr));

    }



    void TearDown() override {

        delete lexer;

        delete mockXref;

    }

};



TEST_F(LexerTest_1457, SkipCharCallsGetChar_1457) {

    EXPECT_CALL(*mockStreamPtr.get(), getChar()).Times(1);

    lexer->skipChar();

}



// Boundary conditions and exceptional cases are not directly observable from the given interface

// as there is no error handling or specific boundary conditions mentioned. However, we can still add

// tests for normal operations and external interactions.



TEST_F(LexerTest_1457, GetPosReturnsValidOffset_1457) {

    Goffset pos = lexer->getPos();

    // Assuming getPos() returns a valid offset without side effects

    EXPECT_GE(pos, 0);

}



TEST_F(LexerTest_1457, SetAndGetPosWorksConsistently_1457) {

    Goffset newPos = 10;

    lexer->setPos(newPos);

    Goffset retrievedPos = lexer->getPos();

    EXPECT_EQ(retrievedPos, newPos);

}



TEST_F(LexerTest_1457, GetStreamReturnsNonNull_1457) {

    Stream* stream = lexer->getStream();

    EXPECT_NE(stream, nullptr);

}
