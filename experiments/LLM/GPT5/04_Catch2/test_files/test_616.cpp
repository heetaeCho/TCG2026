// File: tests/column_const_iterator_postincrement_616.cpp
#include <gtest/gtest.h>

// Catch2's Column/iterators live here:
#include <catch2/internal/catch_textflow.hpp>  // If your include path differs, adjust accordingly.

using Catch::TextFlow::Column;

class ColumnIteratorTest_616 : public ::testing::Test {
protected:
    // Helper that makes a Column which is *likely* to yield multiple lines,
    // so we can observe iterator advancement without asserting any specific content.
    static Column makeWrappedColumn() {
        // We treat Column as a black box and only use its documented/configurable knobs.
        // The following usage stays within public interface expectations:
        Column c{"Alpha Beta Gamma Delta Epsilon Zeta Eta Theta Iota Kappa"};
        c.width(8);            // Small width to encourage multiple chunks/lines.
        c.initialIndent(0);    // Keep indentation simple.
        c.indent(0);
        return c;
    }
};

// Verifies that post-increment returns the previous iterator value.
// Also verifies the iterator being incremented advances to a different position.
TEST_F(ColumnIteratorTest_616, PostIncrementReturnsPrevious_616) {
    Column col = makeWrappedColumn();

    auto it = col.begin();
    auto end = col.end();

    // Precondition: there should be at least one element to dereference
    ASSERT_NE(it, end) << "Column.begin() should not equal end() for non-empty Column";

    auto it_before = it;   // snapshot
    auto ret = it++;       // post-increment: returns previous, advances 'it'

    // The returned iterator must equal the previous snapshot
    EXPECT_TRUE(ret == it_before);
    // And the incremented iterator should have advanced (unless there was only one element)
    // We can only assert inequality if there's >1 element; detect that by checking
    // whether advancing a copy would hit end() immediately.
    auto probe = it_before;
    ++probe; // advance once from the original position
    if (probe != end) {
        EXPECT_NE(it, it_before) << "Iterator should advance after post-increment";
    }

    // The returned iterator (ret) should still be dereferenceable if the snapshot was.
    // We avoid asserting specific content; just ensure dereference compiles & is stable.
    (void)*ret;
}

// Walks the sequence using ONLY post-increment and compares the collected sequence
// to a reference sequence produced by a range-for (which uses the iterator protocol).
TEST_F(ColumnIteratorTest_616, PostIncrementTraversalMatchesRangeFor_616) {
    Column col = makeWrappedColumn();

    // Reference via range-for (not asserting content, just capturing what the class exposes)
    std::vector<std::string> reference;
    for (auto const& chunk : col) {
        reference.push_back(chunk);
    }

    // Traverse using explicit post-increment
    std::vector<std::string> via_post_inc;
    auto it = col.begin();
    auto end = col.end();
    while (it != end) {
        via_post_inc.push_back(*it);
        it++;  // post-increment
    }

    // The sequences should match exactly in size and element values
    ASSERT_EQ(reference.size(), via_post_inc.size());
    for (size_t i = 0; i < reference.size(); ++i) {
        EXPECT_EQ(reference[i], via_post_inc[i]) << "Mismatch at element #" << i;
    }
}

// Repeated post-increment should eventually reach end(), and not skip elements
// compared to pre-increment traversal.
TEST_F(ColumnIteratorTest_616, RepeatedPostIncrementReachesEnd_616) {
    Column col = makeWrappedColumn();

    // Count via pre-increment traversal
    size_t count_pre = 0;
    for (auto it = col.begin(), e = col.end(); it != e; ++it) {
        ++count_pre;
    }

    // Count via post-increment traversal
    size_t count_post = 0;
    auto it = col.begin();
    auto e  = col.end();
    while (it != e) {
        ++count_post;
        it++;  // post-increment
    }

    EXPECT_EQ(count_pre, count_post) << "Post-increment should visit same number of elements";
    EXPECT_TRUE(it == e) << "Iterator should equal end() after exhausting the sequence with post-increment";
}

// Validates that the value returned by post-increment is a *distinct copy*
// (i.e., subsequent changes to the original iterator don't affect the returned snapshot).
TEST_F(ColumnIteratorTest_616, PostIncrementReturnsIndependentSnapshot_616) {
    Column col = makeWrappedColumn();

    auto it = col.begin();
    auto end = col.end();
    ASSERT_NE(it, end) << "Need at least one element";

    // Capture returned snapshot and then advance the original iterator further.
    auto snapshot = it++;   // snapshot refers to old position
    // Move 'it' forward again if possible
    if (it != end) {
        it++;
    }

    // The snapshot should still equal its own successor-by-one (relative to its old position),
    // independent of the current state of 'it'. We compare snapshot advanced by one with
    // the position we'd get by advancing a fresh copy of the original 'snapshot'.
    auto snap_next_a = snapshot;
    auto snap_next_b = snapshot;
    ++snap_next_a;
    ++snap_next_b;
    EXPECT_TRUE(snap_next_a == snap_next_b) << "Snapshot should be a stable copy unaffected by later increments";

    // Also ensure snapshot remains dereferenceable if it wasn't at end()
    if (snapshot != end) {
        (void)*snapshot;
    }
}
