#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch;

using namespace Catch::Generators;



class FilterGeneratorMock : public IGenerator<int> {

public:

    MOCK_METHOD(const int&, get, (), (const, override));

    MOCK_METHOD(bool, next, (), (override));

};



class FilterGeneratorTest_924 : public ::testing::Test {

protected:

    std::shared_ptr<FilterGeneratorMock> mock_generator;

    Predicate<int> always_true = [](int) { return true; };

    Predicate<int> always_false = [](int) { return false; };



    void SetUp() override {

        mock_generator = std::make_shared<FilterGeneratorMock>();

    }

};



TEST_F(FilterGeneratorTest_924, NextReturnsFalseWhenUnderlyingGeneratorExhausted_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(false));

    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));



    EXPECT_FALSE(filter.next());

}



TEST_F(FilterGeneratorTest_924, NextReturnsTrueWhenUnderlyingGeneratorProvidesMatchingElement_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_generator, get()).WillOnce(::testing::Return(1));

    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));



    EXPECT_TRUE(filter.next());

}



TEST_F(FilterGeneratorTest_924, NextSkipsNonMatchingElementsFromUnderlyingGenerator_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(true))

                                        .WillOnce(::testing::Return(true))

                                        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(::testing::Return(0))  // Non-matching

        .WillOnce(::testing::Return(1));  // Matching



    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));



    EXPECT_TRUE(filter.next());

}



TEST_F(FilterGeneratorTest_924, NextReturnsFalseWhenNoMatchingElementsAreAvailable_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(true))

                                        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(::testing::Return(0));  // Non-matching



    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));



    EXPECT_FALSE(filter.next());

}



TEST_F(FilterGeneratorTest_924, GetReturnsCurrentElementAfterNext_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_generator, get()).WillOnce(::testing::Return(1));



    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));

    filter.next();



    EXPECT_EQ(filter.get(), 1);

}



TEST_F(FilterGeneratorTest_924, GetThrowsWhenNoElementIsAvailable_924) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(false));



    FilterGenerator<int> filter(always_true, GeneratorWrapper<int>(mock_generator));

    EXPECT_FALSE(filter.next());



    EXPECT_THROW(filter.get(), std::logic_error);

}
