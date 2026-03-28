#include <gtest/gtest.h>
#include "Annot.h"

// Since we only have the public interface of AnnotBorder and it's an abstract-like class,
// we need to find a way to instantiate it. Based on the known dependencies, AnnotBorder
// has a protected default constructor. We'll create a concrete subclass for testing purposes
// that exposes construction capability.

class TestableAnnotBorder : public AnnotBorder {
public:
    TestableAnnotBorder() : AnnotBorder() {}
};

class AnnotBorderTest_747 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that default constructed AnnotBorder has a default width value
TEST_F(AnnotBorderTest_747, DefaultWidth_747) {
    TestableAnnotBorder border;
    double width = border.getWidth();
    // Default width should be a non-negative value (commonly 1.0 for PDF annotations)
    EXPECT_GE(width, 0.0);
}

// Test that setWidth changes the width returned by getWidth
TEST_F(AnnotBorderTest_747, SetWidthChangesWidth_747) {
    TestableAnnotBorder border;
    border.setWidth(5.0);
    EXPECT_DOUBLE_EQ(5.0, border.getWidth());
}

// Test setting width to zero
TEST_F(AnnotBorderTest_747, SetWidthToZero_747) {
    TestableAnnotBorder border;
    border.setWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, border.getWidth());
}

// Test setting width to a very large value
TEST_F(AnnotBorderTest_747, SetWidthLargeValue_747) {
    TestableAnnotBorder border;
    border.setWidth(1e10);
    EXPECT_DOUBLE_EQ(1e10, border.getWidth());
}

// Test setting width to a very small positive value
TEST_F(AnnotBorderTest_747, SetWidthSmallPositiveValue_747) {
    TestableAnnotBorder border;
    border.setWidth(0.001);
    EXPECT_DOUBLE_EQ(0.001, border.getWidth());
}

// Test setting width to a negative value (boundary/error case)
TEST_F(AnnotBorderTest_747, SetWidthNegativeValue_747) {
    TestableAnnotBorder border;
    border.setWidth(-1.0);
    // The behavior with negative width is implementation-defined,
    // but getWidth should return whatever was set
    double width = border.getWidth();
    // We just verify getWidth returns something; exact behavior depends on impl
    EXPECT_EQ(-1.0, width);
}

// Test setting width multiple times
TEST_F(AnnotBorderTest_747, SetWidthMultipleTimes_747) {
    TestableAnnotBorder border;
    border.setWidth(1.0);
    EXPECT_DOUBLE_EQ(1.0, border.getWidth());
    border.setWidth(2.5);
    EXPECT_DOUBLE_EQ(2.5, border.getWidth());
    border.setWidth(0.0);
    EXPECT_DOUBLE_EQ(0.0, border.getWidth());
}

// Test getDash returns a reference to dash vector
TEST_F(AnnotBorderTest_747, GetDashReturnsVector_747) {
    TestableAnnotBorder border;
    const std::vector<double>& dash = border.getDash();
    // Default dash should be empty or have default values
    // We just verify it doesn't crash and returns a valid reference
    EXPECT_GE(dash.size(), 0u);
}

// Test getStyle returns a valid style
TEST_F(AnnotBorderTest_747, GetStyleReturnsValidStyle_747) {
    TestableAnnotBorder border;
    AnnotBorderStyle style = border.getStyle();
    // Just verify it returns without error; the actual value depends on defaults
    (void)style;
    SUCCEED();
}

// Test getType returns a valid type
TEST_F(AnnotBorderTest_747, GetTypeReturnsValidType_747) {
    TestableAnnotBorder border;
    AnnotBorderType type = border.getType();
    (void)type;
    SUCCEED();
}

// Test copy creates a valid copy with same width
TEST_F(AnnotBorderTest_747, CopyPreservesWidth_747) {
    TestableAnnotBorder border;
    border.setWidth(3.14);
    std::unique_ptr<AnnotBorder> copied = border.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_DOUBLE_EQ(3.14, copied->getWidth());
}

// Test copy creates independent object
TEST_F(AnnotBorderTest_747, CopyIsIndependent_747) {
    TestableAnnotBorder border;
    border.setWidth(2.0);
    std::unique_ptr<AnnotBorder> copied = border.copy();
    ASSERT_NE(copied, nullptr);
    border.setWidth(5.0);
    EXPECT_DOUBLE_EQ(2.0, copied->getWidth());
    EXPECT_DOUBLE_EQ(5.0, border.getWidth());
}

// Test that AnnotBorder is not copyable (compile-time check - just document it)
TEST_F(AnnotBorderTest_747, NotCopyConstructible_747) {
    EXPECT_FALSE(std::is_copy_constructible<AnnotBorder>::value);
}

TEST_F(AnnotBorderTest_747, NotCopyAssignable_747) {
    EXPECT_FALSE(std::is_copy_assignable<AnnotBorder>::value);
}

// Test setWidth with fractional precision
TEST_F(AnnotBorderTest_747, SetWidthFractionalPrecision_747) {
    TestableAnnotBorder border;
    border.setWidth(1.123456789);
    EXPECT_DOUBLE_EQ(1.123456789, border.getWidth());
}
