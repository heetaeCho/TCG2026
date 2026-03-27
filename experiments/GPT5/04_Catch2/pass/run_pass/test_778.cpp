#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <ostream>
#include <sstream>

// --------------------------------------------------------------------------------------
// Test-side compatibility layer
// If you compile inside your project, define CATCH2_IN_PROJECT (e.g. via build system)
// and include the real Catch2 headers instead of these small stubs.
// --------------------------------------------------------------------------------------
#if defined(CATCH2_IN_PROJECT)
  #include "catch2/reporters/catch_reporter_common_base.hpp"
  // ^ Adjust include path as in your repo.
#else
// --------------------------- Minimal, build-only stubs (TEST-ONLY) --------------------
// These exist solely so the test TU compiles in isolation. They do NOT re-implement
// ReporterBase internals; they just provide enough types to call the real member we test
// when compiled against your project (when CATCH2_IN_PROJECT is defined, these stubs
// are disabled and your real headers are used).

namespace Catch {

struct ListenerDescription {
    // opaque for test; we do not inspect fields
    std::string name;
};

struct IStream {
    virtual ~IStream() = default;
    virtual std::ostream& stream() = 0;
};

struct ColourImpl { virtual ~ColourImpl() = default; };
enum class ColourMode { None };

struct IConfig { virtual ~IConfig() = default; };

namespace Detail {
    template <typename T>
    using unique_ptr = std::unique_ptr<T>;
}

struct ReporterConfig {
    ReporterConfig(IConfig const* cfg,
                   Detail::unique_ptr<IStream> strm,
                   ColourMode mode = ColourMode::None)
        : m_cfg(cfg), m_stream(std::move(strm)), m_mode(mode) {}

    IConfig const* fullConfig() const { return m_cfg; }
    Detail::unique_ptr<IStream> takeStream() { return std::move(m_stream); }
    ColourMode colourMode() const { return m_mode; }
    // Minimal shim:
    struct CustomOptions { };
    CustomOptions const& customOptions() const { static CustomOptions opts; return opts; }

    IConfig const* m_cfg;
    Detail::unique_ptr<IStream> m_stream;
    ColourMode m_mode;
};

struct IEventListener {
    explicit IEventListener(IConfig const*) {}
    virtual ~IEventListener() = default;
    // virtuals not needed for this test
};

// Factory expected by ReporterBase ctor
inline Detail::unique_ptr<ColourImpl> makeColourImpl(ColourMode, IStream*) {
    return Detail::unique_ptr<ColourImpl>(new ColourImpl());
}

class ReporterBase : public IEventListener {
protected:
    Detail::unique_ptr<IStream> m_wrapped_stream;
protected:
    std::ostream& m_stream;
protected:
    Detail::unique_ptr<ColourImpl> m_colour;
    ReporterConfig::CustomOptions m_customOptions;

public:
    explicit ReporterBase(ReporterConfig&& config)
        : IEventListener(config.fullConfig())
        , m_wrapped_stream(std::move(config).takeStream())
        , m_stream(m_wrapped_stream->stream())
        , m_colour(makeColourImpl(config.colourMode(), m_wrapped_stream.get()))
        , m_customOptions(config.customOptions()) {}

    virtual ~ReporterBase() = default;

    // The function under test is defined in the real .cpp; to keep this TU linkable
    // in the standalone mode, we provide the same signature here and inline it
    // so that our test uses the exact delegation we’re validating.
    // NOTE: When building inside the real project, remove this inline and let the
    //       real compiled translation unit provide it.
    void listListeners(std::vector<ListenerDescription> const& descriptions);
};

// Declaration of the external collaborator we will intercept:
void defaultListListeners(std::ostream& os,
                          std::vector<ListenerDescription> const& descriptions);

// The implementation of the method under test (mirrors the snippet provided):
inline void ReporterBase::listListeners(
    std::vector<ListenerDescription> const& descriptions) {
    defaultListListeners(m_stream, descriptions);
}

} // namespace Catch

#endif // !CATCH2_IN_PROJECT

// --------------------------------------------------------------------------------------
// Spy for the external collaborator: Catch::defaultListListeners
// We record invocation count and verify the exact objects passed in.
// --------------------------------------------------------------------------------------
namespace Catch {
struct ListListenersSpy {
    int calls = 0;
    std::ostream* last_os = nullptr;
    const void* last_desc_ptr = nullptr; // capture the address of the vector object
    size_t last_desc_size = 0;

    void reset() { calls = 0; last_os = nullptr; last_desc_ptr = nullptr; last_desc_size = 0; }
};
static ListListenersSpy g_listeners_spy;

// Test-side replacement (link seam)
void defaultListListeners(std::ostream& os,
                          std::vector<ListenerDescription> const& descriptions) {
    g_listeners_spy.calls++;
    g_listeners_spy.last_os = &os;
    g_listeners_spy.last_desc_ptr = static_cast<const void*>(&descriptions);
    g_listeners_spy.last_desc_size = descriptions.size();
}
} // namespace Catch

