#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"



using namespace YAML;



class PtrVectorTest_66 : public ::testing::Test {

protected:

    ptr_vector<int> vector;

};



TEST_F(PtrVectorTest_66, ClearRemovesAllElements_66) {

    vector.push_back(std::make_unique<int>(1));

    vector.push_back(std::make_unique<int>(2));

    vector.clear();

    EXPECT_TRUE(vector.empty());

}



TEST_F(PtrVectorTest_66, SizeReturnsCorrectCount_66) {

    EXPECT_EQ(vector.size(), 0);

    vector.push_back(std::make_unique<int>(1));

    EXPECT_EQ(vector.size(), 1);

    vector.push_back(std::make_unique<int>(2));

    EXPECT_EQ(vector.size(), 2);

}



TEST_F(PtrVectorTest_66, EmptyReturnsTrueForEmptyVector_66) {

    EXPECT_TRUE(vector.empty());

}



TEST_F(PtrVectorTest_66, EmptyReturnsFalseForNonEmptyVector_66) {

    vector.push_back(std::make_unique<int>(1));

    EXPECT_FALSE(vector.empty());

}



TEST_F(PtrVectorTest_66, PushBackAddsElement_66) {

    vector.push_back(std::make_unique<int>(42));

    EXPECT_EQ(vector.size(), 1);

    EXPECT_EQ(*vector[0], 42);

}



TEST_F(PtrVectorTest_66, OperatorIndexAccessesCorrectElement_66) {

    vector.push_back(std::make_unique<int>(10));

    vector.push_back(std::make_unique<int>(20));

    EXPECT_EQ(vector[0], 10);

    EXPECT_EQ(vector[1], 20);

}



TEST_F(PtrVectorTest_66, BackReturnsLastElement_66) {

    vector.push_back(std::make_unique<int>(30));

    vector.push_back(std::make_unique<int>(40));

    EXPECT_EQ(vector.back(), 40);

}



TEST_F(PtrVectorTest_66, AccessingOutOfBoundsThrowsException_66) {

    EXPECT_THROW(vector[0], std::out_of_range);

}



TEST_F(PtrVectorTest_66, BackOnEmptyVectorThrowsException_66) {

    EXPECT_THROW(vector.back(), std::out_of_range);

}
