#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstddef>

using ::testing::_;
using ::testing::A;
using ::testing::Return;
using ::testing::StrictMock;

namespace Catch {

// ---- Minimal opaque shims (only what is needed for the interface) ----
struct SourceLineInfo {
    const char* file;
    std::size_t line;
    // Constructible & copyable; contents are opaque to the tests.
    SourceLineInfo(const char* f, std::size_t l) : file(f), line(l) {}
};

struct Counts {
    // Opaque; only the reference identity matters for collaborator calls.
};

class StringRef {
public:
    StringRef(const char* s) : str_(s ? s : "") {}
    // Allow implicit conversion to std::string if needed by APIs
    operator std::string() const { return str_; }
    const char* c_str() const { return str_.c_str(); }
private:
    std::string str_;
};

struct SectionInfo {
    std::string   name;
    SourceLineInfo lineInfo;

    SectionInfo(SourceLineInfo const& _lineInfo,
                std::string _name,
                const char* const /*description*/ = nullptr)
        : name(std::move(_name)), lineInfo(_lineInfo) {}
};

// ---- IResultCapture (only signatures referenced by the code path) ----
class IResultCapture {
public:
    virtual ~IResultCapture() = default;
    virtual bool sectionStarted(StringRef sectionName,
                                SourceLineInfo const& sectionLineInfo,
                                Counts& assertions) = 0;
};

// ---- Global accessor the Section ctor calls. Test overrides this symbol. ----
static IResultCapture* g_resultCapture = nullptr;

IResultCapture& getResultCapture() {
    // In test, this returns our injected mock.
    // ASSERT to fail fast if someone forgot to inject it.
    assert(g_resultCapture && "Test getResultCapture() not initialized");
    return *g_resultCapture;
}

// ---- Timer shim that matches the interface used by Section ctor ----
class Timer {
public:
    void start() {}
    uint64_t getElapsedNanoseconds() const { return 0; }
    uint64_t getElapsedMicroseconds() const { return 0; }
    unsigned int getElapsedMilliseconds() const { return 0; }
    double getElapsedSeconds() const { return 0.0; }
};

// ---- NonCopyable shim (to satisfy Section's inheritance) ----
namespace Detail {
class NonCopyable {
protected:
    NonCopyable() noexcept = default;
    ~NonCopyable() = default;
    NonCopyable(NonCopyable const&)            = delete;
    NonCopyable(NonCopyable&&)                 = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable&&)      = delete;
};
} // namespace Detail

// ---- The SUT interface (only members we use) ----
class Section : private Detail::NonCopyable {
    SectionInfo m_info;
    Counts      m_assertions{};
    bool        m_sectionIncluded{};
    Timer       m_timer{};

public:
    // The rvalue-SectionInfo ctor under test (as provided in the prompt)
    Section(SectionInfo&& info)
        : m_info(std::move(info)),
          m_sectionIncluded(getResultCapture().sectionStarted(m_info.name,
                                                             m_info.lineInfo,
                                                             m_assertions)) {
        if (m_sectionIncluded) {
            m_timer.start();
        }
    }

    // Public, observable query (interface in prompt)
    explicit operator bool() const { return m_sectionIncluded; }
};

} // namespace Catch

// ------------------------- Test doubles -------------------------

class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(bool, sectionStarted,
                (Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&),
                (override));
};

// --------------------------- Fixture ----------------------------

class SectionCtorTest_1089 : public ::testing::Test {
protected:
    StrictMock<MockResultCapture> mock_;

    void SetUp() override {
        Catch::g_resultCapture = &mock_;
    }
    void TearDown() override {
        Catch::g_resultCapture = nullptr;
    }

    static Catch::SectionInfo makeInfo(const char* file,
                                       std::size_t line,
                                       std::string name) {
        return Catch::SectionInfo(Catch::SourceLineInfo(file, line), std::move(name));
    }
};

// ---------------------------- Tests -----------------------------

// Normal operation: sectionStarted returns true -> Section is "active" (truthy).
TEST_F(SectionCtorTest_1089, SectionStartedTrue_YieldsTruthy_1089) {
    auto info = makeInfo("file.cpp", 42, "alpha");

    // Expect collaborator call with name and lineInfo; Counts passed by ref.
    EXPECT_CALL(mock_,
        sectionStarted(testing::Property(&std::string, std::string("alpha")),
                       testing::AllOf(
                           testing::Field(&Catch::SourceLineInfo::file, testing::StrEq("file.cpp")),
                           testing::Field(&Catch::SourceLineInfo::line, 42u)),
                       A<Catch::Counts&>()))
        .WillOnce(Return(true));

    Catch::Section s(std::move(info));
    EXPECT_TRUE(static_cast<bool>(s));
}

// Exceptional/negative path: sectionStarted returns false -> Section is falsy.
TEST_F(SectionCtorTest_1089, SectionStartedFalse_YieldsFalsy_1089) {
    auto info = makeInfo("x.cpp", 7, "beta");

    EXPECT_CALL(mock_,
        sectionStarted(_, testing::_, A<Catch::Counts&>()))
        .WillOnce(Return(false));

    Catch::Section s(std::move(info));
    EXPECT_FALSE(static_cast<bool>(s));
}

// Boundary case: empty section name still forwarded to collaborator correctly.
TEST_F(SectionCtorTest_1089, EmptyName_IsForwardedAndHandled_1089) {
    auto info = makeInfo("b.cpp", 0, "");

    EXPECT_CALL(mock_,
        sectionStarted(testing::Property(&std::string, std::string("")),
                       testing::AllOf(
                           testing::Field(&Catch::SourceLineInfo::file, testing::StrEq("b.cpp")),
                           testing::Field(&Catch::SourceLineInfo::line, 0u)),
                       A<Catch::Counts&>()))
        .WillOnce(Return(true));

    Catch::Section s(std::move(info));
    EXPECT_TRUE(static_cast<bool>(s));
}
