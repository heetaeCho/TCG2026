#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

// Test fixture for ExeName tests
class ExeNameTest_1068 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction - name should be "<executable>"
TEST_F(ExeNameTest_1068, DefaultConstructor_HasDefaultName_1068) {
    ExeName exeName;
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test construction with string reference
TEST_F(ExeNameTest_1068, StringRefConstructor_HasDefaultName_1068) {
    std::string ref;
    ExeName exeName(ref);
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test set with a valid name
TEST_F(ExeNameTest_1068, Set_ValidName_UpdatesName_1068) {
    ExeName exeName;
    auto result = exeName.set("myapp");
    EXPECT_EQ(exeName.name(), "myapp");
}

// Test set with empty string
TEST_F(ExeNameTest_1068, Set_EmptyString_UpdatesName_1068) {
    ExeName exeName;
    auto result = exeName.set("");
    EXPECT_EQ(exeName.name(), "");
}

// Test set updates the name multiple times
TEST_F(ExeNameTest_1068, Set_MultipleTimes_KeepsLatestName_1068) {
    ExeName exeName;
    exeName.set("first");
    EXPECT_EQ(exeName.name(), "first");
    exeName.set("second");
    EXPECT_EQ(exeName.name(), "second");
    exeName.set("third");
    EXPECT_EQ(exeName.name(), "third");
}

// Test construction with lambda
TEST_F(ExeNameTest_1068, LambdaConstructor_HasDefaultName_1068) {
    std::string capturedName;
    ExeName exeName([&capturedName](const std::string& name) {
        capturedName = name;
        return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseResultType::Matched);
    });
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test construction with string ref and set updates ref
TEST_F(ExeNameTest_1068, StringRefConstructor_SetUpdatesRef_1068) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("updated_name");
    EXPECT_EQ(exeName.name(), "updated_name");
    EXPECT_EQ(ref, "updated_name");
}

// Test set with a name containing spaces
TEST_F(ExeNameTest_1068, Set_NameWithSpaces_1068) {
    ExeName exeName;
    exeName.set("my app name");
    EXPECT_EQ(exeName.name(), "my app name");
}

// Test set with a name containing special characters
TEST_F(ExeNameTest_1068, Set_NameWithSpecialChars_1068) {
    ExeName exeName;
    exeName.set("/usr/bin/my-app.exe");
    EXPECT_EQ(exeName.name(), "/usr/bin/my-app.exe");
}

// Test set with a very long name
TEST_F(ExeNameTest_1068, Set_VeryLongName_1068) {
    ExeName exeName;
    std::string longName(1000, 'a');
    exeName.set(longName);
    EXPECT_EQ(exeName.name(), longName);
}

// Test name() returns const reference
TEST_F(ExeNameTest_1068, Name_ReturnsConstReference_1068) {
    ExeName exeName;
    const std::string& nameRef = exeName.name();
    EXPECT_EQ(nameRef, "<executable>");
    exeName.set("changed");
    // The reference should reflect the change since it's to the internal string
    EXPECT_EQ(nameRef, "changed");
}

// Test lambda constructor invokes lambda on set
TEST_F(ExeNameTest_1068, LambdaConstructor_SetInvokesLambda_1068) {
    std::string capturedValue;
    ExeName exeName([&capturedValue](const std::string& name) {
        capturedValue = name;
        return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseResultType::Matched);
    });
    exeName.set("test_exe");
    EXPECT_EQ(exeName.name(), "test_exe");
    EXPECT_EQ(capturedValue, "test_exe");
}

// Test copy behavior - two ExeName instances from default
TEST_F(ExeNameTest_1068, CopyConstructor_IndependentNames_1068) {
    ExeName exeName1;
    exeName1.set("original");
    ExeName exeName2 = exeName1;
    EXPECT_EQ(exeName2.name(), "original");
}

// Test set with name containing null-like characters in string
TEST_F(ExeNameTest_1068, Set_NameWithEmbeddedNull_1068) {
    ExeName exeName;
    std::string nameWithNull = "app";
    nameWithNull += '\0';
    nameWithNull += "name";
    exeName.set(nameWithNull);
    EXPECT_EQ(exeName.name(), nameWithNull);
}
