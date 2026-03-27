// TEST_ID: 794

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Truly;

namespace {

class MockEventListener_794 : public Catch::IEventListener {
public:
    MockEventListener_794() : Catch::IEventListener(nullptr) {}
    ~MockEventListener_794() override = default;

    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
};

struct MultiReporterBenchmarkFailedTest_794 : ::testing::Test {
protected:
    // Helper to create a managed pointer while keeping a raw pointer for expectations
    static Catch::Detail::unique_ptr<Catch::IEventListener>
    makeListener(MockEventListener_794*& outRaw) {
        auto* raw = new MockEventListener_794();
        outRaw = raw;
        return Catch::Detail::unique_ptr<Catch::IEventListener>(raw);
    }
};

} // namespace

// Normal operation: forwards to both reporters and listeners with the same argument
TEST_F(MultiReporterBenchmarkFailedTest_794, ForwardsToAllReporterLikes_794) {
    Catch::MultiReporter mr(nullptr);

    MockEventListener_794* repRaw = nullptr;
    MockEventListener_794* lisRaw = nullptr;

    auto repPtr = makeListener(repRaw);
    auto lisPtr = makeListener(lisRaw);

    const char* msg = "boom";
    EXPECT_CALL(*repRaw, benchmarkFailed(Truly([&](const Catch::StringRef& s){
        return static_cast<std::string>(s) == msg;
    }))).Times(1);
    EXPECT_CALL(*lisRaw, benchmarkFailed(Truly([&](const Catch::StringRef& s){
        return static_cast<std::string>(s) == msg;
    }))).Times(1);

    // Mix addReporter and addListener to ensure both are notified
    mr.addReporter(std::move(repPtr));
    mr.addListener(std::move(lisPtr));

    mr.benchmarkFailed(Catch::StringRef(msg));
}

// Boundary: calling with no attached listeners/reporters should be safe
TEST_F(MultiReporterBenchmarkFailedTest_794, HandlesNoListenersGracefully_794) {
    Catch::MultiReporter mr(nullptr);
    EXPECT_NO_THROW(mr.benchmarkFailed(Catch::StringRef("no one cares")));
}

// Error propagation: if a listener throws, the exception is observable to the caller
TEST_F(MultiReporterBenchmarkFailedTest_794, PropagatesExceptionFromListener_794) {
    Catch::MultiReporter mr(nullptr);

    MockEventListener_794* raw = nullptr;
    auto ptr = makeListener(raw);

    EXPECT_CALL(*raw, benchmarkFailed(_))
        .WillOnce(Invoke([](Catch::StringRef){
            throw std::runtime_error("intentional");
        }));

    mr.addListener(std::move(ptr));
    EXPECT_THROW(mr.benchmarkFailed(Catch::StringRef("boom")), std::runtime_error);
}

// Boundary: empty error string is passed through unmodified
TEST_F(MultiReporterBenchmarkFailedTest_794, PassesEmptyStringToListeners_794) {
    Catch::MultiReporter mr(nullptr);

    MockEventListener_794* raw = nullptr;
    auto ptr = makeListener(raw);

    EXPECT_CALL(*raw, benchmarkFailed(Truly([](const Catch::StringRef& s){
        return s.empty();
    }))).Times(1);

    mr.addListener(std::move(ptr));
    mr.benchmarkFailed(Catch::StringRef(""));
}
