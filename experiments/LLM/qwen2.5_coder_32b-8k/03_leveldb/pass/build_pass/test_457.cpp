#include <gtest/gtest.h>

#include "leveldb/slice.h"

#include "util/logging.cc"



class AppendEscapedStringToTest_457 : public ::testing::Test {

protected:

    std::string result;

};



TEST_F(AppendEscapedStringToTest_457, EmptyString_457) {

    leveldb::Slice input("");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, "");

}



TEST_F(AppendEscapedStringToTest_457, PlainText_457) {

    leveldb::Slice input("HelloWorld");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, "HelloWorld");

}



TEST_F(AppendEscapedStringToTest_457, SingleSpace_457) {

    leveldb::Slice input(" ");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, " ");

}



TEST_F(AppendEscapedStringToTest_457, SpecialCharacters_457) {

    leveldb::Slice input("\x01\x02\t\n\r");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, "\\x01\\x02\\t\\n\\r");

}



TEST_F(AppendEscapedStringToTest_457, MixedContent_457) {

    leveldb::Slice input("Hello\x01World\n!");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, "Hello\\x01World\\n!");

}



TEST_F(AppendEscapedStringToTest_457, PrintableCharacters_457) {

    leveldb::Slice input(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

}



TEST_F(AppendEscapedStringToTest_457, NonPrintableCharacters_457) {

    leveldb::Slice input("\x00\x0F\x1F\x7F");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, "\\x00\\x0f\\x1f\\x7f");

}



TEST_F(AppendEscapedStringToTest_457, LongString_457) {

    std::string long_string(1024, 'A');

    leveldb::Slice input(long_string);

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, std::string(1024, 'A'));

}



TEST_F(AppendEscapedStringToTest_457, BoundaryCharacters_457) {

    leveldb::Slice input(" ~");

    leveldb::AppendEscapedStringTo(&result, input);

    EXPECT_EQ(result, " ~");

}
