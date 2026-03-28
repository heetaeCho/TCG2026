#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;

using ::testing::Ref;



class JsonValueWriterTest_535 : public ::testing::Test {

protected:

    std::ostringstream oss;

    JsonValueWriter writer;



    JsonValueWriterTest_535() : writer(oss) {}

};



TEST_F(JsonValueWriterTest_535, WriteString_535) {

    writer.write("test");

    EXPECT_EQ(oss.str(), "\"test\"");

}



TEST_F(JsonValueWriterTest_535, WriteBooleanTrue_535) {

    writer.write(true);

    EXPECT_EQ(oss.str(), "true");

}



TEST_F(JsonValueWriterTest_535, WriteBooleanFalse_535) {

    writer.write(false);

    EXPECT_EQ(oss.str(), "false");

}



TEST_F(JsonValueWriterTest_535, WriteObjectNormalOperation_535) {

    auto objWriter = std::move(writer).writeObject();

    EXPECT_TRUE(objWriter.m_os.good());

}



TEST_F(JsonValueWriterTest_535, WriteArrayNormalOperation_535) {

    auto arrayWriter = std::move(writer).writeArray();

    EXPECT_TRUE(arrayWriter.m_os.good());

}



TEST_F(JsonValueWriterTest_535, MoveSemanticsForObjectWriter_535) {

    auto objWriter1 = std::move(writer).writeObject();

    auto objWriter2 = std::move(objWriter1);

    EXPECT_TRUE(objWriter2.m_os.good());

}



TEST_F(JsonValueWriterTest_535, MoveSemanticsForArrayWriter_535) {

    auto arrayWriter1 = std::move(writer).writeArray();

    auto arrayWriter2 = std::move(arrayWriter1);

    EXPECT_TRUE(arrayWriter2.m_os.good());

}
