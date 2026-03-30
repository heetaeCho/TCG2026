#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"

// Mock the BasicIo class for testing purposes
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(void, close, (), (override));
};

// Test Fixture for IoCloser
class IoCloserTest_60 : public ::testing::Test {
protected:
    MockBasicIo mockBasicIo;
    Exiv2::IoCloser* ioCloser;

    void SetUp() override {
        ioCloser = new Exiv2::IoCloser(mockBasicIo);
    }

    void TearDown() override {
        delete ioCloser;
    }
};

// Test for normal operation - ensuring close() is called in destructor
TEST_F(IoCloserTest_60, DestructorCallsClose_60) {
    // Set up the expectation that close() will be called during the destruction
    EXPECT_CALL(mockBasicIo, close()).Times(1);

    // Destroying IoCloser should invoke close on the mock
    delete ioCloser;
}

// Test constructor and destructor
TEST_F(IoCloserTest_60, ConstructorDestructor_60) {
    // Ensure the object can be created and destroyed without issues
    Exiv2::IoCloser* testIoCloser = new Exiv2::IoCloser(mockBasicIo);
    EXPECT_CALL(mockBasicIo, close()).Times(1);
    delete testIoCloser;
}

// Test close function directly
TEST_F(IoCloserTest_60, CloseFunctionCalled_60) {
    // Set up the expectation that close() will be called on the mock
    EXPECT_CALL(mockBasicIo, close()).Times(1);

    // Call the close function manually
    ioCloser->close();
}

// Test for exceptional cases - handle non-ideal situations
TEST_F(IoCloserTest_60, CloseHandlesExceptions_60) {
    // If close() throws an exception, we should be able to handle it gracefully
    EXPECT_CALL(mockBasicIo, close()).WillOnce([]() {
        throw std::runtime_error("close failed");
    });

    try {
        ioCloser->close();
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "close failed");
    }
}