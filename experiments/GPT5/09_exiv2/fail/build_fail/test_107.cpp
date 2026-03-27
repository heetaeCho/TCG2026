#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstddef>
#include <utility>

// Include the header file to test
#include "./TestProjects/exiv2/src/tiffimage_int.hpp"

// Unit test suite for TiffGroupKey_hash
namespace Exiv2 { namespace Internal {

// TEST CASE 1: Normal Operation
TEST_F(TiffGroupKey_hash_107, HashComputationForValidTiffGroupKey_107) {
    TiffGroupKey pair(42, 1001);  // Example pair
    TiffGroupKey_hash hash_fn;

    // Expected hash value should be computed correctly
    std::size_t expected_hash = std::hash<uint64_t>{}(static_cast<uint64_t>(pair.first) << 32 | static_cast<uint64_t>(pair.second));
    
    // Assert the hash computation is correct
    EXPECT_EQ(hash_fn(pair), expected_hash);
}

// TEST CASE 2: Boundary Condition (minimum value)
TEST_F(TiffGroupKey_hash_107, HashComputationForMinimumValues_107) {
    TiffGroupKey pair(0, 0);  // Minimum possible values
    TiffGroupKey_hash hash_fn;

    // Expected hash value should be computed correctly
    std::size_t expected_hash = std::hash<uint64_t>{}(static_cast<uint64_t>(pair.first) << 32 | static_cast<uint64_t>(pair.second));

    // Assert the hash computation is correct
    EXPECT_EQ(hash_fn(pair), expected_hash);
}

// TEST CASE 3: Boundary Condition (maximum values)
TEST_F(TiffGroupKey_hash_107, HashComputationForMaximumValues_107) {
    TiffGroupKey pair(UINT32_MAX, UINT32_MAX);  // Maximum possible 32-bit unsigned integer values
    TiffGroupKey_hash hash_fn;

    // Expected hash value should be computed correctly
    std::size_t expected_hash = std::hash<uint64_t>{}(static_cast<uint64_t>(pair.first) << 32 | static_cast<uint64_t>(pair.second));

    // Assert the hash computation is correct
    EXPECT_EQ(hash_fn(pair), expected_hash);
}

// TEST CASE 4: Exceptional Case (handling invalid input)
TEST_F(TiffGroupKey_hash_107, HashComputationForInvalidValues_107) {
    // Since we are using unsigned integers and the implementation doesn't handle invalid values,
    // this test is not strictly applicable for exceptional input in this case. However, if the class
    // was modified to handle invalid cases, such as null pointers or negative values, we could test that.
    // For now, we assume this case to be a placeholder.
    
    EXPECT_NO_THROW({
        TiffGroupKey pair(0, 0);
        TiffGroupKey_hash hash_fn;
        hash_fn(pair);
    });
}

} }  // namespace Exiv2::Internal