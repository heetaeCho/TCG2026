#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_jsonwriter.hpp"



using namespace Catch;

using namespace testing;



class JsonArrayWriterTest_526 : public Test {

protected:

    std::ostringstream oss;

    JsonArrayWriter writer;



    JsonArrayWriterTest_526() : writer(oss) {}

};



TEST_F(JsonArrayWriterTest_526, WriteBoolValue_526) {

    writer.write(true);

    EXPECT_EQ("[true]", oss.str());

}



TEST_F(JsonArrayWriterTest_526, WriteMultipleValues_526) {

    writer.write(true).write(false).write(42);

    EXPECT_EQ("[true,false,42]", oss.str());

}



TEST_F(JsonArrayWriterTest_526, WriteObject_526) {

    JsonObjectWriter objWriter = writer.writeObject();

    // No observable behavior from writeObject itself in the interface

}



TEST_F(JsonArrayWriterTest_526, WriteArray_526) {

    JsonArrayWriter arrayWriter = writer.writeArray();

    // No observable behavior from writeArray itself in the interface

}



TEST_F(JsonArrayWriterTest_526, MoveConstructor_526) {

    std::ostringstream oss2;

    JsonArrayWriter writer2(oss);

    JsonArrayWriter movedWriter(std::move(writer2));

    movedWriter.write(true);

    EXPECT_EQ("[true]", oss.str());

}



TEST_F(JsonArrayWriterTest_526, Destructor_526) {

    // No observable behavior from destructor in the interface

}
