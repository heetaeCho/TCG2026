#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <sstream>



class EmitterTest_38 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_38, WriteBoolTrue_38) {

    emitter << true;

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_38, WriteBoolFalse_38) {

    emitter << false;

    EXPECT_EQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_38, WriteString_38) {

    emitter << YAML::BeginSeq;

    emitter << "Hello";

    emitter << "World";

    emitter << YAML::EndSeq;

    EXPECT_EQ(emitter.c_str(), "- Hello\n- World\n");

}



TEST_F(EmitterTest_38, SetIndent_38) {

    emitter.SetIndent(4);

    emitter << YAML::BeginMap;

    emitter << YAML::Key << "key";

    emitter << YAML::Value << "value";

    emitter << YAML::EndMap;

    EXPECT_EQ(emitter.c_str(), "key: value\n");

}



TEST_F(EmitterTest_38, SetFloatPrecision_38) {

    emitter.SetFloatPrecision(2);

    emitter << 1.2345f;

    EXPECT_TRUE(std::string(emitter.c_str()).find("1.23") != std::string::npos);

}



TEST_F(EmitterTest_38, SetDoublePrecision_38) {

    emitter.SetDoublePrecision(3);

    emitter << 1.23456789;

    EXPECT_TRUE(std::string(emitter.c_str()).find("1.235") != std::string::npos);

}



TEST_F(EmitterTest_38, GoodStateAfterWrite_38) {

    emitter << YAML::BeginSeq;

    emitter << 1;

    emitter << 2;

    emitter << YAML::EndSeq;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_38, WriteChar_38) {

    emitter << 'A';

    EXPECT_EQ(emitter.c_str(), "A");

}



TEST_F(EmitterTest_38, SetBoolFormatLowercase_38) {

    emitter.SetBoolFormat(YAML::EMITTER_MANIP::LF);

    emitter << true;

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_38, SetBoolFormatUppercase_38) {

    emitter.SetBoolFormat(YAML::EMITTER_MANIP::UF);

    emitter << false;

    EXPECT_EQ(emitter.c_str(), "FALSE");

}
