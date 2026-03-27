#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/tags_int.hpp"

namespace Exiv2 {
namespace Internal {

    // Test fixture class (if needed)
    class TagDetailsTest_176 : public ::testing::Test {
    protected:
        // You can add setup/teardown code here if required for the tests.
    };

    // Normal operation tests
    TEST_F(TagDetailsTest_176, EqualityOperator_ReturnsTrueForEqualKeys_176) {
        TagDetails tagDetails1;
        tagDetails1.val_ = 123;
        
        TagDetails tagDetails2;
        tagDetails2.val_ = 123;

        EXPECT_TRUE(tagDetails1 == tagDetails2.val_);
    }

    TEST_F(TagDetailsTest_176, EqualityOperator_ReturnsFalseForDifferentKeys_176) {
        TagDetails tagDetails1;
        tagDetails1.val_ = 123;
        
        TagDetails tagDetails2;
        tagDetails2.val_ = 456;

        EXPECT_FALSE(tagDetails1 == tagDetails2.val_);
    }

    // Boundary condition tests
    TEST_F(TagDetailsTest_176, EqualityOperator_ZeroValue_176) {
        TagDetails tagDetails1;
        tagDetails1.val_ = 0;
        
        TagDetails tagDetails2;
        tagDetails2.val_ = 0;

        EXPECT_TRUE(tagDetails1 == tagDetails2.val_);
    }

    TEST_F(TagDetailsTest_176, EqualityOperator_NegativeValue_176) {
        TagDetails tagDetails1;
        tagDetails1.val_ = -100;
        
        TagDetails tagDetails2;
        tagDetails2.val_ = -100;

        EXPECT_TRUE(tagDetails1 == tagDetails2.val_);
    }

    // Exceptional or error cases
    TEST_F(TagDetailsTest_176, EqualityOperator_InvalidComparison_176) {
        // There is no explicit invalid case for the given operator.
        // The equality operator only compares integer values, so invalid behavior isn't expected.
        // This test could be removed if not needed for your case.
        TagDetails tagDetails1;
        tagDetails1.val_ = 123;

        // Here, using any non-integer key should lead to a compile-time error.
        // So, we are not implementing it, and there is no exceptional runtime behavior.
    }

    // Verification of external interactions (if needed)
    // Since there is no external handler or dependency in the provided code, this section may be omitted.
}

}  // namespace Internal
}  // namespace Exiv2