#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node_ref.h>



using namespace YAML::detail;



class NodeRefTest_223 : public ::testing::Test {

protected:

    node_ref* ref;



    void SetUp() override {

        ref = new node_ref();

    }



    void TearDown() override {

        delete ref;

    }

};



TEST_F(NodeRefTest_223, SetScalarAndGetScalar_NormalOperation_223) {

    std::string testString = "testValue";

    ref->set_scalar(testString);

    EXPECT_EQ(ref->scalar(), testString);

}



TEST_F(NodeRefTest_223, SetScalarAndGetScalar_EmptyString_223) {

    std::string emptyString = "";

    ref->set_scalar(emptyString);

    EXPECT_EQ(ref->scalar(), emptyString);

}



TEST_F(NodeRefTest_223, SetScalarAndGetScalar_BoundaryCondition_LargeString_223) {

    std::string largeString(1000000, 'a');

    ref->set_scalar(largeString);

    EXPECT_EQ(ref->scalar(), largeString);

}
