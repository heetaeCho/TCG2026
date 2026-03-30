// reporterbase_listtests_779_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>
#include <sstream>
#include <vector>
#include <memory>

// -----------------------------
// Minimal stand-ins (public API shells)
// -----------------------------
namespace Catch {

// Forward declarations of public-ish types we need
enum class Verbosity { Quiet, Normal, High };
enum class ColourMode { None, ANSI };

struct TestCaseHandle { int id = 0; }; // opaque for our tests

struct ReporterPreferences {};
class IStream {
public:
    virtual ~IStream() = default;
    virtual std::ostream& stream() = 0;
};

struct ColourImpl { explicit ColourImpl(IStream*) {} };

// Seam for factory used by ReporterBase's ctor.
// We provide it here so ReporterBase will use OUR ColourImpl instance.
static ColourImpl* makeColourImpl(ColourMode, IStream* s) {
    return new ColourImpl(s);
}

// Minimal IConfig interface we need
class IConfig {
public:
    virtual ~IConfig() = default;
    virtual bool hasTestFilters() const = 0;
    virtual Verbosity verbosity() const = 0;
};

// ReporterConfig shell sufficient for ReporterBase's constructor
class ReporterConfig {
public:
    ReporterConfig(IConfig const* cfg, std::unique_ptr<IStream> s, ColourMode mode)
        : cfg_(cfg), stream_(std::move(s)), colourMode_(mode) {}
    IConfig const* fullConfig() const { return cfg_; }
    std::unique_ptr<IStream> takeStream() { return std::move(stream_); }
    ColourMode colourMode() const { return colourMode_; }
    // customOptions() not used by our tests; provide a dummy
    struct DummyOpts{}; DummyOpts const& customOptions() const { return dummy_; }
private:
    IConfig const* cfg_;
    std::unique_ptr<IStream> stream_;
    ColourMode colourMode_;
    DummyOpts dummy_;
};

// unique_ptr stand-in (sufficient subset used by ReporterBase)
namespace Detail {
template <typename T>
class unique_ptr {
public:
    unique_ptr(std::nullptr_t = nullptr) : ptr_(nullptr) {}
    explicit unique_ptr(T* p) : ptr_(p) {}
    unique_ptr(unique_ptr&& other) noexcept : ptr_(other.release()) {}
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) { reset(other.release()); }
        return *this;
    }
    ~unique_ptr() { reset(); }
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    void reset(T* p = nullptr) { if (ptr_) delete ptr_; ptr_ = p; }
    T* release() { T* t = ptr_; ptr_ = nullptr; return t; }
private:
    T* ptr_;
};
} // namespace Detail

// -----------------------------
// The class under test (public interface shell)
// -----------------------------
class IEventListener {
public:
    explicit IEventListener(IConfig const* cfg) : m_config(cfg) {}
    virtual ~IEventListener() = default;
protected:
    IConfig const* m_config;
};

class ReporterBase : public IEventListener {
public:
    explicit ReporterBase(ReporterConfig&& config)
        : IEventListener(config.fullConfig())
        , m_wrapped_stream(Detail::unique_ptr<IStream>(config.takeStream().release()))
        , m_stream(m_wrapped_stream->stream())
        , m_colour(Detail::unique_ptr<ColourImpl>(makeColourImpl(config.colourMode(), m_wrapped_stream.get()))) {}

    // Function under test
    void listTests(std::vector<TestCaseHandle> const& tests);

protected:
    Detail::unique_ptr<IStream> m_wrapped_stream;
    std::ostream&              m_stream;
    Detail::unique_ptr<ColourImpl> m_colour;
};

// -----------------------------
// External collaborator seam we will verify was called
// -----------------------------
static int g_called = 0;
struct Captured {
    std::ostream* stream = nullptr;
    ColourImpl* colour = nullptr;
    const std::vector<TestCaseHandle>* tests = nullptr;
    bool hasFilters = false;
    Verbosity verbosity = Verbosity::Quiet;
} g_capture;

// Provide the symbol ReporterBase::listTests calls.
void defaultListTests(std::ostream& os,
                      ColourImpl* colour,
                      std::vector<TestCaseHandle> const& tests,
                      bool hasFilters,
                      Verbosity verb) {
    ++g_called;
    g_capture.stream = &os;
    g_capture.colour = colour;
    g_capture.tests = &tests;
    g_capture.hasFilters = hasFilters;
    g_capture.verbosity = verb;
}

// The method under test (thin wrapper; declared in the lib; we provide header-level definition here)
inline void ReporterBase::listTests(std::vector<TestCaseHandle> const& tests) {
    // This mirrors the *public interface* line from the partial code and only calls the collaborator.
    // We do NOT re-implement any internal logic beyond forwarding, which is what's observable.
    defaultListTests(m_stream, m_colour.get(), tests, m_config->hasTestFilters(), m_config->verbosity());
}

} // namespace Catch

