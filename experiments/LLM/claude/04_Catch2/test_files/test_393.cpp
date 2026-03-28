#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <memory>

using namespace Catch::Clara;

// Test that default-constructed ExeName has a default name
TEST(ExeNameTest_393, DefaultConstructorHasDefaultName_393) {
    ExeName exeName;
    // The default name should be "<executable>" based on the known implementation
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test that ExeName constructed with a string reference has the default name initially
TEST(ExeNameTest_393, StringRefConstructorHasDefaultName_393) {
    std::string ref;
    ExeName exeName(ref);
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test that set() updates the name
TEST(ExeNameTest_393, SetUpdatesName_393) {
    ExeName exeName;
    auto result = exeName.set("my_program");
    EXPECT_EQ(exeName.name(), "my_program");
}

// Test that set() with empty string updates the name to empty
TEST(ExeNameTest_393, SetEmptyStringUpdatesName_393) {
    ExeName exeName;
    auto result = exeName.set("");
    EXPECT_EQ(exeName.name(), "");
}

// Test that set() with a path-like name works
TEST(ExeNameTest_393, SetWithPathLikeName_393) {
    ExeName exeName;
    exeName.set("/usr/bin/my_program");
    EXPECT_EQ(exeName.name(), "/usr/bin/my_program");
}

// Test that set() can be called multiple times
TEST(ExeNameTest_393, SetCanBeCalledMultipleTimes_393) {
    ExeName exeName;
    exeName.set("first");
    EXPECT_EQ(exeName.name(), "first");
    exeName.set("second");
    EXPECT_EQ(exeName.name(), "second");
    exeName.set("third");
    EXPECT_EQ(exeName.name(), "third");
}

// Test that name() returns a const reference
TEST(ExeNameTest_393, NameReturnsConstReference_393) {
    ExeName exeName;
    const std::string& nameRef = exeName.name();
    EXPECT_EQ(nameRef, "<executable>");
    exeName.set("updated");
    // After set, the reference should reflect the new value since it points to the shared string
    EXPECT_EQ(nameRef, "updated");
}

// Test that ExeName constructed with string ref updates the ref on set
TEST(ExeNameTest_393, StringRefConstructorUpdatesRefOnSet_393) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("new_name");
    // The bound reference should be updated
    EXPECT_EQ(ref, "new_name");
}

// Test with special characters in name
TEST(ExeNameTest_393, SetWithSpecialCharacters_393) {
    ExeName exeName;
    exeName.set("my program (v2.0) [test]");
    EXPECT_EQ(exeName.name(), "my program (v2.0) [test]");
}

// Test with very long name
TEST(ExeNameTest_393, SetWithVeryLongName_393) {
    ExeName exeName;
    std::string longName(10000, 'a');
    exeName.set(longName);
    EXPECT_EQ(exeName.name(), longName);
}

// Test copy behavior - two ExeName objects sharing state
TEST(ExeNameTest_393, CopySharesState_393) {
    ExeName exeName1;
    ExeName exeName2 = exeName1;
    // Both should have the same default name
    EXPECT_EQ(exeName1.name(), exeName2.name());
}

// Test with lambda constructor
TEST(ExeNameTest_393, LambdaConstructorHasDefaultName_393) {
    std::string captured;
    ExeName exeName([&captured](const std::string& name) {
        captured = name;
        return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseState::Matched);
    });
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test set with Windows-style path
TEST(ExeNameTest_393, SetWithWindowsPath_393) {
    ExeName exeName;
    exeName.set("C:\\Program Files\\app.exe");
    EXPECT_EQ(exeName.name(), "C:\\Program Files\\app.exe");
}

// Test set with unicode-like characters
TEST(ExeNameTest_393, SetWithUnicodeCharacters_393) {
    ExeName exeName;
    exeName.set("程序");
    EXPECT_EQ(exeName.name(), "程序");
}
