#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_211 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_211, IsDefinedInitiallyFalse_211) {

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_211, MarkDefinedSetsIsDefinedTrue_211) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}



TEST_F(NodeRefTest_211, SetScalarDoesNotAffectIsDefined_211) {

    ref.set_scalar("test");

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_211, SetTypeDoesNotAffectIsDefined_211) {

    ref.set_type(NodeType::Scalar);

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_211, SetTagDoesNotAffectIsDefined_211) {

    ref.set_tag("test");

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_211, SetStyleDoesNotAffectIsDefined_211) {

    ref.set_style(EmitterStyle::Flow);

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_211, SetNullDoesNotAffectIsDefined_211) {

    ref.set_null();

    EXPECT_FALSE(ref.is_defined());

}
