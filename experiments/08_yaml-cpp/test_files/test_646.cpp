#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_646 : public ::testing::Test {

protected:

    node_data testData;

};



TEST_F(NodeDataTest_646, SetScalar_ChangesTypeToScalar_646) {

    testData.set_scalar("test");

    EXPECT_EQ(testData.type(), NodeType::Scalar);

}



TEST_F(NodeDataTest_646, SetScalar_UpdatesScalarValue_646) {

    testData.set_scalar("test");

    EXPECT_EQ(testData.scalar(), "test");

}



TEST_F(NodeDataTest_646, SetScalar_MarksNodeAsDefined_646) {

    EXPECT_FALSE(testData.is_defined());

    testData.set_scalar("test");

    EXPECT_TRUE(testData.is_defined());

}



TEST_F(NodeDataTest_646, SetEmptyScalar_UpdatesScalarValueToEmpty_646) {

    testData.set_scalar("");

    EXPECT_EQ(testData.scalar(), "");

}



TEST_F(NodeDataTest_646, SetScalar_DoesNotAffectTag_646) {

    testData.set_tag("tag");

    testData.set_scalar("test");

    EXPECT_EQ(testData.tag(), "tag");

}



TEST_F(NodeDataTest_646, SetScalar_DoesNotAffectStyle_646) {

    testData.set_style(EmitterStyle::Flow);

    testData.set_scalar("test");

    EXPECT_EQ(testData.style(), EmitterStyle::Flow);

}
