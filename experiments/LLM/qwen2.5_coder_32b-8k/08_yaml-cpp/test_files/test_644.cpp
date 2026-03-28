#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_644 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_644, SetStyle_DefaultValue_644) {

    EmitterStyle::value style = data.style();

    EXPECT_EQ(style, EmitterStyle::Default);

}



TEST_F(NodeDataTest_644, SetStyle_NormalOperation_644) {

    data.set_style(EmitterStyle::Block);

    EXPECT_EQ(data.style(), EmitterStyle::Block);

}



TEST_F(NodeDataTest_644, SetStyle_BoundaryConditions_644) {

    data.set_style(EmitterStyle::Flow);

    EXPECT_EQ(data.style(), EmitterStyle::Flow);



    data.set_style(static_cast<EmitterStyle::value>(-1));

    EXPECT_NE(data.style(), static_cast<EmitterStyle::value>(-1)); // Assuming invalid values are handled gracefully

}



TEST_F(NodeDataTest_644, SetStyle_ExceptionalCases_644) {

    // No exceptional cases observable through the interface for set_style

}



// Additional tests for other public methods



TEST_F(NodeDataTest_644, MarkDefined_DefaultValue_644) {

    EXPECT_FALSE(data.is_defined());

}



TEST_F(NodeDataTest_644, MarkDefined_NormalOperation_644) {

    data.mark_defined();

    EXPECT_TRUE(data.is_defined());

}



TEST_F(NodeDataTest_644, SetMark_NormalOperation_644) {

    Mark mark(1, 2);

    data.set_mark(mark);

    EXPECT_EQ(data.mark(), mark);

}



TEST_F(NodeDataTest_644, SetType_NormalOperation_644) {

    data.set_type(NodeType::Map);

    EXPECT_EQ(data.type(), NodeType::Map);



    data.set_type(NodeType::Sequence);

    EXPECT_EQ(data.type(), NodeType::Sequence);



    data.set_type(NodeType::Scalar);

    EXPECT_EQ(data.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_644, SetTag_NormalOperation_644) {

    std::string tag = "tag:example.com,2019:foo";

    data.set_tag(tag);

    EXPECT_EQ(data.tag(), tag);

}



TEST_F(NodeDataTest_644, SetNull_NormalOperation_644) {

    data.set_null();

    EXPECT_EQ(data.type(), NodeType::Null);

}



TEST_F(NodeDataTest_644, SetScalar_NormalOperation_644) {

    std::string scalar = "example";

    data.set_scalar(scalar);

    EXPECT_EQ(data.scalar(), scalar);

}



TEST_F(NodeDataTest_644, Size_DefaultValue_644) {

    EXPECT_EQ(data.size(), 0);

}
