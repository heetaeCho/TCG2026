// File: tests/xmlwriter_scoped_element_move_tests_1071.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the public headers exactly as they are exposed in your project
// (paths taken from the prompt)
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlWriter;
using Catch::XmlFormatting;

namespace {

// Helper factory that constructs a ScopedElement with a null writer.
// We only rely on the public constructor signature and do not assume any internal logic.
inline XmlWriter::ScopedElement makeNullWriterElem(XmlFormatting fmt = XmlFormatting::None) {
    return XmlWriter::ScopedElement(nullptr, fmt);
}

} // namespace

// -----------------------------------------------------------------------------
// Type-trait based tests (compile-time guarantees derived from public signatures)
// -----------------------------------------------------------------------------

// Verifies that the move constructor is declared noexcept, per the provided implementation.
TEST(XmlWriterScopedElementTest_1071, MoveCtor_IsNoexcept_1071) {
    static_assert(std::is_nothrow_move_constructible<XmlWriter::ScopedElement>::value,
                  "ScopedElement must be nothrow move-constructible");
    SUCCEED(); // Keep gtest happy even if only static_assert fires at compile-time.
}

// Verifies that move-assignment is noexcept (declared in the provided header snippet).
TEST(XmlWriterScopedElementTest_1071, MoveAssign_IsNoexcept_1071) {
    static_assert(std::is_nothrow_move_assignable<XmlWriter::ScopedElement>::value,
                  "ScopedElement must be nothrow move-assignable");
    SUCCEED();
}

// As the interface only exposes move operations, copy should be unavailable.
// We assert the *absence* of copy operations based on the public interface.
TEST(XmlWriterScopedElementTest_1071, CopyCtor_IsDeletedOrUnavailable_1071) {
    static_assert(!std::is_copy_constructible<XmlWriter::ScopedElement>::value,
                  "ScopedElement should not be copy-constructible");
    SUCCEED();
}

TEST(XmlWriterScopedElementTest_1071, CopyAssign_IsDeletedOrUnavailable_1071) {
    static_assert(!std::is_copy_assignable<XmlWriter::ScopedElement>::value,
                  "ScopedElement should not be copy-assignable");
    SUCCEED();
}

// -----------------------------------------------------------------------------
// Runtime safety/behavior tests based on observable effects (no crashes/throws)
// -----------------------------------------------------------------------------

// Moving from an object should leave both destination and source in valid,
// destructible states. We do not inspect private state, only ensure no crashes.
TEST(XmlWriterScopedElementTest_1071, MoveCtor_FromNullWriter_IsSafe_1071) {
    auto src = makeNullWriterElem(XmlFormatting::Indent);
    // Move-construct
    XmlWriter::ScopedElement dst(std::move(src));

    // Scope end: both dst and (moved-from) src must be safely destructible.
    SUCCEED();
}

// Repeated moves should also be safe and noexcept (based on signature).
TEST(XmlWriterScopedElementTest_1071, RepeatedMoves_AreSafe_1071) {
    auto a = makeNullWriterElem(XmlFormatting::Newline);
    XmlWriter::ScopedElement b(std::move(a));       // first move
    XmlWriter::ScopedElement c(std::move(b));       // second move

    // Destruction should be safe for all (moved-to and moved-from) instances.
    SUCCEED();
}

// Move-assign between two distinct instances constructed through the public
// constructor should be noexcept and leave both objects valid for destruction.
TEST(XmlWriterScopedElementTest_1071, MoveAssign_BetweenDistinctObjects_IsSafe_1071) {
    auto lhs = makeNullWriterElem(XmlFormatting::Indent);
    auto rhs = makeNullWriterElem(XmlFormatting::None);

    // Move-assign
    lhs = std::move(rhs);

    // Both should be safely destructible at scope end.
    SUCCEED();
}

// Self move-assignment must not throw. We make no assumptions about internal
// effects, only that it remains safe/valid to destroy.
TEST(XmlWriterScopedElementTest_1071, SelfMoveAssign_DoesNotThrow_1071) {
    auto e = makeNullWriterElem(XmlFormatting::None);

    // Even though self-move is typically avoided, this checks robustness strictly
    // through the public interface (no-throw and safe destruction).
    ASSERT_NO_THROW({
        e = std::move(e);
    });
    SUCCEED();
}

