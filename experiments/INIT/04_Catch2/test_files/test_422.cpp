// File: tests/reporter_spec_custom_options_422_tests.cpp

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <type_traits>

// Include the provided interface header
#include "Catch2/src/catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

class ReporterSpecTest_422 : public ::testing::Test {
protected:
    // Helpers to create disengaged optionals if the Optional type supports default construction.
    Optional<std::string> noneStr_{};
    Optional<ColourMode> noneColour_{};
};

TEST_F(ReporterSpecTest_422, CustomOptions_EmptyMapReturnsEmpty_422) {
    std::map<std::string, std::string> empty;
    ReporterSpec spec{"console", noneStr_, noneColour_, empty};

    const auto& opts = spec.customOptions();
    EXPECT_TRUE(opts.empty());
    EXPECT_EQ(opts.size(), 0u);
}

TEST_F(ReporterSpecTest_422, CustomOptions_PreservesKeyValuePairs_422) {
    std::map<std::string, std::string> input{
        {"key", "value"},
        {"another", "123"},
        {"with-space", "hello world"},
        {"", "empty-key"},
        {"unicode", u8"값"}
    };
    ReporterSpec spec{"xml", noneStr_, noneColour_, input};

    const auto& opts = spec.customOptions();
    ASSERT_EQ(opts.size(), input.size());

    // Verify values by key lookup (observable behavior only)
    for (const auto& kv : input) {
        auto it = opts.find(kv.first);
        ASSERT_NE(it, opts.end()) << "Missing key: '" << kv.first << "'";
        EXPECT_EQ(it->second, kv.second) << "Mismatched value for key: '" << kv.first << "'";
    }
}

TEST_F(ReporterSpecTest_422, CustomOptions_ReturnTypeIsConstRef_422) {
    std::map<std::string, std::string> input{{"a", "b"}};
    ReporterSpec spec{"junit", noneStr_, noneColour_, input};

    // Check the exact return type at compile time without relying on implementation details
    using ReturnT = decltype(spec.customOptions());
    static_assert(std::is_reference<ReturnT>::value, "customOptions() should return a reference");
    static_assert(std::is_const<typename std::remove_reference<ReturnT>::type>::value,
                  "customOptions() should return a const reference");
    (void)spec; // silence unused warning in case static_asserts compile away
}

TEST_F(ReporterSpecTest_422, CustomOptions_ConsistencyAcrossCalls_422) {
    std::map<std::string, std::string> input{{"one", "1"}, {"two", "2"}};
    ReporterSpec spec{"compact", noneStr_, noneColour_, input};

    // Multiple calls should consistently reflect the same observable data
    const auto& first = spec.customOptions();
    const auto& second = spec.customOptions();

    ASSERT_EQ(first.size(), second.size());
    for (const auto& kv : first) {
        auto it = second.find(kv.first);
        ASSERT_NE(it, second.end());
        EXPECT_EQ(it->second, kv.second);
    }
}

TEST_F(ReporterSpecTest_422, CustomOptions_SupportsLargeNumberOfEntries_422) {
    std::map<std::string, std::string> many;
    for (int i = 0; i < 200; ++i) {
        many.emplace("k" + std::to_string(i), "v" + std::to_string(i));
    }
    ReporterSpec spec{"console", noneStr_, noneColour_, many};

    const auto& opts = spec.customOptions();
    EXPECT_EQ(opts.size(), many.size());
    // Spot-check a few boundary-like entries
    EXPECT_EQ(opts.at("k0"), "v0");
    EXPECT_EQ(opts.at("k199"), "v199");
}
