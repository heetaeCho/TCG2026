#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/internal/catch_context.hpp"

// We need access to getMutableRegistryHub and the registry
// Include the amalgamated header or relevant headers
#include "catch2/catch_test_macros.hpp"

namespace {

// A simple test invoker implementation for testing purposes
class DummyTestInvoker : public Catch::ITestInvoker {
public:
    void invoke() const override {
        // Do nothing
    }
};

// Test fixture for AutoReg tests
class AutoRegTest_1115 : public ::testing::Test {
protected:
    void SetUp() override {
        // Nothing specific needed
    }

    void TearDown() override {
        // Nothing specific needed
    }
};

// Test that AutoReg can be constructed with valid parameters without throwing
TEST_F(AutoRegTest_1115, ConstructWithValidParameters_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 42),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("TestName", "[tag]")
        );
    });
}

// Test AutoReg with empty class/method name
TEST_F(AutoRegTest_1115, ConstructWithEmptyClassName_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 1),
            Catch::StringRef(""),
            Catch::NameAndTags("TestName", "[tag]")
        );
    });
}

// Test AutoReg with empty test name
TEST_F(AutoRegTest_1115, ConstructWithEmptyTestName_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 10),
            Catch::StringRef("SomeClass"),
            Catch::NameAndTags("", "")
        );
    });
}

// Test AutoReg with empty tags
TEST_F(AutoRegTest_1115, ConstructWithEmptyTags_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 100),
            Catch::StringRef("MyClass"),
            Catch::NameAndTags("MyTest", "")
        );
    });
}

// Test AutoReg with nullptr invoker - boundary case
TEST_F(AutoRegTest_1115, ConstructWithNullptrInvoker_1115) {
    // Passing a null unique_ptr; the constructor is noexcept so it should not throw
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(nullptr),
            Catch::SourceLineInfo("test_file.cpp", 5),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("TestName", "[tag]")
        );
    });
}

// Test AutoReg with large line number - boundary
TEST_F(AutoRegTest_1115, ConstructWithLargeLineNumber_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 999999),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("LargeLineTest", "[boundary]")
        );
    });
}

// Test AutoReg with line number zero - boundary
TEST_F(AutoRegTest_1115, ConstructWithZeroLineNumber_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 0),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("ZeroLineTest", "[boundary]")
        );
    });
}

// Test AutoReg with multiple tags
TEST_F(AutoRegTest_1115, ConstructWithMultipleTags_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 25),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("MultiTagTest", "[tag1][tag2][tag3]")
        );
    });
}

// Test AutoReg with class::method style classOrMethod string
TEST_F(AutoRegTest_1115, ConstructWithClassMethodFormat_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("another_file.cpp", 77),
            Catch::StringRef("MyNamespace::MyClass"),
            Catch::NameAndTags("MethodStyleTest", "[unit]")
        );
    });
}

// Test that AutoReg is non-copyable (compile-time check - if it compiles, it fails)
// This is verified by the NonCopyable base class; we just confirm the type exists
TEST_F(AutoRegTest_1115, IsNonCopyable_1115) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::AutoReg>::value);
    EXPECT_FALSE(std::is_copy_assignable<Catch::AutoReg>::value);
}

// Test that AutoReg is non-movable
TEST_F(AutoRegTest_1115, IsNonMovable_1115) {
    EXPECT_FALSE(std::is_move_constructible<Catch::AutoReg>::value);
    EXPECT_FALSE(std::is_move_assignable<Catch::AutoReg>::value);
}

// Test AutoReg with special characters in test name
TEST_F(AutoRegTest_1115, ConstructWithSpecialCharsInName_1115) {
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker()),
            Catch::SourceLineInfo("test_file.cpp", 33),
            Catch::StringRef("TestClass"),
            Catch::NameAndTags("Test with spaces & special chars!@#$%", "[special]")
        );
    });
}

// Test AutoReg constructor is noexcept
TEST_F(AutoRegTest_1115, ConstructorIsNoexcept_1115) {
    // The constructor is declared noexcept; verify it handles exceptions internally
    auto invoker = Catch::Detail::unique_ptr<Catch::ITestInvoker>(new DummyTestInvoker());
    Catch::SourceLineInfo lineInfo("file.cpp", 1);
    Catch::StringRef classOrMethod("Class");
    Catch::NameAndTags nameAndTags("Name", "[tag]");

    // This should not throw even if internal registration has issues
    EXPECT_NO_THROW({
        Catch::AutoReg autoreg(
            std::move(invoker),
            lineInfo,
            classOrMethod,
            nameAndTags
        );
    });
}

// Test NameAndTags default construction
TEST_F(AutoRegTest_1115, NameAndTagsDefaultConstruction_1115) {
    Catch::NameAndTags nat;
    EXPECT_TRUE(nat.tags.empty());
}

// Test NameAndTags with name and tags
TEST_F(AutoRegTest_1115, NameAndTagsWithValues_1115) {
    Catch::NameAndTags nat("TestName", "[mytag]");
    EXPECT_EQ(nat.tags, Catch::StringRef("[mytag]"));
}

// Test SourceLineInfo construction and equality
TEST_F(AutoRegTest_1115, SourceLineInfoEquality_1115) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 10);
    EXPECT_TRUE(a == b);
}

// Test SourceLineInfo less than comparison
TEST_F(AutoRegTest_1115, SourceLineInfoLessThan_1115) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

} // namespace
