#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_238 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_238, IsDefinedInitiallyFalse_238) {

    EXPECT_FALSE(testNode.is_defined());

}



TEST_F(NodeTest_238, MarkDefinedSetsIsDefinedTrue_238) {

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_238, SetDataPreservesIsDefinedState_238) {

    node anotherNode;

    anotherNode.mark_defined();

    testNode.set_data(anotherNode);

    EXPECT_EQ(testNode.is_defined(), anotherNode.is_defined());

}



TEST_F(NodeTest_238, MarkSetsCorrectMark_238) {

    Mark mark(1, 2, "file.yaml");

    testNode.set_mark(mark);

    EXPECT_EQ(testNode.mark().line, mark.line);

    EXPECT_EQ(testNode.mark().column, mark.column);

    EXPECT_EQ(testNode.mark().name, mark.name);

}



TEST_F(NodeTest_238, SetTypeAndGetCorrectType_238) {

    NodeType::value testType = NodeType::Map;

    testNode.set_type(testType);

    EXPECT_EQ(testNode.type(), testType);

}



TEST_F(NodeTest_238, SetTagAndGetCorrectTag_238) {

    std::string tag = "test_tag";

    testNode.set_tag(tag);

    EXPECT_EQ(testNode.tag(), tag);

}



TEST_F(NodeTest_238, SetScalarAndGetCorrectScalar_238) {

    std::string scalar = "test_scalar";

    testNode.set_scalar(scalar);

    EXPECT_EQ(testNode.scalar(), scalar);

}



TEST_F(NodeTest_238, SetStyleAndGetCorrectStyle_238) {

    EmitterStyle::value style = EmitterStyle::Flow;

    testNode.set_style(style);

    EXPECT_EQ(testNode.style(), style);

}



TEST_F(NodeTest_238, SizeInitiallyZero_238) {

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_238, PushBackIncreasesSize_238) {

    node childNode;

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.push_back(childNode, pMemory);

    EXPECT_EQ(testNode.size(), 1);

}



TEST_F(NodeTest_238, InsertIncreasesSize_238) {

    node keyNode, valueNode;

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(testNode.size(), 1);

}



TEST_F(NodeTest_238, ForceInsertIncreasesSize_238) {

    std::string key = "test_key";

    std::string value = "test_value";

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.force_insert(key, value, pMemory);

    EXPECT_EQ(testNode.size(), 1);

}



TEST_F(NodeTest_238, RemoveByKeyDecreasesSize_238) {

    std::string key = "test_key";

    std::string value = "test_value";

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.force_insert(key, value, pMemory);

    EXPECT_TRUE(testNode.remove(key, pMemory));

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_238, RemoveByNodeDecreasesSize_238) {

    node keyNode;

    node valueNode;

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_TRUE(testNode.remove(keyNode, pMemory));

    EXPECT_EQ(testNode.size(), 0);

}



TEST_F(NodeTest_238, GetByKeyReturnsCorrectNode_238) {

    std::string key = "test_key";

    std::string value = "test_value";

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.force_insert(key, value, pMemory);

    node* retrievedNode = testNode.get(key, pMemory);

    EXPECT_NE(retrievedNode, nullptr);

}



TEST_F(NodeTest_238, GetByNodeReturnsCorrectNode_238) {

    node keyNode;

    node valueNode;

    shared_memory_holder pMemory = nullptr; // Assuming this is how it's used

    testNode.insert(keyNode, valueNode, pMemory);

    node* retrievedNode = testNode.get(keyNode, pMemory);

    EXPECT_NE(retrievedNode, nullptr);

}
