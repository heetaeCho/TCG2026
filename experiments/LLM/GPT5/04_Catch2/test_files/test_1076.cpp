// File: tests/jsonobjectwriter_move_ctor_1076.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <type_traits>

// Use the public interface only
#include "catch2/internal/catch_jsonwriter.hpp"

using Catch::JsonObjectWriter;

class JsonObjectWriterMoveCtorTest_1076 : public ::testing::Test {};

// --- Compile-time interface checks (allowed; no runtime logic assumed) ---

// Move ctor should be nothrow (as declared with noexcept)
static_assert(std::is_nothrow_move_constructible<JsonObjectWriter>::value,
              "JsonObjectWriter move constructor must be noexcept");

// Move assignment is deleted per interface
static_assert(!std::is_move_assignable<JsonObjectWriter>::value,
              "JsonObjectWriter move assignment should be deleted");


// --- Runtime, observable-behavior tests ---

// The goal here is to *only* assert on observable effects on the stream.
// We do not assume the exact formatting, only that the moved-from instance
// becomes inactive (per interface: source.m_active is set to false in move ctor),
// and thus its destruction should not add output, while the moved-to instance
// remains active and its destruction *does* add output.

TEST_F(JsonObjectWriterMoveCtorTest_1076, MoveCtor_DeactivatesSource_NoExtraOutputOnSourceDestruction_1076) {
    std::ostringstream os;

    // Construct an object writing to the stream (any opening output is allowed).
    auto before_anything = os.str().size();
    {
        JsonObjectWriter original{os};
        // Capture stream size after construction (whatever the ctor wrote).
        const auto after_construct = os.str().size();

        // Move-construct into 'moved'. This should not itself write to the stream.
        JsonObjectWriter moved{std::move(original)};
        const auto after_move = os.str().size();
        EXPECT_EQ(after_move, after_construct)
            << "Move construction should not produce immediate stream output.";

        // Explicitly destroy the moved-from object ('original' goes out of scope here).
        // Since move-ctor deactivates the source, destroying it should not change output.
    }
    // After inner-scope ends, both 'moved' and 'original' are destroyed.
    // We cannot separate their destruction times in that scope. Create a more
    // controlled version where we destroy them independently:

    os.str("");
    os.clear();

    // Re-run with controlled lifetimes using unique_ptrs.
    {
        auto uptr_source = std::make_unique<JsonObjectWriter>(os);
        const auto after_construct = os.str().size();

        auto uptr_target = std::make_unique<JsonObjectWriter>(std::move(*uptr_source));
        const auto after_move = os.str().size();
        EXPECT_EQ(after_move, after_construct)
            << "Move construction should not change the stream.";

        // Destroy the moved-from instance explicitly; since it's inactive, this should
        // not modify the stream at all.
        uptr_source.reset(nullptr);
        const auto after_destroy_moved_from = os.str().size();
        EXPECT_EQ(after_destroy_moved_from, after_move)
            << "Destroying the moved-from object must not add output.";
    }

    // Note: We only asserted about the moved-from behavior here (no extra output).
    // Additional verification of moved-to behavior is done below.
    (void)before_anything; // silence unused (kept for clarity)
}

TEST_F(JsonObjectWriterMoveCtorTest_1076, MoveCtor_KeepsTargetActive_TargetDestructionProducesAdditionalOutput_1076) {
    std::ostringstream os;

    // Build with controlled lifetimes to observe each step's effect
    std::size_t size_after_construct = 0;
    std::size_t size_after_move = 0;
    std::size_t size_after_destroy_moved_from = 0;

    std::unique_ptr<JsonObjectWriter> uptr_target;
    {
        auto uptr_source = std::make_unique<JsonObjectWriter>(os);
        size_after_construct = os.str().size();

        uptr_target = std::make_unique<JsonObjectWriter>(std::move(*uptr_source));
        size_after_move = os.str().size();
        EXPECT_EQ(size_after_move, size_after_construct)
            << "Move construction should not modify the stream immediately.";

        // Destroy moved-from first — per interface it is deactivated and should not write.
        uptr_source.reset();
        size_after_destroy_moved_from = os.str().size();
        EXPECT_EQ(size_after_destroy_moved_from, size_after_move)
            << "Destroying moved-from writer should not change the stream.";
    }

    // Now destroy the moved-to writer; if it remains active, its destruction can produce
    // additional output (e.g., closing of an object). We do not assert *what* exactly is
    // written, only that something observable is produced at this point (non-empty delta).
    const auto before_target_destruction = os.str().size();
    uptr_target.reset();
    const auto after_target_destruction = os.str().size();

    // If the active writer writes something on destruction (typical for scoped writers),
    // the size should increase. We only assert that *some* additional output appeared.
    EXPECT_GT(after_target_destruction, before_target_destruction)
        << "Destroying the moved-to (still-active) writer should produce observable output.";
}

TEST_F(JsonObjectWriterMoveCtorTest_1076, MoveCtor_WithExplicitIndent_StreamRemainsConsistentThroughMove_1076) {
    std::ostringstream os;

    // Construct with a non-zero indent level; we don't assert exact formatting,
    // only that the stream length remains unchanged by the move itself, and that
    // destroying the target later emits additional output.
    std::unique_ptr<JsonObjectWriter> target;
    std::size_t size_after_construct = 0;

    {
        JsonObjectWriter src{os, static_cast<std::uint64_t>(4)};
        size_after_construct = os.str().size();

        target = std::make_unique<JsonObjectWriter>(std::move(src));
        EXPECT_EQ(os.str().size(), size_after_construct)
            << "Moving should not emit output regardless of indent.";
    }

    const auto size_before_target_destruction = os.str().size();
    target.reset();
    const auto size_after_target_destruction = os.str().size();

    EXPECT_GT(size_after_target_destruction, size_before_target_destruction)
        << "Destroying the moved-to writer should add observable output even with indent.";
}
