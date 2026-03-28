// multi_reporter_listtags_tests_809.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::Ref;
using ::testing::StrictMock;

namespace Catch {
// If TagInfo isn't transitively included in your build env, you can
// uncomment this minimal forward decl to satisfy the signature.
// struct TagInfo {};
}

class MockListener_809 : public Catch::IEventListener {
public:
    MockListener_809() : Catch::IEventListener(nullptr) {}
    MOCK_METHOD(void, listTags,
                (const std::vector<Catch::TagInfo>&),
                (override));
    // Other callbacks use default base implementations.
};

class MultiReporterListTagsTest_809 : public ::testing::Test {
protected:
    // MultiReporter typically accepts a config pointer; nullptr is fine here.
    Catch::MultiReporter uut_{nullptr};

    // Helper to construct the expected pointer type
    static Catch::IEventListenerPtr makePtr(Catch::IEventListener* p) {
        return Catch::IEventListenerPtr(p);
    }
};

// [Normal operation] Single listener receives the exact same tags reference
TEST_F(MultiReporterListTagsTest_809, ListTags_ForwardsToSingleListener_809) {
    auto* mock = new StrictMock<MockListener_809>();
    uut_.addListener(makePtr(mock));

    std::vector<Catch::TagInfo> tags;
    EXPECT_CALL(*mock, listTags(Ref(tags))).Times(1);

    uut_.listTags(tags);
}

// [Normal operation] Both a listener and a reporter receive the call once each
TEST_F(MultiReporterListTagsTest_809, ListTags_ForwardsToReporterAndListener_809) {
    auto* mockListener = new StrictMock<MockListener_809>();
    auto* mockReporter = new StrictMock<MockListener_809>();

    uut_.addListener(makePtr(mockListener));
    uut_.addReporter(makePtr(mockReporter));

    std::vector<Catch::TagInfo> tags(3); // non-empty to cover boundary variety
    EXPECT_CALL(*mockListener, listTags(Ref(tags))).Times(1);
    EXPECT_CALL(*mockReporter, listTags(Ref(tags))).Times(1);

    uut_.listTags(tags);
}

// [Boundary/empty state] No registered sinks: call is safe and does nothing observable
TEST_F(MultiReporterListTagsTest_809, ListTags_WithNoRegisteredSinks_DoesNotCrash_809) {
    std::vector<Catch::TagInfo> empty;
    EXPECT_NO_THROW(uut_.listTags(empty));
}
