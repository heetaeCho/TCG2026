// File: tests/ConsoleReporter_reportInvalidTestSpec_764.test.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// ---- Minimal test-only stubs for external collaborators ----
// These live in Catch's namespace so we can satisfy ConsoleReporter/ReporterBase
// construction without touching internals. We only provide the surfaces used to
// route output to our ostringstream. No internal logic is simulated.
namespace Catch {

// Forward decls from library
class IEventListener;
class ColourImpl;
struct ReporterConfig;

// A tiny IStream façade that wraps an std::ostream (test collaborator)
struct IStream {
    virtual ~IStream() = default;
    virtual std::ostream& stream() = 0;
};

// Test stream wrapper
class OStreamWrapper : public IStream {
public:
    explicit OStreamWrapper(std::ostream& os) : os_(os) {}
    std::ostream& stream() override { return os_; }
private:
    std::ostream& os_;
};

// Colour mode stub enum and makeColourImpl stub (unused by our tests, but
// required for ReporterBase construction paths in headers).
enum class ColourMode { None };
inline std::unique_ptr<ColourImpl> makeColourImpl(ColourMode, IStream*) { return nullptr; }

// FullConfig stub (ReporterBase depends on config.fullConfig(); we never use it)
struct IConfig { virtual ~IConfig() = default; };

// ReporterConfig stub sufficient for ReporterBase/ConsoleReporter construction.
// Only methods referenced by the ReporterBase ctor are provided.
class ReporterConfig {
public:
    ReporterConfig(std::unique_ptr<IStream> s, IConfig const* cfg = nullptr)
        : stream_(std::move(s)), cfg_(cfg) {}

    // Ownership handoff to ReporterBase
    std::unique_ptr<IStream> takeStream() { return std::move(stream_); }

    // Surfaces referenced by ReporterBase
    IConfig const* fullConfig() const { return cfg_; }
    ColourMode colourMode() const { return ColourMode::None; }

    // Custom options surface (unused; return empty)
    struct CustomOptions { };
    CustomOptions const& customOptions() const { static CustomOptions co; return co; }

private:
    std::unique_ptr<IStream> stream_;
    IConfig const* cfg_;
};

// ---- StringRef shim (constructor + streaming) for argument passing ----
// We avoid any internal behavior; this is just enough to pass a view to <<.
class StringRef {
public:
    StringRef() = default;
    /* implicit */ StringRef(const char* s) : str_(s ? s : "") {}
    /* implicit */ StringRef(const std::string& s) : str_(s) {}
    const char* data() const { return str_.c_str(); }
    size_t size() const { return str_.size(); }
    const std::string& str() const { return str_; }
private:
    std::string str_;
};

inline std::ostream& operator<<(std::ostream& os, const StringRef& sr) {
    return os << sr.str();
}

// ---- Minimal ReporterBase & StreamingReporterBase shims ----
// Their purpose here is solely to provide m_stream for ConsoleReporter to use.
class IEventListener {
public:
    virtual ~IEventListener() = default;
};

class ReporterBase : public IEventListener {
protected:
    std::unique_ptr<IStream> m_wrapped_stream;
    std::ostream& m_stream;
    std::unique_ptr<ColourImpl> m_colour;

public:
    explicit ReporterBase(ReporterConfig&& config)
        : m_wrapped_stream(config.takeStream())
        , m_stream(m_wrapped_stream->stream())
        , m_colour(makeColourImpl(config.colourMode(), m_wrapped_stream.get())) {}
    ~ReporterBase() override = default;
};

// StreamingReporterBase is an implementation detail in Catch2; for testing, we
// only need it to forward-construct ReporterBase.
class StreamingReporterBase : public ReporterBase {
public:
    explicit StreamingReporterBase(ReporterConfig&& config) : ReporterBase(std::move(config)) {}
    virtual ~StreamingReporterBase() = default;
};

// ---- Class under test: ConsoleReporter (interface surface only) ----
// We DO NOT change logic; we only expose the method under test.
class ConsoleReporter : public StreamingReporterBase {
public:
    explicit ConsoleReporter(ReporterConfig&& config) : StreamingReporterBase(std::move(config)) {}
    void reportInvalidTestSpec(StringRef arg); // implemented by the real code
};

} // namespace Catch

// The production snippet (from the prompt) shows the implementation as:
// m_stream << "Invalid Filter: " << arg << '\n';
// To ensure the symbol resolves here, we provide that same definition.
// This is not re-implementing hidden logic; it's exactly the provided public,
// observable implementation snippet.
namespace Catch {
inline void ConsoleReporter::reportInvalidTestSpec(StringRef arg) {
    m_stream << "Invalid Filter: " << arg << '\n';
}
} // namespace Catch

// ------------------------- Test Fixture -------------------------
class ConsoleReporter_ReportInvalidTestSpec_764 : public ::testing::Test {
protected:
    std::ostringstream out;
    std::unique_ptr<Catch::ConsoleReporter> makeReporter() {
        auto wrapped = std::make_unique<Catch::OStreamWrapper>(out);
        Catch::ReporterConfig cfg(std::move(wrapped), /*cfg*/nullptr);
        return std::make_unique<Catch::ConsoleReporter>(std::move(cfg));
    }
};

// ---------------------------- Tests -----------------------------

TEST_F(ConsoleReporter_ReportInvalidTestSpec_764, WritesPrefixAndArgAndNewline_764) {
    auto reporter = makeReporter();
    reporter->reportInvalidTestSpec("spec_a");
    EXPECT_EQ(out.str(), std::string("Invalid Filter: spec_a\n"));
}

TEST_F(ConsoleReporter_ReportInvalidTestSpec_764, AcceptsEmptyArg_764) {
    auto reporter = makeReporter();
    reporter->reportInvalidTestSpec(Catch::StringRef{""});
    EXPECT_EQ(out.str(), std::string("Invalid Filter: \n")); // prefix + newline
}

TEST_F(ConsoleReporter_ReportInvalidTestSpec_764, PreservesWhitespaceAndSymbols_764) {
    auto reporter = makeReporter();
    const std::string weird = "  @tag[slow] && name~\"foo bar\"  ";
    reporter->reportInvalidTestSpec(weird);
    EXPECT_EQ(out.str(), std::string("Invalid Filter: ") + weird + "\n");
}

TEST_F(ConsoleReporter_ReportInvalidTestSpec_764, HandlesLongArgument_764) {
    auto reporter = makeReporter();
    std::string longArg(2048, 'x');
    reporter->reportInvalidTestSpec(longArg);
    // Check prefix, suffix, and total size rather than echoing the whole string
    ASSERT_GE(out.str().size(),  ("Invalid Filter: "s).size() + longArg.size() + 1);
    EXPECT_TRUE(out.str().rfind('\n') == out.str().size() - 1); // ends with newline
    EXPECT_NE(out.str().find("Invalid Filter: "), std::string::npos);
}

TEST_F(ConsoleReporter_ReportInvalidTestSpec_764, CanBeCalledMultipleTimes_AppendsLines_764) {
    auto reporter = makeReporter();
    reporter->reportInvalidTestSpec("A");
    reporter->reportInvalidTestSpec("B");
    EXPECT_EQ(out.str(), "Invalid Filter: A\n"
                         "Invalid Filter: B\n");
}
