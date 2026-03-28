#include <gtest/gtest.h>
#include <string>

// ---- Minimal stubs to satisfy the provided partial interfaces ----
// These are lightweight, interface-only shims to let the tests compile,
// and do not re-implement any internal logic.

namespace Catch {

struct SourceLineInfo {
    const char* file = "";
    std::size_t line = 0;
    SourceLineInfo(const char* f = "", std::size_t l = 0) : file(f), line(l) {}
};

struct Counts {
    // Keep empty for interface purposes only
};

struct SectionInfo {
    std::string name;
    SourceLineInfo lineInfo;

    SectionInfo(SourceLineInfo const& _lineInfo,
                std::string _name,
                const char* const = nullptr)
        : name(std::move(_name)), lineInfo(_lineInfo) {}
};

struct SectionStats {
    // public members per snippet
    bool missingAssertions{false};

    // minimal fields to satisfy construction; real impl is hidden
    SectionInfo sectionInfo{SourceLineInfo{}, ""};
    Counts assertions{};
    double durationInSeconds{0.0};

    SectionStats(SectionInfo&& _sectionInfo,
                 Counts const& _assertions,
                 double _durationInSeconds,
                 bool _missingAssertions)
        : missingAssertions(_missingAssertions),
          sectionInfo(std::move(_sectionInfo)),
          assertions(_assertions),
          durationInSeconds(_durationInSeconds) {}
};

// Forward declare Detail::unique_ptr used in headers
namespace Detail {
template <typename T>
class unique_ptr {
    T* m_ptr;
public:
    constexpr unique_ptr(std::nullptr_t = nullptr) : m_ptr(nullptr) {}
    explicit constexpr unique_ptr(T* ptr) : m_ptr(ptr) {}
    unique_ptr(unique_ptr const&) = delete;
    unique_ptr(unique_ptr&& rhs) noexcept : m_ptr(rhs.m_ptr) { rhs.m_ptr = nullptr; }
    unique_ptr& operator=(unique_ptr const&) = delete;
    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs) { delete m_ptr; m_ptr = rhs.m_ptr; rhs.m_ptr = nullptr; }
        return *this;
    }
    ~unique_ptr() { delete m_ptr; }
    T& operator*() { return *m_ptr; }
    T* operator->() noexcept { return m_ptr; }
    T* get() { return m_ptr; }
    void reset(T* ptr = nullptr) { delete m_ptr; m_ptr = ptr; }
    T* release() { T* p = m_ptr; m_ptr = nullptr; return p; }
    explicit operator bool() const { return m_ptr != nullptr; }
};
} // namespace Detail

// Minimal ReporterBase & config to satisfy inheritance
struct ReporterConfig {
    // Only what we need to construct the base
};

class ReporterBase {
public:
    explicit ReporterBase(ReporterConfig&&) {}
    virtual ~ReporterBase() = default;

    // Virtuals referenced in the header; keep them virtual to satisfy vtable.
    virtual void sectionStarting(SectionInfo const&) {}
};

// ------------------- Class Under Test (public interface only) -----------------
// We don't re-implement; we just bring in the signature we need to call.
class CumulativeReporterBase : public ReporterBase {
public:
    using ReporterBase::ReporterBase;
    // We are going to call this; the real implementation is linked in prod code.
    void sectionStarting(SectionInfo const& sectionInfo) override;
};

} // namespace Catch

// ----------------------------- Test Fixture ----------------------------------

class CumulativeReporterBase_857 : public ::testing::Test {
protected:
    // A concrete, do-nothing reporter we can instantiate.
    struct TestableReporter : public Catch::CumulativeReporterBase {
        explicit TestableReporter(Catch::ReporterConfig&& cfg)
            : Catch::CumulativeReporterBase(std::move(cfg)) {}
        ~TestableReporter() override = default;
    };

    Catch::SourceLineInfo lineRoot{"file.cpp", 10};
    Catch::SourceLineInfo lineChildA{"file.cpp", 20};
    Catch::SourceLineInfo lineChildB{"file.cpp", 30};

    Catch::SectionInfo root{lineRoot, "Root"};
    Catch::SectionInfo childA{lineChildA, "ChildA"};
    Catch::SectionInfo childB{lineChildB, "ChildB"};

    TestableReporter makeReporter() {
        return TestableReporter(Catch::ReporterConfig{});
    }
};

// ------------------------------ Test Cases -----------------------------------

// Normal operation: first section becomes the root; must not throw.
TEST_F(CumulativeReporterBase_857, SectionStarting_RootSection_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));
}

// Boundary/normal: starting a child after root should be accepted and not throw.
TEST_F(CumulativeReporterBase_857, SectionStarting_ChildUnderRoot_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));
    EXPECT_NO_THROW(rep.sectionStarting(childA));
}

// Multiple siblings under the same parent should be accepted and not throw.
TEST_F(CumulativeReporterBase_857, SectionStarting_MultipleSiblings_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));
    EXPECT_NO_THROW(rep.sectionStarting(childA));
    EXPECT_NO_THROW(rep.sectionStarting(childB));
}

// Deep nesting: root -> childA -> childB should be accepted and not throw.
TEST_F(CumulativeReporterBase_857, SectionStarting_DeepNesting_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));
    EXPECT_NO_THROW(rep.sectionStarting(childA));
    EXPECT_NO_THROW(rep.sectionStarting(childB));
}

// Idempotency-ish surface check: starting the same child twice under the same parent
// should be well-defined per the interface (no crash/throw). Implementation
// deduplicates internally, but we don't assert internals.
TEST_F(CumulativeReporterBase_857, SectionStarting_RepeatedSameSection_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));
    EXPECT_NO_THROW(rep.sectionStarting(childA));
    EXPECT_NO_THROW(rep.sectionStarting(childA)); // starting same SectionInfo again
}

// Stress-ish edge: sequence of many sections (simulate a wider, shallow tree)
// ensures no unexpected exceptions with repeated starts.
TEST_F(CumulativeReporterBase_857, SectionStarting_WideShallow_NoThrow_857) {
    auto rep = makeReporter();
    EXPECT_NO_THROW(rep.sectionStarting(root));

    for (int i = 0; i < 50; ++i) {
        Catch::SourceLineInfo li{"file.cpp", static_cast<std::size_t>(100 + i)};
        Catch::SectionInfo si{li, std::string("S_") + std::to_string(i)};
        EXPECT_NO_THROW(rep.sectionStarting(si));
    }
}
