#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_string_ref.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// We need to test the TypedListenerFactory's getName() method.
// Since TypedListenerFactory is a template class nested inside ListenerRegistrar,
// we need a concrete listener type to instantiate it.

// A minimal listener implementation for testing purposes
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"

namespace {

// A simple test listener that we can use to instantiate TypedListenerFactory
class TestListener567 : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    static std::string getDescription() {
        return "Test listener for unit tests";
    }
};

} // anonymous namespace

class TypedListenerFactoryTest_567 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TypedListenerFactoryTest_567, GetNameReturnsCorrectName_567) {
    // Create a TypedListenerFactory with a known name
    Catch::StringRef listenerName("MyTestListener");
    
    // Use ListenerRegistrar's TypedListenerFactory
    // TypedListenerFactory is instantiated with the listener type
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(listenerName);
    
    Catch::StringRef result = factory.getName();
    
    EXPECT_EQ(result, listenerName);
}

TEST_F(TypedListenerFactoryTest_567, GetNameReturnsEmptyForEmptyName_567) {
    Catch::StringRef emptyName("");
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(emptyName);
    
    Catch::StringRef result = factory.getName();
    
    EXPECT_EQ(result, Catch::StringRef(""));
}

TEST_F(TypedListenerFactoryTest_567, GetNamePreservesExactString_567) {
    Catch::StringRef name("some_complex-listener.name/v2");
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(name);
    
    Catch::StringRef result = factory.getName();
    
    EXPECT_EQ(result, name);
}

TEST_F(TypedListenerFactoryTest_567, GetNameWithLongString_567) {
    std::string longName(256, 'a');
    Catch::StringRef name(longName.c_str());
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(name);
    
    Catch::StringRef result = factory.getName();
    
    EXPECT_EQ(result, name);
}

TEST_F(TypedListenerFactoryTest_567, GetNameCalledMultipleTimesReturnsSameValue_567) {
    Catch::StringRef listenerName("ConsistentListener");
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(listenerName);
    
    Catch::StringRef result1 = factory.getName();
    Catch::StringRef result2 = factory.getName();
    Catch::StringRef result3 = factory.getName();
    
    EXPECT_EQ(result1, listenerName);
    EXPECT_EQ(result2, listenerName);
    EXPECT_EQ(result3, listenerName);
}

TEST_F(TypedListenerFactoryTest_567, GetNameWithSpecialCharacters_567) {
    Catch::StringRef name("listener with spaces & special!@#$%");
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(name);
    
    Catch::StringRef result = factory.getName();
    
    EXPECT_EQ(result, name);
}

TEST_F(TypedListenerFactoryTest_567, TwoDifferentFactoriesReturnDifferentNames_567) {
    Catch::StringRef name1("Listener1");
    Catch::StringRef name2("Listener2");
    
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory1(name1);
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory2(name2);
    
    EXPECT_EQ(factory1.getName(), name1);
    EXPECT_EQ(factory2.getName(), name2);
    EXPECT_NE(factory1.getName(), factory2.getName());
}

TEST_F(TypedListenerFactoryTest_567, GetDescriptionReturnsNonEmpty_567) {
    Catch::StringRef name("DescListener");
    Catch::ListenerRegistrar::TypedListenerFactory<TestListener567> factory(name);
    
    std::string description = factory.getDescription();
    
    // The description should be obtainable without crashing
    // It should return the static getDescription from TestListener567
    EXPECT_FALSE(description.empty());
}
