#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;



class JsonObjectWriterTest_1076 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(JsonObjectWriterTest_1076, ConstructorWithStream_1076) {

    JsonObjectWriter writer(oss);

}



TEST_F(JsonObjectWriterTest_1076, ConstructorWithStreamAndIndentLevel_1076) {

    JsonObjectWriter writer(oss, 2);

}



TEST_F(JsonObjectWriterTest_1076, MoveConstructor_1076) {

    JsonObjectWriter original(oss);

    JsonObjectWriter moved(std::move(original));

}



TEST_F(JsonObjectWriterTest_1076, WriteMethod_ReturnsJsonValueWriter_1076) {

    JsonObjectWriter writer(oss);

    JsonValueWriter valueWriter = writer.write("key");

}



TEST_F(JsonObjectWriterTest_1076, MoveAssignmentOperatorDeleted_1076) {

    JsonObjectWriter original(oss);

    JsonObjectWriter other(oss);

    EXPECT_FALSE((std::is_assignable<JsonObjectWriter&, JsonObjectWriter&&>::value));

}
