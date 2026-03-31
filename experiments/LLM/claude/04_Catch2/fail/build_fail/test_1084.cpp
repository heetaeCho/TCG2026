#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_stringref.hpp"

// A minimal listener implementation to use as template parameter
class TestListener_1084 : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;
};

class ListenerRegistrarTest_1084 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ListenerRegistrar can be constructed with a string literal name
TEST_F(ListenerRegistrarTest_1084, ConstructWithStringLiteral_1084) {
    // Should not throw when constructing with a valid listener name
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar("TestListener_1084_literal");
    });
}

// Test that ListenerRegistrar can be constructed with a StringRef
TEST_F(ListenerRegistrarTest_1084, ConstructWithStringRef_1084) {
    Catch::StringRef name("TestListener_1084_stringref");
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar(name);
    });
}

// Test that ListenerRegistrar can be constructed with an std::string based StringRef
TEST_F(ListenerRegistrarTest_1084, ConstructWithStdString_1084) {
    std::string nameStr = "TestListener_1084_stdstring";
    Catch::StringRef name(nameStr);
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar(name);
    });
}

// Test construction with an empty name
TEST_F(ListenerRegistrarTest_1084, ConstructWithEmptyName_1084) {
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar("");
    });
}

// Test construction with a single character name
TEST_F(ListenerRegistrarTest_1084, ConstructWithSingleCharName_1084) {
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar("X");
    });
}

// Test construction with a long name
TEST_F(ListenerRegistrarTest_1084, ConstructWithLongName_1084) {
    std::string longName(1000, 'A');
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar(Catch::StringRef(longName));
    });
}

// Test construction with a name containing special characters
TEST_F(ListenerRegistrarTest_1084, ConstructWithSpecialCharsName_1084) {
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar("test-listener_1084.special@chars!");
    });
}

// Test that multiple registrars with different names can coexist
TEST_F(ListenerRegistrarTest_1084, MultipleRegistrarsWithDifferentNames_1084) {
    EXPECT_NO_THROW({
        static Catch::ListenerRegistrar<TestListener_1084> registrar1("MultiListener1_1084");
        static Catch::ListenerRegistrar<TestListener_1084> registrar2("MultiListener2_1084");
    });
}
