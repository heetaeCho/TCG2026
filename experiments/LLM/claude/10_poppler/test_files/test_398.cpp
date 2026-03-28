#include <gtest/gtest.h>
#include "GfxState.h"

// Since GfxColorTransform has a deleted copy constructor, deleted copy assignment,
// and the default constructor is private, we need to use the parameterized constructor.
// However, the constructor takes a void* transform which likely refers to a CMS transform handle.
// We need to be careful about what we pass in.

// Note: The constructor signature is:
// GfxColorTransform(void* transformA, int cmsIntent, unsigned int inputPixelType, unsigned int transformPixelType);

// We'll test the observable interface methods: getInputPixelType(), getIntent(), getTransformPixelType()

class GfxColorTransformTest_398 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getInputPixelType returns the value passed during construction
TEST_F(GfxColorTransformTest_398, GetInputPixelType_ReturnsConstructedValue_398) {
    // We pass nullptr as the transform handle - the getter should still work
    // since it only reads the stored inputPixelType field
    unsigned int expectedInputPixelType = 42;
    GfxColorTransform ct(nullptr, 0, expectedInputPixelType, 0);
    EXPECT_EQ(ct.getInputPixelType(), static_cast<int>(expectedInputPixelType));
}

// Test getInputPixelType with zero value
TEST_F(GfxColorTransformTest_398, GetInputPixelType_Zero_398) {
    GfxColorTransform ct(nullptr, 0, 0, 0);
    EXPECT_EQ(ct.getInputPixelType(), 0);
}

// Test getInputPixelType with a large value
TEST_F(GfxColorTransformTest_398, GetInputPixelType_LargeValue_398) {
    unsigned int largeVal = 0xFFFF;
    GfxColorTransform ct(nullptr, 0, largeVal, 0);
    EXPECT_EQ(ct.getInputPixelType(), static_cast<int>(largeVal));
}

// Test getIntent returns the value passed during construction
TEST_F(GfxColorTransformTest_398, GetIntent_ReturnsConstructedValue_398) {
    int expectedIntent = 1;
    GfxColorTransform ct(nullptr, expectedIntent, 0, 0);
    EXPECT_EQ(ct.getIntent(), expectedIntent);
}

// Test getIntent with zero
TEST_F(GfxColorTransformTest_398, GetIntent_Zero_398) {
    GfxColorTransform ct(nullptr, 0, 0, 0);
    EXPECT_EQ(ct.getIntent(), 0);
}

// Test getIntent with negative value
TEST_F(GfxColorTransformTest_398, GetIntent_NegativeValue_398) {
    int negativeIntent = -1;
    GfxColorTransform ct(nullptr, negativeIntent, 0, 0);
    EXPECT_EQ(ct.getIntent(), negativeIntent);
}

// Test getTransformPixelType returns the value passed during construction
TEST_F(GfxColorTransformTest_398, GetTransformPixelType_ReturnsConstructedValue_398) {
    unsigned int expectedTransformPixelType = 100;
    GfxColorTransform ct(nullptr, 0, 0, expectedTransformPixelType);
    EXPECT_EQ(ct.getTransformPixelType(), static_cast<int>(expectedTransformPixelType));
}

// Test getTransformPixelType with zero
TEST_F(GfxColorTransformTest_398, GetTransformPixelType_Zero_398) {
    GfxColorTransform ct(nullptr, 0, 0, 0);
    EXPECT_EQ(ct.getTransformPixelType(), 0);
}

// Test all getters together with distinct values
TEST_F(GfxColorTransformTest_398, AllGetters_DistinctValues_398) {
    int intent = 2;
    unsigned int inputPT = 10;
    unsigned int transformPT = 20;
    GfxColorTransform ct(nullptr, intent, inputPT, transformPT);
    EXPECT_EQ(ct.getIntent(), intent);
    EXPECT_EQ(ct.getInputPixelType(), static_cast<int>(inputPT));
    EXPECT_EQ(ct.getTransformPixelType(), static_cast<int>(transformPT));
}

// Test that the object is not copyable (compile-time check - this is just documentation)
// GfxColorTransform has deleted copy constructor and copy assignment operator
// We verify this conceptually; if uncommented, the following should NOT compile:
// TEST_F(GfxColorTransformTest_398, CopyDeleted_398) {
//     GfxColorTransform ct(nullptr, 0, 0, 0);
//     GfxColorTransform ct2(ct); // Should not compile
//     GfxColorTransform ct3 = ct; // Should not compile
// }

// Test with boundary value for unsigned int input pixel type
TEST_F(GfxColorTransformTest_398, GetInputPixelType_MaxUnsignedShort_398) {
    unsigned int val = 65535;
    GfxColorTransform ct(nullptr, 0, val, 0);
    EXPECT_EQ(ct.getInputPixelType(), static_cast<int>(val));
}
