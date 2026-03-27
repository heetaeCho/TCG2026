#include <gtest/gtest.h>

#include <sstream>

#include "catch2/internal/catch_jsonwriter.hpp"



class JsonArrayWriterTest_1077 : public ::testing::Test {

protected:

    std::ostringstream os;

};



TEST_F(JsonArrayWriterTest_1077, ConstructorWithIndentLevel_WritesOpeningBracket_1077) {

    Catch::JsonArrayWriter writer(os, 2);

    EXPECT_EQ("[", os.str());

}



TEST_F(JsonArrayWriterTest_1077, ConstructorWithoutIndentLevel_WritesOpeningBracket_1077) {

    Catch::JsonArrayWriter writer(os);

    EXPECT_EQ("[", os.str());

}



TEST_F(JsonArrayWriterTest_1077, WriteBoolValue_WritesBooleanAsString_1077) {

    Catch::JsonArrayWriter writer(os);

    writer.write(true).write(false);

    EXPECT_EQ("[true,false]", os.str());

}



TEST_F(JsonArrayWriterTest_1077, WriteObject_ReturnsJsonObjectWriter_1077) {

    Catch::JsonArrayWriter writer(os);

    auto objWriter = writer.writeObject();

    // This test primarily checks that the method returns an object of type JsonObjectWriter.

    // Further interaction with the returned object is out of scope for this test.

}



TEST_F(JsonArrayWriterTest_1077, WriteArray_ReturnsJsonArrayWriter_1077) {

    Catch::JsonArrayWriter writer(os);

    auto arrayWriter = writer.writeArray();

    // This test primarily checks that the method returns an object of type JsonArrayWriter.

    // Further interaction with the returned object is out of scope for this test.

}



TEST_F(JsonArrayWriterTest_1077, WriteGenericValue_WritesValueAsString_1077) {

    Catch::JsonArrayWriter writer(os);

    writer.write(42).write("test");

    EXPECT_EQ("[42,\"test\"]", os.str());

}
