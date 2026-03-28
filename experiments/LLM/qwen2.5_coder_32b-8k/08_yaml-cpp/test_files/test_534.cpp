#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_534 : public ::testing::Test {

protected:

    std::ostringstream output;

    Emitter emitter{output};

};



TEST_F(EmitterTest_534, WriteIncreasesSize_534) {

    std::size_t initialSize = emitter.size();

    const char* testString = "test";

    emitter.Write(testString, strlen(testString));

    EXPECT_GT(emitter.size(), initialSize);

}



TEST_F(EmitterTest_534, WritePlainText_534) {

    const char* testString = "plain_text";

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), testString);

}



TEST_F(EmitterTest_534, WriteSingleQuotedText_534) {

    const char* testString = "single_quoted";

    emitter.SetStringFormat(SingleQuoted);

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), "'single_quoted'");

}



TEST_F(EmitterTest_534, WriteDoubleQuotedText_534) {

    const char* testString = "double_quoted";

    emitter.SetStringFormat(DoubleQuoted);

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), "\"double_quoted\"");

}



TEST_F(EmitterTest_534, WriteLiteralTextShort_534) {

    const char* testString = "literal_text\nshort";

    emitter.SetStringFormat(Literal);

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), "|-\nliteral_text\nshort");

}



TEST_F(EmitterTest_534, WriteLiteralTextLong_534) {

    const char* testString = "a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long";

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), "|-\na_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long_a_long_string_that_needs_to_be_written_in_literal_format_because_it_is_more_than_one_kilobyte_long");

}



TEST_F(EmitterTest_534, WriteEmptyString_534) {

    const char* testString = "";

    emitter.Write(testString, strlen(testString));

    EXPECT_EQ(output.str(), "");

}



TEST_F(EmitterTest_534, WriteNullStream_534) {

    Emitter nullEmitter;

    const char* testString = "test";

    nullEmitter.Write(testString, strlen(testString));

    EXPECT_FALSE(nullEmitter.good());

}
