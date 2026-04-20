#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <sstream>

using namespace JsonBox;

class ValueTest_65 : public ::testing::Test {
protected:
    // You can add any setup or teardown code here if needed.
};

TEST_F(ValueTest_65, WriteToStream_String_Normal_65) {
    Value value("testString");
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("\"testString\"", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Integer_Normal_65) {
    Value value(12345);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("12345", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Double_Normal_65) {
    Value value(123.456);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("123.456", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Boolean_True_Normal_65) {
    Value value(true);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("true", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Boolean_False_Normal_65) {
    Value value(false);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("false", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Null_Normal_65) {
    Value value;
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("null", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Object_Normal_65) {
    Object obj = {{"key1", "value1"}, {"key2", 42}};
    Value value(obj);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("{\"key1\":\"value1\",\"key2\":42}", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_Array_Normal_65) {
    Array arr = {"item1", 100};
    Value value(arr);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("[\"item1\",100]", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_String_EscapeAll_65) {
    Value value("test\nstring\twith\"quotes");
    std::ostringstream stream;
    value.writeToStream(stream, false, true);
    EXPECT_EQ("\"test\\nstring\\twith\\\"quotes\"", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_EmptyString_Normal_65) {
    Value value("");
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("\"\"", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_EmptyObject_Normal_65) {
    Object obj;
    Value value(obj);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("{}", stream.str());
}

TEST_F(ValueTest_65, WriteToStream_EmptyArray_Normal_65) {
    Array arr;
    Value value(arr);
    std::ostringstream stream;
    value.writeToStream(stream, false, false);
    EXPECT_EQ("[]", stream.str());
}