#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class JsonObjectWriterTest_530 : public ::testing::Test {

protected:

    std::ostringstream os;

    JsonObjectWriter writer;

    

    JsonObjectWriterTest_530() : writer(os) {}

};



TEST_F(JsonObjectWriterTest_530, WriteAppendsKeyWithColon_530) {

    StringRef key("testKey");

    writer.write(key);

    EXPECT_THAT(os.str(), HasSubstr("\"testKey\": "));

}



TEST_F(JsonObjectWriterTest_530, WriteHandlesMultipleKeys_530) {

    StringRef key1("key1");

    StringRef key2("key2");

    writer.write(key1);

    writer.write(key2);

    EXPECT_THAT(os.str(), HasSubstr("\"key1\": \",\n\"key2\": "));

}



TEST_F(JsonObjectWriterTest_530, WriteHandlesEmptyKey_530) {

    StringRef key("");

    writer.write(key);

    EXPECT_THAT(os.str(), HasSubstr("\"\": "));

}



TEST_F(JsonObjectWriterTest_530, WriteHandlesLargeIndentLevel_530) {

    JsonObjectWriter largeIndentWriter(os, 10);

    StringRef key("testKey");

    largeIndentWriter.write(key);

    // Assuming indent level affects the output formatting

    EXPECT_THAT(os.str(), HasSubstr("\"testKey\": "));

}



TEST_F(JsonObjectWriterTest_530, WriteWithNonEmptyStream_530) {

    os << "Existing content\n";

    StringRef key("testKey");

    writer.write(key);

    EXPECT_THAT(os.str(), HasSubstr("Existing content\n\"testKey\": "));

}
