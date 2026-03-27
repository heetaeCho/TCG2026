#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;



class JsonValueWriterTest_525 : public ::testing::Test {

protected:

    std::ostringstream os;

    JsonValueWriter writer;



    JsonValueWriterTest_525() : writer(os) {}

};



TEST_F(JsonValueWriterTest_525, WriteString_SimpleString_525) {

    writer.write("test");

    EXPECT_EQ(os.str(), "\"test\"");

}



TEST_F(JsonValueWriterTest_525, WriteBool_True_525) {

    writer.write(true);

    EXPECT_EQ(os.str(), "true");

}



TEST_F(JsonValueWriterTest_525, WriteBool_False_525) {

    writer.write(false);

    EXPECT_EQ(os.str(), "false");

}



TEST_F(JsonValueWriterTest_525, WriteString_EmptyString_525) {

    writer.write("");

    EXPECT_EQ(os.str(), "\"\"");

}



TEST_F(JsonValueWriterTest_525, WriteObject_ReturnsJsonObjectWriter_525) {

    auto objWriter = writer.writeObject();

    (void)objWriter; // Just to make sure the function returns something

}



TEST_F(JsonValueWriterTest_525, WriteArray_ReturnsJsonArrayWriter_525) {

    auto arrWriter = writer.writeArray();

    (void)arrWriter; // Just to make sure the function returns something

}



// Assuming that writeImpl is called internally and we can't directly test it,

// but we can infer its behavior through the observable output.



TEST_F(JsonValueWriterTest_525, WriteStringWithSpaces_StringWithSpaces_525) {

    writer.write("test string");

    EXPECT_EQ(os.str(), "\"test string\"");

}



TEST_F(JsonValueWriterTest_525, WriteStringWithQuotes_StringWithEscapedQuotes_525) {

    writer.write("test \"string\"");

    EXPECT_EQ(os.str(), "\"test \\\"string\\\"\"");

}
