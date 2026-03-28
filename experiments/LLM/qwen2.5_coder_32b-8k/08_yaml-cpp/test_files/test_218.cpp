#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_218 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_218, DefaultConstructor_IsUndefined_218) {

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_218, MarkDefined_MarkAsDefined_218) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}



TEST_F(NodeRefTest_218, SetMark_ChangeMark_218) {

    Mark mark;

    ref.set_mark(mark);

    EXPECT_EQ(ref.mark(), mark);

}



TEST_F(NodeRefTest_218, SetType_ChangeType_218) {

    NodeType::value type = NodeType::Scalar;

    ref.set_type(type);

    EXPECT_EQ(ref.type(), type);

}



TEST_F(NodeRefTest_218, SetTag_ChangeTag_218) {

    std::string tag = "test_tag";

    ref.set_tag(tag);

    EXPECT_EQ(ref.tag(), tag);

}



TEST_F(NodeRefTest_218, SetNull_SetTypeToNull_218) {

    ref.set_null();

    EXPECT_EQ(ref.type(), NodeType::Undefined); // Assuming set_null sets type to undefined or null

}



TEST_F(NodeRefTest_218, SetScalar_ChangeScalar_218) {

    std::string scalar = "test_scalar";

    ref.set_scalar(scalar);

    EXPECT_EQ(ref.scalar(), scalar);

}



TEST_F(NodeRefTest_218, SetStyle_ChangeStyle_218) {

    EmitterStyle::value style = EmitterStyle::Flow;

    ref.set_style(style);

    EXPECT_EQ(ref.style(), style);

}



TEST_F(NodeRefTest_218, Size_DefaultIsZero_218) {

    EXPECT_EQ(ref.size(), 0u);

}



TEST_F(NodeRefTest_218, SetData_CopyDataFromAnotherNodeRef_218) {

    node_ref other;

    other.set_scalar("other_scalar");

    ref.set_data(other);

    EXPECT_EQ(ref.scalar(), other.scalar());

}
