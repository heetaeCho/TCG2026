#include <gtest/gtest.h>

#include "yaml-cpp/depthguard.h"



class DeepRecursionTest_91 : public ::testing::Test {

protected:

    YAML::DeepRecursion CreateDeepRecursionInstance(int depth, const YAML::Mark& mark, const std::string& msg) {

        return YAML::DeepRecursion(depth, mark, msg);

    }

};



TEST_F(DeepRecursionTest_91, DepthReturnsCorrectValue_91) {

    YAML::Mark dummyMark;

    std::string dummyMsg = "Dummy message";

    int testDepth = 5;



    YAML::DeepRecursion dr = CreateDeepRecursionInstance(testDepth, dummyMark, dummyMsg);



    EXPECT_EQ(dr.depth(), testDepth);

}



TEST_F(DeepRecursionTest_91, DepthBoundaryConditionZero_91) {

    YAML::Mark dummyMark;

    std::string dummyMsg = "Dummy message";

    int testDepth = 0;



    YAML::DeepRecursion dr = CreateDeepRecursionInstance(testDepth, dummyMark, dummyMsg);



    EXPECT_EQ(dr.depth(), testDepth);

}



TEST_F(DeepRecursionTest_91, DepthBoundaryConditionNegative_91) {

    YAML::Mark dummyMark;

    std::string dummyMsg = "Dummy message";

    int testDepth = -5;



    YAML::DeepRecursion dr = CreateDeepRecursionInstance(testDepth, dummyMark, dummyMsg);



    EXPECT_EQ(dr.depth(), testDepth);

}



TEST_F(DeepRecursionTest_91, DepthBoundaryConditionLargeValue_91) {

    YAML::Mark dummyMark;

    std::string dummyMsg = "Dummy message";

    int testDepth = 1000;



    YAML::DeepRecursion dr = CreateDeepRecursionInstance(testDepth, dummyMark, dummyMsg);



    EXPECT_EQ(dr.depth(), testDepth);

}
