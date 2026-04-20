#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Escaper.h"

#include <sstream>



using namespace JsonBox;

using ::testing::StrictMock;



class MockStreambuf : public std::streambuf {

public:

    MOCK_METHOD2(sputn, std::streamsize(const char* s, std::streamsize n));

    MOCK_METHOD1(sputc, int(int c));

};



class EscaperTest_1 : public ::testing::Test {

protected:

    Escaper escaper;

    MockStreambuf mockDestination;

};



TEST_F(EscaperTest_1, NormalCharacterPassthrough_1) {

    EXPECT_CALL(mockDestination, sputc('a')).Times(1);

    escaper(mockDestination, 'a');

}



TEST_F(EscaperTest_1, ReverseSolidusEscaped_1) {

    EXPECT_CALL(mockDestination, sputn("\\\\", 2)).Times(1);

    escaper(mockDestination, '\\');

}



TEST_F(EscaperTest_1, BackspaceEscaped_1) {

    EXPECT_CALL(mockDestination, sputn("\\b", 2)).Times(1);

    escaper(mockDestination, '\b');

}



TEST_F(EscaperTest_1, FormFeedEscaped_1) {

    EXPECT_CALL(mockDestination, sputn("\\f", 2)).Times(1);

    escaper(mockDestination, '\f');

}



TEST_F(EscaperTest_1, LineFeedEscaped_1) {

    EXPECT_CALL(mockDestination, sputn("\\n", 2)).Times(1);

    escaper(mockDestination, '\n');

}



TEST_F(EscaperTest_1, TabEscaped_1) {

    EXPECT_CALL(mockDestination, sputn("\\t", 2)).Times(1);

    escaper(mockDestination, '\t');

}



TEST_F(EscaperTest_1, ControlCharacterEscapedToUnicode_1) {

    EXPECT_CALL(mockDestination, sputn("\\u0000", 6)).Times(1);

    escaper(mockDestination, '\0');

}



TEST_F(EscaperTest_1, StringStartEndHandling_1) {

    EXPECT_CALL(mockDestination, sputc('"')).WillOnce(testing::Return('"'));

    escaper(mockDestination, '"'); // start string

    EXPECT_CALL(mockDestination, sputn("\\\\", 2)).Times(1);

    escaper(mockDestination, '\\');

    EXPECT_CALL(mockDestination, sputc('"')).WillOnce(testing::Return('"'));

    escaper(mockDestination, '"'); // end string

}



TEST_F(EscaperTest_1, EscapeSequenceHandling_1) {

    EXPECT_CALL(mockDestination, sputc('"')).WillOnce(testing::Return('"'));

    escaper(mockDestination, '"');

    EXPECT_CALL(mockDestination, sputn("\\\\", 2)).Times(1);

    escaper(mockDestination, '\\'); // escape sequence

    EXPECT_CALL(mockDestination, sputc('\\')).WillOnce(testing::Return('\\'));

    escaper(mockDestination, '\\');

    EXPECT_CALL(mockDestination, sputc('"')).WillOnce(testing::Return('"'));

    escaper(mockDestination, '"');

}



TEST_F(EscaperTest_1, BoundaryControlCharacterEscapedToUnicode_1) {

    EXPECT_CALL(mockDestination, sputn("\\u001f", 6)).Times(1);

    escaper(mockDestination, '\x1f');

}
