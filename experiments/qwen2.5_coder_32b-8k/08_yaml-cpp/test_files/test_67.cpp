#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"

#include <memory>



using namespace YAML;



class PtrVectorTest_67 : public ::testing::Test {

protected:

    ptr_vector<int> vec;

};



TEST_F(PtrVectorTest_67, SizeInitiallyZero_67) {

    EXPECT_EQ(vec.size(), 0);

}



TEST_F(PtrVectorTest_67, EmptyInitiallyTrue_67) {

    EXPECT_TRUE(vec.empty());

}



TEST_F(PtrVectorTest_67, PushBackIncreasesSize_67) {

    vec.push_back(std::make_unique<int>(1));

    EXPECT_EQ(vec.size(), 1);

}



TEST_F(PtrVectorTest_67, EmptyFalseAfterPushBack_67) {

    vec.push_back(std::make_unique<int>(1));

    EXPECT_FALSE(vec.empty());

}



TEST_F(PtrVectorTest_67, BackReturnsCorrectElement_67) {

    vec.push_back(std::make_unique<int>(42));

    EXPECT_EQ(*vec.back(), 42);

}



TEST_F(PtrVectorTest_67, OperatorBracketAccessesElements_67) {

    vec.push_back(std::make_unique<int>(10));

    vec.push_back(std::make_unique<int>(20));

    EXPECT_EQ(vec[0], 10);

    EXPECT_EQ(vec[1], 20);

}



TEST_F(PtrVectorTest_67, ClearResetsSizeToZero_67) {

    vec.push_back(std::make_unique<int>(1));

    vec.clear();

    EXPECT_EQ(vec.size(), 0);

}



TEST_F(PtrVectorTest_67, ClearSetsEmptyToTrue_67) {

    vec.push_back(std::make_unique<int>(1));

    vec.clear();

    EXPECT_TRUE(vec.empty());

}



TEST_F(PtrVectorTest_67, OperatorBracketThrowsOnOutOfRange_67) {

    EXPECT_THROW(vec[0], std::out_of_range);

}
