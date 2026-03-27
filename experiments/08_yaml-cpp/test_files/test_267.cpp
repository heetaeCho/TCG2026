#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



// Fixture for array tests

template <typename T, std::size_t N>

class ArrayTest : public ::testing::Test {

protected:

    array<T, N> arr;

};



typedef ::testing::Types<int, double, char> Implementations;

TYPED_TEST_SUITE(ArrayTest, Implementations);



// Test normal operation: accessing valid index

TYPETEST(ArrayTest, AccessValidIndex_267) {

    this->arr.data_[0] = TypeParam{1};

    EXPECT_EQ(this->arr[0], TypeParam{1});

}



// Test boundary condition: accessing first element

TYPETEST(ArrayTest, AccessFirstElement_267) {

    if constexpr (N > 0) {

        this->arr.data_[0] = TypeParam{42};

        EXPECT_EQ(this->arr[0], TypeParam{42});

    }

}



// Test boundary condition: accessing last element

TYPETEST(ArrayTest, AccessLastElement_267) {

    if constexpr (N > 0) {

        this->arr.data_[N - 1] = TypeParam{84};

        EXPECT_EQ(this->arr[N - 1], TypeParam{84});

    }

}



// Test exceptional case: accessing out of bounds index

TYPETEST(ArrayTest, AccessOutOfBounds_267) {

    if constexpr (N > 0) {

        EXPECT_THROW({

            [[maybe_unused]] auto value = this->arr[N];

        }, std::out_of_range);

    } else {

        EXPECT_THROW({

            [[maybe_unused]] auto value = this->arr[0];

        }, std::out_of_range);

    }

}

```



Note: The above test assumes that accessing an out-of-bounds index would throw `std::out_of_range`. However, the provided code snippet has a `noexcept` specifier, which suggests no exceptions are thrown. If `noexcept` is correct and no exceptions are expected, then the out-of-bounds tests should be adjusted to check for undefined behavior or some other form of error handling if available in the actual implementation. Given the constraints, I've included the exception test as a hypothetical scenario based on typical C++ practices.


