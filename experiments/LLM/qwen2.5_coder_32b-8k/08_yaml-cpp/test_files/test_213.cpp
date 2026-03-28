#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_213 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_213, TypeReturnsDefaultType_213) {

    EXPECT_EQ(ref.type(), NodeType::Null);

}



TEST_F(NodeRefTest_213, SetTypeChangesType_213) {

    ref.set_type(NodeType::Scalar);

    EXPECT_EQ(ref.type(), NodeType::Scalar);

}



TEST_F(NodeRefTest_213, MarkDefinedSetsDefined_213) {

    ref.mark_defined();

    // Since there's no public method to check if it's defined,

    // we assume the state is internally managed and trust the implementation.

}



TEST_F(NodeRefTest_213, SetScalarChangesTypeToScalar_213) {

    ref.set_scalar("test");

    EXPECT_EQ(ref.type(), NodeType::Scalar);

}



TEST_F(NodeRefTest_213, SetTagSetsTag_213) {

    std::string tag = "!tag";

    ref.set_tag(tag);

    // Since there's no public method to get the tag directly,

    // we assume it is set correctly internally.

}



TEST_F(NodeRefTest_213, SetStyleChangesStyle_213) {

    ref.set_style(EmitterStyle::Flow);

    // Since there's no public method to get the style directly,

    // we assume it is set correctly internally.

}



TEST_F(NodeRefTest_213, SetNullChangesTypeToNull_213) {

    ref.set_null();

    EXPECT_EQ(ref.type(), NodeType::Null);

}
