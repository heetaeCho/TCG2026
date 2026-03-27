// File: tests/TestSpecFilterMatches_1005.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::NiceMock;

namespace {

// ---- GMock for TestSpec::Pattern (external collaborator) ----
class MockPattern : public Catch::TestSpec::Pattern {
public:
    explicit MockPattern(const std::string& name = "pat")
        : Catch::TestSpec::Pattern(name) {}

    // Signature follows public interface (no assumptions about internals)
    MOCK_METHOD(bool, matches, (const Catch::TestCaseInfo&), (override));
};

// ---- Small helpers to build TestCaseInfo via the public interface ----
inline Catch::TestCaseInfo MakeTestCaseVisible(const std::string& name = "T") {
    using Catch::NameAndTags;
    using Catch::SourceLineInfo;
    // No tags → not hidden
    return Catch::TestCaseInfo(/*className*/"", NameAndTags{name, ""}, SourceLineInfo{__FILE__, __LINE__});
}

inline Catch::TestCaseInfo MakeTestCaseHidden(const std::string& name = "T") {
    using Catch::NameAndTags;
    using Catch::SourceLineInfo;
    // Tag a test as hidden via the public NameAndTags input
    // (We rely only on the observable effect through isHidden().)
    return Catch::TestCaseInfo(/*className*/"", NameAndTags{name, "[.]"}, SourceLineInfo{__FILE__, __LINE__});
}

inline Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>
MakePatternReturning(NiceMock<MockPattern>*& out_ptr, bool result, const std::string& name = "p") {
    auto raw = new NiceMock<MockPattern>(name);
    out_ptr = raw;
    EXPECT_CALL(*raw, matches(_)).WillRepeatedly(Return(result));
    return Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(raw);
}

} // namespace

// ---- Tests ----

TEST(TestSpecFilterMatches_1005, NoPatterns_Visible_ReturnsTrue_1005) {
    Catch::TestSpec::Filter f;
    auto tc = MakeTestCaseVisible("visible");

    // No required/forbidden patterns
    EXPECT_TRUE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, NoPatterns_Hidden_ReturnsFalse_1005) {
    Catch::TestSpec::Filter f;
    auto tc = MakeTestCaseHidden("hidden");

    EXPECT_FALSE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, RequiredAllMatch_OverridesHidden_ReturnsTrue_1005) {
    Catch::TestSpec::Filter f;

    NiceMock<MockPattern>* p1{};
    NiceMock<MockPattern>* p2{};
    f.m_required.push_back(MakePatternReturning(p1, /*result*/ true, "req1"));
    f.m_required.push_back(MakePatternReturning(p2, /*result*/ true, "req2"));

    auto tc = MakeTestCaseHidden("hidden_but_required_match");

    // With any required pattern present, visibility should not suppress a match
    // as long as all required match and no forbidden match.
    EXPECT_TRUE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, AnyRequiredFails_ReturnsFalse_1005) {
    Catch::TestSpec::Filter f;

    // Use strict call expectations to verify external interactions (short-circuit)
    MockPattern* r1 = new MockPattern("reqFirst");
    MockPattern* r2 = new MockPattern("reqSecond");

    // First required fails -> function should return false immediately,
    // second required should not be called.
    EXPECT_CALL(*r1, matches(_)).Times(Exactly(1)).WillOnce(Return(false));
    EXPECT_CALL(*r2, matches(_)).Times(0);

    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r1));
    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r2));

    auto tc = MakeTestCaseVisible("visible");

    EXPECT_FALSE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, ForbiddenAnyMatches_ReturnsFalse_1005) {
    Catch::TestSpec::Filter f;

    NiceMock<MockPattern>* req{};
    NiceMock<MockPattern>* forb{};

    f.m_required.push_back(MakePatternReturning(req, true, "reqOK"));
    f.m_forbidden.push_back(MakePatternReturning(forb, true, "forbHits"));

    auto tc = MakeTestCaseVisible("visible");

    // Even if required pass, any forbidden match must reject the test case.
    EXPECT_FALSE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, RequiredAllMatch_ForbiddenAllFail_ReturnsTrue_1005) {
    Catch::TestSpec::Filter f;

    NiceMock<MockPattern>* r1{};
    NiceMock<MockPattern>* r2{};
    NiceMock<MockPattern>* f1{};
    NiceMock<MockPattern>* f2{};

    f.m_required.push_back(MakePatternReturning(r1, true, "r1"));
    f.m_required.push_back(MakePatternReturning(r2, true, "r2"));
    f.m_forbidden.push_back(MakePatternReturning(f1, false, "f1"));
    f.m_forbidden.push_back(MakePatternReturning(f2, false, "f2"));

    auto tc = MakeTestCaseVisible("visible");

    EXPECT_TRUE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, NoRequired_ForbiddenMatches_Visible_ReturnsFalse_1005) {
    Catch::TestSpec::Filter f;

    NiceMock<MockPattern>* forb{};
    f.m_forbidden.push_back(MakePatternReturning(forb, true, "forb"));

    auto tc = MakeTestCaseVisible("visible");

    EXPECT_FALSE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, MultipleRequired_AllCheckedInOrder_1005) {
    Catch::TestSpec::Filter f;

    // Verify that evaluation proceeds in order through required patterns
    MockPattern* r1 = new MockPattern("r1");
    MockPattern* r2 = new MockPattern("r2");
    MockPattern* r3 = new MockPattern("r3");

    {
        InSequence seq;
        EXPECT_CALL(*r1, matches(_)).WillOnce(Return(true));
        EXPECT_CALL(*r2, matches(_)).WillOnce(Return(true));
        EXPECT_CALL(*r3, matches(_)).WillOnce(Return(true));
    }

    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r1));
    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r2));
    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r3));

    auto tc = MakeTestCaseVisible("visible");
    EXPECT_TRUE(f.matches(tc));
}

TEST(TestSpecFilterMatches_1005, ForbiddenCheckedAfterRequired_1005) {
    Catch::TestSpec::Filter f;

    // All required match, then forbidden triggers rejection.
    MockPattern* r1 = new MockPattern("r1");
    MockPattern* forb = new MockPattern("forb");

    {
        InSequence seq;
        EXPECT_CALL(*r1, matches(_)).WillOnce(Return(true));
        EXPECT_CALL(*forb, matches(_)).WillOnce(Return(true));
    }

    f.m_required.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(r1));
    f.m_forbidden.push_back(Catch::Detail::unique_ptr<Catch::TestSpec::Pattern>(forb));

    auto tc = MakeTestCaseVisible("visible");
    EXPECT_FALSE(f.matches(tc));
}
