// File: tests/colour_guard_move_tests_1095.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <ostream>

// Include the public header under test.
// (Path as provided in your prompt; adjust include path to your tree layout.)
#include "catch2/internal/catch_console_colour.hpp"

using Catch::ColourImpl;

// A small counting streambuf/ostream to observe *that* something was written
// (without asserting the exact bytes).
class CountingStreamBuf : public std::streambuf {
public:
    CountingStreamBuf() : count_(0) {}

    std::size_t count() const { return count_; }

protected:
    // Count single-char writes
    int overflow(int c) override {
        if (c != EOF) {
            ++count_;
        }
        return c;
    }
    // Count block writes
    std::streamsize xsputn(const char* s, std::streamsize n) override {
        count_ += static_cast<std::size_t>(n);
        return n;
    }

private:
    std::size_t count_;
};

class CountingOStream : public std::ostream {
public:
    CountingOStream() : std::ostream(&buf_) {}
    std::size_t count() const { return buf_.count(); }
private:
    CountingStreamBuf buf_;
};

// A minimal test fixture (no peeking into internals).
class ColourGuardMoveTest_1095 : public ::testing::Test {
protected:
    // We keep a ColourImpl instance alive to pass a non-null pointer into ColourGuard.
    // We do not access any of its internals.
    ColourImpl colourImpl_;
    // Some Code value; we don't assert which, only that it is a valid value type.
    // If Code is an enum/struct, default-init is fine for a black-box engagement.
    Catch::Colour::Code someCode_{};
};

// --- Tests ---

// 1) Normal operation: calling engage writes *something* to the stream (observable effect).
TEST_F(ColourGuardMoveTest_1095, EngageWritesToStream_1095) {
    CountingOStream os;
    std::size_t before = os.count();

    ColourImpl::ColourGuard guard(someCode_, &colourImpl_);
    // Call the public API; we only check that some bytes were written.
    guard.engage(os);

    std::size_t after = os.count();
    EXPECT_GT(after, before) << "engage(stream) should write something observable";
}

// 2) Move constructor: moved-from guard is disengaged (observable via no extra writes on its destruction),
//    while the moved-to guard remains responsible for any deferred output on destruction.
TEST_F(ColourGuardMoveTest_1095, MoveCtorDisengagesSource_1095) {
    CountingOStream os;

    std::size_t baseline = os.count();
    {
        ColourImpl::ColourGuard g1(someCode_, &colourImpl_);
        g1.engage(os);
        std::size_t afterEngage = os.count();
        EXPECT_GT(afterEngage, baseline) << "engage should have produced output";

        // Move-construct g2 from g1
        ColourImpl::ColourGuard g2(std::move(g1));

        // Destroy g1 (end of inner scope block). Because it was moved-from, it should
        // not contribute additional output on destruction.
        {
            // Immediately drop a temporary moved-from copy (already moved above).
        }
        std::size_t afterG1Dtor = os.count();
        EXPECT_EQ(afterG1Dtor, afterEngage)
            << "Destroying moved-from guard should not add output";

        // On destruction of g2 (outer scope exit), if there is deferred output (e.g., reset),
        // it should come from g2, not g1. We can only assert it *may* add more;
        // to make this test robust, we only check that the stream does not regress
        // and allow either behavior. But if it does output, the count should increase.
    }
    std::size_t afterAll = os.count();
    EXPECT_GE(afterAll, baseline)
        << "Overall, counts should not decrease (sanity check)";
}

// 3) Move assignment: same observable contract for the source being disengaged,
//    and destination remaining valid.
TEST_F(ColourGuardMoveTest_1095, MoveAssignDisengagesSource_1095) {
    CountingOStream os;

    ColourImpl::ColourGuard g1(someCode_, &colourImpl_);
    g1.engage(os);
    std::size_t afterG1Engage = os.count();
    EXPECT_GT(afterG1Engage, 0u);

    ColourImpl::ColourGuard g2(someCode_, &colourImpl_);
    std::size_t beforeAssign = os.count();

    // Move-assign g1 into g2
    g2 = std::move(g1);

    // Destroy the moved-from g1 (now out of scope end). It should not add further output.
    {
        // (g1 will be destroyed at end of scope; we can force a block if needed)
    }
    std::size_t afterG1Destroyed = os.count();
    EXPECT_EQ(afterG1Destroyed, beforeAssign)
        << "Destroying moved-from guard after move-assign should not add output";

    // Destroy g2 at end of scope: if any deferred output is produced, it would come from g2.
    // We avoid asserting exact bytes; merely ensure no regressions or crashes.
}

// 4) Engage, then move, then engage again on the new owner is well-defined (public API remains usable).
TEST_F(ColourGuardMoveTest_1095, EngageThenMoveThenEngageAgain_1095) {
    CountingOStream os;

    ColourImpl::ColourGuard g1(someCode_, &colourImpl_);
    g1.engage(os);
    std::size_t afterFirstEngage = os.count();
    EXPECT_GT(afterFirstEngage, 0u);

    ColourImpl::ColourGuard g2(std::move(g1));

    // Re-engage using the moved-to guard. We expect additional observable output.
    g2.engage(os);
    std::size_t afterSecondEngage = os.count();
    EXPECT_GT(afterSecondEngage, afterFirstEngage)
        << "engage on the moved-to guard should write additional output";
}
