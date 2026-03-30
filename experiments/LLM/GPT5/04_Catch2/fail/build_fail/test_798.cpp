// File: tests/multi_reporter_sectionStarting_798.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::StrictMock;
using ::testing::Truly;

namespace {

// Minimal mock that only overrides what we observe: sectionStarting.
class MockListener : public Catch::IEventListener {
public:
    // Inherit the base constructor: takes IConfig const* (we'll pass nullptr).
    using Catch::IEventListener::IEventListener;

    MOCK_METHOD(void, sectionStarting, (const Catch::SectionInfo&), (override));
};

// Helper to build a SectionInfo with stable, explicit values.
inline Catch::SectionInfo makeSectionInfo(const char* file, std::size_t line, std::string name) {
    Catch::SourceLineInfo sli{file, static_cast<std::size_t>(line)};
    return Catch::SectionInfo{sli, std::move(name)};
}

} // namespace

// [Normal] Calling sectionStarting with no registered listeners/reporters should be a no-op (no crash).
TEST(MultiReporter_798, SectionStarting_NoReporters_DoesNotCrash_798) {
    // Arrange
    // MultiReporter derives from IEventListener and is constructible as-is.
    // If your project requires a config, the base ctor accepts nullptr config.
    Catch::MultiReporter uut; // default-constructed

    auto info = makeSectionInfo("file_a.cpp", 10, "EmptyCase");

    // Act + Assert: Just call; test passes if it does not throw/abort.
    uut.sectionStarting(info);
}

// [Normal] Single listener receives exactly one call with the same SectionInfo object (identity + content).
TEST(MultiReporter_798, SectionStarting_ForwardsToSingleListener_PassesSameObject_798) {
    Catch::MultiReporter uut;

    // Prepare a strict mock and keep a raw pointer for expectations
    auto* raw = new StrictMock<MockListener>(/*config*/nullptr);

    // Move into Catch's unique_ptr alias (IEventListenerPtr) and register as a listener.
    Catch::IEventListenerPtr ptr(raw);
    uut.addListener(std::move(ptr));

    auto info = makeSectionInfo("file_b.cpp", 42, "OneListener");

    // Expect one call; verify both identity (same object) and salient fields.
    EXPECT_CALL(*raw, sectionStarting(Truly([&](const Catch::SectionInfo& s) {
        return &s == &info && s.name == "OneListener" && s.lineInfo.line == 42;
    }))).Times(1);

    uut.sectionStarting(info);
}

// [Normal] Multiple registered collaborators (listener + reporter) each receive the call exactly once.
TEST(MultiReporter_798, SectionStarting_ForwardsToAllReporterLikes_OnceEach_798) {
    Catch::MultiReporter uut;

    // Listener mock
    auto* listenerRaw = new StrictMock<MockListener>(nullptr);
    Catch::IEventListenerPtr listenerPtr(listenerRaw);
    uut.addListener(std::move(listenerPtr));

    // Reporter mock (we reuse the same mock type; it's still an IEventListener)
    auto* reporterRaw = new StrictMock<MockListener>(nullptr);
    Catch::IEventListenerPtr reporterPtr(reporterRaw);
    uut.addReporter(std::move(reporterPtr));

    auto info = makeSectionInfo("file_c.cpp", 7, "TwoRecipients");

    EXPECT_CALL(*listenerRaw, sectionStarting(Field(&Catch::SectionInfo::name, "TwoRecipients"))).Times(1);
    EXPECT_CALL(*reporterRaw, sectionStarting(Field(&Catch::SectionInfo::name, "TwoRecipients"))).Times(1);

    uut.sectionStarting(info);
}

// [Boundary] Unicode / long names are forwarded intact.
TEST(MultiReporter_798, SectionStarting_PropagatesUnicodeAndLongNames_798) {
    Catch::MultiReporter uut;

    auto* raw = new StrictMock<MockListener>(nullptr);
    Catch::IEventListenerPtr ptr(raw);
    uut.addReporter(std::move(ptr));

    std::string longUnicodeName = u8"섹션-테스트-🧪-"
                                  + std::string(1024, 'X'); // long tail to check size handling
    auto info = makeSectionInfo("unicode.cpp", 123, longUnicodeName);

    EXPECT_CALL(*raw, sectionStarting(Field(&Catch::SectionInfo::name, longUnicodeName))).Times(1);

    uut.sectionStarting(info);
}
