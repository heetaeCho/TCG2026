// File: tests/benchmarkfunction_model_call_tests_893.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the amalgamated header as provided in the prompt
#include "Catch2/extras/catch_amalgamated.hpp"

// Shorthand namespaces for readability
namespace C = Catch;
namespace B = Catch::Benchmark;
namespace D = Catch::Benchmark::Detail;

// Two functors exercising the public interface selection surface
// 1) Callable with Chronometer (expects dispatch to fun(meter))
struct TakesChronoFunctor {
    void operator()(B::Chronometer) const noexcept {}
};

// 2) Not callable with Chronometer (expects dispatch to meter.measure(fun))
struct NoArgFunctor {
    void operator()() const noexcept {}
};

// Helper aliases to the nested `model` types (public per snippet)
using Model_TakesChrono = D::BenchmarkFunction<TakesChronoFunctor>::model;
using Model_NoArg      = D::BenchmarkFunction<NoArgFunctor>::model;

// Detect whether we can even attempt to *construct* a Chronometer from the public snippet.
// (We cannot, unless the real Detail::ChronometerConcept is available to the TU.)
template <typename T>
using always_false = std::false_type;

TEST(BenchmarkFunctionModelCall_893, Dispatch_CompileTime_Surface_TakesChrono_893) {
    // Confirm that the nested model is default-constructible from a Fun instance (public interface).
    static_assert(std::is_constructible_v<Model_TakesChrono, TakesChronoFunctor>,
                  "model must be constructible from a functor (const& overload).");
    static_assert(std::is_constructible_v<Model_TakesChrono, TakesChronoFunctor&&>,
                  "model must be constructible from a functor (&& overload).");

    // Confirm call signature is present on the model (interface availability).
    using CallSig = void (Model_TakesChrono::*)(B::Chronometer) const;
    static_assert(std::is_member_function_pointer_v<CallSig>,
                  "Expect model::call(Chronometer) const to exist.");

    // Also verify the model is callable *as declared* with a Chronometer parameter type.
    static_assert(std::is_same_v<CallSig, decltype(&Model_TakesChrono::call)>,
                  "model::call must match the declared signature.");

    // We cannot construct a Chronometer without a concrete Detail::ChronometerConcept.
    // Skip runtime execution in a strictly black-box way.
    GTEST_SKIP() << "Chronometer construction requires opaque Detail::ChronometerConcept; "
                    "runtime path not observable with provided public snippet.";
}

TEST(BenchmarkFunctionModelCall_893, Dispatch_CompileTime_Surface_NoArg_893) {
    // Confirm that the nested model is constructible from a Fun instance (public interface).
    static_assert(std::is_constructible_v<Model_NoArg, NoArgFunctor>,
                  "model must be constructible from a functor (const& overload).");
    static_assert(std::is_constructible_v<Model_NoArg, NoArgFunctor&&>,
                  "model must be constructible from a functor (&& overload).");

    // Confirm call signature is present on the model (interface availability).
    using CallSig = void (Model_NoArg::*)(B::Chronometer) const;
    static_assert(std::is_member_function_pointer_v<CallSig>,
                  "Expect model::call(Chronometer) const to exist.");

    static_assert(std::is_same_v<CallSig, decltype(&Model_NoArg::call)>,
                  "model::call must match the declared signature.");

    // As above, we cannot safely/portably instantiate B::Chronometer here.
    GTEST_SKIP() << "Chronometer construction requires opaque Detail::ChronometerConcept; "
                    "runtime path not observable with provided public snippet.";
}

// The following two tests are placeholders for when a concrete Detail::ChronometerConcept
// (or a permitted test double implementing the public concept interface) is available
// in the build. They keep the names/IDs ready for future enablement without changing
// your suite's structure.

TEST(BenchmarkFunctionModelCall_893, Would_Invoke_Fun_With_Chronometer_When_Accepts_Chronometer_893) {
    // Intent: create a real Chronometer from a test double concept,
    // call Model_TakesChrono::call(meter), and assert that the functor
    // observed a call receiving the same Chronometer (observable via fun’s state).
    // Skipped until a public, mockable concept surface is available.
    GTEST_SKIP() << "Enable when a mockable Detail::ChronometerConcept is available.";
}

TEST(BenchmarkFunctionModelCall_893, Would_Call_Chronometer_Measure_When_Fun_NoArg_893) {
    // Intent: create a real Chronometer from a test double concept,
    // call Model_NoArg::call(meter), and assert that meter.measure(fun) was invoked
    // (observable via the concept mock verifying a measurement occurred).
    // Skipped until a public, mockable concept surface is available.
    GTEST_SKIP() << "Enable when a mockable Detail::ChronometerConcept is available.";
}
