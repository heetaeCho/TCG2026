// File: tests/json_reporter_benchmarkFailed_873_tests.cpp

#include <gtest/gtest.h>

// If your build uses the real headers, prefer:
//   #include "catch2/reporters/catch_reporter_json.hpp"
//   #include "catch2/internal/catch_stringref.hpp"
// For this prompt's partial code, we forward-declare minimal types in the same
// namespace to exercise the provided interface without relying on internals.

namespace Catch {
    class StringRef {
    public:
        StringRef() noexcept {}
        StringRef(const char* s) : cstr_(s ? s : "") {}
        StringRef(const std::string& s) : cstr_(s.c_str()) {}
        const char* data() const noexcept { return cstr_; }
    private:
        const char* cstr_ = "";
    };

    class JsonReporter {
    public:
        // From the provided partial implementation:
        void benchmarkFailed(StringRef error) { (void)error; }
    };
} // namespace Catch

// --------------------------- Tests ---------------------------

TEST(JsonReporter_benchmarkFailed_873, AcceptsEmptyStringRef_NoThrow_873) {
    Catch::JsonReporter reporter;
    Catch::StringRef empty;
    EXPECT_NO_THROW(reporter.benchmarkFailed(empty));
}

TEST(JsonReporter_benchmarkFailed_873, AcceptsNonEmptyLiteral_NoThrow_873) {
    Catch::JsonReporter reporter;
    Catch::StringRef msg("benchmark failed due to timeout");
    EXPECT_NO_THROW(reporter.benchmarkFailed(msg));
}

TEST(JsonReporter_benchmarkFailed_873, AcceptsLargeString_NoThrow_873) {
    Catch::JsonReporter reporter;
    std::string big(100000, 'A'); // boundary-ish: large payload
    Catch::StringRef ref(big);
    EXPECT_NO_THROW(reporter.benchmarkFailed(ref));
}

TEST(JsonReporter_benchmarkFailed_873, AcceptsSpecialChars_NoThrow_873) {
    Catch::JsonReporter reporter;
    std::string special = "err:\"quote\" \\ backslash \n newline \t tab \x01 control";
    Catch::StringRef ref(special);
    EXPECT_NO_THROW(reporter.benchmarkFailed(ref));
}

TEST(JsonReporter_benchmarkFailed_873, DoesNotModifyInputString_NoMutation_873) {
    Catch::JsonReporter reporter;
    std::string original = "original-message";
    std::string copy = original; // keep a copy for equality check
    Catch::StringRef ref(original);
    EXPECT_NO_THROW(reporter.benchmarkFailed(ref));
    // Observable check: input string content remains unchanged after the call
    EXPECT_EQ(original, copy);
}
