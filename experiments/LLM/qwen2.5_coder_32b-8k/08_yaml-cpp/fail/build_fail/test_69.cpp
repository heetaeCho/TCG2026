#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"



using namespace YAML;



class PtrVectorTest_69 : public ::testing::Test {

protected:

    ptr_vector<int> test_vector;

};



TEST_F(PtrVectorTest_69, PushBackIncreasesSize_69) {

    std::unique_ptr<int> ptr1 = std::make_unique<int>(1);

    std::unique_ptr<int> ptr2 = std::make_unique<int>(2);



    EXPECT_EQ(test_vector.size(), 0);

    test_vector.push_back(std::move(ptr1));

    EXPECT_EQ(test_vector.size(), 1);

    test_vector.push_back(std::move(ptr2));

    EXPECT_EQ(test_vector.size(), 2);

}



TEST_F(PtrVectorTest_69, PushBackRetainsValue_69) {

    std::unique_ptr<int> ptr = std::make_unique<int>(42);



    test_vector.push_back(std::move(ptr));



    EXPECT_EQ(*test_vector[0], 42);

}



TEST_F(PtrVectorTest_69, BackReturnsLastElement_69) {

    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);

    std::unique_ptr<int> ptr2 = std::make_unique<int>(20);



    test_vector.push_back(std::move(ptr1));

    test_vector.push_back(std::move(ptr2));



    EXPECT_EQ(test_vector.back(), 20);

}



TEST_F(PtrVectorTest_69, EmptyReturnsTrueWhenEmpty_69) {

    EXPECT_TRUE(test_vector.empty());

}



TEST_F(PtrVectorTest_69, EmptyReturnsFalseWhenNotEmpty_69) {

    std::unique_ptr<int> ptr = std::make_unique<int>(5);



    test_vector.push_back(std::move(ptr));



    EXPECT_FALSE(test_vector.empty());

}



TEST_F(PtrVectorTest_69, ClearEmptiesTheVector_69) {

    std::unique_ptr<int> ptr1 = std::make_unique<int>(1);

    std::unique_ptr<int> ptr2 = std::make_unique<int>(2);



    test_vector.push_back(std::move(ptr1));

    test_vector.push_back(std::move(ptr2));



    EXPECT_FALSE(test_vector.empty());

    test_vector.clear();

    EXPECT_TRUE(test_vector.empty());

}



TEST_F(PtrVectorTest_69, OperatorSquareBracketAccessesElements_69) {

    std::unique_ptr<int> ptr1 = std::make_unique<int>(100);

    std::unique_ptr<int> ptr2 = std::make_unique<int>(200);



    test_vector.push_back(std::move(ptr1));

    test_vector.push_back(std::move(ptr2));



    EXPECT_EQ(test_vector[0], 100);

    EXPECT_EQ(test_vector[1], 200);

}



TEST_F(PtrVectorTest_69, SizeReturnsZeroAfterClear_69) {

    std::unique_ptr<int> ptr = std::make_unique<int>(3);



    test_vector.push_back(std::move(ptr));

    EXPECT_EQ(test_vector.size(), 1);



    test_vector.clear();

    EXPECT_EQ(test_vector.size(), 0);

}
