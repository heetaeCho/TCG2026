#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"

#include <map>
#include <string>
#include <sstream>

namespace {

// A concrete mock/stub for IStream since it's likely abstract
class StubStream : public Catch::IStream {
public:
    std::ostream& stream() override {
        return m_oss;
    }
private:
    std::ostringstream m_oss;
};

// A concrete mock/stub for IConfig since it's likely abstract
class StubConfig : public Catch::IConfig {
public:
    // Implement pure virtual methods as needed - providing minimal stubs
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return "stub"; }
    int abortAfter() const override { return 1; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
};

} // anonymous namespace

class ReporterConfigTest_111 : public ::testing::Test {
protected:
    StubConfig stubConfig;
};

TEST_F(ReporterConfigTest_111, Construction_WithValidParameters_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    std::map<std::string, std::string> options;
    options["key1"] = "value1";

    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        options
    );

    EXPECT_EQ(config.fullConfig(), &stubConfig);
    EXPECT_EQ(config.colourMode(), Catch::ColourMode::PlatformDefault);
    EXPECT_EQ(config.customOptions().size(), 1u);
    EXPECT_EQ(config.customOptions().at("key1"), "value1");
}

TEST_F(ReporterConfigTest_111, FullConfig_ReturnsConfigPointer_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_EQ(config.fullConfig(), &stubConfig);
}

TEST_F(ReporterConfigTest_111, ColourMode_ReturnsCorrectMode_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::ANSI,
        {}
    );

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::ANSI);
}

TEST_F(ReporterConfigTest_111, CustomOptions_ReturnsEmptyMapWhenNoneProvided_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_TRUE(config.customOptions().empty());
}

TEST_F(ReporterConfigTest_111, CustomOptions_ReturnsMultipleOptions_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    std::map<std::string, std::string> options;
    options["opt1"] = "val1";
    options["opt2"] = "val2";
    options["opt3"] = "val3";

    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        options
    );

    EXPECT_EQ(config.customOptions().size(), 3u);
    EXPECT_EQ(config.customOptions().at("opt1"), "val1");
    EXPECT_EQ(config.customOptions().at("opt2"), "val2");
    EXPECT_EQ(config.customOptions().at("opt3"), "val3");
}

TEST_F(ReporterConfigTest_111, TakeStream_ReturnsValidStream_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    auto* rawPtr = stream.get();

    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    auto takenStream = std::move(config).takeStream();
    EXPECT_TRUE(static_cast<bool>(takenStream));
    EXPECT_EQ(takenStream.get(), rawPtr);
}

TEST_F(ReporterConfigTest_111, MoveConstruction_TransfersOwnership_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    auto* rawStreamPtr = stream.get();

    Catch::ReporterConfig config1(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::ANSI,
        {{"key", "value"}}
    );

    Catch::ReporterConfig config2(std::move(config1));

    EXPECT_EQ(config2.fullConfig(), &stubConfig);
    EXPECT_EQ(config2.colourMode(), Catch::ColourMode::ANSI);
    EXPECT_EQ(config2.customOptions().at("key"), "value");

    auto takenStream = std::move(config2).takeStream();
    EXPECT_EQ(takenStream.get(), rawStreamPtr);
}

TEST_F(ReporterConfigTest_111, MoveAssignment_TransfersOwnership_111) {
    auto stream1 = Catch::Detail::make_unique<StubStream>();
    auto stream2 = Catch::Detail::make_unique<StubStream>();
    auto* rawPtr2 = stream2.get();

    Catch::ReporterConfig config1(
        &stubConfig,
        std::move(stream1),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    Catch::ReporterConfig config2(
        &stubConfig,
        std::move(stream2),
        Catch::ColourMode::ANSI,
        {{"moved", "yes"}}
    );

    config1 = std::move(config2);

    EXPECT_EQ(config1.colourMode(), Catch::ColourMode::ANSI);
    EXPECT_EQ(config1.customOptions().at("moved"), "yes");

    auto takenStream = std::move(config1).takeStream();
    EXPECT_EQ(takenStream.get(), rawPtr2);
}

TEST_F(ReporterConfigTest_111, FullConfig_WithNullConfig_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    Catch::ReporterConfig config(
        nullptr,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        {}
    );

    EXPECT_EQ(config.fullConfig(), nullptr);
}

TEST_F(ReporterConfigTest_111, ColourMode_None_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::None,
        {}
    );

    EXPECT_EQ(config.colourMode(), Catch::ColourMode::None);
}

TEST_F(ReporterConfigTest_111, Destruction_DoesNotCrash_111) {
    {
        auto stream = Catch::Detail::make_unique<StubStream>();
        Catch::ReporterConfig config(
            &stubConfig,
            std::move(stream),
            Catch::ColourMode::PlatformDefault,
            {}
        );
        // config goes out of scope - should not crash
    }
    SUCCEED();
}

TEST_F(ReporterConfigTest_111, CustomOptions_WithEmptyStringValues_111) {
    auto stream = Catch::Detail::make_unique<StubStream>();
    std::map<std::string, std::string> options;
    options[""] = "";
    options["key"] = "";

    Catch::ReporterConfig config(
        &stubConfig,
        std::move(stream),
        Catch::ColourMode::PlatformDefault,
        options
    );

    EXPECT_EQ(config.customOptions().size(), 2u);
    EXPECT_EQ(config.customOptions().at(""), "");
    EXPECT_EQ(config.customOptions().at("key"), "");
}
