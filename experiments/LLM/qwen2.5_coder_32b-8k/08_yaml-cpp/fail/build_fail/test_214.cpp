#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeRefTest : public ::testing::Test {

protected:

    node_ref* ref;



    void SetUp() override {

        ref = new node_ref();

    }



    void TearDown() override {

        delete ref;

    }

};



TEST_F(NodeRefTest_214, Scalar_ReturnsEmptyStringByDefault_214) {

    EXPECT_EQ(ref->scalar(), "");

}



TEST_F(NodeRefTest_214, Scalar_ReturnsSetStringValue_214) {

    node_data data;

    std::string test_scalar = "test_scalar";

    data.set_scalar(test_scalar);

    ref->set_data(node_ref(data));

    EXPECT_EQ(ref->scalar(), test_scalar);

}



TEST_F(NodeRefTest_214, IsDefined_ReturnsFalseByDefault_214) {

    EXPECT_FALSE(ref->is_defined());

}



TEST_F(NodeRefTest_214, MarkDefined_MarksNodeAsDefined_214) {

    ref->mark_defined();

    EXPECT_TRUE(ref->is_defined());

}
