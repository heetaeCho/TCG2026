// File: tests/ExeNameTest_393.cpp
#include <gtest/gtest.h>
#include <string>

// Include the provided header where ExeName is declared
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::ExeName;

class ExeNameTest_393 : public ::testing::Test {};

// Verifies the default constructed name is "<executable>"
TEST_F(ExeNameTest_393, DefaultNameIsExecutable_393) {
    ExeName exe;
    EXPECT_EQ(exe.name(), std::string("<executable>"));
}

// Verifies that set(...) updates the observable name
TEST_F(ExeNameTest_393, SetUpdatesName_393) {
    ExeName exe;
    // We do not assert on return type/values to avoid coupling to internals
    (void)exe.set("my_app");
    EXPECT_EQ(exe.name(), std::string("my_app"));
}

// Verifies that constructing with an external std::string& propagates updates via set(...)
TEST_F(ExeNameTest_393, SetPropagatesToBoundRef_393) {
    std::string external = "initial";
    ExeName exe(external);

    (void)exe.set("bound_app");
    EXPECT_EQ(exe.name(), std::string("bound_app"));
    // Observable effect on the external collaborator
    EXPECT_EQ(external, std::string("bound_app"));
}

// Boundary: empty string should be accepted and observable
TEST_F(ExeNameTest_393, EmptyStringAllowed_393) {
    ExeName exe;
    (void)exe.set("");
    EXPECT_EQ(exe.name(), std::string(""));
}

// Boundary: unicode and long strings should be preserved
TEST_F(ExeNameTest_393, UnicodeAndLongName_393) {
    ExeName exe;

    // Unicode name
    const std::string unicode_name = u8"프로젝트-앱🚀";
    (void)exe.set(unicode_name);
    EXPECT_EQ(exe.name(), unicode_name);

    // Long name
    std::string long_name(4096, 'a'); // 4KB of 'a'
    (void)exe.set(long_name);
    EXPECT_EQ(exe.name(), long_name);
}

// Stability: name() returns a const reference that remains stable across calls
TEST_F(ExeNameTest_393, NameReturnsConstRef_StableAddress_393) {
    ExeName exe;
    (void)exe.set("stable");

    auto const& ref1 = exe.name();
    auto const& ref2 = exe.name();

    // Same object reference each time (observable via address)
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, std::string("stable"));
}

// Multiple updates: last set wins and is observable via name()
TEST_F(ExeNameTest_393, MultipleSequentialSets_LastOneVisible_393) {
    ExeName exe;
    (void)exe.set("first");
    EXPECT_EQ(exe.name(), std::string("first"));

    (void)exe.set("second");
    EXPECT_EQ(exe.name(), std::string("second"));

    (void)exe.set("third");
    EXPECT_EQ(exe.name(), std::string("third"));
}
