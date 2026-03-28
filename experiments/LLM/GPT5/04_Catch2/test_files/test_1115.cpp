// File: AutoReg_ctor_tests_1115.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <string>

using ::testing::_;
using ::testing::A;
using ::testing::An;
using ::testing::ByMove;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::Throw;

// -----------------------
// Minimal test-only shims
// -----------------------
namespace Catch {

namespace Detail {
// Minimal unique_ptr shim (test-only): just forward to std::unique_ptr
template <typename T>
using unique_ptr = std::unique_ptr<T>;
} // namespace Detail

// Minimal StringRef usable in signatures (test-only)
class StringRef {
public:
    constexpr StringRef() noexcept : m_(nullptr) {}
    /*implicit*/ StringRef(const char* s) : m_(s) {}
    /*implicit*/ StringRef(const std::string& s) : m_(s.c_str()) {}
    const char* data() const noexcept { return m_; }
private:
    const char* m_;
};

// Minimal SourceLineInfo for signatures (test-only)
struct SourceLineInfo {
    const char* file;
    std::size_t line;
    constexpr SourceLineInfo(const char* f, std::size_t l) noexcept : file(f), line(l) {}
    SourceLineInfo() = delete;
};

// Forward decls for involved types (test-only)
struct TestCaseInfo { /* empty */ };

struct ITestInvoker {
    virtual ~ITestInvoker() = default;
    virtual void invoke() const = 0;
};

// NameAndTags as per dependency snippet (test-only)
struct NameAndTags {
    StringRef name;
    StringRef tags;
    constexpr NameAndTags(StringRef name_ = StringRef(), StringRef tags_ = StringRef()) noexcept
        : name(name_), tags(tags_) {}
};

// IMutableEnumValuesRegistry dummy (required by interface)
struct IMutableEnumValuesRegistry {
    virtual ~IMutableEnumValuesRegistry() = default;
};

// IMutableRegistryHub interface (as per dependency snippet, test-only)
class IMutableRegistryHub {
public:
    virtual ~IMutableRegistryHub() = default;

    // Only two of these are used by the code under test; others exist to match the signature.
    virtual void registerReporter(const std::string&, /* IReporterFactoryPtr */ void*) {}
    virtual void registerListener(/* Detail::unique_ptr<EventListenerFactory> */ Detail::unique_ptr<void> ) {}
    virtual void registerTest( Detail::unique_ptr<TestCaseInfo>&& testInfo,
                               Detail::unique_ptr<ITestInvoker>&& invoker ) = 0;
    virtual void registerTranslator( Detail::unique_ptr<void>&& ) {}
    virtual void registerTagAlias(const std::string&, const std::string&, const SourceLineInfo&) {}
    virtual void registerStartupException() = 0;
    virtual IMutableEnumValuesRegistry& getMutableEnumValuesRegistry() {
        static IMutableEnumValuesRegistry dummy;
        return dummy;
    }
};

// Global seam to access the hub (what the ctor uses)
static IMutableRegistryHub* gHub = nullptr;
IMutableRegistryHub& getMutableRegistryHub() { return *gHub; }

// Free functions used by the ctor — provide trivial test doubles
// We do NOT assert on their internals; they only need to exist so the ctor can call them.
static inline StringRef extractClassName(StringRef classOrMethod) {
    // test-only: just return input; internal parsing is not under test here
    return classOrMethod;
}

static inline Detail::unique_ptr<TestCaseInfo>
makeTestCaseInfo(StringRef /*className*/, const NameAndTags& /*nameAndTags*/, const SourceLineInfo& /*line*/) {
    return Detail::unique_ptr<TestCaseInfo>(new TestCaseInfo());
}

// The class under test (constructor body from the provided snippet).
// We include just enough to instantiate it in tests.
struct AutoReg {
    AutoReg( Detail::unique_ptr<ITestInvoker> invoker,
             SourceLineInfo const& lineInfo,
             StringRef classOrMethod,
             NameAndTags const& nameAndTags ) noexcept {
        // Provided code path (wrapped in try/catch)
        try {
            getMutableRegistryHub()
                .registerTest(
                    makeTestCaseInfo( extractClassName( classOrMethod ),
                                      nameAndTags,
                                      lineInfo),
                    std::move(invoker) );
        } catch (...) {
            getMutableRegistryHub().registerStartupException();
        }
    }
};

} // namespace Catch

