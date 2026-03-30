// File: tests/startup_exception_registry_tests_680.cpp

#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>
#include <string>
#include "catch2/internal/catch_startup_exception_registry.hpp"

using Catch::StartupExceptionRegistry;

namespace {

// Compile-time guarantee from the interface (no observable behavior change).
static_assert(noexcept(std::declval<StartupExceptionRegistry&>()
                           .add(std::declval<std::exception_ptr>())),
              "StartupExceptionRegistry::add must be noexcept");

class StartupExceptionRegistryTest_680 : public ::testing::Test {
protected:
    StartupExceptionRegistry reg_;
};

} // namespace

// [Normal] Empty registry has no exceptions.
TEST_F(StartupExceptionRegistryTest_680, InitiallyEmpty_680) {
    const auto& ex = reg_.getExceptions();
    EXPECT_TRUE(ex.empty());
    EXPECT_EQ(ex.size(), 0u);
}

// [Normal] Adding one exception stores it and it can be rethrown as the same type.
TEST_F(StartupExceptionRegistryTest_680, AddSingleException_StoresAndRetrievable_680) {
    auto ep = std::make_exception_ptr(std::runtime_error("boom"));
    reg_.add(ep);

    const auto& ex = reg_.getExceptions();
    ASSERT_EQ(ex.size(), 1u);

    // Observable behavior: rethrow and inspect the caught exception.
    try {
        std::rethrow_exception(ex[0]);
        FAIL() << "Expected exception to be rethrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), std::string("boom").c_str());
    } catch (...) {
        FAIL() << "Caught unexpected exception type";
    }
}

// [Normal] Adding multiple exceptions preserves insertion order.
TEST_F(StartupExceptionRegistryTest_680, AddMultipleExceptions_PreservesOrder_680) {
    auto e1 = std::make_exception_ptr(std::runtime_error("rte"));
    auto e2 = std::make_exception_ptr(std::logic_error("lte"));

    reg_.add(e1);
    reg_.add(e2);

    const auto& ex = reg_.getExceptions();
    ASSERT_EQ(ex.size(), 2u);

    // First is runtime_error
    try {
        std::rethrow_exception(ex[0]);
        FAIL() << "Expected exception to be rethrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), std::string("rte").c_str());
    } catch (...) {
        FAIL() << "First exception is not runtime_error";
    }

    // Second is logic_error
    try {
        std::rethrow_exception(ex[1]);
        FAIL() << "Expected exception to be rethrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), std::string("lte").c_str());
    } catch (...) {
        FAIL() << "Second exception is not logic_error";
    }
}

// [Boundary] Adding a default-constructed (null) exception_ptr is observable via bool conversion.
TEST_F(StartupExceptionRegistryTest_680, AddNullExceptionPtr_IsStoredAndNull_680) {
    std::exception_ptr null_eptr; // null
    reg_.add(null_eptr);

    const auto& ex = reg_.getExceptions();
    ASSERT_EQ(ex.size(), 1u);
    EXPECT_FALSE(static_cast<bool>(ex[0])) << "Stored exception_ptr should be null";
    // Do NOT rethrow null; behavior is implementation-defined (would typically throw std::bad_exception).
}

// [Boundary/Interface] getExceptions returns a stable reference to the same container object.
TEST_F(StartupExceptionRegistryTest_680, GetExceptions_ReturnsSameContainerReference_680) {
    auto const& first_ref = reg_.getExceptions();
    auto e = std::make_exception_ptr(std::runtime_error("x"));
    reg_.add(e);
    auto const& second_ref = reg_.getExceptions();

    // References should refer to the same container object (observable via address of reference).
    EXPECT_EQ(&first_ref, &second_ref);
    // And the content reflects the addition.
    EXPECT_EQ(second_ref.size(), 1u);
}

