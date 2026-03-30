// File: tests/startup_exception_registry_add_679.tests.cpp

#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <vector>

// Include the public interface under test
#include "Catch2/src/catch2/internal/catch_startup_exception_registry.hpp"

namespace {

class StartupExceptionRegistryTest_679 : public ::testing::Test {
protected:
    Catch::StartupExceptionRegistry reg;
};

} // namespace

// --- Interface/ABI properties (no runtime behavior assumptions) ---

TEST_F(StartupExceptionRegistryTest_679, AddIsNoexcept_679) {
    // add(...) must be noexcept as per interface
    static_assert(
        noexcept(std::declval<Catch::StartupExceptionRegistry&>()
                     .add(std::declval<std::exception_ptr const&>())),
        "StartupExceptionRegistry::add must be noexcept"
    );
    SUCCEED();
}

TEST_F(StartupExceptionRegistryTest_679, GetExceptionsSignatureNoexceptAndConstRef_679) {
    // getExceptions() must be noexcept and return const-ref to the vector
    static_assert(
        noexcept(std::declval<Catch::StartupExceptionRegistry const&>().getExceptions()),
        "StartupExceptionRegistry::getExceptions must be noexcept"
    );
    using ReturnT =
        decltype(std::declval<Catch::StartupExceptionRegistry const&>().getExceptions());
    static_assert(
        std::is_same<ReturnT, std::vector<std::exception_ptr> const&>::value,
        "getExceptions should return const std::vector<std::exception_ptr>&"
    );
    SUCCEED();
}

// --- Observable behavior via public interface only ---

TEST_F(StartupExceptionRegistryTest_679, AddStoresExceptionAndIncreasesCount_679) {
    const auto& before = reg.getExceptions();
    const auto initialSize = before.size();

    std::exception_ptr p = std::make_exception_ptr(std::runtime_error("boom"));
    reg.add(p);

    const auto& after = reg.getExceptions();
    ASSERT_EQ(initialSize + 1, after.size());
    EXPECT_EQ(after.back(), p); // pointer identity is observable
}

TEST_F(StartupExceptionRegistryTest_679, AddPreservesInsertionOrder_679) {
    std::exception_ptr p1 = std::make_exception_ptr(std::runtime_error("r1"));
    std::exception_ptr p2 = std::make_exception_ptr(std::logic_error("l2"));
    std::exception_ptr p3 = std::make_exception_ptr(std::bad_alloc());

    reg.add(p1);
    reg.add(p2);
    reg.add(p3);

    const auto& v = reg.getExceptions();
    ASSERT_GE(v.size(), 3u);
    const size_t n = v.size();
    EXPECT_EQ(v[n - 3], p1);
    EXPECT_EQ(v[n - 2], p2);
    EXPECT_EQ(v[n - 1], p3);
}

TEST_F(StartupExceptionRegistryTest_679, AddAcceptsNullExceptionPtr_679) {
    std::exception_ptr empty; // null exception_ptr is a valid value object
    reg.add(empty);

    const auto& v = reg.getExceptions();
    ASSERT_FALSE(v.empty());
    EXPECT_FALSE(v.back()); // still null after storage
}

TEST_F(StartupExceptionRegistryTest_679, RethrowOfStoredExceptionMatchesOriginal_679) {
    std::exception_ptr p = std::make_exception_ptr(std::runtime_error("payload-679"));
    reg.add(p);

    const auto& v = reg.getExceptions();
    ASSERT_FALSE(v.empty());
    ASSERT_EQ(v.back(), p);

    try {
        std::rethrow_exception(v.back());
        FAIL() << "Expected exception to be rethrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ("payload-679", e.what());
    } catch (...) {
        FAIL() << "Caught unexpected exception type";
    }
}
