// File: column_width_tests_50.cpp
#include <gtest/gtest.h>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnWidthTest_50 : public ::testing::Test {
protected:
    ColumnWidthTest_50() : text_("hello") {}
    std::string text_;
};

// [Normal] width() returns the default width derived from the configuration
// From the provided dependency snippet: CATCH_CONFIG_CONSOLE_WIDTH = 80 -> default m_width = 80 - 1 = 79
TEST_F(ColumnWidthTest_50, DefaultWidthIsConsoleWidthMinusOne_50) {
    Column col(text_);
    EXPECT_EQ(col.width(), static_cast<size_t>(79));
}

// [Normal] Setting width via the fluent setter reflects in width()
TEST_F(ColumnWidthTest_50, WidthSetterUpdatesWidth_50) {
    Column col(text_);
    col.width(20);
    EXPECT_EQ(col.width(), static_cast<size_t>(20));
}

// [Fluent API] width(size_t) returns lvalue reference to the same object (for chaining)
TEST_F(ColumnWidthTest_50, WidthSetterReturnsSelfReference_50) {
    Column col(text_);
    Column& ret = col.width(33);
    EXPECT_EQ(&ret, &col);            // same object (reference identity)
    EXPECT_EQ(col.width(), size_t(33)); // side effect visible via public getter
}

// [Boundary] Setting width to 0 should be observable via width()
TEST_F(ColumnWidthTest_50, WidthCanBeZero_50) {
    Column col(text_);
    col.width(0);
    EXPECT_EQ(col.width(), size_t(0));
}

// [Boundary] Setting a very large width is reflected by width()
TEST_F(ColumnWidthTest_50, WidthCanBeLarge_50) {
    Column col(text_);
    const size_t big = 10000;
    col.width(big);
    EXPECT_EQ(col.width(), big);
}

// [Stability] Repeated calls to width() do not change the value
TEST_F(ColumnWidthTest_50, WidthGetterIsIdempotent_50) {
    Column col(text_);
    col.width(42);
    EXPECT_EQ(col.width(), size_t(42));
    EXPECT_EQ(col.width(), size_t(42)); // call again; observable state unchanged
}
