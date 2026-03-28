#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::Return;

using ::testing::_;



// Mocking a simple predicate for testing purposes

class MockPredicate {

public:

    MOCK_METHOD1(operator(), bool(const int&));

};



TEST_F(FilterGeneratorTest_923, GetReturnsFilteredValue_923) {

    GeneratorWrapper<int> gen({1, 2, 3, 4, 5});

    MockPredicate mockPred;

    

    EXPECT_CALL(mockPred, operator()(1)).WillOnce(Return(false));

    EXPECT_CALL(mockPred, operator()(2)).WillOnce(Return(true));



    FilterGenerator<int, MockPredicate> filterGen(mockPred, std::move(gen));



    ASSERT_TRUE(filterGen.next());

    EXPECT_EQ(2, filterGen.get());

}



TEST_F(FilterGeneratorTest_923, NextSkipsFilteredValues_923) {

    GeneratorWrapper<int> gen({1, 2, 3});

    MockPredicate mockPred;

    

    EXPECT_CALL(mockPred, operator()(1)).WillOnce(Return(false));

    EXPECT_CALL(mockPred, operator()(2)).WillOnce(Return(false));

    EXPECT_CALL(mockPred, operator()(3)).WillOnce(Return(true));



    FilterGenerator<int, MockPredicate> filterGen(mockPred, std::move(gen));



    ASSERT_TRUE(filterGen.next());

    EXPECT_EQ(3, filterGen.get());

}



TEST_F(FilterGeneratorTest_923, NextReturnsFalseWhenNoMoreValues_923) {

    GeneratorWrapper<int> gen({1});

    MockPredicate mockPred;

    

    EXPECT_CALL(mockPred, operator()(1)).WillOnce(Return(false));



    FilterGenerator<int, MockPredicate> filterGen(mockPred, std::move(gen));



    ASSERT_FALSE(filterGen.next());

}



TEST_F(FilterGeneratorTest_923, GetThrowsWhenNoCurrent_923) {

    GeneratorWrapper<int> gen({1});

    MockPredicate mockPred;

    

    EXPECT_CALL(mockPred, operator()(1)).WillOnce(Return(false));



    FilterGenerator<int, MockPredicate> filterGen(mockPred, std::move(gen));

    ASSERT_FALSE(filterGen.next());



    EXPECT_THROW(filterGen.get(), std::runtime_error);

}



TEST_F(FilterGeneratorTest_923, AllValuesFilteredOut_923) {

    GeneratorWrapper<int> gen({1, 2, 3});

    MockPredicate mockPred;

    

    EXPECT_CALL(mockPred, operator()(1)).WillOnce(Return(false));

    EXPECT_CALL(mockPred, operator()(2)).WillOnce(Return(false));

    EXPECT_CALL(mockPred, operator()(3)).WillOnce(Return(false));



    FilterGenerator<int, MockPredicate> filterGen(mockPred, std::move(gen));



    ASSERT_FALSE(filterGen.next());

}
