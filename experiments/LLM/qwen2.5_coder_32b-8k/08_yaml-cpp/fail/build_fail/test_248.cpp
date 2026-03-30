#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>

#include <yaml-cpp/mark.h>



using namespace YAML::detail;



class NodeTest_248 : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_248, SetMarkAndGetMark_NormalOperation_248) {

    Mark mark(10, 5, 3);

    node.set_mark(mark);

    EXPECT_EQ(node.mark().pos, mark.pos);

    EXPECT_EQ(node.mark().line, mark.line);

    EXPECT_EQ(node.mark().column, mark.column);

}



TEST_F(NodeTest_248, SetMarkAndGetMark_DefaultMark_248) {

    Mark defaultMark;

    node.set_mark(defaultMark);

    EXPECT_TRUE(node.mark().is_null());

}



TEST_F(NodeTest_248, SetMarkAndGetMark_BoundaryConditions_248) {

    Mark boundaryMark(-1, -1, -1);

    node.set_mark(boundaryMark);

    EXPECT_EQ(node.mark().pos, boundaryMark.pos);

    EXPECT_EQ(node.mark().line, boundaryMark.line);

    EXPECT_EQ(node.mark().column, boundaryMark.column);

}



TEST_F(NodeTest_248, IsDefined_DefaultState_248) {

    EXPECT_FALSE(node.is_defined());

}



TEST_F(NodeTest_248, MarkDefined_IsDefinedChangesToTrue_248) {

    node.mark_defined();

    EXPECT_TRUE(node.is_defined());

}
