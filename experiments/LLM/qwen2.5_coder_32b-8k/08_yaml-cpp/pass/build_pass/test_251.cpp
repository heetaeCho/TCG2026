#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_251 : public ::testing::Test {

protected:

    node sut;

};



TEST_F(NodeTest_251, SetScalar_NormalOperation_251) {

    std::string scalar = "test_scalar";

    sut.set_scalar(scalar);

    EXPECT_EQ(sut.scalar(), scalar);

}



TEST_F(NodeTest_251, SetScalar_BoundaryCondition_EmptyString_251) {

    std::string scalar = "";

    sut.set_scalar(scalar);

    EXPECT_EQ(sut.scalar(), scalar);

}



TEST_F(NodeTest_251, SetScalar_BoundaryCondition_MaxLengthString_251) {

    std::string scalar(1024, 'a'); // Example of a long string

    sut.set_scalar(scalar);

    EXPECT_EQ(sut.scalar(), scalar);

}



TEST_F(NodeTest_251, IsDefined_AfterSetScalar_251) {

    EXPECT_FALSE(sut.is_defined());

    sut.set_scalar("some_value");

    EXPECT_TRUE(sut.is_defined());

}
