// File: test_clara_detail_is_container_377.cpp

#include <gtest/gtest.h>
#include <vector>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BoundValueRef;

class ClaraDetail_IsContainerTest_377 : public ::testing::Test {};

TEST_F(ClaraDetail_IsContainerTest_377, ReturnsTrue_WhenBoundToVector_377) {
    std::vector<int> vec;
    // Per the provided interface, the container-binding ctor accepts std::vector<T>&
    BoundValueRef<int> bound_vec(vec);

    EXPECT_TRUE(bound_vec.isContainer())
        << "isContainer() should report true for container-bound references.";
}

TEST_F(ClaraDetail_IsContainerTest_377, ConstQualifiedCall_StillTrue_377) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> bound_vec(vec);

    // Verify const-correctness / no state mutation required to invoke
    const auto& const_ref = bound_vec;
    EXPECT_TRUE(const_ref.isContainer())
        << "isContainer() should be callable on const objects and remain true.";
}
