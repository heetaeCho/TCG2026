// TEST_ID: 626

#include <gtest/gtest.h>
#include <sstream>
#include <iterator>
#include <string>

// Include the headers from the provided paths
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class ColumnsPlusEqualRvalue_626 : public ::testing::Test {};

// Verifies that adding a single rvalue Column increases the iterable size by 1
TEST_F(ColumnsPlusEqualRvalue_626, AddsSingleColumn_626) {
    Columns cols;

    // Before: expect empty
    EXPECT_EQ(std::distance(cols.begin(), cols.end()), 0);

    cols += Column("hello");

    // After: exactly 1
    EXPECT_EQ(std::distance(cols.begin(), cols.end()), 1);

    // Observable behavior: the stored Column streams out its content
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    const auto& firstCol = *it;

    std::ostringstream os;
    os << firstCol; // Uses Column's operator<<
    // We only assert that original content is present (avoid formatting specifics)
    EXPECT_NE(os.str().find("hello"), std::string::npos);
}

// Verifies chaining works by returning lhs reference and adding multiple columns
TEST_F(ColumnsPlusEqualRvalue_626, ChainingAddsMultipleColumns_626) {
    Columns cols;

    (cols += Column("left")) += Column("right");

    EXPECT_EQ(std::distance(cols.begin(), cols.end()), 2);

    // Verify order is preserved through observable streaming of each Column
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    std::ostringstream os1, os2;

    os1 << *it; // first
    ++it;
    ASSERT_NE(it, cols.end());
    os2 << *it; // second

    EXPECT_NE(os1.str().find("left"), std::string::npos);
    EXPECT_NE(os2.str().find("right"), std::string::npos);
}

// Verifies that operator+= returns a reference to lhs (enables chaining)
TEST_F(ColumnsPlusEqualRvalue_626, ReturnsLhsReference_626) {
    Columns cols;

    Columns& ref = (cols += Column("x"));
    EXPECT_EQ(&ref, &cols);
}

// Accepts temporaries constructed from both std::string rvalues and string literals
TEST_F(ColumnsPlusEqualRvalue_626, AcceptsRvalueTemporary_626) {
    Columns cols;

    // rvalue temporary from literal
    cols += Column("tmp1");

    // rvalue temporary from moved std::string
    std::string s = "tmp2";
    cols += Column(std::move(s));

    EXPECT_EQ(std::distance(cols.begin(), cols.end()), 2);

    // Stream both out to ensure contents are observable after moves
    auto it = cols.begin();
    std::ostringstream a, b;
    a << *it;
    ++it;
    ASSERT_NE(it, cols.end());
    b << *it;

    EXPECT_NE(a.str().find("tmp1"), std::string::npos);
    EXPECT_NE(b.str().find("tmp2"), std::string::npos);
}

// Boundary: adding an empty string column still appends an element
TEST_F(ColumnsPlusEqualRvalue_626, HandlesEmptyString_626) {
    Columns cols;

    cols += Column("");
    EXPECT_EQ(std::distance(cols.begin(), cols.end()), 1);

    // The streamed output for an empty Column should not crash; we only check that it is *some* string (possibly empty/newline)
    std::ostringstream os;
    os << *cols.begin();
    // No strict expectation on formatting; just ensure the operation is safe
    SUCCEED();
}
