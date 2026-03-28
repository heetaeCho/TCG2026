// tests/catch_generators_generate_tests_327.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstddef>
#include <utility>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

//
// ---- Minimal interfaces matching the provided headers (no internal reimplementation) ----
// These are lightweight collaborators/fakes so we can observe interactions.
// They stand in for external dependencies and are allowed per the constraints.
//

namespace Catch {

// StringRef interface surface used by the unit under test
class StringRef {
public:
    StringRef() noexcept = default;
    StringRef(const char* raw) : s_(raw ? raw : ""), n_(raw ? std::strlen(raw) : 0) {}
    StringRef(const char* raw, std::size_t n) : s_(raw ? raw : ""), n_(n) {}
    // observable API we need: comparisons/equality not required for these tests
    const char* data() const noexcept { return s_; }
    std::size_t size() const noexcept { return n_; }
private:
    const char* s_ = "";
    std::size_t n_ = 0;
};

struct SourceLineInfo {
    const char* file;
    std::size_t line;
    constexpr SourceLineInfo(const char* f, std::size_t l) noexcept : file(f), line(l) {}
};

namespace Detail {
// Minimal unique_ptr matching the interface surface we need
template <typename T>
class unique_ptr {
public:
    constexpr unique_ptr(std::nullptr_t = nullptr) : p_(nullptr) {}
    explicit unique_ptr(T* p) : p_(p) {}
    unique_ptr(unique_ptr&& rhs) noexcept : p_(rhs.p_) { rhs.p_ = nullptr; }
    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs) { reset(); p_ = rhs.p_; rhs.p_ = nullptr; }
        return *this;
    }
    ~unique_ptr() { reset(); }
    T* get() const { return p_; }
    T& operator*() const { return *p_; }
    T* operator->() const { return p_; }
    void reset(T* np = nullptr) { if (p_) delete p_; p_ = np; }
    T* release() { T* t = p_; p_ = nullptr; return t; }
    explicit operator bool() const { return p_ != nullptr; }
private:
    T* p_;
};
template <typename T, typename... A>
unique_ptr<T> make_unique(A&&... a) { return unique_ptr<T>(new T(std::forward<A>(a)...)); }

} // namespace Detail

namespace Generators {

// Base class and pointer alias used by IGeneratorTracker
struct IGeneratorBase {
    virtual ~IGeneratorBase() = default;
};

using GeneratorBasePtr = Catch::Detail::unique_ptr<IGeneratorBase>;

// Strongly typed generator interface the code casts to
template <typename T>
struct IGenerator : IGeneratorBase {
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
};

// Concrete minimal generator used by collaborator construction
template <typename T>
class Generators : public IGenerator<T> {
public:
    // Accept any expression object (black box for the test), store a value T
    template <typename Expr>
    explicit Generators(Expr const& expr) : value_(extract(expr)) {}

    T const& get() const override { return value_; }

private:
    // Helper to obtain underlying type value from expression object.
    // We keep it minimal: if it has `.value`, use it; else assume it is T directly.
    template <typename Expr>
    static T const& extract(Expr const& e) {
        return e.value; // Our test expressions will expose .value
    }

    T value_;
};

} // namespace Generators

// Tracker interface used by the unit under test
class IGeneratorTracker {
public:
    virtual ~IGeneratorTracker() = default;
    virtual bool hasGenerator() = 0;
    virtual Generators::GeneratorBasePtr const& getGenerator() = 0;
    virtual void setGenerator(Generators::GeneratorBasePtr&&) = 0;
};

// The free functions used by Catch::Generators::generate (collaborators we’ll fake)
IGeneratorTracker* acquireGeneratorTracker(StringRef, SourceLineInfo const&);
IGeneratorTracker* createGeneratorTracker(StringRef, SourceLineInfo const&, Catch::Detail::unique_ptr<void>);

// We will provide test-side definitions below that match the calls made by `generate`.

} // namespace Catch

// ----------------- Unit under test (from prompt) -----------------
namespace Catch { namespace Generators {
template<typename L>
auto generate( StringRef generatorName,
               SourceLineInfo const& lineInfo,
               L const& generatorExpression )
-> typename decltype(generatorExpression())::type {
    using UnderlyingType = typename decltype(generatorExpression())::type;

    IGeneratorTracker* tracker =
        acquireGeneratorTracker( generatorName, lineInfo );
    if (!tracker) {
        // Note: our fake createGeneratorTracker will ignore the exact pointer type,
        // since we only need to observe that creation happens.
        tracker = createGeneratorTracker(
            generatorName,
            lineInfo,
            Catch::Detail::make_unique<Generators<UnderlyingType>>( generatorExpression() )
        );
    }
    auto const& generator =
        static_cast<IGenerator<UnderlyingType> const&>( *tracker->getGenerator() );
    return generator.get();
}
} } // namespace Catch::Generators

//
// ----------- Test doubles & plumbing for collaborators -----------
//

