#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_222 : public ::testing::Test {

protected:

    node_ref* ref;



    void SetUp() override {

        ref = new node_ref();

    }



    void TearDown() override {

        delete ref;

    }

};



TEST_F(NodeRefTest_222, SetNullSetsTypeToNull_222) {

    ref->set_null();

    EXPECT_EQ(ref->type(), NodeType::Null);

}



TEST_F(NodeRefTest_222, IsDefinedReturnsFalseInitially_222) {

    EXPECT_FALSE(ref->is_defined());

}



TEST_F(NodeRefTest_222, MarkDefinedSetsIsDefinedToTrue_222) {

    ref->mark_defined();

    EXPECT_TRUE(ref->is_defined());

}



TEST_F(NodeRefTest_222, SetScalarChangesTypeToScalar_222) {

    ref->set_scalar("test");

    EXPECT_EQ(ref->type(), NodeType::Scalar);

}



TEST_F(NodeRefTest_222, SetTagUpdatesTag_222) {

    std::string tag = "!test";

    ref->set_tag(tag);

    EXPECT_EQ(ref->tag(), tag);

}



TEST_F(NodeRefTest_222, SetStyleUpdatesStyle_222) {

    EmitterStyle::value style = EmitterStyle::Flow;

    ref->set_style(style);

    EXPECT_EQ(ref->style(), style);

}
