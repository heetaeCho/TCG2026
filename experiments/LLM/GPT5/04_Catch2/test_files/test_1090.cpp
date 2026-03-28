#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use real Catch2 public types where possible.
// If your tree uses different include paths, adjust these includes accordingly.
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

// We only need the Section interface used by the constructor & operator bool
#include <catch2/internal/catch_section.hpp>

// ===============================
// Linker seam for getResultCapture
// ===============================
//
// We provide a test-side definition of Catch::getResultCapture() that returns
// a global mock. This cleanly injects a mock IResultCapture without modifying
// production code.
//
// To keep within the “black-box” constraint, we mock only the external
// collaborator’s method actually used by the constructor: sectionStarted(...).
//
// If your build already links another definition of getResultCapture(), place
// this test TU in a separate test target so this definition is used.

namespace Catch {
    // Minimal “counts” type used by sectionStarted signature.
    // If your Catch2 version already defines Catch::Counts, include it instead.
    struct Counts {
        std::size_t passed = 0, failed = 0, failedButOk = 0;
    };

    // Forward declaration of the collaborator interface used by getResultCapture.
    // We declare only the method exercised by the constructor to avoid relying
    // on any private/internal behavior.
    struct IResultCapture {
        virtual ~IResultCapture() = default;
        virtual bool sectionStarted( StringRef name,
                                     SourceLineInfo const& lineInfo,
                                     Counts& assertions ) = 0;
    };

    // getResultCapture is what Section calls inside its ctor. We define it to
    // return our test’s global mock instance (set in the fixture).
    IResultCapture& getResultCapture();
} // namespace Catch

// Global pointer used by our injected getResultCapture() to return the mock.
static Catch::IResultCapture* g_mockCapture = nullptr;

namespace Catch {
    IResultCapture& getResultCapture() {
        // This must be set by the test fixture before constructing Section.
        assert(g_mockCapture != nullptr && "g_mockCapture not set");
        return *g_mockCapture;
    }
} // namespace Catch

// ===============================
// Google Mock for IResultCapture
// ===============================
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(bool, sectionStarted,
                (Catch::StringRef name,
                 const Catch::SourceLineInfo& lineInfo,
                 Catch::Counts& assertions),
                (override));
};

// ===============================
// Test Fixture
// ===============================
class SectionCtorTest_1090 : public ::testing::Test {
protected:
    ::testing::NiceMock<MockResultCapture> mock;

    void SetUp() override { g_mockCapture = &mock; }
    void TearDown() override { g_mockCapture = nullptr; }

    // Helper to build a SourceLineInfo quickly
    static Catch::SourceLineInfo SLI(const char* file, std::size_t line) {
        return Catch::SourceLineInfo{file, line};
    }
};

// ---------------------------------------------
// [1090] External interaction: sectionStarted is
//        called exactly once with the given params
// ---------------------------------------------
TEST_F(SectionCtorTest_1090, SectionStartedIsCalledWithNameAndLine_1090) {
    using ::testing::_;
    using ::testing::AllOf;
    using ::testing::Property;
    using ::testing::Truly;

    const char* file = "unit/section_ctor_test.cpp";
    const std::size_t line = 42;
    Catch::SourceLineInfo sli = SLI(file, line);
    Catch::StringRef name{"outer/inner"};

    // We do not inspect internal counters/timers; just that the call happens
    // with the expected name and line info. The third param is an out/ref and
    // should be accepted by the collaborator.
    EXPECT_CALL(mock, sectionStarted(
                         // Match name content
                         Truly([&](Catch::StringRef n) { return n == name; }),
                         // Match exact file/line
                         Truly([&](const Catch::SourceLineInfo& li) {
                             return li.file == file && li.line == line;
                         }),
                         _))
        .Times(1)
        .WillOnce(::testing::Return(true)); // return value not under test here

    // Act: constructing Section triggers the call
    Catch::Section s{sli, name, /*description*/nullptr};

    // No further expectations: this test focuses only on interaction
}

// ---------------------------------------------
// [1090] When collaborator returns true,
//        Section evaluates to true (normal path)
// ---------------------------------------------
TEST_F(SectionCtorTest_1090, TruthyWhenSectionIncluded_1090) {
    using ::testing::_;
    const char* file = "f.cpp";
    Catch::SourceLineInfo sli = SLI(file, 7);
    Catch::StringRef name{"included-section"};

    EXPECT_CALL(mock, sectionStarted(_, _, _))
        .Times(1)
        .WillOnce(::testing::Return(true));

    Catch::Section s{sli, name, nullptr};

    // Observable behavior: Section should be truthy when included
    bool executed = false;
    if (s) {
        executed = true;
    }
    EXPECT_TRUE(executed);
}

// ---------------------------------------------
// [1090] When collaborator returns false,
//        Section evaluates to false (skipped path)
// ---------------------------------------------
TEST_F(SectionCtorTest_1090, FalsyWhenSectionExcluded_1090) {
    using ::testing::_;
    const char* file = "g.cpp";
    Catch::SourceLineInfo sli = SLI(file, 13);
    Catch::StringRef name{"excluded-section"};

    EXPECT_CALL(mock, sectionStarted(_, _, _))
        .Times(1)
        .WillOnce(::testing::Return(false));

    Catch::Section s{sli, name, nullptr};

    bool executed = false;
    if (s) {
        executed = true;
    }
    EXPECT_FALSE(executed);
}
