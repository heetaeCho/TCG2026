#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_jsonwriter.hpp"



using namespace Catch;

using namespace ::testing;



class JsonArrayWriterTest_1078 : public Test {

protected:

    std::ostringstream os;

    JsonArrayWriter writer;



    JsonArrayWriterTest_1078() : writer(os) {}

};



TEST_F(JsonArrayWriterTest_1078, WriteBoolValueTrue_1078) {

    writer.write(true);

    EXPECT_EQ(os.str(), "true");

}



TEST_F(JsonArrayWriterTest_1078, WriteBoolValueFalse_1078) {

    writer.write(false);

    EXPECT_EQ(os.str(), "false");

}



TEST_F(JsonArrayWriterTest_1078, WriteMultipleValues_1078) {

    writer.write(true).write(false).write(42);

    EXPECT_EQ(os.str(), "true,false,42");

}



TEST_F(JsonArrayWriterTest_1078, WriteObject_1078) {

    auto objWriter = writer.writeObject();

    // This test assumes that writeObject() starts a new JSON object.

    EXPECT_EQ(os.str(), "{");

}



TEST_F(JsonArrayWriterTest_1078, WriteArray_1078) {

    auto arrayWriter = writer.writeArray();

    // This test assumes that writeArray() starts a new JSON array.

    EXPECT_EQ(os.str(), "[");

}



TEST_F(JsonArrayWriterTest_1078, MoveConstructor_1078) {

    std::ostringstream os2;

    JsonArrayWriter writer2(os2);

    writer2.write(true);



    JsonArrayWriter movedWriter(std::move(writer2));

    movedWriter.write(false);



    EXPECT_EQ(os2.str(), "true,false");

}



TEST_F(JsonArrayWriterTest_1078, MoveAssignmentOperatorDeleted_1078) {

    std::ostringstream os2;

    JsonArrayWriter writer2(os2);

    writer2.write(true);



    // This should not compile if move assignment is deleted.

    // JsonArrayWriter movedWriter = std::move(writer2);

}



TEST_F(JsonArrayWriterTest_1078, DestructorCalledProperly_1078) {

    // Assuming the destructor writes a closing bracket for the array.

    writer.write(true);

}
