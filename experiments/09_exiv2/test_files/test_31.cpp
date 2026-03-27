#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace testing;



TEST(Exiv2FindTest_31, NormalOperation_Found_31) {

    int arr[] = {1, 2, 3, 4, 5};

    const int* result = find(arr, 3);

    EXPECT_EQ(result, &arr[2]);

}



TEST(Exiv2FindTest_31, NormalOperation_NotFound_31) {

    int arr[] = {1, 2, 3, 4, 5};

    const int* result = find(arr, 6);

    EXPECT_EQ(result, nullptr);

}



TEST(Exiv2FindTest_31, BoundaryCondition_FirstElement_31) {

    int arr[] = {1, 2, 3, 4, 5};

    const int* result = find(arr, 1);

    EXPECT_EQ(result, &arr[0]);

}



TEST(Exiv2FindTest_31, BoundaryCondition_LastElement_31) {

    int arr[] = {1, 2, 3, 4, 5};

    const int* result = find(arr, 5);

    EXPECT_EQ(result, &arr[4]);

}



TEST(Exiv2FindTest_31, BoundaryCondition_EmptyArrayStaticAssert_31) {

    // This test case is more of a compile-time check due to static_assert.

    // If the array size is 0, the code will not compile. Thus, we cannot have a runtime test for this.

}



TEST(Exiv2FindTest_31, DifferentTypes_Found_31) {

    std::string arr[] = {"apple", "banana", "cherry"};

    const std::string* result = find(arr, "banana");

    EXPECT_EQ(result, &arr[1]);

}



TEST(Exiv2FindTest_31, DifferentTypes_NotFound_31) {

    std::string arr[] = {"apple", "banana", "cherry"};

    const std::string* result = find(arr, "orange");

    EXPECT_EQ(result, nullptr);

}
