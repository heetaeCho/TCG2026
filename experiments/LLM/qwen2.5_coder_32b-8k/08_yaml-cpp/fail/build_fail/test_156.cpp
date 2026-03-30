#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "scanner.h"

#include <sstream>



using namespace YAML;



class ScannerTest_156 : public ::testing::Test {

protected:

    std::istringstream inputStream;

    Scanner scanner;



    ScannerTest_156() : inputStream(""), scanner(inputStream) {}

};



TEST_F(ScannerTest_156, MarkInitiallyValid_156) {

    Mark mark = scanner.mark();

    EXPECT_TRUE(mark.valid);

}



TEST_F(ScannerTest_156, EmptyStreamReturnsEmptyMark_156) {

    Mark mark = scanner.mark();

    EXPECT_EQ(mark.index, 0);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(ScannerTest_156, NonEmptyStreamMarkUpdatesCorrectly_156) {

    inputStream.str("test\nstring");

    scanner.peek(); // Read first character to update mark

    Mark mark = scanner.mark();

    EXPECT_EQ(mark.index, 1);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 1);



    scanner.get(); // Move to next character

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 2);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 2);



    scanner.eat(3); // Eat "st\n"

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 6);

    EXPECT_EQ(mark.line, 1);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(ScannerTest_156, MarkDoesNotChangeOnEmptyStreamGet_156) {

    Mark initialMark = scanner.mark();

    char ch = scanner.get(); // Try to get character from empty stream

    EXPECT_EQ(ch, Stream::eof());

    Mark finalMark = scanner.mark();

    EXPECT_TRUE(initialMark == finalMark);

}



TEST_F(ScannerTest_156, MarkDoesNotChangeOnEmptyStreamPeek_156) {

    Mark initialMark = scanner.mark();

    char ch = scanner.peek(); // Peek at character from empty stream

    EXPECT_EQ(ch, Stream::eof());

    Mark finalMark = scanner.mark();

    EXPECT_TRUE(initialMark == finalMark);

}



TEST_F(ScannerTest_156, MarkUpdatesWithStreamPositionChanges_156) {

    inputStream.str("Hello World");

    scanner.get(); // Read 'H'

    Mark mark = scanner.mark();

    EXPECT_EQ(mark.index, 1);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 1);



    scanner.eat(4); // Eat "ello"

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 5);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 5);



    scanner.peek(); // Peek at ' '

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 5);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 5);



    scanner.get(); // Read ' '

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 6);

    EXPECT_EQ(mark.line, 0);

    EXPECT_EQ(mark.column, 6);

}



TEST_F(ScannerTest_156, MarkUpdatesWithNewLinesCorrectly_156) {

    inputStream.str("Line1\nLine2");

    scanner.eat(6); // Eat "Line1\n"

    Mark mark = scanner.mark();

    EXPECT_EQ(mark.index, 6);

    EXPECT_EQ(mark.line, 1);

    EXPECT_EQ(mark.column, 0);



    scanner.get(); // Read 'L'

    mark = scanner.mark();

    EXPECT_EQ(mark.index, 7);

    EXPECT_EQ(mark.line, 1);

    EXPECT_EQ(mark.column, 1);

}
