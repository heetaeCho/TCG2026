#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_43 : public ::testing::Test {

protected:

    std::ostringstream stream;

    Emitter emitter;

    Emitter streamEmitter;



    EmitterTest_43() : emitter(), streamEmitter(stream) {}

};



TEST_F(EmitterTest_43, GoodInitiallyTrue_43) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_43, WriteStringIncreasesSize_43) {

    size_t initialSize = emitter.size();

    emitter.Write("test");

    EXPECT_GT(emitter.size(), initialSize);

}



TEST_F(EmitterTest_43, WriteBoolReturnsEmitterReference_43) {

    Emitter& result = emitter.Write(true);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_43, WriteCharReturnsEmitterReference_43) {

    Emitter& result = emitter.Write('a');

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_43, SetIndentWithZeroValue_43) {

    EXPECT_TRUE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_43, SetIndentWithNonZeroValue_43) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_43, SetFloatPrecisionWithValidValue_43) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

}



TEST_F(EmitterTest_43, SetDoublePrecisionWithValidValue_43) {

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_43, WriteTagWithValidTag_43) {

    _Tag tag("!mytag", "content", Type::value::verbatimized);

    Emitter& result = emitter.Write(tag);

    EXPECT_EQ(&result, &emitter);

}



TEST_F(EmitterTest_43, GetLastErrorInitiallyEmpty_43) {

    EXPECT_TRUE(emitter.GetLastError().empty());

}



TEST_F(EmitterTest_43, WriteToStreamReturnsEmitterReference_43) {

    Emitter& result = streamEmitter.Write("test");

    EXPECT_EQ(&result, &streamEmitter);

}



TEST_F(EmitterTest_43, StreamContainsWrittenString_43) {

    streamEmitter.Write("hello world");

    EXPECT_EQ(stream.str(), "hello world");

}
