// File: tests/assertion_handler_handleExceptionNotThrownAsExpected_557.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/internal/catch_assertion_handler.hpp"
#include "Catch2/src/catch2/internal/catch_result_type.hpp"

// If these headers live under a different include root in your tree,
// adjust paths accordingly (kept as provided in the prompt).

namespace {

using Catch::AssertionHandler;
using Catch::ResultWas;
using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::ResultDisposition;

// Minimal helpers to construct required arguments
static SourceLineInfo kDummyLineInfo{"dummy_file.cpp", 123};
static StringRef kMacro{"TEST_MACRO"};
static StringRef kCapturedExpr{""};
static ResultDisposition::Flags kDisposition = static_cast<ResultDisposition::Flags>(0);

// NOTE:
// We treat AssertionHandler as a black box. We only assert behavior observable
// through its public interface (no internal state peeking, no logic inference).

} // namespace

// 1) Smoke: calling the method should be noexcept from the interface perspective
//    (i.e., it should not propagate). This verifies basic normal operation.
TEST(AssertionHandler_557, HandleExceptionNotThrownAsExpected_DoesNotThrow_557) {
    AssertionHandler ah{kMacro, kDummyLineInfo, kCapturedExpr, kDisposition};
    EXPECT_NO_THROW({
        ah.handleExceptionNotThrownAsExpected();
    });
}

// 2) Idempotence-ish safety: calling it multiple times should still not throw.
//    Boundary-ish: repeated usage without intervening completion.
TEST(AssertionHandler_557, HandleExceptionNotThrownAsExpected_MultipleCallsSafe_557) {
    AssertionHandler ah{kMacro, kDummyLineInfo, kCapturedExpr, kDisposition};
    EXPECT_NO_THROW(ah.handleExceptionNotThrownAsExpected());
    EXPECT_NO_THROW(ah.handleExceptionNotThrownAsExpected());
}

// 3) Interaction safety around lifecycle: calling the method before complete(),
//    and then calling complete(), should not throw. We do not assert internal
//    effects—only that the documented public calls remain safe/valid to make.
TEST(AssertionHandler_557, HandleExceptionNotThrownAsExpected_BeforeComplete_ThenComplete_557) {
    AssertionHandler ah{kMacro, kDummyLineInfo, kCapturedExpr, kDisposition};
    EXPECT_NO_THROW(ah.handleExceptionNotThrownAsExpected());
    EXPECT_NO_THROW(ah.complete());
}
