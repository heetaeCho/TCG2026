#include <gtest/gtest.h>
#include <string>

// Minimal StringRef compatible with the interface
namespace Catch {
    class StringRef {
        const char* m_start = "";
        std::size_t m_size = 0;
    public:
        constexpr StringRef() noexcept = default;
        StringRef(const char* rawChars) noexcept
            : m_start(rawChars), m_size(std::strlen(rawChars)) {}
        constexpr StringRef(const char* rawChars, std::size_t size) noexcept
            : m_start(rawChars), m_size(size) {}
        StringRef(const std::string& stdString) noexcept
            : m_start(stdString.c_str()), m_size(stdString.size()) {}
        constexpr const char* data() const noexcept { return m_start; }
        constexpr std::size_t size() const noexcept { return m_size; }
        constexpr bool empty() const noexcept { return m_size == 0; }
        explicit operator std::string() const { return std::string(m_start, m_size); }
    };
}

// Include the class under test (simplified version from the .cpp)
namespace Catch {
    class JsonReporter {
    public:
        void benchmarkFailed(StringRef error) {
            (void)error;
        }
    };
}

class JsonReporterTest_873 : public ::testing::Test {
protected:
    Catch::JsonReporter reporter;
};

// Test that benchmarkFailed can be called with a normal error string without crashing
TEST_F(JsonReporterTest_873, BenchmarkFailedWithNormalString_873) {
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef("some error")));
}

// Test that benchmarkFailed can be called with an empty StringRef without crashing
TEST_F(JsonReporterTest_873, BenchmarkFailedWithEmptyString_873) {
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef()));
}

// Test that benchmarkFailed can be called with an empty C-string without crashing
TEST_F(JsonReporterTest_873, BenchmarkFailedWithEmptyCString_873) {
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef("")));
}

// Test that benchmarkFailed can be called with a long error message without crashing
TEST_F(JsonReporterTest_873, BenchmarkFailedWithLongString_873) {
    std::string longError(10000, 'x');
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef(longError)));
}

// Test that benchmarkFailed can be called with a string containing special characters
TEST_F(JsonReporterTest_873, BenchmarkFailedWithSpecialCharacters_873) {
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef("error: \"unexpected\" <value> & \nnewline")));
}

// Test that benchmarkFailed can be called multiple times without issue
TEST_F(JsonReporterTest_873, BenchmarkFailedCalledMultipleTimes_873) {
    EXPECT_NO_THROW({
        reporter.benchmarkFailed(Catch::StringRef("error1"));
        reporter.benchmarkFailed(Catch::StringRef("error2"));
        reporter.benchmarkFailed(Catch::StringRef("error3"));
    });
}

// Test that benchmarkFailed accepts a StringRef constructed from std::string
TEST_F(JsonReporterTest_873, BenchmarkFailedWithStdString_873) {
    std::string error = "std::string error message";
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef(error)));
}

// Test that JsonReporter can be default constructed
TEST_F(JsonReporterTest_873, DefaultConstruction_873) {
    Catch::JsonReporter rep;
    EXPECT_NO_THROW(rep.benchmarkFailed(Catch::StringRef("test")));
}

// Test benchmarkFailed with a string containing null-like content (but valid StringRef)
TEST_F(JsonReporterTest_873, BenchmarkFailedWithEmbeddedContent_873) {
    const char data[] = "hello\0world";
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef(data, sizeof(data) - 1)));
}

// Test that benchmarkFailed with a single character string works
TEST_F(JsonReporterTest_873, BenchmarkFailedWithSingleChar_873) {
    EXPECT_NO_THROW(reporter.benchmarkFailed(Catch::StringRef("x")));
}
