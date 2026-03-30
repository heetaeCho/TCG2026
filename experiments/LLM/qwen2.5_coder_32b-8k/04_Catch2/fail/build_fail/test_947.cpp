#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function to be tested is part of a class or namespace.

// Since no class is provided, we will assume it's in a namespace for testing purposes.



namespace TestNamespace {



using Catch::Detail::check_element_counts;



template <typename ForwardIter1, typename Sentinel1, typename ForwardIter2, typename Sentinel2, typename Comparator>

constexpr bool check_element_counts(ForwardIter1 first_1, const Sentinel1 end_1, ForwardIter2 first_2, const Sentinel2 end_2, Comparator cmp) {

    return Catch::Detail::check_element_counts(first_1, end_1, first_2, end_2, cmp);

}



} // namespace TestNamespace



namespace {



TEST(CheckElementCountsTest_947, EqualElements_947) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {3, 2, 1};



    EXPECT_TRUE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, DifferentElements_947) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {4, 5, 6};



    EXPECT_FALSE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, ExtraElementInFirst_947) {

    std::vector<int> vec1 = {1, 2, 3, 4};

    std::vector<int> vec2 = {1, 2, 3};



    EXPECT_FALSE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, ExtraElementInSecond_947) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {1, 2, 3, 4};



    EXPECT_FALSE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, DuplicateElementsSameCount_947) {

    std::vector<int> vec1 = {1, 1, 2, 3};

    std::vector<int> vec2 = {1, 2, 3, 1};



    EXPECT_TRUE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, DifferentCountElements_947) {

    std::vector<int> vec1 = {1, 1, 2, 3};

    std::vector<int> vec2 = {1, 2, 3};



    EXPECT_FALSE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, EmptyVectors_947) {

    std::vector<int> vec1 = {};

    std::vector<int> vec2 = {};



    EXPECT_TRUE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, FirstVectorEmpty_947) {

    std::vector<int> vec1 = {};

    std::vector<int> vec2 = {1, 2, 3};



    EXPECT_TRUE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



TEST(CheckElementCountsTest_947, SecondVectorEmpty_947) {

    std::vector<int> vec1 = {1, 2, 3};

    std::vector<int> vec2 = {};



    EXPECT_FALSE(TestNamespace::check_element_counts(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::equal_to<>()));

}



} // namespace
