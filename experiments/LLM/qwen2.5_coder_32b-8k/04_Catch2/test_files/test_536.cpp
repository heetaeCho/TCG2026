#include <gtest/gtest.h>

#include "catch2/internal/catch_jsonwriter.hpp"

#include <sstream>



using namespace Catch;



class JsonValueWriterTest_536 : public ::testing::Test {

protected:

    std::stringstream ss;

    JsonValueWriter writer;



    JsonValueWriterTest_536() : writer(ss) {}

};



TEST_F(JsonValueWriterTest_536, WriteArray_ReturnsJsonArrayWriter_536) {

    JsonArrayWriter arrayWriter = writer.writeArray();

    EXPECT_EQ(arrayWriter.getStream().rdbuf(), ss.rdbuf());

}



// Boundary conditions

TEST_F(JsonValueWriterTest_536, WriteArray_AfterWrite_ReturnsSeparateInstances_536) {

    JsonArrayWriter firstArrayWriter = writer.writeArray();

    writer.write("test");

    JsonArrayWriter secondArrayWriter = writer.writeArray();

    EXPECT_NE(firstArrayWriter.getStream().rdbuf(), secondArrayWriter.getStream().rdbuf());

}



// Exceptional or error cases (if observable through the interface)

// None explicitly observable from the provided interface



// Verification of external interactions

// No mocks needed as per constraints, since there are no collaborators to mock.



// Additional tests for other methods if required

TEST_F(JsonValueWriterTest_536, WriteString_CorrectlyWritesToStream_536) {

    writer.write("test");

    EXPECT_EQ(ss.str(), "\"test\"");

}



TEST_F(JsonValueWriterTest_536, WriteBooleanTrue_CorrectlyWritesToStream_536) {

    writer.write(true);

    EXPECT_EQ(ss.str(), "true");

}



TEST_F(JsonValueWriterTest_536, WriteBooleanFalse_CorrectlyWritesToStream_536) {

    writer.write(false);

    EXPECT_EQ(ss.str(), "false");

}
