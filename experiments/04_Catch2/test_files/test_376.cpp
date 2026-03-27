#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class BoundValueRefTest_376 : public ::testing::Test {

protected:

    int intValue;

    std::vector<std::string> vectorValue;



    void SetUp() override {

        intValue = 0;

        vectorValue.clear();

    }



    BoundValueRef<int> intBoundRef{intValue};

    BoundValueRef<std::vector<std::string>> vectorBoundRef{vectorValue};

};



TEST_F(BoundValueRefTest_376, SetValueForInt_376) {

    EXPECT_EQ(intBoundRef.setValue("42").ok(), true);

    EXPECT_EQ(intValue, 42);

}



TEST_F(BoundValueRefTest_376, SetValueForVector_376) {

    EXPECT_EQ(vectorBoundRef.setValue("test1").ok(), true);

    EXPECT_EQ(vectorValue.size(), 1);

    EXPECT_EQ(vectorValue[0], "test1");



    EXPECT_EQ(vectorBoundRef.setValue("test2").ok(), true);

    EXPECT_EQ(vectorValue.size(), 2);

    EXPECT_EQ(vectorValue[1], "test2");

}



TEST_F(BoundValueRefTest_376, SetValueForInvalidInt_376) {

    EXPECT_EQ(intBoundRef.setValue("abc").ok(), false);

    EXPECT_EQ(intValue, 0); // Ensure no change on invalid input

}



TEST_F(BoundValueRefTest_376, IsContainerForVector_376) {

    EXPECT_TRUE(vectorBoundRef.isContainer());

}



TEST_F(BoundValueRefTest_376, IsContainerForInt_376) {

    EXPECT_FALSE(intBoundRef.isContainer());

}