// -----------------------
// Google Mock for the hub
// -----------------------
namespace {
struct MockRegistryHub : Catch::IMutableRegistryHub {
    MOCK_METHOD(void, registerTest,
        (Catch::Detail::unique_ptr<Catch::TestCaseInfo>&&,
         Catch::Detail::unique_ptr<Catch::ITestInvoker>&&),
        (override));

    MOCK_METHOD(void, registerStartupException, (), (override));
};

// Dummy invoker we can pass via unique_ptr
struct DummyInvoker : Catch::ITestInvoker {
    void invoke() const override {}
};

// Test fixture wires the global seam
class AutoRegCtorTest_1115 : public ::testing::Test {
protected:
    StrictMock<MockRegistryHub> hub;

    void SetUp() override { Catch::gHub = &hub; }
    void TearDown() override { Catch::gHub = nullptr; }
};

} // namespace

// -----------------------
// Tests
// -----------------------

// Compile-time contract: constructor is noexcept
TEST_F(AutoRegCtorTest_1115, CtorIsNoexcept_1115) {
    using Catch::AutoReg;
    using Catch::ITestInvoker;
    using Catch::SourceLineInfo;
    using Catch::StringRef;
    using Catch::NameAndTags;

    static_assert(
        noexcept(AutoReg( Catch::Detail::unique_ptr<ITestInvoker>(),
                          SourceLineInfo("file.cpp", 123),
                          StringRef("Suite::Case"),
                          NameAndTags("Name", "[tag]") )),
        "AutoReg constructor must be noexcept");
}

// Normal operation: registers test once, no startup exception
TEST_F(AutoRegCtorTest_1115, RegistersTestOnConstruction_1115) {
    using Catch::AutoReg;
    using Catch::Detail::unique_ptr;
    using Catch::ITestInvoker;
    using Catch::NameAndTags;
    using Catch::SourceLineInfo;
    using Catch::StringRef;

    EXPECT_CALL(hub, registerStartupException()).Times(0);

    EXPECT_CALL(hub, registerTest(A<unique_ptr<Catch::TestCaseInfo>&&>(),
                                  A<unique_ptr<ITestInvoker>&&>()))
        .Times(1);

    unique_ptr<ITestInvoker> inv(new DummyInvoker());
    AutoReg reg(std::move(inv),
                SourceLineInfo("fake.cpp", 42),
                StringRef("MySuite::MyTest"),
                NameAndTags("MyName", "[tag]"));
}

// Exception path: if registration throws, startup exception is recorded
TEST_F(AutoRegCtorTest_1115, RecordsStartupExceptionWhenRegistrationThrows_1115) {
    using Catch::AutoReg;
    using Catch::Detail::unique_ptr;
    using Catch::ITestInvoker;
    using Catch::NameAndTags;
    using Catch::SourceLineInfo;
    using Catch::StringRef;

    EXPECT_CALL(hub, registerTest(_, _))
        .WillOnce(Throw(std::runtime_error("boom")));

    EXPECT_CALL(hub, registerStartupException()).Times(1);

    unique_ptr<ITestInvoker> inv(new DummyInvoker());
    AutoReg reg(std::move(inv),
                SourceLineInfo("fake.cpp", 7),
                StringRef("Suite::Case"),
                NameAndTags("N", "[x]"));
}

// Boundary: null invoker pointer should still attempt to register the test (no throw)
TEST_F(AutoRegCtorTest_1115, AcceptsNullInvoker_RegistersOnce_1115) {
    using Catch::AutoReg;
    using Catch::Detail::unique_ptr;
    using Catch::ITestInvoker;
    using Catch::NameAndTags;
    using Catch::SourceLineInfo;
    using Catch::StringRef;

    EXPECT_CALL(hub, registerStartupException()).Times(0);
    EXPECT_CALL(hub, registerTest(_, _)).Times(1);

    unique_ptr<ITestInvoker> inv(nullptr); // boundary input
    AutoReg reg(std::move(inv),
                SourceLineInfo("null.cpp", 1),
                StringRef("S::C"),
                NameAndTags("N", ""));
}
