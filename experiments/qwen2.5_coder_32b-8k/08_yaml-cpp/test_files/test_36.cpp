#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_36 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_36, WriteString_36) {

    emitter << std::string_view("test");

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteBool_36) {

    emitter.Write(true);

    emitter.Write(false);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteChar_36) {

    emitter.Write('a');

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteEmptyString_36) {

    emitter.Write("");

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, SetIndentValid_36) {

    EXPECT_TRUE(emitter.SetIndent(2));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, SetIndentInvalid_36) {

    EXPECT_FALSE(emitter.SetIndent(0)); // Invalid indent

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, SetFloatPrecisionValid_36) {

    EXPECT_TRUE(emitter.SetFloatPrecision(5));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, SetDoublePrecisionInvalid_36) {

    EXPECT_FALSE(emitter.SetDoublePrecision(20)); // Invalid precision

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, GetLastErrorCode_36) {

    emitter.Write("test");

    std::string error = emitter.GetLastError();

    EXPECT_EQ(error, "");

}



TEST_F(EmitterTest_36, WriteStreamable_36) {

    emitter << 42;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteAlias_36) {

    emitter.Write(_Alias("alias"));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteAnchor_36) {

    emitter.Write(_Anchor("anchor"));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteTag_36) {

    emitter.Write(_Tag("!tag"));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteComment_36) {

    emitter.Write(_Comment("comment"));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteNull_36) {

    emitter.Write(_Null());

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_36, WriteBinary_36) {

    Binary binary((const unsigned char*)"binary", 6);

    emitter.Write(binary);

    EXPECT_TRUE(emitter.good());

}
