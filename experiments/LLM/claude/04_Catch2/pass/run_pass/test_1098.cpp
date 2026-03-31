#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

// Test fixture
class ExeNameTest_1098 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor - name should be "<executable>"
TEST_F(ExeNameTest_1098, DefaultConstructorSetsDefaultName_1098) {
    std::string ref;
    ExeName exeName(ref);
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test that name() returns default name for default-constructed ExeName
TEST_F(ExeNameTest_1098, NameReturnsDefaultExecutable_1098) {
    std::string ref;
    ExeName exeName(ref);
    std::string const& name = exeName.name();
    EXPECT_EQ(name, "<executable>");
}

// Test set() with a valid name
TEST_F(ExeNameTest_1098, SetValidNameUpdatesName_1098) {
    std::string ref;
    ExeName exeName(ref);
    auto result = exeName.set("myapp");
    EXPECT_EQ(exeName.name(), "myapp");
}

// Test set() with empty string
TEST_F(ExeNameTest_1098, SetEmptyNameUpdatesName_1098) {
    std::string ref;
    ExeName exeName(ref);
    auto result = exeName.set("");
    EXPECT_EQ(exeName.name(), "");
}

// Test set() updates the bound reference
TEST_F(ExeNameTest_1098, SetUpdatesBoundReference_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("testexe");
    EXPECT_EQ(ref, "testexe");
}

// Test set() with a name containing path separators
TEST_F(ExeNameTest_1098, SetNameWithPathSeparators_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("/usr/bin/myapp");
    // The name should be stored (possibly stripped of path)
    // We just verify it doesn't crash and returns something
    EXPECT_FALSE(exeName.name().empty());
}

// Test set() called multiple times
TEST_F(ExeNameTest_1098, SetCalledMultipleTimesUpdatesCorrectly_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("first");
    EXPECT_EQ(exeName.name(), "first");
    exeName.set("second");
    EXPECT_EQ(exeName.name(), "second");
    exeName.set("third");
    EXPECT_EQ(exeName.name(), "third");
}

// Test that bound reference reflects changes after multiple sets
TEST_F(ExeNameTest_1098, BoundReferenceReflectsMultipleSets_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("alpha");
    EXPECT_EQ(ref, "alpha");
    exeName.set("beta");
    EXPECT_EQ(ref, "beta");
}

// Test set() with a very long name
TEST_F(ExeNameTest_1098, SetVeryLongName_1098) {
    std::string ref;
    ExeName exeName(ref);
    std::string longName(1000, 'x');
    exeName.set(longName);
    EXPECT_FALSE(exeName.name().empty());
}

// Test set() with special characters
TEST_F(ExeNameTest_1098, SetNameWithSpecialCharacters_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("my-app_v2.0");
    EXPECT_FALSE(exeName.name().empty());
}

// Test name() returns const reference
TEST_F(ExeNameTest_1098, NameReturnsConstReference_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("testapp");
    const std::string& name1 = exeName.name();
    const std::string& name2 = exeName.name();
    // Both references should point to the same string
    EXPECT_EQ(&name1, &name2);
}

// Test construction with pre-populated reference string
TEST_F(ExeNameTest_1098, ConstructWithPrePopulatedRef_1098) {
    std::string ref = "initial_value";
    ExeName exeName(ref);
    // Default name should still be "<executable>" regardless of ref's initial value
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test set with Windows-style path
TEST_F(ExeNameTest_1098, SetWindowsStylePath_1098) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("C:\\Program Files\\app.exe");
    EXPECT_FALSE(exeName.name().empty());
}