// --------------------------------------------------------------------------------------
// Tiny concrete IStream for tests: wraps a std::ostringstream
// --------------------------------------------------------------------------------------
namespace Catch {
class OStringIStream : public IStream {
public:
    explicit OStringIStream(std::ostringstream& oss) : m_oss(oss) {}
    std::ostream& stream() override { return m_oss; }
private:
    std::ostringstream& m_oss;
};
} // namespace Catch

// --------------------------------------------------------------------------------------
// Helper subclass to surface ReporterBase's ctor publicly (no behavior changes).
// --------------------------------------------------------------------------------------
namespace Catch {
class TestReporter : public ReporterBase {
public:
    explicit TestReporter(ReporterConfig&& cfg) : ReporterBase(std::move(cfg)) {}
    using ReporterBase::listListeners; // expose for test
};
} // namespace Catch

// ======================================================================================
//                                          TESTS
// ======================================================================================

using ::testing::Eq;
using ::testing::Ne;

class ReporterBase_ListListeners_778 : public ::testing::Test {
protected:
    void SetUp() override { Catch::g_listeners_spy.reset(); }
};

// Normal operation: forwards to defaultListListeners with the reporter's stream and the
// exact same descriptions object.
TEST_F(ReporterBase_ListListeners_778, ForwardsToDefaultWithSameArgs_778) {
    using namespace Catch;

    // Arrange: build a reporter with a known stream
    std::ostringstream oss;
    OStringIStream* wrapped = new OStringIStream(oss);
    ReporterConfig cfg{ /*IConfig*/ nullptr,
                        Detail::unique_ptr<IStream>(wrapped),
                        ColourMode::None };

    TestReporter reporter(std::move(cfg));

    std::vector<ListenerDescription> descs{
        ListenerDescription{"A"}, ListenerDescription{"B"}
    };

    // Act
    reporter.listListeners(descs);

    // Assert: collaborator was called exactly once, with the same stream and vector
    EXPECT_THAT(g_listeners_spy.calls, Eq(1));
    EXPECT_THAT(g_listeners_spy.last_os, Eq(&static_cast<std::ostream&>(oss)));
    EXPECT_THAT(g_listeners_spy.last_desc_ptr, Eq(static_cast<const void*>(&descs)));
    EXPECT_THAT(g_listeners_spy.last_desc_size, Eq(descs.size()));
}

// Boundary: empty descriptions vector is still forwarded exactly once and unmodified.
TEST_F(ReporterBase_ListListeners_778, ForwardsWhenEmpty_778) {
    using namespace Catch;

    std::ostringstream oss;
    OStringIStream* wrapped = new OStringIStream(oss);
    ReporterConfig cfg{ nullptr, Detail::unique_ptr<IStream>(wrapped), ColourMode::None };
    TestReporter reporter(std::move(cfg));

    std::vector<ListenerDescription> descs; // empty

    reporter.listListeners(descs);

    EXPECT_THAT(g_listeners_spy.calls, Eq(1));
    EXPECT_THAT(g_listeners_spy.last_os, Eq(&static_cast<std::ostream&>(oss)));
    EXPECT_THAT(g_listeners_spy.last_desc_ptr, Eq(static_cast<const void*>(&descs)));
    EXPECT_THAT(g_listeners_spy.last_desc_size, Eq(0u));
}

// Robustness: the call should not alter the input container (observably).
TEST_F(ReporterBase_ListListeners_778, DoesNotMutateInputContainer_778) {
    using namespace Catch;

    std::ostringstream oss;
    OStringIStream* wrapped = new OStringIStream(oss);
    ReporterConfig cfg{ nullptr, Detail::unique_ptr<IStream>(wrapped), ColourMode::None };
    TestReporter reporter(std::move(cfg));

    std::vector<ListenerDescription> descs{
        ListenerDescription{"OnlyOne"}
    };
    const void* pre_addr = static_cast<const void*>(&descs);
    const size_t pre_size = descs.size();

    reporter.listListeners(descs);

    EXPECT_THAT(static_cast<const void*>(&descs), Eq(pre_addr));
    EXPECT_THAT(descs.size(), Eq(pre_size));
}

// (Optional) Stream wiring: if the reporter is constructed on a specific stream,
// the collaborator should receive that same stream (not a different one).
TEST_F(ReporterBase_ListListeners_778, UsesInjectedStream_778) {
    using namespace Catch;

    std::ostringstream oss1, oss2;
    // reporter wired to oss2; oss1 is just to make sure addresses differ
    OStringIStream* wrapped = new OStringIStream(oss2);
    ReporterConfig cfg{ nullptr, Detail::unique_ptr<IStream>(wrapped), ColourMode::None };
    TestReporter reporter(std::move(cfg));

    std::vector<ListenerDescription> descs;

    reporter.listListeners(descs);

    EXPECT_THAT(g_listeners_spy.calls, Eq(1));
    EXPECT_THAT(g_listeners_spy.last_os, Ne(&static_cast<std::ostream&>(oss1)));
    EXPECT_THAT(g_listeners_spy.last_os, Eq(&static_cast<std::ostream&>(oss2)));
}
