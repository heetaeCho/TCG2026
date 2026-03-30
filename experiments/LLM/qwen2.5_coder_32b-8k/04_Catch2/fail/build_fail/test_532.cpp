#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/Catch2/src/catch2/internal/catch_jsonwriter.hpp"



using namespace Catch;

using namespace testing;



class JsonArrayWriterTest_532 : public Test {

protected:

    std::ostringstream os;

    JsonArrayWriter writer;



    JsonArrayWriterTest_532() : writer(os) {}

};



TEST_F(JsonArrayWriterTest_532, WriteObjectAppendsCommaNewlineOnce_532) {

    bool should_comma = false;

    EXPECT_CALL(mockJsonUtils, appendCommaNewline(Ref(os), Ref(should_comma), Eq(1))).Times(1);



    writer.writeObject();

}



TEST_F(JsonArrayWriterTest_532, WriteObjectReturnsJsonObjectWriterWithCorrectIndentLevel_532) {

    JsonObjectWriter objectWriter = writer.writeObject();



    EXPECT_EQ(objectWriter.getIndentLevel(), 1);

}



TEST_F(JsonArrayWriterTest_532, WriteObjectUsesProvidedOutputStream_532) {

    writer.writeObject();

    std::string expectedOutput = ",\n"; // Assuming m_should_comma is true and m_indent_level is 0

    EXPECT_EQ(os.str(), expectedOutput);

}



TEST_F(JsonArrayWriterTest_532, WriteObjectHandlesMultipleCallsConsistently_532) {

    writer.writeObject();

    writer.writeObject();



    std::string expectedOutput = ",\n,\n";

    EXPECT_EQ(os.str(), expectedOutput);

}
