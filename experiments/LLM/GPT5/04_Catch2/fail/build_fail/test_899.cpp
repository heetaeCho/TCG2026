// File: tests/detail_invoke_899_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the provided interface (as given in the prompt)
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::_;
using ::testing::Exactly;
using ::testing::StrEq;

namespace C = Catch::Benchmark::Detail;

//
// Helpers used by tests (external collaborators / observable effects)
//

// 1) A mock functor to verify arguments and that operator() is invoked.
struct MockFunctor {
    MOCK_METHOD(void, Call, (int, const std::string&), ());
    void operator()(int x, const std::string& s) { Call(x, s); }
};

// 2) Overload-detecting functor for lvalue-vs-rvalue functor forwarding.
struct LRFunctor {
    int* flag; // 1 if & overload called, 2 if && overload called
    void operator()() &  { *flag = 1; }
    void operator()() && { *flag = 2; }
};

// 3) Spy type to observe whether an argument was moved-from (rvalue forwarding).
struct MoveSpy {
    bool* was_moved_from; // set to true on move
    explicit MoveSpy(bool* moved) : was_moved_from(moved) {}
    MoveSpy(const MoveSpy&) = delete;
    MoveSpy& operator=(const MoveSpy&) = delete;
    MoveSpy(MoveSpy&& other) noexcept : was_moved_from(nullptr) {
        if (other.was_moved_from) {
            *(other.was_moved_from) = true;
            // leave other's pointer intact or null — we only care about the flag change
        }
    }
    MoveSpy& operator=(MoveSpy&& other) noexcept {
        if (this != &other && other.was_moved_from) {
            *(other.was_moved_from) = true;
        }
        return *this;
    }
};

// 4) A free function to test function pointer callables.
static void FreeFunctionIncrement(int* p, int delta) {
    if (p) *p += delta;
}

class DetailInvokeTest_899 : public ::testing::Test {};

// --- Tests ---

// Verifies: basic invocation and parameter passing with a mock functor.
TEST_F(DetailInvokeTest_899, InvokesCallableWithArgs_899) {
    MockFunctor mf;
    EXPECT_CALL(mf, Call(42, StrEq("hello"))).Times(Exactly(1));
    auto r = C::invoke(mf, 42, std::string{"hello"});
    (void)r; // The return is a CompleteType_t<void>; just ensure it compiles/returns.
}

// Verifies: works with zero-argument callables (normal operation).
TEST_F(DetailInvokeTest_899, InvokesZeroArgCallable_899) {
    bool called = false;
    auto lambda = [&] { called = true; };
    auto r = C::invoke(lambda);
    (void)r;
    EXPECT_TRUE(called);
}

// Verifies: exceptions from the callable are propagated (observable behavior).
TEST_F(DetailInvokeTest_899, PropagatesExceptions_899) {
    auto throwing = []() -> void {
        throw std::runtime_error("oops");
    };
    EXPECT_THROW((void)C::invoke(throwing), std::runtime_error);
}

// Verifies: perfect forwarding of the *functor* — lvalue vs rvalue overload is selected.
TEST_F(DetailInvokeTest_899, ForwardsFunctorValueCategory_899) {
    int flag = 0;
    LRFunctor f{&flag};

    // Lvalue functor -> operator&() called
    flag = 0;
    (void)C::invoke(f);
    EXPECT_EQ(flag, 1);

    // Rvalue functor -> operator&&() called
    flag = 0;
    (void)C::invoke(LRFunctor{&flag});
    EXPECT_EQ(flag, 2);
}

// Verifies: perfect forwarding of *arguments* — rvalue arguments are moved.
TEST_F(DetailInvokeTest_899, ForwardsRvalueArguments_899) {
    bool moved_from = false;
    MoveSpy spy{&moved_from};

    // Functor that consumes MoveSpy by value (will move from the argument
    // if passed as an rvalue); we only care that the move happened.
    auto consumer = [](MoveSpy /*by_value*/) {};

    (void)C::invoke(consumer, std::move(spy));
    EXPECT_TRUE(moved_from);
}

// Verifies: works with function pointers and multiple arguments (normal operation).
TEST_F(DetailInvokeTest_899, InvokesFunctionPointer_899) {
    int v = 5;
    using FnPtr = void(*)(int*, int);
    FnPtr fn = &FreeFunctionIncrement;

    (void)C::invoke(fn, &v, 7);
    EXPECT_EQ(v, 12);
}

// Verifies: return type exists and is default-constructible (compile-time property only).
TEST_F(DetailInvokeTest_899, ReturnTypeIsDefaultConstructible_899) {
    auto noop = [] {};
    using Ret = decltype(C::invoke(noop));
    // This is a compile-time assertion; it doesn't check internals,
    // only that the public return type can be default-constructed.
    static_assert(std::is_default_constructible<Ret>::value,
                  "invoke's CompleteType_t<void> return should be default-constructible");
    auto r = C::invoke(noop);
    (void)r; // avoid unused warning
}

// Verifies: const argument lvalue is passed as-is (no mutation observable).
TEST_F(DetailInvokeTest_899, PassesConstLvalueArg_899) {
    const int x = 10;
    bool saw_const = false;
    auto observer = [&](const int& rx) {
        // Observable behavior: receiving a const lvalue reference; ensure value is unchanged.
        if (rx == 10) saw_const = true;
    };
    (void)C::invoke(observer, x);
    EXPECT_TRUE(saw_const);
}
