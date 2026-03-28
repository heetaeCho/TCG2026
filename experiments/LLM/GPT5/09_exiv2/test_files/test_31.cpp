#include <gtest/gtest.h>
#include <algorithm> // for std::find
#include <vector>

namespace Exiv2 {
    template <typename T, typename K, size_t N>
    const T* find(T (&src)[N], const K& key) {
        static_assert(N > 0, "Passed zero length find");
        auto rc = std::find(src, src + N, key);
        return rc == src + N ? nullptr : rc;
    }
}

TEST(Exiv2FindTest_31, FindElementInArray_31) {
    int arr[] = {1, 2, 3, 4, 5};
    int key = 3;
    const int* result = Exiv2::find(arr, key);
    ASSERT_NE(result, nullptr); // Expect a non-null result
    EXPECT_EQ(*result, key);    // The value pointed to should be equal to key
}

TEST(Exiv2FindTest_32, FindElementNotInArray_32) {
    int arr[] = {1, 2, 3, 4, 5};
    int key = 6;
    const int* result = Exiv2::find(arr, key);
    EXPECT_EQ(result, nullptr); // Expect a null result since the key is not in the array
}

TEST(Exiv2FindTest_33, FindElementInEmptyArray_33) {
    int arr[] = {}; // Empty array
    int key = 1;
    const int* result = Exiv2::find(arr, key);
    EXPECT_EQ(result, nullptr); // Expect a null result since the array is empty
}

TEST(Exiv2FindTest_34, FindElementAtStart_34) {
    int arr[] = {1, 2, 3, 4, 5};
    int key = 1;
    const int* result = Exiv2::find(arr, key);
    ASSERT_NE(result, nullptr); // Expect a non-null result
    EXPECT_EQ(*result, key);    // The value should be the key, as it's at the start of the array
}

TEST(Exiv2FindTest_35, FindElementAtEnd_35) {
    int arr[] = {1, 2, 3, 4, 5};
    int key = 5;
    const int* result = Exiv2::find(arr, key);
    ASSERT_NE(result, nullptr); // Expect a non-null result
    EXPECT_EQ(*result, key);    // The value should be the key, as it's at the end of the array
}

TEST(Exiv2FindTest_36, TestZeroLengthArray_36) {
    int arr[] = {}; // Empty array
    int key = 1;
    // This should trigger static_assert failure due to zero-length array
    EXPECT_DEATH(Exiv2::find(arr, key), "Passed zero length find");
}