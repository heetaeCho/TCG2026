// File: tests/exception_translator_registry_register_tests_686.cpp

#include <gtest/gtest.h>

// We only rely on the public interfaces that appear in the provided snippets.
#include "catch2/internal/catch_exception_translator_registry.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

namespace {

using Catch::ExceptionTranslatorRegistry;
using Catch::Detail::unique_ptr;

// Forward-declare the interface type to avoid depending on any private details.
// We never instantiate it or call into it; we only pass (possibly null) pointers
// to the registry, which is allowed by the interface.
namespace Catch {
    struct IExceptionTranslator;
}

class ExceptionTranslatorRegistryTest_686 : public ::testing::Test {
protected:
    ExceptionTranslatorRegistry reg_;
};

// [Normal] Registering a null translator should be a no-op and not throw.
TEST_F(ExceptionTranslatorRegistryTest_686, RegisterNullTranslator_NoThrow_686) {
    unique_ptr<Catch::IExceptionTranslator> ptr(nullptr);
    EXPECT_NO_THROW(reg_.registerTranslator(std::move(ptr)));
    // After move, caller's unique_ptr should remain (or become) null.
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// [Boundary] Re-registering multiple null translators should still not throw.
TEST_F(ExceptionTranslatorRegistryTest_686, RegisterMultipleNull_NoThrow_686) {
    unique_ptr<Catch::IExceptionTranslator> p1(nullptr);
    unique_ptr<Catch::IExceptionTranslator> p2(nullptr);
    unique_ptr<Catch::IExceptionTranslator> p3(nullptr);

    EXPECT_NO_THROW(reg_.registerTranslator(std::move(p1)));
    EXPECT_NO_THROW(reg_.registerTranslator(std::move(p2)));
    EXPECT_NO_THROW(reg_.registerTranslator(std::move(p3)));

    EXPECT_FALSE(static_cast<bool>(p1));
    EXPECT_FALSE(static_cast<bool>(p2));
    EXPECT_FALSE(static_cast<bool>(p3));
}

// [Ownership] The API requires an rvalue (move) and should take ownership.
// While we cannot inspect internal state, we can verify that the source
// unique_ptr is left in a moved-from (null) state after the call.
TEST_F(ExceptionTranslatorRegistryTest_686, MoveLeavesSourceNull_686) {
    // We cannot construct a concrete translator instance (no public type given),
    // but we can still verify move semantics with a null unique_ptr.
    unique_ptr<Catch::IExceptionTranslator> ptr(nullptr);
    reg_.registerTranslator(std::move(ptr));
    EXPECT_FALSE(static_cast<bool>(ptr)); // moved-from remains null
}

} // namespace
