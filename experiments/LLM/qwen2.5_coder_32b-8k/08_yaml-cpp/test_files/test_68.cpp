#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"

#include <memory>



using namespace YAML;



class PtrVectorTest_68 : public ::testing::Test {

protected:

    ptr_vector<int> vec;

};



TEST_F(PtrVectorTest_68, DefaultConstructorCreatesEmptyVector_68) {

    EXPECT_TRUE(vec.empty());

}



TEST_F(PtrVectorTest_68, PushBackIncreasesSize_68) {

    vec.push_back(std::make_unique<int>(42));

    EXPECT_FALSE(vec.empty());

    EXPECT_EQ(vec.size(), 1);

}



TEST_F(PtrVectorTest_68, ClearEmptiesVector_68) {

    vec.push_back(std::make_unique<int>(42));

    vec.clear();

    EXPECT_TRUE(vec.empty());

    EXPECT_EQ(vec.size(), 0);

}



TEST_F(PtrVectorTest_68, AccessOperatorReturnsCorrectElement_68) {

    vec.push_back(std::make_unique<int>(42));

    EXPECT_EQ(*vec[0], 42);

}



TEST_F(PtrVectorTest_68, BackReturnsLastElement_68) {

    vec.push_back(std::make_unique<int>(42));

    vec.push_back(std::make_unique<int>(13));

    EXPECT_EQ(vec.back(), 13);

}



TEST_F(PtrVectorTest_68, SizeReturnsCorrectCount_68) {

    vec.push_back(std::make_unique<int>(42));

    vec.push_back(std::make_unique<int>(13));

    EXPECT_EQ(vec.size(), 2);

}



TEST_F(PtrVectorTest_68, AccessOperatorThrowsOnEmptyVector_68) {

    EXPECT_THROW(vec[0], std::out_of_range);

}



TEST_F(PtrVectorTest_68, BackThrowsOnEmptyVector_68) {

    EXPECT_THROW(vec.back(), std::out_of_range);

}
