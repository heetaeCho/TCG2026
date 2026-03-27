#include <gtest/gtest.h>

#include <array>

#include <Catch2/matchers/catch_matchers_templated.hpp>



namespace Catch { namespace Matchers { namespace Detail {



class ArrayCatTest_148 : public ::testing::Test {

protected:

    std::array<void const*, 3> lhs = {reinterpret_cast<void const*>(0x1), reinterpret_cast<void const*>(0x2), reinterpret_cast<void const*>(0x3)};

    std::array<void const*, 2> rhs = {reinterpret_cast<void const*>(0x4), reinterpret_cast<void const*>(0x5)};

};



TEST_F(ArrayCatTest_148, ConcatenatesArraysProperly_148) {

    auto result = array_cat(std::move(lhs), std::move(rhs));

    std::array<void const*, 5> expected = {reinterpret_cast<void const*>(0x1), reinterpret_cast<void const*>(0x2), reinterpret_cast<void const*>(0x3), reinterpret_cast<void const*>(0x4), reinterpret_cast<void const*>(0x5)};

    EXPECT_EQ(result, expected);

}



TEST_F(ArrayCatTest_148, HandlesEmptyLeftArray_148) {

    std::array<void const*, 0> empty_lhs;

    auto result = array_cat(std::move(empty_lhs), std::move(rhs));

    std::array<void const*, 2> expected = {reinterpret_cast<void const*>(0x4), reinterpret_cast<void const*>(0x5)};

    EXPECT_EQ(result, expected);

}



TEST_F(ArrayCatTest_148, HandlesEmptyRightArray_148) {

    std::array<void const*, 0> empty_rhs;

    auto result = array_cat(std::move(lhs), std::move(empty_rhs));

    std::array<void const*, 3> expected = {reinterpret_cast<void const*>(0x1), reinterpret_cast<void const*>(0x2), reinterpret_cast<void const*>(0x3)};

    EXPECT_EQ(result, expected);

}



TEST_F(ArrayCatTest_148, HandlesBothEmptyArrays_148) {

    std::array<void const*, 0> empty_lhs;

    std::array<void const*, 0> empty_rhs;

    auto result = array_cat(std::move(empty_lhs), std::move(empty_rhs));

    std::array<void const*, 0> expected = {};

    EXPECT_EQ(result, expected);

}



} } }
