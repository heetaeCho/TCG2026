#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>
#include <vector>

// Include the header for the class under test
#include "catch2/internal/catch_startup_exception_registry.hpp"

class StartupExceptionRegistryTest_679 : public ::testing::Test {
protected:
    Catch::StartupExceptionRegistry registry;
};

// Test that a newly constructed registry has no exceptions
TEST_F(StartupExceptionRegistryTest_679, InitiallyEmpty_679) {
    const auto& exceptions = registry.getExceptions();
    EXPECT_TRUE(exceptions.empty());
    EXPECT_EQ(exceptions.size(), 0u);
}

// Test adding a single exception and retrieving it
TEST_F(StartupExceptionRegistryTest_679, AddSingleException_679) {
    auto ex = std::make_exception_ptr(std::runtime_error("test error"));
    registry.add(ex);

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), 1u);
}

// Test adding multiple exceptions
TEST_F(StartupExceptionRegistryTest_679, AddMultipleExceptions_679) {
    auto ex1 = std::make_exception_ptr(std::runtime_error("error 1"));
    auto ex2 = std::make_exception_ptr(std::logic_error("error 2"));
    auto ex3 = std::make_exception_ptr(std::overflow_error("error 3"));

    registry.add(ex1);
    registry.add(ex2);
    registry.add(ex3);

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), 3u);
}

// Test that the stored exception can be rethrown and caught with the correct type
TEST_F(StartupExceptionRegistryTest_679, StoredExceptionRetainsType_679) {
    auto ex = std::make_exception_ptr(std::runtime_error("specific error"));
    registry.add(ex);

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 1u);

    bool caught = false;
    try {
        std::rethrow_exception(exceptions[0]);
    } catch (const std::runtime_error& e) {
        caught = true;
        EXPECT_STREQ(e.what(), "specific error");
    } catch (...) {
        FAIL() << "Expected std::runtime_error but caught a different exception";
    }
    EXPECT_TRUE(caught);
}

// Test that exceptions are stored in order
TEST_F(StartupExceptionRegistryTest_679, ExceptionsStoredInOrder_679) {
    auto ex1 = std::make_exception_ptr(std::runtime_error("first"));
    auto ex2 = std::make_exception_ptr(std::logic_error("second"));

    registry.add(ex1);
    registry.add(ex2);

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 2u);

    try {
        std::rethrow_exception(exceptions[0]);
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "first");
    } catch (...) {
        FAIL() << "Expected std::runtime_error for first exception";
    }

    try {
        std::rethrow_exception(exceptions[1]);
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "second");
    } catch (...) {
        FAIL() << "Expected std::logic_error for second exception";
    }
}

// Test adding a null exception_ptr (boundary case)
TEST_F(StartupExceptionRegistryTest_679, AddNullExceptionPtr_679) {
    std::exception_ptr null_ex;
    registry.add(null_ex);

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), 1u);
    EXPECT_EQ(exceptions[0], nullptr);
}

// Test that getExceptions returns a const reference (multiple calls return same data)
TEST_F(StartupExceptionRegistryTest_679, GetExceptionsReturnsConsistentReference_679) {
    auto ex = std::make_exception_ptr(std::runtime_error("test"));
    registry.add(ex);

    const auto& ref1 = registry.getExceptions();
    const auto& ref2 = registry.getExceptions();

    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1.size(), ref2.size());
}

// Test adding many exceptions (stress/boundary)
TEST_F(StartupExceptionRegistryTest_679, AddManyExceptions_679) {
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        auto ex = std::make_exception_ptr(std::runtime_error("error " + std::to_string(i)));
        registry.add(ex);
    }

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), count);
}

// Test adding different exception types
TEST_F(StartupExceptionRegistryTest_679, AddDifferentExceptionTypes_679) {
    registry.add(std::make_exception_ptr(std::runtime_error("runtime")));
    registry.add(std::make_exception_ptr(std::logic_error("logic")));
    registry.add(std::make_exception_ptr(std::bad_alloc()));
    registry.add(std::make_exception_ptr(42)); // non-standard exception type

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 4u);

    // Verify the int exception
    try {
        std::rethrow_exception(exceptions[3]);
    } catch (int val) {
        EXPECT_EQ(val, 42);
    } catch (...) {
        FAIL() << "Expected int exception";
    }
}

// Test that getExceptions is noexcept
TEST_F(StartupExceptionRegistryTest_679, GetExceptionsIsNoexcept_679) {
    EXPECT_TRUE(noexcept(registry.getExceptions()));
}

// Test that add is noexcept
TEST_F(StartupExceptionRegistryTest_679, AddIsNoexcept_679) {
    auto ex = std::make_exception_ptr(std::runtime_error("test"));
    EXPECT_TRUE(noexcept(registry.add(ex)));
}
