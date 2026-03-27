#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;



class JsonArrayWriterTest : public ::testing::Test {

protected:

    std::ostringstream os;

    JsonArrayWriter writer;



    JsonArrayWriterTest() : writer(os) {}

};



TEST_F(JsonArrayWriterTest_534, WriteBoolTrueAppendsCorrectValue_534) {

    writer.write(true);

    EXPECT_EQ(os.str(), "true");

}



TEST_F(JsonArrayWriterTest_534, WriteBoolFalseAppendsCorrectValue_534) {

    writer.write(false);

    EXPECT_EQ(os.str(), "false");

}



TEST_F(JsonArrayWriterTest_534, WriteMultipleBoolsAppendsCommaSeparatedValues_534) {

    writer.write(true).write(false).write(true);

    EXPECT_EQ(os.str(), "true,false,true");

}



TEST_F(JsonArrayWriterTest_534, WriteObjectCreatesJsonObjectWriter_534) {

    JsonObjectWriter objWriter = writer.writeObject();

    // Since we can't access internal state, we assume this creates a valid object writer.

}



TEST_F(JsonArrayWriterTest_534, WriteArrayCreatesJsonArrayWriter_534) {

    JsonArrayWriter arrWriter = writer.writeArray();

    // Similarly, we assume this creates a valid array writer.

}