namespace {

// Expression object type used by tests to satisfy `generatorExpression()::type`
template <typename T>
struct TestExpr {
    using type = T;
    explicit TestExpr(const T& v) : value(v) {}
    T value;
}

// Strict mock for a typed generator
template <typename T>
class MockTypedGenerator : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD((T const&), get, (), (const, override));
};

// Strict mock for IGeneratorTracker
class MockTracker : public Catch::IGeneratorTracker {
public:
    MOCK_METHOD(bool, hasGenerator, (), (override));
    MOCK_METHOD((Catch::Generators::GeneratorBasePtr const&), getGenerator, (), (override));
    MOCK_METHOD(void, setGenerator, (Catch::Generators::GeneratorBasePtr&&), (override));

    // We keep the owned generator pointer for returning by reference
    Catch::Generators::GeneratorBasePtr ownedGen_{nullptr};
};

// Hooks to observe invocations of the free functions
struct TrackerHooks {
    // captured args
    std::string lastName;
    std::string lastFile;
    std::size_t lastLine = 0;

    int acquireCalls = 0;
    int createCalls  = 0;

    // behavior controls
    Catch::IGeneratorTracker* acquireRet = nullptr;
    Catch::IGeneratorTracker* createRet  = nullptr;

    void reset() {
        lastName.clear();
        lastFile.clear();
        lastLine = 0;
        acquireCalls = createCalls = 0;
        acquireRet = createRet = nullptr;
    }
};

TrackerHooks g_hooks;

// Concrete definitions of the collaborators used by generate()

} // namespace

namespace Catch {

// Our test-side implementations capture parameters and return controlled fakes.
IGeneratorTracker* acquireGeneratorTracker(StringRef name, SourceLineInfo const& li) {
    g_hooks.acquireCalls++;
    g_hooks.lastName = std::string(name.data(), name.size());
    g_hooks.lastFile = li.file ? li.file : "";
    g_hooks.lastLine = li.line;
    return g_hooks.acquireRet;
}

// The third parameter’s exact type is a unique_ptr<Generators<UnderlyingType>> in real code.
// We accept it as unique_ptr<void> in the declaration above to avoid template explosion,
// and because we only need to observe that creation was attempted.
IGeneratorTracker* createGeneratorTracker(StringRef name,
                                          SourceLineInfo const& li,
                                          Catch::Detail::unique_ptr<void> /*ignored*/) {
    g_hooks.createCalls++;
    g_hooks.lastName = std::string(name.data(), name.size());
    g_hooks.lastFile = li.file ? li.file : "";
    g_hooks.lastLine = li.line;
    return g_hooks.createRet;
}

} // namespace Catch

//
// ------------------------------ TESTS ------------------------------
//

struct GenerateTest_327 : public ::testing::Test {
    void SetUp() override {
        g_hooks.reset();
    }
    void TearDown() override { g_hooks.reset(); }
};

// 1) Normal operation: existing tracker path -> returns value from tracker’s generator
TEST_F(GenerateTest_327, ReturnsValueFromExistingTracker_327) {
    StrictMock<MockTracker> tracker;
    StrictMock<MockTypedGenerator<int>> gen;

    // Prepare owned generator pointer and expectation
    tracker.ownedGen_.reset(&gen); // will be released by test (we won’t delete mock)
    EXPECT_CALL(tracker, getGenerator())
        .WillRepeatedly(::testing::ReturnRef(tracker.ownedGen_));
    EXPECT_CALL(gen, get()).WillOnce(Return(std::cref(42)));

    // acquire returns our tracker, so create must NOT be called
    g_hooks.acquireRet = &tracker;
    g_hooks.createRet  = nullptr;

    auto name = Catch::StringRef("num");
    Catch::SourceLineInfo line("test_file.cpp", 101);

    // generatorExpression ignored in this path; still must conform to interface
    int const value = Catch::Generators::generate(
        name, line, [] { return TestExpr<int>(0); } );

    EXPECT_EQ(value, 42);
    EXPECT_EQ(g_hooks.acquireCalls, 1);
    EXPECT_EQ(g_hooks.createCalls, 0);
    EXPECT_EQ(g_hooks.lastName, "num");
    EXPECT_EQ(g_hooks.lastFile, "test_file.cpp");
    EXPECT_EQ(g_hooks.lastLine, 101u);
}

// 2) Boundary/branch: missing tracker -> create is called and result value is returned
TEST_F(GenerateTest_327, CreatesTrackerIfMissing_327) {
    StrictMock<MockTracker> tracker;
    StrictMock<MockTypedGenerator<std::string>> gen;

    // Hook tracker to return our generator
    tracker.ownedGen_.reset(&gen);
    EXPECT_CALL(tracker, getGenerator())
        .WillRepeatedly(::testing::ReturnRef(tracker.ownedGen_));
    EXPECT_CALL(gen, get()).WillOnce(Return(std::cref(std::string("ok"))));

    // acquire returns nullptr; create returns our tracker
    g_hooks.acquireRet = nullptr;
    g_hooks.createRet  = &tracker;

    auto name = Catch::StringRef("str");
    Catch::SourceLineInfo line("gen.cpp", 7);

    std::string out = Catch::Generators::generate(
        name, line, [] { return TestExpr<std::string>("ignored"); });

    EXPECT_EQ(out, "ok");
    EXPECT_EQ(g_hooks.acquireCalls, 1);
    EXPECT_EQ(g_hooks.createCalls, 1);
    EXPECT_EQ(g_hooks.lastName, "str");
    EXPECT_EQ(g_hooks.lastFile, "gen.cpp");
    EXPECT_EQ(g_hooks.lastLine, 7u);
}

