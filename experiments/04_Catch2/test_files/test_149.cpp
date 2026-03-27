#include <gtest/gtest.h>

#include <Catch2/matchers/catch_matchers_templated.hpp>



namespace Catch { namespace Matchers { namespace Detail {



template<std::size_t N>

class ArrayCatTest : public ::testing::Test {

protected:

    std::array<void const*, N> lhs;

    void const* rhs = reinterpret_cast<void const*>(0x1234);

};



using TestTypes = ::testing::Types<0, 1, 5>;

TYPED_TEST_SUITE(ArrayCatTest, TestTypes);



TYPED_TEST(ArrayCatTest, AddsElementToEmptyArray_149) {

    if (std::is_same_v<std::integral_constant<std::size_t, TypeParam>, std::integral_constant<std::size_t, 0>>) {

        auto result = array_cat(std::move(this->lhs), this->rhs);

        EXPECT_EQ(result.size(), 1);

        EXPECT_EQ(result[0], this->rhs);

    }

}



TYPED_TEST(ArrayCatTest, AddsElementToArray_149) {

    if (!std::is_same_v<std::integral_constant<std::size_t, TypeParam>, std::integral_constant<std::size_t, 0>>) {

        for (std::size_t i = 0; i < this->lhs.size(); ++i) {

            this->lhs[i] = reinterpret_cast<void const*>(i);

        }

        auto result = array_cat(std::move(this->lhs), this->rhs);

        EXPECT_EQ(result.size(), TypeParam + 1);

        for (std::size_t i = 0; i < this->lhs.size(); ++i) {

            EXPECT_EQ(result[i], this->lhs[i]);

        }

        EXPECT_EQ(result[TypeParam], this->rhs);

    }

}



TYPED_TEST(ArrayCatTest, OriginalArrayNotModified_149) {

    if (!std::is_same_v<std::integral_constant<std::size_t, TypeParam>, std::integral_constant<std::size_t, 0>>) {

        for (std::size_t i = 0; i < this->lhs.size(); ++i) {

            this->lhs[i] = reinterpret_cast<void const*>(i);

        }

        auto original_lhs = this->lhs;

        array_cat(std::move(this->lhs), this->rhs);

        EXPECT_EQ(original_lhs, this->lhs); // lhs is moved and should not be relied upon after move

    }

}



} } }


