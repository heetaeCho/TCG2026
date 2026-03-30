#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"



namespace Catch {

    class JsonValueWriterTest_537 : public ::testing::Test {

    protected:

        std::ostringstream os;

        JsonValueWriter writer;



        JsonValueWriterTest_537() : writer(os) {}

    };



    TEST_F(JsonValueWriterTest_537, WriteString_NormalOperation_537) {

        StringRef value("test");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"test\"");

    }



    TEST_F(JsonValueWriterTest_537, WriteString_EmptyString_537) {

        StringRef value("");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"\"");

    }



    TEST_F(JsonValueWriterTest_537, WriteString_BoundaryCondition_537) {

        StringRef value("a");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"a\"");

    }



    TEST_F(JsonValueWriterTest_537, WriteBool_NormalOperationTrue_537) {

        writer.write(true);

        EXPECT_EQ(os.str(), "true");

    }



    TEST_F(JsonValueWriterTest_537, WriteBool_NormalOperationFalse_537) {

        writer.write(false);

        EXPECT_EQ(os.str(), "false");

    }



    TEST_F(JsonValueWriterTest_537, WriteString_SpecialCharacters_537) {

        StringRef value("test\\\"with\\special\\\\characters\nand\ttabs");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"test\\\"with\\\\special\\\\characters\\nand\\ttabs\"");

    }



    TEST_F(JsonValueWriterTest_537, WriteString_ControlCharacters_537) {

        StringRef value("\x01\x02\x03");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"\\u0001\\u0002\\u0003\"");

    }



    TEST_F(JsonValueWriterTest_537, WriteString_EscapedCharacters_537) {

        StringRef value("\\b\\f\\n\\r\\t");

        writer.write(value);

        EXPECT_EQ(os.str(), "\"\\\\b\\\\f\\\\n\\\\r\\\\t\"");

    }

}
