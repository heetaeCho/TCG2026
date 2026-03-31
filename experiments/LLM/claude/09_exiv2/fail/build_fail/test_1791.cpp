#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <vector>
#include <memory>

// Include necessary headers from exiv2
#include "crwimage_int.hpp"
#include "error.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffComponentTest_1791 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doAdd throws an exception as it is not supported
TEST_F(CiffComponentTest_1791, DoAddThrowsError_1791) {
    CiffComponent component;
    CrwDirs crwDirs;
    uint16_t crwTagId = 0;

    EXPECT_THROW(
        {
            component.doAdd(crwDirs, crwTagId);
        },
        Error
    );
}

// Test that doAdd throws with a specific error code
TEST_F(CiffComponentTest_1791, DoAddThrowsFunctionNotSupportedError_1791) {
    CiffComponent component;
    CrwDirs crwDirs;
    uint16_t crwTagId = 0;

    try {
        component.doAdd(crwDirs, crwTagId);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerFunctionNotSupported);
    } catch (...) {
        FAIL() << "Expected Error but caught different exception";
    }
}

// Test doAdd with various tag IDs - all should throw
TEST_F(CiffComponentTest_1791, DoAddThrowsForAnyTagId_1791) {
    CiffComponent component;
    CrwDirs crwDirs;

    // Test with minimum uint16_t value
    EXPECT_THROW(component.doAdd(crwDirs, 0), Error);

    // Test with maximum uint16_t value
    EXPECT_THROW(component.doAdd(crwDirs, 0xFFFF), Error);

    // Test with mid-range value
    EXPECT_THROW(component.doAdd(crwDirs, 0x8000), Error);

    // Test with another arbitrary value
    EXPECT_THROW(component.doAdd(crwDirs, 42), Error);
}

// Test doAdd with non-empty CrwDirs - should still throw
TEST_F(CiffComponentTest_1791, DoAddThrowsWithNonEmptyDirs_1791) {
    CiffComponent component;
    CrwDirs crwDirs;
    // Add some entries to crwDirs if possible
    crwDirs.push_back(std::make_pair(0x0001, 0x0002));

    EXPECT_THROW(component.doAdd(crwDirs, 100), Error);
}

// Test that the error message contains relevant information
TEST_F(CiffComponentTest_1791, DoAddErrorMessageContainsFunctionName_1791) {
    CiffComponent component;
    CrwDirs crwDirs;
    uint16_t crwTagId = 0;

    try {
        component.doAdd(crwDirs, crwTagId);
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        std::string what = e.what();
        // The error should reference "CiffEntry::doAdd" based on the implementation
        EXPECT_TRUE(what.find("CiffEntry::doAdd") != std::string::npos ||
                     what.find("not supported") != std::string::npos ||
                     what.find("Not supported") != std::string::npos)
            << "Error message was: " << what;
    } catch (...) {
        FAIL() << "Expected Error but caught different exception";
    }
}

// Test that doAdd can be called multiple times and always throws
TEST_F(CiffComponentTest_1791, DoAddAlwaysThrows_1791) {
    CiffComponent component;
    CrwDirs crwDirs;

    for (int i = 0; i < 10; ++i) {
        EXPECT_THROW(component.doAdd(crwDirs, static_cast<uint16_t>(i)), Error);
    }
}
