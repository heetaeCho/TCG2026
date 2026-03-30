#include <gtest/gtest.h>

#include <yaml-cpp/src/ptr_vector.h>



class PtrVectorTest_71 : public ::testing::Test {

protected:

    YAML::ptr_vector<int> ptrVec;

};



TEST_F(PtrVectorTest_71, SizeInitiallyZero_71) {

    EXPECT_EQ(ptrVec.size(), 0);

}



TEST_F(PtrVectorTest_71, EmptyInitiallyTrue_71) {

    EXPECT_TRUE(ptrVec.empty());

}



TEST_F(PtrVectorTest_71, PushBackIncreasesSize_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    EXPECT_EQ(ptrVec.size(), 1);

}



TEST_F(PtrVectorTest_71, PushBackChangesEmptyToFalse_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    EXPECT_FALSE(ptrVec.empty());

}



TEST_F(PtrVectorTest_71, BackReturnsLastElement_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    EXPECT_EQ(ptrVec.back(), 42);

}



TEST_F(PtrVectorTest_71, OperatorAccessReturnsCorrectElement_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    EXPECT_EQ(ptrVec[0], 42);

}



TEST_F(PtrVectorTest_71, ClearReducesSizeToZero_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    ptrVec.clear();

    EXPECT_EQ(ptrVec.size(), 0);

}



TEST_F(PtrVectorTest_71, ClearChangesEmptyToTrue_71) {

    ptrVec.push_back(std::make_unique<int>(42));

    ptrVec.clear();

    EXPECT_TRUE(ptrVec.empty());

}



TEST_F(PtrVectorTest_71, BackThrowsOnEmpty_71) {

    EXPECT_THROW(ptrVec.back(), std::out_of_range);

}



TEST_F(PtrVectorTest_71, OperatorAccessThrowsOnInvalidIndex_71) {

    EXPECT_THROW(ptrVec[0], std::out_of_range);

}
