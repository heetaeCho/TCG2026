// File: tests/multireporter_listReporters_806_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/reporters/catch_reporter_multi.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::Ref;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace {

using namespace Catch;

// Minimal mock of IEventListener focusing only on listReporters.
// Other virtuals have default implementations in the real codebase,
// so we do not re-implement or infer any internal logic.
class MockEventListener : public IEventListener {
public:
    MockEventListener() : IEventListener(nullptr) {}
    ~MockEventListener() override = default;

    MOCK_METHOD(void, listReporters,
                (const std::vector<ReporterDescription>& descriptions),
                (override));
};

// A small fixture for convenience. We do not touch any private state,
// and we construct MultiReporter with a null config pointer (interface-allowed).
class MultiReporter_ListReportersTest_806 : public ::testing::Test {
protected:
    // NOTE: If MultiReporter in your codebase requires a config, pass it here.
    // The header shows it's derived from IEventListener; real code usually
    // provides a constructor taking IConfig*. Using nullptr keeps it black-box.
    MultiReporter uut{ /* config */ nullptr };
};

} // namespace

// TEST_ID: 806
TEST_F(MultiReporter_ListReportersTest_806, NoReportersDoesNothing_806) {
    // Arrange
    std::vector<ReporterDescription> descriptions; // can be empty

    // Act + Assert: Just ensure no crash and no interactions (there are none added).
    // With no added reporters/listeners, calling should be a no-op.
    EXPECT_NO_THROW(uut.listReporters(descriptions));
}

// TEST_ID: 806
TEST_F(MultiReporter_ListReportersTest_806, ForwardsToSingleReporter_806) {
    // Arrange
    auto p1 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());
    auto& r1 = *static_cast<StrictMock<MockEventListener>*>(p1.get());

    std::vector<ReporterDescription> descriptions;

    // Expect exactly one forward with the same reference
    EXPECT_CALL(r1, listReporters(Ref(descriptions))).Times(1);

    // Act
    uut.addReporter(std::move(p1));
    uut.listReporters(descriptions);
}

// TEST_ID: 806
TEST_F(MultiReporter_ListReportersTest_806, ForwardsToAllInInsertionOrder_MixedReporterAndListener_806) {
    // Arrange
    auto p1 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());
    auto p2 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());
    auto p3 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());

    auto& r1 = *static_cast<StrictMock<MockEventListener>*>(p1.get());
    auto& r2 = *static_cast<StrictMock<MockEventListener>*>(p2.get());
    auto& r3 = *static_cast<StrictMock<MockEventListener>*>(p3.get());

    std::vector<ReporterDescription> descriptions;

    // We verify call ordering purely via observable interactions.
    InSequence seq;
    EXPECT_CALL(r1, listReporters(Ref(descriptions))).Times(1);
    EXPECT_CALL(r2, listReporters(Ref(descriptions))).Times(1);
    EXPECT_CALL(r3, listReporters(Ref(descriptions))).Times(1);

    // Act
    // Mix addReporter / addListener to ensure MultiReporter treats both as "reporter-likes"
    uut.addListener(std::move(p1));  // 1st
    uut.addReporter(std::move(p2));  // 2nd
    uut.addListener(std::move(p3));  // 3rd

    uut.listReporters(descriptions);
}

// TEST_ID: 806
TEST_F(MultiReporter_ListReportersTest_806, SubsequentCallsReflectNewlyAddedReporterLike_806) {
    // Arrange
    auto p1 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());
    auto& r1 = *static_cast<StrictMock<MockEventListener>*>(p1.get());

    std::vector<ReporterDescription> firstCall;
    std::vector<ReporterDescription> secondCall;

    // First, only r1 should be called
    EXPECT_CALL(r1, listReporters(Ref(firstCall))).Times(1);

    uut.addReporter(std::move(p1));
    uut.listReporters(firstCall);

    // Now add a second one and expect both in order on the next call
    auto p2 = Detail::unique_ptr<IEventListener>(new StrictMock<MockEventListener>());
    auto& r2 = *static_cast<StrictMock<MockEventListener>*>(p2.get());

    {
        InSequence seq;
        EXPECT_CALL(r1, listReporters(Ref(secondCall))).Times(1);
        EXPECT_CALL(r2, listReporters(Ref(secondCall))).Times(1);
    }

    uut.addListener(std::move(p2));
    uut.listReporters(secondCall);
}
