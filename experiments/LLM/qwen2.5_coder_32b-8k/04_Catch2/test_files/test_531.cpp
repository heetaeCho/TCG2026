#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/Catch2/src/catch2/internal/catch_jsonwriter.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class JsonArrayWriterTest_531 : public ::testing::Test {

protected:

    std::ostringstream os;

};



TEST_F(JsonArrayWriterTest_531, ConstructorWithStream_531) {

    JsonArrayWriter writer(os);

}



TEST_F(JsonArrayWriterTest_531, ConstructorWithStreamAndIndentLevel_531) {

    JsonArrayWriter writer(os, 2);

}



TEST_F(JsonArrayWriterTest_531, MoveConstructor_531) {

    JsonArrayWriter original(os);

    JsonArrayWriter moved(std::move(original));

}



TEST_F(JsonArrayWriterTest_531, DestructorWithoutActiveFlag_531) {

    JsonArrayWriter writer(os);

    writer.m_active = false;

}



TEST_F(JsonArrayWriterTest_531, DestructorWithActiveFlag_531) {

    JsonArrayWriter writer(os);

    writer.m_active = true;

}



TEST_F(JsonArrayWriterTest_531, WriteBoolValueTrue_531) {

    JsonArrayWriter writer(os);

    writer.write(true);

    EXPECT_THAT(os.str(), HasSubstr("true"));

}



TEST_F(JsonArrayWriterTest_531, WriteBoolValueFalse_531) {

    JsonArrayWriter writer(os);

    writer.write(false);

    EXPECT_THAT(os.str(), HasSubstr("false"));

}



TEST_F(JsonArrayWriterTest_531, WriteObject_531) {

    JsonArrayWriter writer(os);

    JsonObjectWriter objWriter = writer.writeObject();

}



TEST_F(JsonArrayWriterTest_531, WriteArray_531) {

    JsonArrayWriter writer(os);

    JsonArrayWriter arrWriter = writer.writeArray();

}