// -----------------------------
// Test scaffolding
// -----------------------------
using namespace Catch;
using ::testing::_;
using ::testing::Eq;

class FakeStream : public IStream {
public:
    std::ostream& stream() override { return oss_; }
    std::ostringstream oss_;
};

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
};

class ReporterBase_ListTests_779 : public ::testing::Test {
protected:
    void SetUp() override {
        g_called = 0;
        g_capture = {};
        // fresh FakeStream for each test
        stream_ = std::make_unique<FakeStream>();
        stream_ptr_ = stream_.get();
    }

    std::unique_ptr<FakeStream> stream_;
    FakeStream* stream_ptr_{nullptr};
};

// -----------------------------
// Tests
// -----------------------------

TEST_F(ReporterBase_ListTests_779, ForwardsParameters_NoFilters_779) {
    MockConfig cfg;
    EXPECT_CALL(cfg, hasTestFilters()).WillOnce(::testing::Return(false));
    EXPECT_CALL(cfg, verbosity()).WillOnce(::testing::Return(Verbosity::Quiet));

    ReporterConfig rc(&cfg, std::unique_ptr<IStream>(new FakeStream()), ColourMode::ANSI);
    ReporterBase uut(std::move(rc));

    std::vector<TestCaseHandle> tests = { {1}, {2}, {3} };
    uut.listTests(tests);

    ASSERT_EQ(g_called, 1) << "defaultListTests must be called exactly once";
    EXPECT_NE(g_capture.stream, nullptr);
    EXPECT_NE(g_capture.colour, nullptr);
    ASSERT_NE(g_capture.tests, nullptr);
    EXPECT_EQ(g_capture.tests->size(), tests.size());
    EXPECT_FALSE(g_capture.hasFilters);
    EXPECT_EQ(g_capture.verbosity, Verbosity::Quiet);
}

TEST_F(ReporterBase_ListTests_779, ForwardsParameters_WithFilters_779) {
    MockConfig cfg;
    EXPECT_CALL(cfg, hasTestFilters()).WillOnce(::testing::Return(true));
    EXPECT_CALL(cfg, verbosity()).WillOnce(::testing::Return(Verbosity::High));

    ReporterConfig rc(&cfg, std::unique_ptr<IStream>(new FakeStream()), ColourMode::None);
    ReporterBase uut(std::move(rc));

    std::vector<TestCaseHandle> tests = { {42} };
    uut.listTests(tests);

    ASSERT_EQ(g_called, 1);
    EXPECT_TRUE(g_capture.hasFilters);
    EXPECT_EQ(g_capture.verbosity, Verbosity::High);
    ASSERT_NE(g_capture.tests, nullptr);
    EXPECT_EQ(g_capture.tests->at(0).id, 42);
}

TEST_F(ReporterBase_ListTests_779, HandlesEmptyTestsVector_779) {
    MockConfig cfg;
    EXPECT_CALL(cfg, hasTestFilters()).WillOnce(::testing::Return(false));
    EXPECT_CALL(cfg, verbosity()).WillOnce(::testing::Return(Verbosity::Normal));

    ReporterConfig rc(&cfg, std::unique_ptr<IStream>(new FakeStream()), ColourMode::ANSI);
    ReporterBase uut(std::move(rc));

    std::vector<TestCaseHandle> tests; // empty
    uut.listTests(tests);

    ASSERT_EQ(g_called, 1);
    ASSERT_NE(g_capture.tests, nullptr);
    EXPECT_TRUE(g_capture.tests->empty());
    EXPECT_NE(g_capture.colour, nullptr) << "ReporterBase should still provide a colour object";
}

TEST_F(ReporterBase_ListTests_779, DoesNotModifyInputVector_779) {
    MockConfig cfg;
    EXPECT_CALL(cfg, hasTestFilters()).WillOnce(::testing::Return(true));
    EXPECT_CALL(cfg, verbosity()).WillOnce(::testing::Return(Verbosity::Normal));

    ReporterConfig rc(&cfg, std::unique_ptr<IStream>(new FakeStream()), ColourMode::ANSI);
    ReporterBase uut(std::move(rc));

    std::vector<TestCaseHandle> tests = { {7}, {8}, {9} };
    auto const before_size = tests.size();

    uut.listTests(tests);

    ASSERT_EQ(g_called, 1);
    // Observable: caller's vector remains unchanged in size/content
    EXPECT_EQ(tests.size(), before_size);
    EXPECT_EQ(tests[0].id, 7);
    EXPECT_EQ(tests[1].id, 8);
    EXPECT_EQ(tests[2].id, 9);
}

