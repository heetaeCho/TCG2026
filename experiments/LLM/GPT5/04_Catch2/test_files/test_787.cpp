// File: tests/Reporter_Multi_addReporter_787.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::AtLeast;
using ::testing::ReturnRef;

namespace Catch {

// If the alias is not visible from included headers in your tree,
// uncomment the following line to match the production alias.
// using IEventListenerPtr = Detail::unique_ptr<IEventListener>;

// ---- Test doubles ----

// Mock that exposes getPreferences for interaction verification.
// We keep an internal ReporterPreferences instance and ReturnRef it
// so the reference stays valid for the duration of calls.
class MockListener_787 : public IEventListener {
public:
    MockListener_787() : IEventListener(nullptr) {}

    ReporterPreferences prefs; // configured per-test

    MOCK_METHOD((ReporterPreferences const&), getPreferences, (),
                (const, override));
};

// A minimal listener used to verify ownership semantics: its destructor
// flips a flag so we can observe that MultiReporter deleted it.
class FlagListener_787 : public IEventListener {
public:
    explicit FlagListener_787(bool* destroyedFlag)
        : IEventListener(nullptr), flag_(destroyedFlag) {}

    ~FlagListener_787() override {
        if (flag_) *flag_ = true;
    }

private:
    bool* flag_;
};

class MultiReporterTest_787 : public ::testing::Test { };


// ---- Tests ----

// Ensures addReporter consults the reporter's preferences (observable via getPreferences()).
TEST_F(MultiReporterTest_787, AddReporter_InvokesGetPreferences_WhenAdded_787) {
    MultiReporter multi(/*config*/nullptr);

    auto mock = Detail::unique_ptr<MockListener_787>(new MockListener_787{});
    // Try both states to make the test robust; contract only requires the call,
    // not a specific count, because updatePreferences may also read preferences.
    mock->prefs.shouldRedirectStdOut = false;

    EXPECT_CALL(*mock, getPreferences())
        .Times(AtLeast(1))
        .WillRepeatedly(ReturnRef(mock->prefs));

    // Move into base-typed pointer and add
    Detail::unique_ptr<IEventListener> basePtr(std::move(mock));
    multi.addReporter(std::move(basePtr));
}

// Same as above but with shouldRedirectStdOut = true, to cover both branches
// of the observable input passed back via getPreferences().
TEST_F(MultiReporterTest_787, AddReporter_InvokesGetPreferences_WithRedirectTrue_787) {
    MultiReporter multi(/*config*/nullptr);

    auto mock = Detail::unique_ptr<MockListener_787>(new MockListener_787{});
    mock->prefs.shouldRedirectStdOut = true;

    EXPECT_CALL(*mock, getPreferences())
        .Times(AtLeast(1))
        .WillRepeatedly(ReturnRef(mock->prefs));

    Detail::unique_ptr<IEventListener> basePtr(std::move(mock));
    multi.addReporter(std::move(basePtr));
}

// Verifies ownership transfer: the added reporter is destroyed when
// MultiReporter is destroyed (observable via FlagListener_787's destructor side-effect).
TEST_F(MultiReporterTest_787, AddReporter_TakesOwnership_AndDestroysOnScopeExit_787) {
    bool destroyed = false;
    {
        MultiReporter multi(/*config*/nullptr);

        auto owned = Detail::unique_ptr<FlagListener_787>(new FlagListener_787(&destroyed));
        // Convert to base type and hand it over
        Detail::unique_ptr<IEventListener> basePtr(std::move(owned));
        multi.addReporter(std::move(basePtr));

        // While multi is alive, the listener should not be destroyed yet
        EXPECT_FALSE(destroyed);
    }
    // After multi goes out of scope, listener should be destroyed
    EXPECT_TRUE(destroyed);
}

// Adding multiple reporters: all should be owned and destroyed on MultiReporter destruction.
TEST_F(MultiReporterTest_787, AddReporter_MultipleReporters_AllOwnedAndDestroyed_787) {
    bool destroyedA = false;
    bool destroyedB = false;

    {
        MultiReporter multi(/*config*/nullptr);

        Detail::unique_ptr<IEventListener> a(new FlagListener_787(&destroyedA));
        Detail::unique_ptr<IEventListener> b(new FlagListener_787(&destroyedB));

        multi.addReporter(std::move(a));
        multi.addReporter(std::move(b));

        EXPECT_FALSE(destroyedA);
        EXPECT_FALSE(destroyedB);
    }
    EXPECT_TRUE(destroyedA);
    EXPECT_TRUE(destroyedB);
}

} // namespace Catch
