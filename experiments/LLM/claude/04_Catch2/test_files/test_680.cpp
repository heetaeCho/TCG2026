#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>
#include <vector>

// Include the header for the class under test
#include "catch2/internal/catch_startup_exception_registry.hpp"

class StartupExceptionRegistryTest_680 : public ::testing::Test {
protected:
    Catch::StartupExceptionRegistry registry;
};

// Test that a newly constructed registry has no exceptions
TEST_F(StartupExceptionRegistryTest_680, DefaultConstructedRegistryIsEmpty_680) {
    const auto& exceptions = registry.getExceptions();
    EXPECT_TRUE(exceptions.empty());
    EXPECT_EQ(exceptions.size(), 0u);
}

// Test that adding a single exception increases the count to 1
TEST_F(StartupExceptionRegistryTest_680, AddSingleExceptionIncreasesCount_680) {
    try {
        throw std::runtime_error("test error");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), 1u);
}

// Test that adding multiple exceptions stores all of them
TEST_F(StartupExceptionRegistryTest_680, AddMultipleExceptionsStoresAll_680) {
    try {
        throw std::runtime_error("error 1");
    } catch (...) {
        registry.add(std::current_exception());
    }

    try {
        throw std::logic_error("error 2");
    } catch (...) {
        registry.add(std::current_exception());
    }

    try {
        throw std::out_of_range("error 3");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    EXPECT_EQ(exceptions.size(), 3u);
}

// Test that stored exceptions can be rethrown and contain correct information
TEST_F(StartupExceptionRegistryTest_680, StoredExceptionCanBeRethrown_680) {
    try {
        throw std::runtime_error("specific error message");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 1u);
    ASSERT_NE(exceptions[0], nullptr);

    try {
        std::rethrow_exception(exceptions[0]);
        FAIL() << "Expected std::runtime_error to be thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "specific error message");
    } catch (...) {
        FAIL() << "Expected std::runtime_error but got different exception type";
    }
}

// Test that getExceptions returns a const reference (not a copy) - same address on repeated calls
TEST_F(StartupExceptionRegistryTest_680, GetExceptionsReturnsConsistentReference_680) {
    const auto& ref1 = registry.getExceptions();
    const auto& ref2 = registry.getExceptions();
    EXPECT_EQ(&ref1, &ref2);
}

// Test that the stored exception preserves the exception type for different exception types
TEST_F(StartupExceptionRegistryTest_680, StoredExceptionsPreserveTypes_680) {
    try {
        throw std::runtime_error("runtime");
    } catch (...) {
        registry.add(std::current_exception());
    }

    try {
        throw std::logic_error("logic");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 2u);

    // Check first exception type
    try {
        std::rethrow_exception(exceptions[0]);
        FAIL();
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "runtime");
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }

    // Check second exception type
    try {
        std::rethrow_exception(exceptions[1]);
        FAIL();
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "logic");
    } catch (...) {
        FAIL() << "Expected std::logic_error";
    }
}

// Test that getExceptions is noexcept
TEST_F(StartupExceptionRegistryTest_680, GetExceptionsIsNoexcept_680) {
    EXPECT_TRUE(noexcept(registry.getExceptions()));
}

// Test adding an exception_ptr that holds a non-standard exception type (e.g., int)
TEST_F(StartupExceptionRegistryTest_680, AddNonStandardExceptionType_680) {
    try {
        throw 42;
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 1u);

    try {
        std::rethrow_exception(exceptions[0]);
        FAIL();
    } catch (int val) {
        EXPECT_EQ(val, 42);
    } catch (...) {
        FAIL() << "Expected int exception";
    }
}

// Test that exceptions are stored in order
TEST_F(StartupExceptionRegistryTest_680, ExceptionsAreStoredInOrder_680) {
    for (int i = 0; i < 5; ++i) {
        try {
            throw std::runtime_error(std::to_string(i));
        } catch (...) {
            registry.add(std::current_exception());
        }
    }

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 5u);

    for (int i = 0; i < 5; ++i) {
        try {
            std::rethrow_exception(exceptions[i]);
            FAIL();
        } catch (const std::runtime_error& e) {
            EXPECT_EQ(std::string(e.what()), std::to_string(i));
        } catch (...) {
            FAIL();
        }
    }
}

// Test that stored exception_ptrs are not null
TEST_F(StartupExceptionRegistryTest_680, StoredExceptionPtrsAreNotNull_680) {
    try {
        throw std::runtime_error("test");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    for (const auto& ex : exceptions) {
        EXPECT_NE(ex, nullptr);
    }
}

// Test adding a string exception
TEST_F(StartupExceptionRegistryTest_680, AddStringException_680) {
    try {
        throw std::string("string exception");
    } catch (...) {
        registry.add(std::current_exception());
    }

    const auto& exceptions = registry.getExceptions();
    ASSERT_EQ(exceptions.size(), 1u);

    try {
        std::rethrow_exception(exceptions[0]);
        FAIL();
    } catch (const std::string& s) {
        EXPECT_EQ(s, "string exception");
    } catch (...) {
        FAIL() << "Expected std::string exception";
    }
}
