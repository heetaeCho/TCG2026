#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>
#include <string>

// We need to include the Poppler Qt5 form header that declares setNSSPasswordCallback
// Since we're testing the public interface of Poppler::setNSSPasswordCallback
#include "poppler-form.h"

namespace {

class SetNSSPasswordCallbackTest_1380 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that calling setNSSPasswordCallback with a valid callback does not crash
TEST_F(SetNSSPasswordCallbackTest_1380, CallWithValidCallback_1380) {
    std::function<char*(const char*)> callback = [](const char* prompt) -> char* {
        // Return a copy of a test password
        char* pwd = new char[5];
        strcpy(pwd, "test");
        return pwd;
    };
    
    // Should not throw or crash
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback));
}

// Test that calling setNSSPasswordCallback with a nullptr/empty function does not crash
TEST_F(SetNSSPasswordCallbackTest_1380, CallWithNullCallback_1380) {
    std::function<char*(const char*)> nullCallback = nullptr;
    
    // Should not throw or crash even with a null callback
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(nullCallback));
}

// Test that calling setNSSPasswordCallback with a lambda that returns nullptr does not crash
TEST_F(SetNSSPasswordCallbackTest_1380, CallWithNullReturningCallback_1380) {
    std::function<char*(const char*)> callback = [](const char*) -> char* {
        return nullptr;
    };
    
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback));
}

// Test that calling setNSSPasswordCallback multiple times does not crash
TEST_F(SetNSSPasswordCallbackTest_1380, CallMultipleTimes_1380) {
    std::function<char*(const char*)> callback1 = [](const char*) -> char* {
        return nullptr;
    };
    
    std::function<char*(const char*)> callback2 = [](const char*) -> char* {
        char* pwd = new char[9];
        strcpy(pwd, "password");
        return pwd;
    };
    
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback1));
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback2));
    // Reset to null
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(std::function<char*(const char*)>(nullptr)));
}

// Test that calling setNSSPasswordCallback with a capturing lambda works
TEST_F(SetNSSPasswordCallbackTest_1380, CallWithCapturingLambda_1380) {
    std::string storedPassword = "mySecret";
    
    std::function<char*(const char*)> callback = [&storedPassword](const char*) -> char* {
        char* pwd = new char[storedPassword.size() + 1];
        strcpy(pwd, storedPassword.c_str());
        return pwd;
    };
    
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback));
}

// Test replacing callback with another callback
TEST_F(SetNSSPasswordCallbackTest_1380, ReplaceCallback_1380) {
    bool firstCallbackSet = false;
    bool secondCallbackSet = false;
    
    std::function<char*(const char*)> callback1 = [&firstCallbackSet](const char*) -> char* {
        firstCallbackSet = true;
        return nullptr;
    };
    
    std::function<char*(const char*)> callback2 = [&secondCallbackSet](const char*) -> char* {
        secondCallbackSet = true;
        return nullptr;
    };
    
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback1));
    EXPECT_NO_THROW(Poppler::setNSSPasswordCallback(callback2));
}

} // namespace
