#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeRefTest_226 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_226, BeginReturnsValidIterator_226) {

    const_node_iterator it = ref.begin();

    EXPECT_NE(it, ref.end());

}



// Assuming that size() can be used to verify boundary conditions

TEST_F(NodeRefTest_226, SizeReturnsZeroForEmptyNode_226) {

    EXPECT_EQ(ref.size(), 0);

}



// Assuming that mark_defined() affects is_defined()

TEST_F(NodeRefTest_226, MarkDefinedSetsIsDefinedTrue_226) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}



// Assuming that set_scalar() changes the scalar value

TEST_F(NodeRefTest_226, SetScalarChangesScalarValue_226) {

    const std::string test_scalar = "test_scalar";

    ref.set_scalar(test_scalar);

    EXPECT_EQ(ref.scalar(), test_scalar);

}



// Assuming that set_tag() changes the tag value

TEST_F(NodeRefTest_226, SetTagChangesTagValue_226) {

    const std::string test_tag = "test_tag";

    ref.set_tag(test_tag);

    EXPECT_EQ(ref.tag(), test_tag);

}



// Assuming that set_style() changes the style value

TEST_F(NodeRefTest_226, SetStyleChangesStyleValue_226) {

    EmitterStyle::value test_style = EmitterStyle::Block;

    ref.set_style(test_style);

    EXPECT_EQ(ref.style(), test_style);

}



// Assuming that set_null() sets the type to Null

TEST_F(NodeRefTest_226, SetNullSetsTypeToNull_226) {

    ref.set_null();

    EXPECT_EQ(ref.type(), NodeType::Null);

}
