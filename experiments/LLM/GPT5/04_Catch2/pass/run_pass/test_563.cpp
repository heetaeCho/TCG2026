// StreamingReporterBase_sectionStarting_tests_563.cpp
#include <gtest/gtest.h>
#include <string>
#include <vector>

//
// ---- Minimal stubs to satisfy the interface seen in the prompt ----
// (Only what's necessary for compilation & calling sectionStarting)
//
namespace Catch {

struct SourceLineInfo {
    const char* file;
    std::size_t line;
};

struct SectionInfo {
    SectionInfo(SourceLineInfo const& _lineInfo,
                std::string _name,
                const char* const /*desc*/ = nullptr)
        : name(std::move(_name)), lineInfo(_lineInfo) {}
    std::string name;
    SourceLineInfo lineInfo;
};

// Reporter base + config stubs
struct ReporterConfig {};
class ReporterBase {
public:
    explicit ReporterBase(ReporterConfig&&) {}
    virtual ~ReporterBase() = default;
    virtual void sectionStarting(SectionInfo const&) {}
};

// Class under test: only members we need for these tests.
// Implementation of sectionStarting is the one shown in the prompt.
class StreamingReporterBase : public ReporterBase {
public:
    explicit StreamingReporterBase(ReporterConfig&& cfg)
        : ReporterBase(std::move(cfg)) {}
    ~StreamingReporterBase() override = default;

    void sectionStarting(SectionInfo const& _sectionInfo) override {
        m_sectionStack.push_back(_sectionInfo);
    }

protected:
    std::vector<SectionInfo> m_sectionStack;
};

} // namespace Catch

//
// ---- Test double exposing read-only observations for assertions ----
//
class ObservableStreamingReporter : public Catch::StreamingReporterBase {
public:
    ObservableStreamingReporter()
        : Catch::StreamingReporterBase(Catch::ReporterConfig{}) {}

    // Re-expose the public entry point to be explicit in tests
    using Catch::StreamingReporterBase::sectionStarting;

    // Read-only observation helpers (derived class can read protected state)
    size_t stackSize() const { return m_sectionStack.size(); }
    std::string topSectionName() const {
        if (m_sectionStack.empty()) return {};
        return m_sectionStack.back().name;
    }
};

//
// ---- Test fixture ----
class StreamingReporterBaseTest_563 : public ::testing::Test {
protected:
    Catch::SourceLineInfo line(const char* f, std::size_t l) {
        return Catch::SourceLineInfo{f, l};
    }
};

//
// ---- Tests ----
//

TEST_F(StreamingReporterBaseTest_563, PushesSingleSection_563) {
    ObservableStreamingReporter rep;

    EXPECT_EQ(rep.stackSize(), 0u);

    rep.sectionStarting(Catch::SectionInfo{line("t.cpp", 10), "root"});

    EXPECT_EQ(rep.stackSize(), 1u);
    EXPECT_EQ(rep.topSectionName(), "root");
}

TEST_F(StreamingReporterBaseTest_563, PushesMultipleSectionsInOrder_LIFOObservation_563) {
    ObservableStreamingReporter rep;

    rep.sectionStarting(Catch::SectionInfo{line("a.cpp", 1), "A"});
    rep.sectionStarting(Catch::SectionInfo{line("b.cpp", 2), "B"});
    rep.sectionStarting(Catch::SectionInfo{line("c.cpp", 3), "C"});

    EXPECT_EQ(rep.stackSize(), 3u);
    EXPECT_EQ(rep.topSectionName(), "C"); // last pushed is at the top
}

TEST_F(StreamingReporterBaseTest_563, HandlesEmptyName_563) {
    ObservableStreamingReporter rep;

    rep.sectionStarting(Catch::SectionInfo{line("x.cpp", 42), ""});

    EXPECT_EQ(rep.stackSize(), 1u);
    EXPECT_EQ(rep.topSectionName(), ""); // empty is preserved as provided
}

TEST_F(StreamingReporterBaseTest_563, HandlesVeryLongName_563) {
    ObservableStreamingReporter rep;

    std::string longName(10000, 'x'); // boundary-ish: very long section name
    rep.sectionStarting(Catch::SectionInfo{line("long.cpp", 7), longName});

    EXPECT_EQ(rep.stackSize(), 1u);
    EXPECT_EQ(rep.topSectionName(), longName);
}

TEST_F(StreamingReporterBaseTest_563, MultipleIndependentCallsDoNotThrow_563) {
    ObservableStreamingReporter rep;

    EXPECT_NO_THROW({
        rep.sectionStarting(Catch::SectionInfo{line("f.cpp", 11), "S1"});
        rep.sectionStarting(Catch::SectionInfo{line("f.cpp", 12), "S2"});
        rep.sectionStarting(Catch::SectionInfo{line("f.cpp", 13), "S3"});
    });

    EXPECT_EQ(rep.stackSize(), 3u);
    EXPECT_EQ(rep.topSectionName(), "S3");
}
