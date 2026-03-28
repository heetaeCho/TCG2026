// File: tests/sonarqube_writeTestCase_829_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//
// These minimal forward declarations mirror only the
// pieces of the public interface that writeTestCase touches.
// We are NOT re-implementing internal logic; just enough
// surface to set up black-box inputs/observations.
//
namespace Catch {

struct SectionNode {
    // Intentionally empty: writeTestCase only forwards a reference to this.
};

struct TestCaseInfo {
    // Provide only the observable call used by writeTestCase.
    // In the real codebase this already exists; in unit tests this acts
    // as the public interface we rely on (okToFail()).
    virtual ~TestCaseInfo() = default;
    virtual bool okToFail() const = 0;
};

// Convenience concrete TestCaseInfo for tests.
struct TestCaseInfoStub final : TestCaseInfo {
    explicit TestCaseInfoStub(bool val) : val_(val) {}
    bool okToFail() const override { return val_; }
private:
    bool val_;
};

// Catch::Detail::unique_ptr is used in real sources; for the purpose of
// exercising writeTestCase we can use std::unique_ptr, as we only need
// the *observable* behavior (owning pointer with operator* returning a ref).
// If your project requires Catch's unique_ptr, include its header and
// replace this alias with Catch::Detail::unique_ptr.
template <typename T>
using UniquePtr = std::unique_ptr<T>;

// A minimal "Node" that mimics the few members writeTestCase actually touches.
template <typename T>
struct NodeLike {
    struct Value {
        TestCaseInfo* testInfo = nullptr; // writeTestCase reads this->okToFail()
    } value;

    std::vector<UniquePtr<SectionNode>> children;
};

// Public type names used by SonarQubeReporter interface:
using TestCaseNode = NodeLike<int>; // T's concrete type is irrelevant to writeTestCase
                                    // (only .value.testInfo and .children are used)

class SonarQubeReporter {
public:
    // Method under test (already implemented in production code).
    void writeTestCase(TestCaseNode const& testCaseNode);

    // Dependency that writeTestCase calls; we declare it virtual so we can
    // observe calls in the test via a partial mock. In your production header,
    // if this is already virtual, great; if not, see the note below.
    virtual void writeSection(std::string const& rootName,
                              SectionNode const& sectionNode,
                              bool okToFail) {
        // Default no-op; real implementation writes XML, etc.
        (void)rootName; (void)sectionNode; (void)okToFail;
    }

    virtual ~SonarQubeReporter() = default;
};

} // namespace Catch

// ----------------------- Test doubles -----------------------

namespace {

using ::testing::_;
using ::testing::Eq;
using ::testing::Ref;
using ::testing::StrEq;

class MockSonarQubeReporter : public Catch::SonarQubeReporter {
public:
    MOCK_METHOD(void, writeSection,
        (const std::string& rootName, const Catch::SectionNode& sectionNode, bool okToFail),
        (override));
};

// Helper to build a TestCaseNode with 0/1/N children and selectable okToFail.
struct TCNBuilder {
    Catch::TestCaseNode node;
    std::vector<std::unique_ptr<Catch::SectionNode>> owned; // keep raw addrs stable if needed
    Catch::TestCaseInfoStub* tci_raw = nullptr;
    std::unique_ptr<Catch::TestCaseInfoStub> tci;

    TCNBuilder& withOkToFail(bool v) {
        tci = std::make_unique<Catch::TestCaseInfoStub>(v);
        tci_raw = tci.get();
        node.value.testInfo = tci_raw;
        return *this;
    }

    TCNBuilder& withChildren(size_t n) {
        node.children.clear();
        for (size_t i = 0; i < n; ++i) {
            node.children.emplace_back(std::make_unique<Catch::SectionNode>());
        }
        return *this;
    }

    const Catch::TestCaseNode& get() const { return node; }
    Catch::SectionNode const& onlyChildRef() const { return *node.children.front(); }
};

} // namespace

// ----------------------- Tests -----------------------

//
// Normal operation: exactly one child; okToFail = false
//
TEST(SonarQubeReporter_WriteTestCase_829, CallsWriteSectionWithEmptyRoot_AndFalseOkToFail_829) {
    MockSonarQubeReporter reporter;

    TCNBuilder b;
    b.withOkToFail(false).withChildren(1);

    // Expect forwarding: rootName "", the sole child by reference, and okToFail=false
    EXPECT_CALL(reporter,
        writeSection(StrEq(""), Ref(b.onlyChildRef()), /*okToFail*/ Eq(false)));

    reporter.writeTestCase(b.get());
}

//
// Normal operation: exactly one child; okToFail = true
//
TEST(SonarQubeReporter_WriteTestCase_829, CallsWriteSectionWithEmptyRoot_AndTrueOkToFail_829) {
    MockSonarQubeReporter reporter;

    TCNBuilder b;
    b.withOkToFail(true).withChildren(1);

    EXPECT_CALL(reporter,
        writeSection(StrEq(""), Ref(b.onlyChildRef()), /*okToFail*/ Eq(true)));

    reporter.writeTestCase(b.get());
}

//
// Boundary condition: 0 children -> assertion should fire.
// These are death tests and run only when assertions are enabled (no NDEBUG).
//
#ifndef NDEBUG
TEST(SonarQubeReporter_WriteTestCase_829, AssertsWhenZeroChildren_829) {
    MockSonarQubeReporter reporter;

    TCNBuilder b;
    b.withOkToFail(false).withChildren(0);

    // Expect the process to die due to the assertion.
    ASSERT_DEATH({ reporter.writeTestCase(b.get()); }, "");
}

TEST(SonarQubeReporter_WriteTestCase_829, AssertsWhenMoreThanOneChild_829) {
    MockSonarQubeReporter reporter;

    TCNBuilder b;
    b.withOkToFail(true).withChildren(2);

    ASSERT_DEATH({ reporter.writeTestCase(b.get()); }, "");
}
#endif

//
// Exceptional/error surface: null testInfo dereference is undefined behavior in the
// implementation (it calls testInfo->okToFail()). We can validate it fails obviously.
// Guarded as a death test in debug-like runs.
//
#ifndef NDEBUG
TEST(SonarQubeReporter_WriteTestCase_829, DiesIfTestInfoIsNull_829) {
    MockSonarQubeReporter reporter;

    Catch::TestCaseNode node;
    node.value.testInfo = nullptr;
    node.children.emplace_back(std::make_unique<Catch::SectionNode>());

    ASSERT_DEATH({ reporter.writeTestCase(node); }, "");
}
#endif

