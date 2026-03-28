// File: tests/ReporterMulti_testCasePartialStarting_797.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_source_line_info.hpp"

#include <limits>

using ::testing::_;
using ::testing::Ref;
using ::testing::Eq;

namespace {

// Minimal mock of IEventListener focused on the method under test.
class MockListener_797 : public Catch::IEventListener {
public:
    explicit MockListener_797(const Catch::IConfig* cfg = nullptr)
        : Catch::IEventListener(cfg) {}

    MOCK_METHOD(void, testCasePartialStarting,
                (Catch::TestCaseInfo const&, uint64_t), (override));
};

// Helper to make a simple TestCaseInfo instance for exercising the API.
// We avoid depending on any private/internal state; values are arbitrary but valid.
inline void makeTestCaseInfo_797(Catch::TestCaseInfo*& outPtr, std::unique_ptr<Catch::TestCaseInfo>& holder) {
    // Construct required inputs
    const char* cls = "DummyClass";
    Catch::NameAndTags nat{ "DummyTest", "[tag1][tag2]" };
    Catch::SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };

    // Allocate on heap to keep lifetime straightforward (NonCopyable).
    holder = std::unique_ptr<Catch::TestCaseInfo>(new Catch::TestCaseInfo(cls, nat, sli));
    outPtr = holder.get();
}

class MultiReporterTest_797 : public ::testing::Test {
protected:
    // MultiReporter inherits IEventListener; we pass nullptr config — not used by tested method.
    Catch::MultiReporter mr{ nullptr };

    // Convenience to wrap a raw mock into the expected pointer type.
    static Catch::IEventListenerPtr makePtr(MockListener_797* p) {
        return Catch::IEventListenerPtr(p); // Catch::Detail::unique_ptr-compatible
    }
};

} // namespace

// Normal operation: single reporter receives the forwarded call with exact params
TEST_F(MultiReporterTest_797, ForwardsCallToSingleReporter_797) {
    auto mock = new MockListener_797();
    mr.addReporter(makePtr(mock));

    std::unique_ptr<Catch::TestCaseInfo> holder;
    Catch::TestCaseInfo* info = nullptr;
    makeTestCaseInfo_797(info, holder);

    const uint64_t partNumber = 5;
    EXPECT_CALL(*mock, testCasePartialStarting(Ref(*info), Eq(partNumber))).Times(1);

    mr.testCasePartialStarting(*info, partNumber);
}

// Normal operation: both a listener and a reporter receive the call exactly once
TEST_F(MultiReporterTest_797, ForwardsCallToAllAttachedListenerAndReporter_797) {
    auto mListener = new MockListener_797();
    auto mReporter = new MockListener_797();

    mr.addListener(makePtr(mListener));
    mr.addReporter(makePtr(mReporter));

    std::unique_ptr<Catch::TestCaseInfo> holder;
    Catch::TestCaseInfo* info = nullptr;
    makeTestCaseInfo_797(info, holder);

    const uint64_t partNumber = 42;
    EXPECT_CALL(*mListener, testCasePartialStarting(Ref(*info), Eq(partNumber))).Times(1);
    EXPECT_CALL(*mReporter, testCasePartialStarting(Ref(*info), Eq(partNumber))).Times(1);

    mr.testCasePartialStarting(*info, partNumber);
}

// Boundary: part number = 0 should be forwarded unchanged
TEST_F(MultiReporterTest_797, ForwardsPartNumberZero_797) {
    auto mock = new MockListener_797();
    mr.addReporter(makePtr(mock));

    std::unique_ptr<Catch::TestCaseInfo> holder;
    Catch::TestCaseInfo* info = nullptr;
    makeTestCaseInfo_797(info, holder);

    const uint64_t partNumber = 0;
    EXPECT_CALL(*mock, testCasePartialStarting(Ref(*info), Eq(partNumber))).Times(1);

    mr.testCasePartialStarting(*info, partNumber);
}

// Boundary: part number = UINT64_MAX should be forwarded unchanged
TEST_F(MultiReporterTest_797, ForwardsPartNumberUint64Max_797) {
    auto mock = new MockListener_797();
    mr.addListener(makePtr(mock));

    std::unique_ptr<Catch::TestCaseInfo> holder;
    Catch::TestCaseInfo* info = nullptr;
    makeTestCaseInfo_797(info, holder);

    const uint64_t partNumber = std::numeric_limits<uint64_t>::max();
    EXPECT_CALL(*mock, testCasePartialStarting(Ref(*info), Eq(partNumber))).Times(1);

    mr.testCasePartialStarting(*info, partNumber);
}

// Exceptional/edge observable case: with no reporters/listeners added, the call should be a no-op (no throw)
TEST_F(MultiReporterTest_797, NoReporters_NoThrow_797) {
    std::unique_ptr<Catch::TestCaseInfo> holder;
    Catch::TestCaseInfo* info = nullptr;
    makeTestCaseInfo_797(info, holder);

    EXPECT_NO_THROW(mr.testCasePartialStarting(*info, 1));
}
