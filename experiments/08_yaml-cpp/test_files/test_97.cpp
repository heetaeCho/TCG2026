#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>



using namespace YAML;



class DumpTest_97 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(DumpTest_97, EmptyNode_ReturnsEmptyString_97) {

    EXPECT_EQ("", Dump(node));

}



TEST_F(DumpTest_97, ScalarNode_ReturnsScalarValue_97) {

    node = "test";

    EXPECT_EQ("test\n", Dump(node));

}



TEST_F(DumpTest_97, SequenceNode_ReturnsSequenceString_97) {

    node.push_back(1);

    node.push_back(2);

    node.push_back(3);

    EXPECT_EQ("- 1\n- 2\n- 3\n", Dump(node));

}



TEST_F(DumpTest_97, MapNode_ReturnsMapString_97) {

    node["key1"] = "value1";

    node["key2"] = "value2";

    EXPECT_TRUE(Dump(node) == "key1: value1\nkey2: value2\n" || Dump(node) == "key2: value2\nkey1: value1\n");

}



TEST_F(DumpTest_97, NestedMap_ReturnsNestedString_97) {

    Node innerNode;

    innerNode["subkey"] = "subvalue";

    node["outerkey"] = innerNode;

    EXPECT_TRUE(Dump(node) == "outerkey:\n  subkey: subvalue\n" || Dump(node) == "outerkey:\n  subkey: subvalue\n");

}



TEST_F(DumpTest_97, ComplexNested_ReturnsComplexString_97) {

    Node innerNode;

    innerNode["subkey1"] = 42;

    innerNode["subkey2"] = "nested";

    node["outerkey"] = innerNode;

    node["anotherkey"] = 3.14;

    EXPECT_TRUE(Dump(node) == "anotherkey: 3.14\nouterkey:\n  subkey1: 42\n  subkey2: nested\n" ||

                Dump(node) == "outerkey:\n  subkey1: 42\n  subkey2: nested\nanotherkey: 3.14\n");

}



TEST_F(DumpTest_97, NodeWithNull_ReturnsNullString_97) {

    node = Node();

    EXPECT_EQ("~\n", Dump(node));

}
