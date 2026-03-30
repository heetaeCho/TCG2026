#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_246 : public ::testing::Test {

protected:

    node default_node;

    node defined_node;

};



TEST_F(NodeTest_246, IsDefined_ReturnsFalseForDefaultNode_246) {

    EXPECT_FALSE(default_node.is_defined());

}



TEST_F(NodeTest_246, IsDefined_ReturnsTrueAfterMarkingDefined_246) {

    default_node.mark_defined();

    EXPECT_TRUE(default_node.is_defined());

}



TEST_F(NodeTest_246, SetRef_CopiesReferenceFromAnotherNode_246) {

    defined_node.mark_defined();

    default_node.set_ref(defined_node);

    EXPECT_EQ(default_node.ref(), defined_node.ref());

}



TEST_F(NodeTest_246, SetRef_MarksDefinedIfRhsIsDefined_246) {

    defined_node.mark_defined();

    default_node.set_ref(defined_node);

    EXPECT_TRUE(default_node.is_defined());

}



TEST_F(NodeTest_246, SetRef_DoesNotMarkDefinedIfRhsIsNotDefined_246) {

    default_node.set_ref(defined_node);

    EXPECT_FALSE(default_node.is_defined());

}
