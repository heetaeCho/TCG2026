// File: acquire_generator_tracker_test_354.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <cstring>

// ---------------- Minimal stubs & forward decls (interface-only) ----------------
namespace Catch {

    // Minimal StringRef for testing parameter forwarding (no internal logic).
    class StringRef {
    public:
        StringRef() : s_(nullptr) {}
        /* implicit */ StringRef(const char* s) : s_(s) {}
        const char* c_str() const { return s_; }
    private:
        const char* s_;
    };

    struct SourceLineInfo {
        const char* file;
        std::size_t line;
        constexpr SourceLineInfo(const char* f, std::size_t l) : file(f), line(l) {}
    };

    namespace Generators {
        struct IGeneratorTracker { virtual ~IGeneratorTracker() = default; };
    }

    class IResultCapture {
    public:
        virtual ~IResultCapture() = default;
        virtual Generators::IGeneratorTracker*
        acquireGeneratorTracker(StringRef generatorName, const SourceLineInfo& lineInfo) = 0;
    };

    // Forward declare dependency seam; defined below to return our mock.
    IResultCapture& getResultCapture();
} // namespace Catch

// ---------------- Include the SUT (delegation wrapper) ----------------
// Uses only the declared interface above.
#include "Catch2/src/catch2/generators/catch_generators.cpp"

// ---------------- Mock & seam implementation ----------------
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(Catch::Generators::IGeneratorTracker*, acquireGeneratorTracker,
        (Catch::StringRef generatorName, const Catch::SourceLineInfo& lineInfo), (override));
};

// Global seam storage for the mock
static MockResultCapture* g_mockCapture = nullptr;

namespace Catch {
    IResultCapture& getResultCapture() {
        if (!g_mockCapture) throw std::logic_error("Mock IResultCapture not set");
        return *g_mockCapture;
    }
}

// Dummy tracker type to return from the mock
struct DummyTracker : Catch::Generators::IGeneratorTracker {};

// ---------------- Test Fixture ----------------
class AcquireGeneratorTrackerTest_354 : public ::testing::Test {
protected:
    ::testing::NiceMock<MockResultCapture> mock_;
    void SetUp() override { g_mockCapture = &mock_; }
    void TearDown() override { g_mockCapture = nullptr; }
};

// ---------------- Tests ----------------

// Verifies that the wrapper returns exactly what IResultCapture::acquireGeneratorTracker returns.
TEST_F(AcquireGeneratorTrackerTest_354, ReturnsPointerFromResultCapture_354) {
    DummyTracker tracker;
    EXPECT_CALL(mock_, acquireGeneratorTracker(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(&tracker));

    auto* out = Catch::Generators::acquireGeneratorTracker("GenA", {"file.cpp", 123});
    EXPECT_EQ(out, &tracker);
}

// Verifies that parameters are forwarded unchanged to the collaborator (name, file, line).
TEST_F(AcquireGeneratorTrackerTest_354, ForwardsParameters_354) {
    DummyTracker tracker;

    // Capture args to assert after call
    Catch::StringRef seenName;
    Catch::SourceLineInfo seenInfo{"", 0};

    EXPECT_CALL(mock_, acquireGeneratorTracker(::testing::_, ::testing::_))
        .WillOnce([&](Catch::StringRef name, const Catch::SourceLineInfo& info) {
            seenName = name;
            seenInfo = info;
            return &tracker;
        });

    const char* kName = "UniformInts";
    const char* kFile = "path/to/generators.cpp";
    const std::size_t kLine = 42;

    auto* out = Catch::Generators::acquireGeneratorTracker(kName, {kFile, kLine});
    ASSERT_EQ(out, &tracker);

    ASSERT_NE(seenName.c_str(), nullptr);
    EXPECT_STREQ(seenName.c_str(), kName);
    EXPECT_STREQ(seenInfo.file, kFile);
    EXPECT_EQ(seenInfo.line, kLine);
}

// Verifies boundary-ish inputs (empty name, line=0) are passed through without alteration.
TEST_F(AcquireGeneratorTrackerTest_354, HandlesEmptyNameAndZeroLine_354) {
    DummyTracker tracker;

    EXPECT_CALL(mock_, acquireGeneratorTracker(::testing::_, ::testing::_))
        .WillOnce([&](Catch::StringRef name, const Catch::SourceLineInfo& info) {
            // name could be "", ensure it is forwarded as-is
            const char* s = name.c_str();
            EXPECT_TRUE(s == nullptr || std::strlen(s) == 0);
            EXPECT_STREQ(info.file, "");
            EXPECT_EQ(info.line, 0u);
            return &tracker;
        });

    auto* out = Catch::Generators::acquireGeneratorTracker("", {"", 0});
    EXPECT_EQ(out, &tracker);
}

// Verifies that exceptions from the collaborator propagate unchanged.
TEST_F(AcquireGeneratorTrackerTest_354, PropagatesExceptions_354) {
    EXPECT_CALL(mock_, acquireGeneratorTracker(::testing::_, ::testing::_))
        .WillOnce(::testing::Throw(std::runtime_error("boom")));

    EXPECT_THROW(
        (void)Catch::Generators::acquireGeneratorTracker("X", {"f.cpp", 7}),
        std::runtime_error
    );
}
