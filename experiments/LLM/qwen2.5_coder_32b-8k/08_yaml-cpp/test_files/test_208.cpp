#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_208 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_208, ScalarDefaultValue_208) {

    EXPECT_EQ(data.scalar(), "");

}



TEST_F(NodeDataTest_208, SetScalarAndGet_208) {

    data.set_scalar("test_value");

    EXPECT_EQ(data.scalar(), "test_value");

}



TEST_F(NodeDataTest_208, SetEmptyStringAsScalar_208) {

    data.set_scalar("");

    EXPECT_EQ(data.scalar(), "");

}



TEST_F(NodeDataTest_208, ScalarAfterSettingNull_208) {

    data.set_null();

    EXPECT_EQ(data.scalar(), "");

}
