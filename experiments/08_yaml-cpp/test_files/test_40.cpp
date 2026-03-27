#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;

using ::testing::_;

using ::testing::Return;



class EmitterTest_40 : public ::testing::Test {

protected:

    std::ostringstream stream;

    Emitter emitter;

    Emitter streamEmitter;



    EmitterTest_40() : emitter(), streamEmitter(stream) {}

};



TEST_F(EmitterTest_40, WriteString_NormalOperation_40) {

    streamEmitter.Write("Hello");

    EXPECT_EQ(stream.str(), "Hello");

}



TEST_F(EmitterTest_40, WriteCString_NormalOperation_40) {

    const char* str = "World";

    streamEmitter.Write(str);

    EXPECT_EQ(stream.str(), "World");

}



TEST_F(EmitterTest_40, WriteChar_NormalOperation_40) {

    streamEmitter.Write('A');

    EXPECT_EQ(stream.str(), "A");

}



TEST_F(EmitterTest_40, WriteBool_NormalOperation_40) {

    streamEmitter.Write(true);

    EXPECT_EQ(stream.str(), "true");



    stream.str("");

    streamEmitter.Write(false);

    EXPECT_EQ(stream.str(), "false");

}



TEST_F(EmitterTest_40, SetIndent_ValidValue_40) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_40, SetIndent_BoundaryValueMin_40) {

    EXPECT_TRUE(emitter.SetIndent(1));

}



TEST_F(EmitterTest_40, SetIndent_BoundaryValueMax_40) {

    EXPECT_TRUE(emitter.SetIndent(10));

}



TEST_F(EmitterTest_40, SetIndent_OutOfBoundsTooLow_40) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_40, SetIndent_OutOfBoundsTooHigh_40) {

    EXPECT_FALSE(emitter.SetIndent(11));

}



TEST_F(EmitterTest_40, SetFloatPrecision_ValidValue_40) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_40, SetDoublePrecision_ValidValue_40) {

    EXPECT_TRUE(emitter.SetDoublePrecision(6));

}



TEST_F(EmitterTest_40, WriteIntegralType_NormalOperationInt_40) {

    streamEmitter.WriteIntegralType(123);

    EXPECT_EQ(stream.str(), "123");

}



TEST_F(EmitterTest_40, WriteStreamable_NormalOperationString_40) {

    streamEmitter.WriteStreamable(std::string("test"));

    EXPECT_EQ(stream.str(), "test");

}



TEST_F(EmitterTest_40, Good_AfterWrite_ReturnsTrue_40) {

    emitter.Write("Good test");

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_40, GetLastError_NoError_ReturnsEmptyString_40) {

    emitter.Write("No error test");

    EXPECT_EQ(emitter.GetLastError(), "");

}
