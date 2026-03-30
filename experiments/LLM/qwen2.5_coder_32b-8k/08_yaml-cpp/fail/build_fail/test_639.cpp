#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_639 : public ::testing::Test {

protected:

    node_data testData;

};



TEST_F(NodeDataTest_639, EmptyScalar_ReturnsEmptyString_639) {

    const std::string& result = testData.empty_scalar();

    EXPECT_TRUE(result.empty());

}



TEST_F(NodeDataTest_639, IsDefined_DefaultState_IsFalse_639) {

    EXPECT_FALSE(testData.is_defined());

}



TEST_F(NodeDataTest_639, MarkDefined_ChangesIsDefinedToTrue_639) {

    testData.mark_defined();

    EXPECT_TRUE(testData.is_defined());

}



TEST_F(NodeDataTest_639, SetScalar_UpdatesScalarValue_639) {

    const std::string testString = "test";

    testData.set_scalar(testString);

    EXPECT_EQ(testData.scalar(), testString);

}



TEST_F(NodeDataTest_639, SetTag_UpdatesTagValue_639) {

    const std::string testTag = "!test";

    testData.set_tag(testTag);

    EXPECT_EQ(testData.tag(), testTag);

}



TEST_F(NodeDataTest_639, SetType_UpdatesTypeValue_639) {

    NodeType::value testType = NodeType::Map;

    testData.set_type(testType);

    EXPECT_EQ(testData.type(), testType);

}



TEST_F(NodeDataTest_639, SetStyle_UpdatesStyleValue_639) {

    EmitterStyle::value testStyle = EmitterStyle::Block;

    testData.set_style(testStyle);

    EXPECT_EQ(testData.style(), testStyle);

}



TEST_F(NodeDataTest_639, Size_DefaultState_IsZero_639) {

    EXPECT_EQ(testData.size(), 0);

}
