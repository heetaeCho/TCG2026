#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_245 : public ::testing::Test {

protected:

    node node1;

    node node2;

};



TEST_F(NodeTest_245, AddDependencyWhenDefined_245) {

    node1.mark_defined();

    node2.add_dependency(node1);

    EXPECT_TRUE(node2.is_defined());

}



TEST_F(NodeTest_245, AddDependencyWhenNotDefined_245) {

    node2.add_dependency(node1);

    EXPECT_FALSE(node2.is_defined());

    EXPECT_EQ(1u, node1.m_dependencies.size());

    EXPECT_EQ(&node2, *node1.m_dependencies.begin());

}



TEST_F(NodeTest_245, AddSameDependencyTwice_245) {

    node2.add_dependency(node1);

    node2.add_dependency(node1);

    EXPECT_FALSE(node2.is_defined());

    EXPECT_EQ(1u, node1.m_dependencies.size());

    EXPECT_EQ(&node2, *node1.m_dependencies.begin());

}



TEST_F(NodeTest_245, AddDependencySelfReference_245) {

    node1.add_dependency(node1);

    EXPECT_TRUE(node1.is_defined());

}



TEST_F(NodeTest_245, AddMultipleDependencies_245) {

    node node3;

    node node4;

    node1.add_dependency(node2);

    node1.add_dependency(node3);

    node1.add_dependency(node4);

    EXPECT_FALSE(node2.is_defined());

    EXPECT_FALSE(node3.is_defined());

    EXPECT_FALSE(node4.is_defined());

    EXPECT_EQ(3u, node1.m_dependencies.size());

}
