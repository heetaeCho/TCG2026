#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BoundRefTest : public ::testing::Test {

protected:

    BoundRef boundRef;

};



TEST_F(BoundRefTest_659, IsContainer_Default_ReturnsFalse_659) {

    EXPECT_FALSE(boundRef.isContainer());

}



TEST_F(BoundRefTest_659, IsFlag_Default_ReturnsFalse_659) {

    EXPECT_FALSE(boundRef.isFlag());

}
