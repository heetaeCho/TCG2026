#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/parse.cpp"



using namespace YAML;

using ::testing::Return;



class ParseTest_578 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(ParseTest_578, LoadValidYamlString_578) {

    std::string validYaml = "key: value";

    Node node = Load(validYaml);

    EXPECT_TRUE(node.IsMap());

    EXPECT_EQ(node["key"].as<std::string>(), "value");

}



TEST_F(ParseTest_578, LoadEmptyString_578) {

    std::string emptyYaml = "";

    Node node = Load(emptyYaml);

    EXPECT_FALSE(node);

}



TEST_F(ParseTest_578, LoadInvalidYamlString_578) {

    std::string invalidYaml = "key: value\n  - item";

    Node node = Load(invalidYaml);

    EXPECT_FALSE(node);

}



TEST_F(ParseTest_578, LoadNestedMap_578) {

    std::string nestedYaml = "outer:\n  inner: value";

    Node node = Load(nestedYaml);

    EXPECT_TRUE(node.IsMap());

    EXPECT_TRUE(node["outer"].IsMap());

    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");

}



TEST_F(ParseTest_578, LoadList_578) {

    std::string listYaml = "- item1\n- item2";

    Node node = Load(listYaml);

    EXPECT_TRUE(node.IsSequence());

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<std::string>(), "item1");

    EXPECT_EQ(node[1].as<std::string>(), "item2");

}



TEST_F(ParseTest_578, LoadComplexDataTypes_578) {

    std::string complexYaml = "integer: 42\nfloat: 3.14\nboolean: true";

    Node node = Load(complexYaml);

    EXPECT_TRUE(node.IsMap());

    EXPECT_EQ(node["integer"].as<int>(), 42);

    EXPECT_DOUBLE_EQ(node["float"].as<double>(), 3.14);

    EXPECT_EQ(node["boolean"].as<bool>(), true);

}
