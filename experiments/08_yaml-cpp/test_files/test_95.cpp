#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class YamlEmitterTest_95 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(YamlEmitterTest_95, EmitScalar_NormalOperation_95) {

    Node node = Load("test_scalar");

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "test_scalar\n");

}



TEST_F(YamlEmitterTest_95, EmitSequence_NormalOperation_95) {

    Node node = Load("[1, 2, 3]");

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "- 1\n- 2\n- 3\n");

}



TEST_F(YamlEmitterTest_95, EmitMap_NormalOperation_95) {

    Node node = Load("key: value");

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "key: value\n");

}



TEST_F(YamlEmitterTest_95, EmitNestedStructure_NormalOperation_95) {

    Node node = Load("outer:\n  inner: value");

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "outer:\n  inner: value\n");

}



TEST_F(YamlEmitterTest_95, EmitEmptyNode_NormalOperation_95) {

    Node node;

    emitter << node;

    EXPECT_TRUE(emitter.good());

}



TEST_F(YamlEmitterTest_95, EmitAliasedNodes_NormalOperation_95) {

    Node root = Load("&anchor key: value\nanother_key: *anchor");

    emitter << root;

    EXPECT_EQ(emitter.c_str(), "key: &anchor value\nanother_key: *anchor\n");

}



TEST_F(YamlEmitterTest_95, EmitWithDifferentStyles_NormalOperation_95) {

    Node node = Load("[1, 2, 3]");

    node.SetStyle(EmitterStyle::Flow);

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]\n");

}



TEST_F(YamlEmitterTest_95, EmitScalar_BoundaryConditions_95) {

    Node emptyString = Load("");

    emitter << emptyString;

    EXPECT_EQ(emitter.c_str(), "\"\"\n");



    Node stringWithSpaces = Load("string with spaces");

    emitter << stringWithSpaces;

    EXPECT_EQ(emitter.c_str(), "string with spaces\n");



    Node specialChars = Load("!@#$%^&*()_+");

    emitter << specialChars;

    EXPECT_EQ(emitter.c_str(), "!@#$%^&*()_+\n");

}



TEST_F(YamlEmitterTest_95, EmitSequence_BoundaryConditions_95) {

    Node emptySequence = Load("[]");

    emitter << emptySequence;

    EXPECT_EQ(emitter.c_str(), "[]\n");



    Node singleElementSequence = Load("[single]");

    emitter << singleElementSequence;

    EXPECT_EQ(emitter.c_str(), "- single\n");

}



TEST_F(YamlEmitterTest_95, EmitMap_BoundaryConditions_95) {

    Node emptyMap = Load("{}");

    emitter << emptyMap;

    EXPECT_EQ(emitter.c_str(), "{}\n");



    Node singleElementMap = Load("key: value");

    emitter << singleElementMap;

    EXPECT_EQ(emitter.c_str(), "key: value\n");

}



TEST_F(YamlEmitterTest_95, EmitWithComments_NormalOperation_95) {

    Node node = Load("# comment\nkey: value # inline comment");

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "# comment\nkey: value # inline comment\n");

}



TEST_F(YamlEmitterTest_95, EmitBinaryData_NormalOperation_95) {

    Binary binaryData("test", 4);

    Node node = Load("");

    node.push_back(binaryData);

    emitter << node;

    EXPECT_EQ(emitter.c_str(), "- !!binary dGVzdA==\n");

}



TEST_F(YamlEmitterTest_95, EmitWithErrors_ExceptionalCases_95) {

    // Assuming there's no direct way to cause errors in emitting valid YAML

    // This is a placeholder as the interface provided does not seem to have direct error states

    Node invalidNode;

    emitter << invalidNode;

    EXPECT_TRUE(emitter.good());

}
