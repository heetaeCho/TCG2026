// File: xmlwriter_scopedelement_move_assign_tests_468.cpp

#include <gtest/gtest.h>
#include <sstream>

// Use the provided headers/interfaces
#include "catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlWriter;
using Catch::XmlFormatting;

// Helper to check substring presence/absence without depending on exact formatting
static bool Contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

// ============================================================================
// TEST 1: When assigning from a *non-empty* ScopedElement into a *non-empty*
//         ScopedElement, the current element of the LHS is ended immediately.
//         Also, the moved-from RHS should not close its element upon destruction
//         (because it is nulled out by the move), and the new LHS will later
//         close the newly adopted element at its destruction.
// ============================================================================
TEST(XmlWriter_ScopedElement_MoveAssign_468, MoveAssignEndsPreviousElementImmediately_468) {
    std::ostringstream oss1;
    std::ostringstream oss2;
    XmlWriter w1(oss1);
    XmlWriter w2(oss2);

    // Create 2 live scoped elements on different writers
    auto e1 = w1.scopedElement("one", XmlFormatting::None); // opens <one ...>
    {
        auto e2 = w2.scopedElement("two", XmlFormatting::None); // opens <two ...>

        // Move-assign: should end LHS ("one") immediately, adopt RHS ("two"),
        // and null-out e2.
        e1 = std::move(e2);

        // After move-assignment:
        // - LHS's previous element ("one") should already be closed.
        EXPECT_TRUE(Contains(oss1.str(), "</one>"))
            << "Move-assignment should end the previous LHS element immediately.";

        // - The element adopted from RHS ("two") should NOT be closed yet,
        //   because it will be closed when 'e1' (now owning it) is destroyed.
        EXPECT_FALSE(Contains(oss2.str(), "</two>"))
            << "The adopted element should not be closed until the new owner is destroyed.";
        // e2 (moved-from) will be destroyed at the end of this inner scope; it should do nothing.
    }

    // Now 'e1' is still alive and owns "two". When 'e1' goes out of scope at the end
    // of the test, it should close "two".
    // Destroy 'e1' explicitly here to make the check right after.
    // (Leaving it to go out of scope at the end of the function works the same.)
}

// We explicitly destroy e1 by ending its scope; check after that destruction:
TEST(XmlWriter_ScopedElement_MoveAssign_468, MoveAssignThenDestructionClosesAdoptedElement_468) {
    std::ostringstream oss2;
    {
        std::ostringstream oss1;
        XmlWriter w1(oss1);
        XmlWriter w2(oss2);

        auto e1 = w1.scopedElement("one", XmlFormatting::None);
        {
            auto e2 = w2.scopedElement("two", XmlFormatting::None);
            e1 = std::move(e2);

            // LHS's original ("one") ended; adopted ("two") not closed yet
            EXPECT_TRUE(Contains(oss1.str(), "</one>"));
            EXPECT_FALSE(Contains(oss2.str(), "</two>"));
        }
        // e1 still alive here, owns "two"
        // On leaving this block, e1 is destroyed and should close "two".
    }
    // After e1 destruction, "two" should be closed exactly once.
    EXPECT_TRUE(Contains(oss2.str(), "</two>"))
        << "The adopted element should be closed when the (new) owner is destroyed.";
}

// ============================================================================
// TEST 2: Move-assign into an *empty* LHS (moved-from) should NOT attempt to
//         end any element on assignment (because LHS has no writer).
//         The originally moved-to owner should still close its element later.
// ============================================================================
TEST(XmlWriter_ScopedElement_MoveAssign_468, MoveAssignIntoEmptyDoesNotEndAnything_468) {
    std::ostringstream ossA, ossB;
    XmlWriter wA(ossA);
    XmlWriter wB(ossB);

    // Make an empty LHS by move-constructing out of it
    auto originalA = wA.scopedElement("A", XmlFormatting::None); // opens <A>
    auto emptyLHS = std::move(originalA); // originalA becomes moved-from (empty LHS holds writer A)
    (void)emptyLHS; // keep it alive so that A will be closed later by RAII

    // Now create a new element on writer B and move-assign it into the *moved-from* originalA.
    auto tempB = wB.scopedElement("B", XmlFormatting::None); // opens <B>
    originalA = std::move(tempB); // originalA had no writer, so no end should be called here

    // Assignment into empty LHS should not close anything immediately on either stream.
    EXPECT_FALSE(Contains(ossA.str(), "</A>"))
        << "No premature close of 'A' expected during move-assign into empty LHS.";
    EXPECT_FALSE(Contains(ossB.str(), "</B>"))
        << "No premature close of 'B' expected during move-assign into empty LHS.";

    // Drop tempB (already moved-from) – should do nothing.
    // When emptyLHS is destroyed, it should close 'A'.
    // When originalA is destroyed, it should close 'B'.
    // Let scope end to trigger both RAII closures.
}

// Confirm the RAII closures happened as expected for test above.
TEST(XmlWriter_ScopedElement_MoveAssign_468, MoveAssignIntoEmpty_RAIICleanupClosesBoth_468) {
    std::ostringstream ossA, ossB;
    {
        XmlWriter wA(ossA);
        XmlWriter wB(ossB);

        auto originalA = wA.scopedElement("A", XmlFormatting::None); // <A>
        auto emptyLHS   = std::move(originalA);                      // emptyLHS owns A
        auto tempB      = wB.scopedElement("B", XmlFormatting::None); // <B>
        originalA       = std::move(tempB);                          // originalA now owns B; no close yet

        // end scope -> emptyLHS closes A, originalA closes B
    }
    EXPECT_TRUE(Contains(ossA.str(), "</A>"))
        << "RAII should close 'A' exactly once at destruction.";
    EXPECT_TRUE(Contains(ossB.str(), "</B>"))
        << "RAII should close 'B' exactly once at destruction.";
}
