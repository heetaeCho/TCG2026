// File: tests/Reporter/MultiReporter_sectionEnded_801.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_multi.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>

// If your build splits interfaces, add any needed headers for SectionInfo/Counts.
// The includes above are enough in a standard Catch2 layout.

using ::testing::_;
using ::testing::Ref;
using ::testing::InSequence;
using ::testing::NiceMock;

namespace {

// Minimal mock of IEventListener that we use strictly as an external collaborator.
class MockListener : public Catch::IEventListener {
public:
    using Catch::IEventListener::IEventListener; // forward ctor(IConfig const*)

    MOCK_METHOD(void, sectionEnded, (Catch::SectionStats const&), (override));

    // Keep other virtuals default (we don't test them here).
};

// Helper to build a valid SectionStats instance without depending on internals.
// We only care that it is a concrete object passed through unchanged.
static Catch::SectionStats makeSectionStats() {
    using namespace Catch;
    // These types are part of public interface; fill with benign values.
    // SectionInfo: name, line info, description (typical Catch2 signature).
    SectionInfo si(StringRef("sec"),
                   SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)},
                   std::string{});

    Counts counts{}; // default constructed is fine for our purposes
    const double duration = 0.0;
    const bool missing = true;

    // The ctor takes SectionInfo&&, Counts const&, double, bool.
    return SectionStats(std::move(si), counts, duration, missing);
}

} // namespace

// Test fixture (keeps naming consistent with TEST_ID).
class MultiReporterSectionEndedTest_801 : public ::testing::Test {
protected:
    // MultiReporter typically takes an IConfig* in its base ctor; nullptr is fine for tests.
    Catch::MultiReporter uut{nullptr};
};

// [Normal] Single reporter: forwarded exactly once with the exact same SectionStats reference.
TEST_F(MultiReporterSectionEndedTest_801, ForwardsToSingleReporter_801) {
    auto stats = makeSectionStats();

    // Create a mock and keep a raw pointer for EXPECT_CALL before moving it into the UUT.
    auto listenerPtr = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));
    auto* listener = listenerPtr.get();

    EXPECT_CALL(*listener, sectionEnded(Ref(stats))).Times(1);

    // You may use addReporter or addListener; both accept IEventListenerPtr.
    uut.addReporter(std::move(listenerPtr));

    // Exercise
    uut.sectionEnded(stats);
}

// [Boundary] No reporters/listeners registered: calling sectionEnded should be a no-op (no crash/throw).
TEST_F(MultiReporterSectionEndedTest_801, NoReporterRegistered_NoThrow_801) {
    auto stats = makeSectionStats();
    EXPECT_NO_THROW(uut.sectionEnded(stats));
}

// [Normal] Multiple reporters: each receives the callback exactly once.
TEST_F(MultiReporterSectionEndedTest_801, ForwardsToAllReporters_OnceEach_801) {
    auto stats = makeSectionStats();

    auto p1 = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));
    auto p2 = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));
    auto p3 = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));

    auto* m1 = p1.get();
    auto* m2 = p2.get();
    auto* m3 = p3.get();

    EXPECT_CALL(*m1, sectionEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*m2, sectionEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*m3, sectionEnded(Ref(stats))).Times(1);

    uut.addReporter(std::move(p1));
    uut.addReporter(std::move(p2));
    uut.addReporter(std::move(p3));

    uut.sectionEnded(stats);
}

// [Normal/Mix] Mix listeners and reporters: all registered “reporter-like” recipients get the callback.
TEST_F(MultiReporterSectionEndedTest_801, ForwardsToListenersAndReporters_801) {
    auto stats = makeSectionStats();

    auto listenerA = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));
    auto reporterB = Catch::Detail::unique_ptr<MockListener>(new MockListener(nullptr));

    auto* mA = listenerA.get();
    auto* mB = reporterB.get();

    EXPECT_CALL(*mA, sectionEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*mB, sectionEnded(Ref(stats))).Times(1);

    uut.addListener(std::move(listenerA));
    uut.addReporter(std::move(reporterB));

    uut.sectionEnded(stats);
}

// [Boundary/Optional] Verify a reasonable call order across recipients (observable behavior).
// If your project does not guarantee order, you can omit this test.
TEST_F(MultiReporterSectionEndedTest_801, ForwardsInRegistrationOrder_Optional_801) {
    auto stats = makeSectionStats();

    NiceMock<MockListener>* m1raw = new NiceMock<MockListener>(nullptr);
    NiceMock<MockListener>* m2raw = new NiceMock<MockListener>(nullptr);

    auto p1 = Catch::Detail::unique_ptr<MockListener>(m1raw);
    auto p2 = Catch::Detail::unique_ptr<MockListener>(m2raw);

    {
        InSequence seq;
        EXPECT_CALL(*m1raw, sectionEnded(Ref(stats))).Times(1);
        EXPECT_CALL(*m2raw, sectionEnded(Ref(stats))).Times(1);
    }

    uut.addReporter(std::move(p1));
    uut.addListener(std::move(p2));

    uut.sectionEnded(stats);
}
