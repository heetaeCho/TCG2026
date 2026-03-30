#include <gtest/gtest.h>

#include "stream.h"

#include <sstream>



using namespace YAML;



TEST_F(StreamTest_679, ConstructorWithValidUtf8Input_679) {

    std::istringstream input("Hello, world!");

    Stream stream(input);

    EXPECT_TRUE(static_cast<bool>(stream));

}



TEST_F(StreamTest_679, ConstructorWithEmptyInput_679) {

    std::istringstream input("");

    Stream stream(input);

    EXPECT_FALSE(static_cast<bool>(stream));

}



TEST_F(StreamTest_679, ConstructorWithInvalidInput_679) {

    std::istringstream input("\xFF");

    Stream stream(input);

    EXPECT_TRUE(static_cast<bool>(stream)); // Even invalid input should not make the stream false

}



TEST_F(StreamTest_679, PeekAtStartOfStream_679) {

    std::istringstream input("Hello");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, GetSingleCharacterFromStream_679) {

    std::istringstream input("Hello");

    Stream stream(input);

    EXPECT_EQ(stream.get(), 'H');

}



TEST_F(StreamTest_679, GetMultipleCharactersFromStream_679) {

    std::istringstream input("Hello");

    Stream stream(input);

    EXPECT_EQ(stream.get(2), "He");

}



TEST_F(StreamTest_679, EatSingleCharacterFromStream_679) {

    std::istringstream input("Hello");

    Stream stream(input);

    stream.eat(1);

    EXPECT_EQ(stream.peek(), 'e');

}



TEST_F(StreamTest_679, EatMultipleCharactersFromStream_679) {

    std::istringstream input("Hello");

    Stream stream(input);

    stream.eat(2);

    EXPECT_EQ(stream.peek(), 'l');

}



TEST_F(StreamTest_679, EatMoreThanAvailableCharacters_679) {

    std::istringstream input("Hi");

    Stream stream(input);

    stream.eat(10); // More than the length of "Hi"

    EXPECT_FALSE(static_cast<bool>(stream));

}



TEST_F(StreamTest_679, StreamWithUtf8Bom_679) {

    std::istringstream input("\xEF\xBB\xBFHello");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, StreamWithUtf16LeBom_679) {

    std::istringstream input("\xFF\xFEH\x00e\x00l\x00l\x00o\x00");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, StreamWithUtf16BeBom_679) {

    std::istringstream input("\xFE\xFF\x00H\x00e\x00l\x00l\x00o");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, StreamWithUtf32LeBom_679) {

    std::istringstream input("\xFF\xFE\x00\x00H\x00\x00\x00e\x00\x00\x00l\x00\x00\x00l\x00\x00\x00o\x00\x00\x00");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, StreamWithUtf32BeBom_679) {

    std::istringstream input("\x00\x00\xFE\xFF\x00\x00\x00H\x00\x00\x00e\x00\x00\x00l\x00\x00\x00l\x00\x00\x00o");

    Stream stream(input);

    EXPECT_EQ(stream.peek(), 'H');

}



TEST_F(StreamTest_679, StreamWithInvalidBom_679) {

    std::istringstream input("\xFE\xFF\xFF\xFEHello"); // Invalid BOM

    Stream stream(input);

    EXPECT_TRUE(static_cast<bool>(stream)); // Even invalid BOM should not make the stream false

}
