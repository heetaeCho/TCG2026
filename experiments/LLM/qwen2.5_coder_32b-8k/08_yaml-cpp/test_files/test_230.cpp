#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML;

using namespace YAML::detail;



class NodeRefTest_230 : public ::testing::Test {

protected:

    node_ref ref;

    shared_memory_holder pMemory = nullptr; // Assuming this is a valid placeholder for tests

};



TEST_F(NodeRefTest_230, IsDefinedInitiallyFalse_230) {

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_230, MarkInitiallyDefaultConstructed_230) {

    Mark defaultMark;

    EXPECT_EQ(ref.mark(), defaultMark);

}



TEST_F(NodeRefTest_230, TypeInitiallyUndefined_230) {

    EXPECT_EQ(ref.type(), NodeType::Undefined);

}



TEST_F(NodeRefTest_230, ScalarInitiallyEmptyString_230) {

    EXPECT_TRUE(ref.scalar().empty());

}



TEST_F(NodeRefTest_230, TagInitiallyEmptyString_230) {

    EXPECT_TRUE(ref.tag().empty());

}



TEST_F(NodeRefTest_230, StyleInitiallyDefaultConstructed_230) {

    EmitterStyle::value defaultStyle = EmitterStyle::Default;

    EXPECT_EQ(ref.style(), defaultStyle);

}



TEST_F(NodeRefTest_230, SizeInitiallyZero_230) {

    EXPECT_EQ(ref.size(), 0u);

}



TEST_F(NodeRefTest_230, MarkDefinedSetsIsDefinedTrue_230) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}



TEST_F(NodeRefTest_230, SetMarkUpdatesMark_230) {

    Mark customMark(1, 2);

    ref.set_mark(customMark);

    EXPECT_EQ(ref.mark(), customMark);

}



TEST_F(NodeRefTest_230, SetTypeUpdatesType_230) {

    NodeType::value customType = NodeType::Scalar;

    ref.set_type(customType);

    EXPECT_EQ(ref.type(), customType);

}



TEST_F(NodeRefTest_230, SetTagUpdatesTag_230) {

    std::string customTag = "tag:yaml.org,2002:str";

    ref.set_tag(customTag);

    EXPECT_EQ(ref.tag(), customTag);

}



TEST_F(NodeRefTest_230, SetStyleUpdatesStyle_230) {

    EmitterStyle::value customStyle = EmitterStyle::Flow;

    ref.set_style(customStyle);

    EXPECT_EQ(ref.style(), customStyle);

}



TEST_F(NodeRefTest_230, SetScalarUpdatesScalar_230) {

    std::string customScalar = "custom scalar";

    ref.set_scalar(customScalar);

    EXPECT_EQ(ref.scalar(), customScalar);

}



TEST_F(NodeRefTest_230, PushBackIncreasesSize_230) {

    node newNode;

    ref.push_back(newNode, pMemory);

    EXPECT_EQ(ref.size(), 1u);

}



TEST_F(NodeRefTest_230, InsertKeyAndValueIncreasesSize_230) {

    node keyNode, valueNode;

    ref.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(ref.size(), 1u);

}



TEST_F(NodeRefTest_230, ForceInsertKeyAndValueSetsValue_230) {

    node keyNode, valueNode;

    std::string customTag = "custom tag";

    valueNode.set_tag(customTag);



    ref.force_insert(keyNode, valueNode, pMemory);



    node* retrievedNode = ref.get(keyNode, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

    EXPECT_EQ(retrievedNode->tag(), customTag);

}



TEST_F(NodeRefTest_230, RemoveKeyDecreasesSize_230) {

    node keyNode, valueNode;

    ref.insert(keyNode, valueNode, pMemory);

    ASSERT_EQ(ref.size(), 1u);



    ref.remove(keyNode, pMemory);

    EXPECT_EQ(ref.size(), 0u);

}



TEST_F(NodeRefTest_230, GetNonExistingKeyReturnsNullptr_230) {

    node keyNode;

    node* retrievedNode = ref.get(keyNode, pMemory);

    EXPECT_EQ(retrievedNode, nullptr);

}
