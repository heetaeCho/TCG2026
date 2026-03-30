#include <gtest/gtest.h>

#include "yaml-cpp/null.h"



namespace YAML {



class NullTest_23 : public ::testing::Test {

protected:

    _Null null1;

    _Null null2;

};



TEST_F(NullTest_23, EqualityOperator_ReturnsTrueForSameNullObjects_23) {

    EXPECT_EQ(null1, null2);

}



TEST_F(NullTest_23, EqualityOperator_ReturnsTrueForSelfComparison_23) {

    EXPECT_EQ(null1, null1);

}



}  // namespace YAML
