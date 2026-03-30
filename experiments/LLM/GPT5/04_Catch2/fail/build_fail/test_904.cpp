// File: tests/measure_one_tests_904.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header that contains `measure_one`
#include "Catch2/extras/catch_amalgamated.hpp"

// We place our test doubles in the exact namespace so ADL/overload picks them up.
// We ONLY mock the external collaborator `complete_invoke`.
// We DO NOT re-implement or infer any internal logic of measure_one.
namespace Catch { namespace Benchmark { namespace Detail {

// Forward declare Chronometer so our mocks can compile even if Chronometer is opaque to us.
using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// A functor that `complete_invoke` will receive and then invoke with a Chronometer.
// We don't know Chronometer's internals; we only treat it as an opaque parameter.
struct MockFunctor_904 {
    MOCK_METHOD(int, Call, (Chronometer), ());
    int operator()(Chronometer c) { return Call(c); }
};

// GoogleMock wrapper for the free function collaborator `complete_invoke`.
// We'll route calls to this global mock instance from our test-local overload below.
struct MockCompleteInvoke_904 {
    MOCK_METHOD(int, Call, (MockFunctor_904&, Chronometer), ());
};

// Global pointer used by our test-local overload to reach the mock from the test body.
static ::testing::StrictMock<MockCompleteInvoke_904>* g_completeInvokeMock_904 = nullptr;

// Test-local overload for the external collaborator.
// This is allowed per constraints as we are mocking an external dependency,
// not simulating the SUT's internals.
inline int complete_invoke(MockFunctor_904& fun, Chronometer c) {
    // Delegate to the mock (observable interaction point).
    return g_completeInvokeMock_904->Call(fun, c);
}

}}} // namespace Catch::Bench
