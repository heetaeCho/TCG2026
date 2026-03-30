#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "crwimage_int.hpp"  // For CiffHeader, CiffComponent, and CrwMap

namespace Exiv2 {
namespace Internal {

class CiffHeaderTest : public ::testing::Test {
protected:
    CiffHeaderTest() : ciffHeader_() {}

    CiffHeader ciffHeader_;
};

// Normal operation tests

TEST_F(CiffHeaderTest, AddComponentTest_1792) {
    // Setup
    uint16_t crwTagId = 0x1234;
    uint16_t crwDir = 0x5678;
    DataBuf buf;

    // Expectation: add a component to the header
    EXPECT_CALL(ciffHeader_, add(crwTagId, crwDir, std::move(buf)))
        .Times(1);

    // Call the function under test
    ciffHeader_.add(crwTagId, crwDir, std::move(buf));
}

TEST_F(CiffHeaderTest, RemoveComponentTest_1793) {
    // Setup
    uint16_t crwTagId = 0x1234;
    uint16_t crwDir = 0x5678;

    // Expectation: remove the component
    EXPECT_CALL(ciffHeader_, remove(crwTagId, crwDir))
        .Times(1);

    // Call the function under test
    ciffHeader_.remove(crwTagId, crwDir);
}

// Boundary condition tests

TEST_F(CiffHeaderTest, RemoveComponentWhenNoRootDirTest_1794) {
    // Setup: Ensure pRootDir_ is nullptr (no root directory available)

    // Expectation: no interaction, as there is no root directory to remove the component
    EXPECT_CALL(ciffHeader_, remove(::testing::_, ::testing::_)).Times(0);

    // Call the function under test
    uint16_t crwTagId = 0x1234;
    uint16_t crwDir = 0x5678;
    ciffHeader_.remove(crwTagId, crwDir);
}

TEST_F(CiffHeaderTest, AddComponentWithEmptyDataBufTest_1795) {
    // Setup
    uint16_t crwTagId = 0x1234;
    uint16_t crwDir = 0x5678;
    DataBuf buf;  // Empty DataBuf

    // Expectation: no issue when adding an empty buffer
    EXPECT_CALL(ciffHeader_, add(crwTagId, crwDir, std::move(buf)))
        .Times(1);

    // Call the function under test
    ciffHeader_.add(crwTagId, crwDir, std::move(buf));
}

// Exceptional or error cases

TEST_F(CiffHeaderTest, RemoveComponentWithNullPointerTest_1796) {
    // Simulate a scenario where the pRootDir_ is a null pointer

    // Expectation: no removal due to a null pointer (no root directory)
    EXPECT_CALL(ciffHeader_, remove(::testing::_, ::testing::_)).Times(0);

    // Call the function under test
    uint16_t crwTagId = 0x1234;
    uint16_t crwDir = 0x5678;
    ciffHeader_.remove(crwTagId, crwDir);
}

// Verification of external interactions

TEST_F(CiffHeaderTest, VerifyCrwMapLoadStackInteractionTest_1797) {
    uint16_t crwDir = 0x5678;
    CrwDirs crwDirs;

    // Verify interaction with CrwMap::loadStack when calling add
    EXPECT_CALL(ciffHeader_, add(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([&](uint16_t tagId, uint16_t dir, DataBuf && buf){
            CrwMap::loadStack(crwDirs, crwDir);
        }));

    uint16_t crwTagId = 0x1234;
    DataBuf buf;
    ciffHeader_.add(crwTagId, crwDir, std::move(buf));
}

}  // namespace Internal
}  // namespace Exiv2