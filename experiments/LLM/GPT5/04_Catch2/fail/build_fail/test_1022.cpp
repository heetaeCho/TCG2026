// File: tests/ITracker_findChild_1022.tests.cpp

#include <gtest/gtest.h>
#include <string>

#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stringref.hpp" // for Catch::StringRef

namespace CT = Catch::TestCaseTracking;
namespace CD = Catch::Detail;

// A minimal concrete tracker just to allow instantiation.
// It does NOT change behavior; it forwards to ITracker.
class DummyTracker_1022 : public CT::ITracker {
public:
    explicit DummyTracker_1022(std::string name,
                               Catch::SourceLineInfo loc,
                               CT::ITracker* parent = nullptr)
    : CT::ITracker(CT::NameAndLocation(std::move(name), loc), parent) {}
    ~DummyTracker_1022() override = default;
};

// Test fixture holding a root tracker to attach children to.
class ITrackerFindChildTest_1022 : public ::testing::Test {
protected:
    DummyTracker_1022 root{ "root", Catch::SourceLineInfo{"root.cpp", 1}, nullptr };

    // Helper to add a child to root with given name/file/line.
    CT::ITracker* addChild(const std::string& name,
                           const char* file,
                           std::size_t line) {
        auto child = CD::unique_ptr<DummyTracker_1022>(
            new DummyTracker_1022(name, Catch::SourceLineInfo{file, line}, &root));
        auto raw = child.get();
        // addChild takes ITrackerPtr&&; upcast happens through unique_ptr's converting ctor.
        root.addChild(CD::unique_ptr<CT::ITracker>(std::move(child)));
        return raw;
    }

    // Helper to create NameAndLocationRef for queries
    static CT::NameAndLocationRef makeRef(const char* name,
                                          const char* file,
                                          std::size_t line) {
        return CT::NameAndLocationRef(Catch::StringRef{name}, Catch::SourceLineInfo{file, line});
    }
};

// --- Tests ---

// 1) No children -> returns nullptr
TEST_F(ITrackerFindChildTest_1022, ReturnsNullWhenNoChildren_1022) {
    auto query = makeRef("any", "a.cpp", 123);
    EXPECT_EQ(root.findChild(query), nullptr);
}

// 2) Exact match on name + file + line -> returns that child
TEST_F(ITrackerFindChildTest_1022, FindsExactMatchingChild_1022) {
    auto* expected = addChild("childA", "fileA.cpp", 10);
    // Also add a non-matching sibling to ensure proper selection
    addChild("childB", "fileB.cpp", 20);

    auto query = makeRef("childA", "fileA.cpp", 10);
    EXPECT_EQ(root.findChild(query), expected);
}

// 3) Same name + file but different line -> does not match (guard rejects on line)
TEST_F(ITrackerFindChildTest_1022, DifferentLineDoesNotMatch_1022) {
    addChild("childA", "fileA.cpp", 10);

    auto query = makeRef("childA", "fileA.cpp", 11); // line differs
    EXPECT_EQ(root.findChild(query), nullptr);
}

// 4) Same line + file but different name -> does not match
TEST_F(ITrackerFindChildTest_1022, DifferentNameSameLineDoesNotMatch_1022) {
    addChild("childA", "fileA.cpp", 10);

    auto query = makeRef("childX", "fileA.cpp", 10); // name differs
    EXPECT_EQ(root.findChild(query), nullptr);
}

// 5) Same name + line but different file -> does not match
TEST_F(ITrackerFindChildTest_1022, DifferentFileSameNameAndLineDoesNotMatch_1022) {
    addChild("childA", "fileA.cpp", 10);

    auto query = makeRef("childA", "other.cpp", 10); // file differs
    EXPECT_EQ(root.findChild(query), nullptr);
}

// 6) Multiple children with only the first one matching -> returns the first match
TEST_F(ITrackerFindChildTest_1022, ReturnsFirstMatchingChildWhenMultiple_1022) {
    // First matching child
    auto* first = addChild("dup", "file.cpp", 42);
    // A non-matching child
    addChild("other", "file.cpp", 42);
    // Another matching child later
    auto* second = addChild("dup", "file.cpp", 42);
    (void)second;

    auto query = makeRef("dup", "file.cpp", 42);
    EXPECT_EQ(root.findChild(query), first);
}
