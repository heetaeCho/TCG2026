#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_220 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_220, SetType_NormalOperation_220) {

    NodeType::value initialType = ref.type();

    NodeType::value newType = NodeType::Scalar;

    ref.set_type(newType);

    EXPECT_EQ(ref.type(), newType);

}



TEST_F(NodeRefTest_220, SetType_BoundaryCondition_220) {

    NodeType::value boundaryType = static_cast<NodeType::value>(-1); // Assuming invalid type

    ref.set_type(boundaryType);

    // We cannot assert the behavior for an invalid type as it's not specified in the interface

}



TEST_F(NodeRefTest_220, SetType_ExceptionalCase_220) {

    // Since there are no exceptions or error codes specified in the interface,

    // we can't test exceptional cases here.

    // This is a placeholder to indicate that if there were any specified,

    // this is where they would be tested.

}



TEST_F(NodeRefTest_220, IsDefined_DefaultState_220) {

    EXPECT_FALSE(ref.is_defined());

}



TEST_F(NodeRefTest_220, MarkDefined_NormalOperation_220) {

    ref.mark_defined();

    EXPECT_TRUE(ref.is_defined());

}



// Additional tests for other methods can be added similarly



TEST_F(NodeRefTest_220, SetTag_NormalOperation_220) {

    std::string initialTag = ref.tag();

    std::string newTag = "tag:yaml.org,2002:str";

    ref.set_tag(newTag);

    EXPECT_EQ(ref.tag(), newTag);

}



TEST_F(NodeRefTest_220, SetScalar_NormalOperation_220) {

    std::string initialScalar = ref.scalar();

    std::string newScalar = "Hello, World!";

    ref.set_scalar(newScalar);

    EXPECT_EQ(ref.scalar(), newScalar);

}



TEST_F(NodeRefTest_220, SetStyle_NormalOperation_220) {

    EmitterStyle::value initialStyle = ref.style();

    EmitterStyle::value newStyle = EmitterStyle::Block;

    ref.set_style(newStyle);

    EXPECT_EQ(ref.style(), newStyle);

}
