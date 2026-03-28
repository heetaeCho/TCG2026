#include <gtest/gtest.h>

#include "util/logging.cc"

#include "leveldb/slice.h"



using namespace leveldb;



class EscapeStringTest_459 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(EscapeStringTest_459, NormalOperation_EmptyString_459) {

    Slice input("");

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "");

}



TEST_F(EscapeStringTest_459, NormalOperation_SimpleString_459) {

    Slice input("hello");

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "hello");

}



TEST_F(EscapeStringTest_459, BoundaryCondition_NullTerminatedString_459) {

    const char* data = "world";

    Slice input(data);

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "world");

}



TEST_F(EscapeStringTest_459, NormalOperation_StringWithSpaces_459) {

    Slice input("hello world");

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "hello\\ world");

}



TEST_F(EscapeStringTest_459, NormalOperation_StringWithSpecialChars_459) {

    Slice input("hello\tworld\n!");

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "hello\\tworld\\n\\!");

}



TEST_F(EscapeStringTest_459, BoundaryCondition_LongString_459) {

    std::string long_str(1024, 'a');

    Slice input(long_str);

    std::string result = EscapeString(input);

    EXPECT_EQ(result, long_str);

}



TEST_F(EscapeStringTest_459, ExceptionalCase_NullData_459) {

    Slice input(static_cast<const char*>(nullptr), 0);

    std::string result = EscapeString(input);

    EXPECT_EQ(result, "");

}
