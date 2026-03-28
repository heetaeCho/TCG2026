// File: tests/catch_version_tests_879.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <cstring>
#include "catch2/catch_version.hpp"

// Forward declaration to ensure we call the real function under test.
namespace Catch {
    Version const& libraryVersion();
}

// TEST_ID: 879
TEST(CatchVersionTest_879, ReturnsExpectedValues_879) {
    const Catch::Version& v = Catch::libraryVersion();

    // Observable values from the public interface.
    EXPECT_EQ(v.majorVersion, 3u);
    EXPECT_EQ(v.minorVersion, 8u);
    EXPECT_EQ(v.patchNumber, 1u);

    // Branch name is an empty string according to the interface usage.
    ASSERT_NE(v.branchName, nullptr);
    EXPECT_STREQ(v.branchName, "");
    EXPECT_EQ(std::strlen(v.branchName), 0u);

    // Build number observable via public field.
    EXPECT_EQ(v.buildNumber, 0u);
}

// TEST_ID: 879
TEST(CatchVersionTest_879, ReturnsSameInstanceAcrossCalls_879) {
    const Catch::Version* v1 = &Catch::libraryVersion();
    const Catch::Version* v2 = &Catch::libraryVersion();
    // Because the function returns a reference to a static instance,
    // repeated calls should yield the same object (observable by address).
    EXPECT_EQ(v1, v2);
}

// TEST_ID: 879
TEST(CatchVersionTest_879, PublicFieldsAreConstByInterface_879) {
    const Catch::Version& v = Catch::libraryVersion();

    // Ensure the types are const-qualified as specified in the interface.
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v)>>,
                  "libraryVersion should return a const reference to Version");

    // Field constness checks (interface contract).
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v.majorVersion)>>, "majorVersion must be const");
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v.minorVersion)>>, "minorVersion must be const");
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v.patchNumber)>>, "patchNumber must be const");
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v.branchName)>>,  "branchName must be const");
    static_assert(std::is_const_v<std::remove_reference_t<decltype(v.buildNumber)>>, "buildNumber must be const");

    // Also assert at runtime that we cannot (and do not) modify the fields.
    // (No writes attempted here; compile-time constness is the key observable.)
    SUCCEED();
}

// TEST_ID: 879
TEST(CatchVersionTest_879, CopyAndAssignmentAreDeletedByInterface_879) {
    // Interface declares copy ctor and assignment as deleted.
    static_assert(!std::is_copy_constructible_v<Catch::Version>, "Version copy constructor should be deleted");
    static_assert(!std::is_copy_assignable_v<Catch::Version>, "Version copy assignment should be deleted");
}