// 3) Verifies parameters are forwarded to both acquire and create branches
TEST_F(GenerateTest_327, ForwardsNameAndLineInfo_327) {
    StrictMock<MockTracker> tracker;
    StrictMock<MockTypedGenerator<double>> gen;

    // First run: acquire succeeds
    tracker.ownedGen_.reset(&gen);
    EXPECT_CALL(tracker, getGenerator())
        .Times(2) // two runs below
        .WillRepeatedly(::testing::ReturnRef(tracker.ownedGen_));
    EXPECT_CALL(gen, get())
        .Times(2)
        .WillRepeatedly(Return(std::cref(3.14)));

    // --- Run 1: acquire path ---
    g_hooks.reset();
    g_hooks.acquireRet = &tracker;
    auto out1 = Catch::Generators::generate(
        Catch::StringRef("A"), Catch::SourceLineInfo("fa.cpp", 1),
        [] { return TestExpr<double>(0.0); });
    EXPECT_DOUBLE_EQ(out1, 3.14);
    EXPECT_EQ(g_hooks.acquireCalls, 1);
    EXPECT_EQ(g_hooks.createCalls, 0);
    EXPECT_EQ(g_hooks.lastName, "A");
    EXPECT_EQ(g_hooks.lastFile, "fa.cpp");
    EXPECT_EQ(g_hooks.lastLine, 1u);

    // --- Run 2: create path ---
    g_hooks.reset();
    g_hooks.acquireRet = nullptr;
    g_hooks.createRet  = &tracker;
    auto out2 = Catch::Generators::generate(
        Catch::StringRef("B"), Catch::SourceLineInfo("fb.cpp", 2),
        [] { return TestExpr<double>(0.0); });
    EXPECT_DOUBLE_EQ(out2, 3.14);
    EXPECT_EQ(g_hooks.acquireCalls, 1);
    EXPECT_EQ(g_hooks.createCalls, 1);
    EXPECT_EQ(g_hooks.lastName, "B");
    EXPECT_EQ(g_hooks.lastFile, "fb.cpp");
    EXPECT_EQ(g_hooks.lastLine, 2u);
}

//
// --------- Additional unit tests for the other provided interfaces ---------
// These assert only the public/observable API surface.
//

// StringRef basic observable behavior
TEST(StringRefTest_327, ConstructionAndBasics_327) {
    Catch::StringRef empty;
    EXPECT_EQ(empty.size(), 0u);

    Catch::StringRef s1("hello");
    EXPECT_EQ(s1.size(), 5u);
    EXPECT_EQ(std::string(s1.data(), s1.size()), "hello");

    Catch::StringRef s2("hi", 1);
    EXPECT_EQ(s2.size(), 1u);
    EXPECT_EQ(std::string(s2.data(), s2.size()), "h");
}

// Detail::unique_ptr observable ownership semantics
TEST(UniquePtrTest_327, OwnershipAndMove_327) {
    using Catch::Detail::unique_ptr;
    struct Foo { int x{0}; int get() const { return x; } };

    unique_ptr<Foo> p;                // default
    EXPECT_FALSE(static_cast<bool>(p));

    p = unique_ptr<Foo>(new Foo{42}); // construct
    EXPECT_TRUE(static_cast<bool>(p));
    EXPECT_EQ(p->get(), 42);
    EXPECT_EQ((*p).x, 42);

    auto raw = p.release();           // release
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_NE(raw, nullptr);
    delete raw;

    unique_ptr<Foo> a(new Foo{7});
    unique_ptr<Foo> b(std::move(a));  // move ctor
    EXPECT_FALSE(static_cast<bool>(a));
    EXPECT_TRUE(static_cast<bool>(b));
    EXPECT_EQ(b->x, 7);

    unique_ptr<Foo> c;
    c = std::move(b);                 // move assign
    EXPECT_FALSE(static_cast<bool>(b));
    EXPECT_TRUE(static_cast<bool>(c));
    EXPECT_EQ(c->x, 7);

    c.reset(new Foo{9});              // reset
    EXPECT_EQ(c->x, 9);
    c.reset();                        // reset to nullptr
    EXPECT_FALSE(static_cast<bool>(c));
}

// SourceLineInfo observable fields
TEST(SourceLineInfoTest_327, StoresFileAndLine_327) {
    Catch::SourceLineInfo s1("file.cpp", 123);
    EXPECT_STREQ(s1.file, "file.cpp");
    EXPECT_EQ(s1.line, 123u);

    Catch::SourceLineInfo s2("other.hpp", 1);
    EXPECT_STREQ(s2.file, "other.hpp");
    EXPECT_EQ(s2.line, 1u);
}
