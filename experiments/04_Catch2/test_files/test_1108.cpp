#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch;

using namespace Catch::Generators;



class FilterGeneratorTest_1108 : public ::testing::Test {

protected:

    struct TestPredicate {

        bool operator()(int value) const { return value % 2 == 0; }

    };



    GeneratorWrapper<int> generator;

    FilterGenerator<int, TestPredicate> filter_generator;



    FilterGeneratorTest_1108() 

        : generator(Generators::FixedValues<int>{1, 2, 3, 4}),

          filter_generator(TestPredicate{}, std::move(generator)) {}

};



TEST_F(FilterGeneratorTest_1108, InitialValueIsEven_1108) {

    EXPECT_EQ(filter_generator.get(), 2);

}



TEST_F(FilterGeneratorTest_1108, NextAdvancesToNextEven_1108) {

    filter_generator.next();

    EXPECT_EQ(filter_generator.get(), 4);

}



TEST_F(FilterGeneratorTest_1108, EndOfSequence_1108) {

    filter_generator.next();

    filter_generator.next();

    EXPECT_FALSE(filter_generator.next());

}



TEST_F(FilterGeneratorTest_1108, NoEvenValues_1108) {

    GeneratorWrapper<int> odd_generator(Generators::FixedValues<int>{1, 3, 5});

    FilterGenerator<int, TestPredicate> no_even_filter(TestPredicate{}, std::move(odd_generator));

    EXPECT_THROW(no_even_filter.get(), Catch::Detail::generatorexception);

}



TEST_F(FilterGeneratorTest_1108, SingleEvenValue_1108) {

    GeneratorWrapper<int> single_even_generator(Generators::FixedValues<int>{1, 2});

    FilterGenerator<int, TestPredicate> single_even_filter(TestPredicate{}, std::move(single_even_generator));

    EXPECT_EQ(single_even_filter.get(), 2);

    EXPECT_FALSE(single_even_filter.next());

}



TEST_F(FilterGeneratorTest_1108, MultipleEvenValues_1108) {

    GeneratorWrapper<int> multiple_evens(Generators::FixedValues<int>{1, 2, 4, 6, 8});

    FilterGenerator<int, TestPredicate> multiple_evens_filter(TestPredicate{}, std::move(multiple_evens));

    EXPECT_EQ(multiple_evens_filter.get(), 2);

    multiple_evens_filter.next();

    EXPECT_EQ(multiple_evens_filter.get(), 4);

    multiple_evens_filter.next();

    EXPECT_EQ(multiple_evens_filter.get(), 6);

    multiple_evens_filter.next();

    EXPECT_EQ(multiple_evens_filter.get(), 8);

    multiple_evens_filter.next();

    EXPECT_FALSE(multiple_evens_filter.next());

}
