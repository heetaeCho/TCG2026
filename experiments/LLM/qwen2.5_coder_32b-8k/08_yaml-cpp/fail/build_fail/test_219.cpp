#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/mark.h"



using namespace YAML::detail;



class NodeRefTest_219 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_219, SetMarkAndGetMark_219) {

    Mark mark(10, 5, 3);

    ref.set_mark(mark);

    EXPECT_EQ(ref.mark(), mark);

}



TEST_F(NodeRefTest_219, DefaultConstructorInitializesNullMark_219) {

    EXPECT_TRUE(ref.mark().is_null());

}



TEST_F(NodeRefTest_219, SetTypeAndGetType_219) {

    ref.set_type(NodeType::Map);

    EXPECT_EQ(ref.type(), NodeType::Map);

}



TEST_F(NodeRefTest_219, SetTagAndGetTag_219) {

    std::string tag = "!mytag";

    ref.set_tag(tag);

    EXPECT_EQ(ref.tag(), tag);

}



TEST_F(NodeRefTest_219, SetScalarAndGetString_219) {

    std::string scalar = "test_scalar";

    ref.set_scalar(scalar);

    EXPECT_EQ(ref.scalar(), scalar);

}



TEST_F(NodeRefTest_219, SetStyleAndGetStyle_219) {

    ref.set_style(EmitterStyle::Block);

    EXPECT_EQ(ref.style(), EmitterStyle::Block);

}



TEST_F(NodeRefTest_219, MarkDefinedIsInitiallyFalse_219) {

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_219, MarkDefinedAfterCallingMarkDefined_219) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}
