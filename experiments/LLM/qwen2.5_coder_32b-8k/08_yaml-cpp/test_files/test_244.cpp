#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_244 : public ::testing::Test {

protected:

    node testNode;

};



TEST_F(NodeTest_244, MarkDefined_MarksNodeAsDefined_244) {

    EXPECT_FALSE(testNode.is_defined());

    testNode.mark_defined();

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_244, MarkDefined_IdempotentOperation_244) {

    testNode.mark_defined();

    bool initiallyDefined = testNode.is_defined();

    testNode.mark_defined();

    EXPECT_EQ(initiallyDefined, testNode.is_defined());

}



// Assuming is_defined() of node_ref works correctly and affects the node's is_defined()

TEST_F(NodeTest_244, MarkDefined_PropagatesToDependencies_244) {

    node dependency;

    testNode.add_dependency(dependency);

    EXPECT_FALSE(testNode.is_defined());

    EXPECT_FALSE(dependency.is_defined());



    testNode.mark_defined();

    

    EXPECT_TRUE(testNode.is_defined());

    EXPECT_TRUE(dependency.is_defined());

}



TEST_F(NodeTest_244, MarkDefined_ClearsDependenciesAfterMarking_244) {

    node dependency;

    testNode.add_dependency(dependency);

    testNode.mark_defined();



    EXPECT_EQ(0u, testNode.m_dependencies.size());

}
