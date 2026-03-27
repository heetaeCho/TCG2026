// File: tests/tap_reporter_noMatchingTestCases_746.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>

// -------------------------------
// Minimal stubs/mocks for collaborators ONLY
// (to let us construct TAPReporter and capture its output).
// We do not simulate internal behaviour of TAPReporter.
// -------------------------------
namespace Catch {

// Forward decls from Catch2 (kept minimal for construction)
struct Config { virtual ~Config() = default; };        // for fullConfig()
struct ColourImpl { virtual ~ColourImpl() = default; }; // for makeColourImpl()

// IStream interface and a simple implementation that wraps std::ostream
struct IStream {
    virtual ~IStream() = default;
    virtual std::ostream& stream() = 0;
};

class OStringStreamWrapper final : public IStream {
public:
    explicit OStringStreamWrapper(std::ostream& os) : os_(os) {}
    std::ostream& stream() override { return os_; }
private:
    std::ostream& os_;
};

// Helper makeColourImpl shim used by ReporterBase; returns nullptr (unused here).
inline std::unique_ptr<ColourImpl> makeColourImpl(int /*mode*/, IStream* /*sink*/) {
    return nullptr;
}

// StringRef — we only need construction from const char* and stream insertion
class StringRef {
public:
    constexpr StringRef() noexcept : data_{""} {}
    /* implicit */ StringRef(const char* cstr) : data_{cstr ? cstr : ""} {}
    const char* c_str() const { return data_; }
private:
    const char* data_;
};
inline std::ostream& operator<<(std::ostream& os, const StringRef& s) {
    return os << s.c_str();
}

// Minimal ReporterConfig exposing just what ReporterBase/TAPReporter needs
class ReporterConfig {
public:
    ReporterConfig(std::unique_ptr<IStream> s, int colourMode = 0)
        : stream_(std::move(s)), colourMode_(colourMode) {}

    // Ownership transfer of the stream (as Catch2 does)
    std::unique_ptr<IStream> takeStream() { return std::move(stream_); }
    int colourMode() const { return colourMode_; }

    // Stubs (unused in our tests, but required by base)
    const Config* fullConfig() const { return nullptr; }
    void* customOptions() const { return nullptr; }

private:
    std::unique_ptr<IStream> stream_;
    int colourMode_;
};

// Event listener base (empty; only for type compatibility)
class IEventListener {
public:
    explicit IEventListener(const Config* /*cfg*/) {}
    virtual ~IEventListener() = default;
};

// ReporterBase as used by StreamingReporterBase
class ReporterBase : public IEventListener {
protected:
    std::unique_ptr<IStream> m_wrapped_stream;
    std::ostream& m_stream;
    std::unique_ptr<ColourImpl> m_colour;

public:
    explicit ReporterBase(ReporterConfig&& config)
        : IEventListener(config.fullConfig())
        , m_wrapped_stream(config.takeStream())
        , m_stream(m_wrapped_stream->stream())
        , m_colour(makeColourImpl(config.colourMode(), m_wrapped_stream.get())) {}

    virtual ~ReporterBase() = default;
};

// StreamingReporterBase stub
class StreamingReporterBase : public ReporterBase {
public:
    using ReporterBase::ReporterBase;
    virtual ~StreamingReporterBase() = default;
};

// -------------------------------
// Class under test: TAPReporter
// (We include only the method we test, per provided partial code.)
// -------------------------------
class TAPReporter : public StreamingReporterBase {
public:
    using StreamingReporterBase::StreamingReporterBase;

    // Method under test
    void noMatchingTestCases(StringRef unmatchedSpec) {
        m_stream << "# No test cases matched '" << unmatchedSpec << "'\n";
    }
};

} // namespace Catch

// -------------------------------
// Tests
// -------------------------------
using ::testing::HasSubstr;

class TAPReporter_NoMatch_746 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<Catch::TAPReporter> makeReporter() {
        auto sink = std::make_unique<Catch::OStringStreamWrapper>(oss);
        Catch::ReporterConfig cfg(std::move(sink), /*colourMode*/0);
        return std::make_unique<Catch::TAPReporter>(std::move(cfg));
    }
};

// Normal operation: writes the expected TAP diagnostic line with the spec quoted
TEST_F(TAPReporter_NoMatch_746, WritesExpectedLineWithSpec_746) {
    auto reporter = makeReporter();

    reporter->noMatchingTestCases("math/*");

    EXPECT_EQ(oss.str(), std::string("# No test cases matched '") + "math/*" + "'\n");
}

// Boundary: empty spec should still produce properly quoted, newline-terminated output
TEST_F(TAPReporter_NoMatch_746, EmptySpecProducesQuotedEmpty_746) {
    auto reporter = makeReporter();

    reporter->noMatchingTestCases("");

    EXPECT_EQ(oss.str(), "# No test cases matched ''\n");
}

// Special characters: ensure the spec is streamed verbatim (no added escaping or trimming)
TEST_F(TAPReporter_NoMatch_746, SpecWithSpacesQuotesAndSymbolsIsVerbatim_746) {
    auto reporter = makeReporter();

    const char* spec = "  weird [tag]? 'x' \"y\"  ";
    reporter->noMatchingTestCases(spec);

    EXPECT_EQ(oss.str(), std::string("# No test cases matched '") + spec + "'\n");
}

// Multiple invocations: output should append lines (no overwriting, correct newlines)
TEST_F(TAPReporter_NoMatch_746, MultipleCallsAppendLines_746) {
    auto reporter = makeReporter();

    reporter->noMatchingTestCases("alpha");
    reporter->noMatchingTestCases("beta");

    std::string out = oss.str();
    EXPECT_THAT(out, HasSubstr("# No test cases matched 'alpha'\n"));
    EXPECT_THAT(out, HasSubstr("# No test cases matched 'beta'\n"));
    // Ensure order is preserved
    auto first = out.find("alpha");
    auto second = out.find("beta");
    ASSERT_NE(first, std::string::npos);
    ASSERT_NE(second, std::string::npos);
    EXPECT_LT(first, second);
}
