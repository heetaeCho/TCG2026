#include <gtest/gtest.h>

#include "yaml-cpp/null.h"



class NullTest_24 : public ::testing::Test {

protected:

    YAML::_Null null1;

    YAML::_Null null2;

};



TEST_F(NullTest_24, InequalityOperatorSameInstance_24) {

    EXPECT_FALSE(null1 != null1);

}



TEST_F(NullTest_24, InequalityOperatorDifferentInstances_24) {

    EXPECT_FALSE(null1 != null2);

}
