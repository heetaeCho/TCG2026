#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Lexer.h"

#include "Stream.h"



using ::testing::NiceMock;

using ::testing::StrictMock;



class MockStream : public Stream {

public:

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

};



class LexerTest_1460 : public ::testing::Test {

protected:

    XRef* xref = nullptr; // Assuming XRef is a valid pointer in the actual usage

    std::unique_ptr<MockStream> mockStream;

    Lexer lexer;



    LexerTest_1460() : mockStream(std::make_unique<NiceMock<MockStream>>()), lexer(xref, std::move(mockStream)) {}



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(LexerTest_1460, SetPos_PosIsSetOnStream_1460) {

    Goffset testPosition = 5;

    EXPECT_CALL(*mockStream, setPos(testPosition, 0)).Times(1);

    lexer.setPos(testPosition);

}



TEST_F(LexerTest_1460, SetPos_StreamIsNull_NothingHappens_1460) {

    lexer.curStr.setToNull();

    Goffset testPosition = 5;

    EXPECT_CALL(*mockStream, setPos(testPosition, 0)).Times(0);

    lexer.setPos(testPosition);

}



TEST_F(LexerTest_1460, SetPos_StreamIsNotAStream_NothingHappens_1460) {

    lexer.curStr = Object(ObjType::objName); // Assuming objName is not a stream type

    Goffset testPosition = 5;

    EXPECT_CALL(*mockStream, setPos(testPosition, 0)).Times(0);

    lexer.setPos(testPosition);

}
