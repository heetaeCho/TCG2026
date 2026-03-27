#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class JsonObjectWriterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    JsonObjectWriter writer;

    JsonObjectWriterTest() : writer(oss) {}

};



TEST_F(JsonObjectWriterTest_529, DestructorWritesClosingBraceWhenActive_529) {

    // Arrange

    writer.~JsonObjectWriter();



    // Assert

    EXPECT_EQ("}\n", oss.str());

}



TEST_F(JsonObjectWriterTest_529, DestructorDoesNotWriteWhenInactive_529) {

    // Arrange

    JsonObjectWriter inactive_writer(oss);

    inactive_writer.m_active = false;

    inactive_writer.~JsonObjectWriter();



    // Assert

    EXPECT_TRUE(oss.str().empty());

}



TEST_F(JsonObjectWriterTest_529, IndentationIsAppliedCorrectlyOnDestruction_529) {

    // Arrange

    JsonObjectWriter indented_writer(oss, 3);

    indented_writer.~JsonObjectWriter();



    // Assert

    EXPECT_EQ("   }\n", oss.str());

}



TEST_F(JsonObjectWriterTest_529, WriteMethodReturnsJsonValueWriter_529) {

    // Act & Assert

    JsonValueWriter value_writer = writer.write("testKey");

    EXPECT_TRUE(value_writer.is_initialized());

}
