#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_templated.hpp"



namespace Catch { namespace Matchers { namespace Detail {



TEST(array_cat_TEST_150, NormalOperationWithEmptyArray_150) {

    void* lhs = reinterpret_cast<void*>(0x1);

    std::array<void const*, 0> rhs = {};

    auto result = array_cat(lhs, std::move(rhs));

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], lhs);

}



TEST(array_cat_TEST_150, NormalOperationWithNonEmptyArray_150) {

    void* lhs = reinterpret_cast<void*>(0x1);

    std::array<void const*, 2> rhs = {reinterpret_cast<void*>(0x2), reinterpret_cast<void*>(0x3)};

    auto result = array_cat(lhs, std::move(rhs));

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], lhs);

    EXPECT_EQ(result[1], rhs[0]);

    EXPECT_EQ(result[2], rhs[1]);

}



TEST(array_cat_TEST_150, BoundaryConditionWithSingleElementArray_150) {

    void* lhs = reinterpret_cast<void*>(0x1);

    std::array<void const*, 1> rhs = {reinterpret_cast<void*>(0x2)};

    auto result = array_cat(lhs, std::move(rhs));

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], lhs);

    EXPECT_EQ(result[1], rhs[0]);

}



TEST(array_cat_TEST_150, BoundaryConditionWithLargeArray_150) {

    void* lhs = reinterpret_cast<void*>(0x1);

    std::array<void const*, 10> rhs = {reinterpret_cast<void*>(0x2), reinterpret_cast<void*>(0x3),

                                       reinterpret_cast<void*>(0x4), reinterpret_cast<void*>(0x5),

                                       reinterpret_cast<void*>(0x6), reinterpret_cast<void*>(0x7),

                                       reinterpret_cast<void*>(0x8), reinterpret_cast<void*>(0x9),

                                       reinterpret_cast<void*>(0xA), reinterpret_cast<void*>(0xB)};

    auto result = array_cat(lhs, std::move(rhs));

    ASSERT_EQ(result.size(), 11);

    EXPECT_EQ(result[0], lhs);

    for (size_t i = 0; i < rhs.size(); ++i) {

        EXPECT_EQ(result[i + 1], rhs[i]);

    }

}



}}}
