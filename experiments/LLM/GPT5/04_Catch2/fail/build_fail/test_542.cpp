// File: tests/make_output_redirect_tests_542.cpp

#include <gtest/gtest.h>

// Try the public/internal header that declares OutputRedirect & makers.
// Adjust include path as needed for your build.
#include <catch2/internal/catch_output_redirect.hpp>

#include <type_traits>
#include <typeinfo>
#include <memory>

using Catch::Detail::makeOutputRedirect;

class MakeOutputRedirectTest_542 : public ::testing::Test {};

// Verifies that passing false creates a "no-op" redirect object.
// We validate via RTTI rather than relying on internal state/behavior.
TEST_F(MakeOutputRedirectTest_542, ReturnsNoopWhenActualIsFalse_542) {
    auto ptr = makeOutputRedirect(false);
    ASSERT_NE(ptr, nullptr) << "Factory must return a valid pointer";

    // The internal types are part of the interface in this TU;
    // we only observe the dynamic type via safe dynamic_cast.
    // If the symbol is not visible in your configuration, replace with typeid name checks.
    auto* asNoop =
        dynamic_cast<Catch::Detail::NoopRedirect*>(ptr.get());
    ASSERT_NE(asNoop, nullptr) << "Expected NoopRedirect when actual=false";
}

// Verifies that passing true creates an "active" redirect depending on the compile-time flag.
// We do not test behavior of capturing itself (black-box constraint); only the exposed type.
TEST_F(MakeOutputRedirectTest_542, ReturnsActiveRedirectWhenActualIsTrue_542) {
    auto ptr = makeOutputRedirect(true);
    ASSERT_NE(ptr, nullptr);

#if defined(CATCH_CONFIG_NEW_CAPTURE)
    auto* asFile = dynamic_cast<Catch::Detail::FileRedirect*>(ptr.get());
    ASSERT_NE(asFile, nullptr) << "Expected FileRedirect when CATCH_CONFIG_NEW_CAPTURE is defined";
#else
    auto* asStream = dynamic_cast<Catch::Detail::StreamRedirect*>(ptr.get());
    ASSERT_NE(asStream, nullptr) << "Expected StreamRedirect when CATCH_CONFIG_NEW_CAPTURE is not defined";
#endif
}

// Ensures the factory returns distinct dynamic types for actual=true vs false.
TEST_F(MakeOutputRedirectTest_542, DistinctTypesForTrueAndFalse_542) {
    auto falsePtr = makeOutputRedirect(false);
    auto truePtr  = makeOutputRedirect(true);

    ASSERT_NE(falsePtr, nullptr);
    ASSERT_NE(truePtr, nullptr);

    // Confirm type difference by comparing type_info names of the pointed objects.
    const std::type_info& tFalse = typeid(*falsePtr);
    const std::type_info& tTrue  = typeid(*truePtr);
    EXPECT_NE(tFalse.hash_code(), tTrue.hash_code())
        << "actual=false and actual=true should yield different dynamic types";
}

// Validates unique ownership semantics: the returned pointer must be movable and leave the source empty.
TEST_F(MakeOutputRedirectTest_542, UniquePtrMoveSemantics_542) {
    auto original = makeOutputRedirect(true);
    ASSERT_NE(original, nullptr);

    auto moved = std::move(original);
    EXPECT_EQ(original, nullptr) << "Moved-from unique_ptr should be null";
    EXPECT_NE(moved, nullptr)    << "Moved-to unique_ptr should hold the object";

    // Still the correct active type after move
#if defined(CATCH_CONFIG_NEW_CAPTURE)
    EXPECT_NE(dynamic_cast<Catch::Detail::FileRedirect*>(moved.get()), nullptr);
#else
    EXPECT_NE(dynamic_cast<Catch::Detail::StreamRedirect*>(moved.get()), nullptr);
#endif
}

// Smoke test that destruction via base pointer is safe (polymorphic deletion).
// We can't assert side-effects per constraints; just ensure no crash.
TEST_F(MakeOutputRedirectTest_542, PolymorphicDeletionIsSafe_542) {
    std::unique_ptr<Catch::Detail::OutputRedirect> basePtr = makeOutputRedirect(true);
    ASSERT_NE(basePtr, nullptr);
    // Scope end invokes destructor via base class; test passes if no crash/UB is observed.
}
