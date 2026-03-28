// File: tests/json_reporter_benchmark_preparing_872.cpp

#include <gtest/gtest.h>

// We only rely on the public interface (function signature).
// Include the real Catch2 headers if they are available in your build.
// If your environment compiles from the provided partials, the .cpp below
// defines a minimal JsonReporter with benchmarkPreparing(StringRef).
#include "Catch2/src/catch2/internal/catch_stringref.hpp"
#include "Catch2/src/catch2/reporters/catch_reporter_json.cpp"

namespace {

using Catch::JsonReporter;
using Catch::StringRef;

// A very light fixture; no internal state is accessed.
class JsonReporter_BenchmarkPreparing_872 : public ::testing::Test {
protected:
    // The partial implementation exposes a default-constructible class.
    // We avoid depending on any unspecified constructor behavior.
    JsonReporter reporter_;
};

TEST_F(JsonReporter_BenchmarkPreparing_872, AcceptsEmptyName_872) {
    // Arrange
    StringRef empty; // default-constructed

    // Act / Assert: call should be well-formed and not throw/crash
    EXPECT_NO_THROW(reporter_.benchmarkPreparing(empty));
}

TEST_F(JsonReporter_BenchmarkPreparing_872, AcceptsTypicalName_872) {
    // Arrange
    const char* name = "matrix_multiply_bench";
    StringRef ref{name, static_cast<StringRef::size_type>(std::strlen(name))};

    // Act / Assert
    EXPECT_NO_THROW(reporter_.benchmarkPreparing(ref));
}

TEST_F(JsonReporter_BenchmarkPreparing_872, AcceptsLongName_872) {
    // Arrange: long input (boundary-ish) — does not assume any internal limit
    std::string longName(4096, 'A'); // 4KB of 'A'
    StringRef ref{longName.c_str(), static_cast<StringRef::size_type>(longName.size())};

    // Act / Assert
    EXPECT_NO_THROW(reporter_.benchmarkPreparing(ref));
}

TEST_F(JsonReporter_BenchmarkPreparing_872, AcceptsUnicodeLikeContent_872) {
    // Arrange: non-ASCII content; StringRef treats it as raw bytes
    const char* utf8 = "🔥 벤치마크 준비 🔧";
    StringRef ref{utf8, static_cast<StringRef::size_type>(std::strlen(utf8))};

    // Act / Assert
    EXPECT_NO_THROW(reporter_.benchmarkPreparing(ref));
}

TEST_F(JsonReporter_BenchmarkPreparing_872, MultipleSequentialCallsAreSafe_872) {
    // Arrange
    const char* names[] = {"A", "B", "C", "D", "E"};
    for (auto* n : names) {
        StringRef ref{n, static_cast<StringRef::size_type>(std::strlen(n))};
        // Act / Assert each call independently
        EXPECT_NO_THROW(reporter_.benchmarkPreparing(ref));
    }
}

} // namespace
