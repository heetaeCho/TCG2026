#include <gtest/gtest.h>

#include "ptr_vector.h"



namespace YAML {

    class MockObject {

    public:

        MOCK_METHOD0(method, void());

    };

}



using namespace YAML;



class PtrVectorTest_70 : public ::testing::Test {

protected:

    ptr_vector<MockObject> vec;

};



TEST_F(PtrVectorTest_70, EmptyOnInit_70) {

    EXPECT_TRUE(vec.empty());

    EXPECT_EQ(vec.size(), 0);

}



TEST_F(PtrVectorTest_70, SizeIncreasesAfterPushBack_70) {

    auto obj = std::make_unique<MockObject>();

    vec.push_back(std::move(obj));

    EXPECT_FALSE(vec.empty());

    EXPECT_EQ(vec.size(), 1);

}



TEST_F(PtrVectorTest_70, AccessOperatorReturnsCorrectElement_70) {

    auto obj = std::make_unique<MockObject>();

    vec.push_back(std::move(obj));



    MockObject& retrievedObj = vec[0];

    EXPECT_EQ(&retrievedObj, vec.m_data[0].get());

}



TEST_F(PtrVectorTest_70, BackReturnsLastElement_70) {

    auto obj1 = std::make_unique<MockObject>();

    auto obj2 = std::make_unique<MockObject>();



    vec.push_back(std::move(obj1));

    vec.push_back(std::move(obj2));



    MockObject& lastObj = vec.back();

    EXPECT_EQ(&lastObj, vec.m_data[1].get());

}



TEST_F(PtrVectorTest_70, ClearEmptiesTheVector_70) {

    auto obj1 = std::make_unique<MockObject>();

    auto obj2 = std::make_unique<MockObject>();



    vec.push_back(std::move(obj1));

    vec.push_back(std::move(obj2));



    vec.clear();

    EXPECT_TRUE(vec.empty());

    EXPECT_EQ(vec.size(), 0);

}



TEST_F(PtrVectorTest_70, AccessOperatorThrowsOnOutOfBound_70) {

    EXPECT_THROW(vec[0], std::out_of_range);

}



TEST_F(PtrVectorTest_70, BackThrowsOnEmptyVector_70) {

    EXPECT_THROW(vec.back(), std::out_of_range);

}
