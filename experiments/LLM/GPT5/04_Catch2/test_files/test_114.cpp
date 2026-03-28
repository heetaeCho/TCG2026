// ReporterConfig_tests_114.cpp
#include <gtest/gtest.h>
#include <map>
#include <memory>
#include <sstream>

// Pull in the CUT headers (paths match your snippet)
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

namespace {

// Minimal stub for IStream to allow constructing a non-null stream.
// We do not test any internal behavior of ReporterConfig using this.
struct DummyStream : Catch::IStream {
    std::ostringstream oss;
    std::ostream& stream() override { return oss; }
    ~DummyStream() override = default;
};

} // namespace

// Fixture kept simple for clarity; each test creates its own instance.
class ReporterConfigTest_114 : public ::testing::Test {};

// --- Normal operation: constructor + accessors (colourMode, fullConfig=nullptr, options) ---
TEST_F(ReporterConfigTest_114, ConstructAndAccessors_ReturnProvidedValues_114) {
    // Arrange
    const Catch::IConfig* cfg = nullptr; // we verify nullptr is preserved via fullConfig()
    // Use an arbitrary ColourMode value without assuming specific enumerators.
    ColourMode mode = static_cast<ColourMode>(3);

    std::map<std::string, std::string> options{
        {"format", "compact"},
        {"verbose", "true"}
    };

    // Give ReporterConfig an empty (null) stream; this avoids depending on IStream details here.
    Catch::Detail::unique_ptr<Catch::IStream> streamPtr{nullptr};

    // Act
    Catch::ReporterConfig rc(cfg, std::move(streamPtr), mode, options);

    // Assert
    EXPECT_EQ(rc.fullConfig(), cfg);                  // preserves provided pointer
    EXPECT_EQ(rc.colourMode(), mode);                 // preserves provided colour mode
    const auto& view = rc.customOptions();            // observable: returns const& to key/values
    ASSERT_EQ(view.size(), options.size());
    EXPECT_EQ(view.at("format"), "compact");
    EXPECT_EQ(view.at("verbose"), "true");
}

// --- Boundary: customOptions with empty map ---
TEST_F(ReporterConfigTest_114, CustomOptions_EmptyMap_ReturnsEmptyView_114) {
    // Arrange
    const Catch::IConfig* cfg = nullptr;
    ColourMode mode = static_cast<ColourMode>(0);
    std::map<std::string, std::string> emptyOptions;
    Catch::Detail::unique_ptr<Catch::IStream> streamPtr{nullptr};

    // Act
    Catch::ReporterConfig rc(cfg, std::move(streamPtr), mode, emptyOptions);

    // Assert
    const auto& view = rc.customOptions();
    EXPECT_TRUE(view.empty());
}

// --- Normal operation: takeStream() && transfers ownership of a non-null stream ---
TEST_F(ReporterConfigTest_114, TakeStream_RvalueReturnsNonNullAndTransfersOwnership_114) {
    // Arrange
    const Catch::IConfig* cfg = nullptr;
    ColourMode mode = static_cast<ColourMode>(1);
    std::map<std::string, std::string> options;

    // Provide a valid IStream implementation instance.
    auto dummy = Catch::Detail::unique_ptr<Catch::IStream>(new DummyStream());

    // Keep a raw pointer for identity check (no ownership).
    auto* expectedAddr = dummy.get();

    Catch::ReporterConfig rc(cfg, std::move(dummy), mode, options);

    // Act: take the stream from an rvalue ReporterConfig
    auto taken = std::move(rc).takeStream();

    // Assert: we received a non-null unique_ptr and it is the same instance
    ASSERT_NE(taken, nullptr);
    EXPECT_EQ(taken.get(), expectedAddr);

    // Note: We do not attempt to use rc after the move, and we do not assume anything
    // about rc's internal state post-move (black-box rule). taken will clean up.
}

// --- Boundary / exceptional path via interface: takeStream on null returns null ---
TEST_F(ReporterConfigTest_114, TakeStream_OnNullStream_ReturnsNullptr_114) {
    // Arrange
    const Catch::IConfig* cfg = nullptr;
    ColourMode mode = static_cast<ColourMode>(2);
    std::map<std::string, std::string> options;
    Catch::Detail::unique_ptr<Catch::IStream> nullStream{nullptr};

    Catch::ReporterConfig rc(cfg, std::move(nullStream), mode, options);

    // Act
    auto taken = std::move(rc).takeStream();

    // Assert
    EXPECT_EQ(taken, nullptr);
}
