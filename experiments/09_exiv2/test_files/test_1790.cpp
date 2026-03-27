#include <gtest/gtest.h>

#include "crwimage_int.hpp"



namespace Exiv2 {

namespace Internal {



class CiffComponentTest : public ::testing::Test {

protected:

    CrwDirs crwDirs;

    uint16_t testTagId = 0x1234;

    std::unique_ptr<CiffComponent> component;

};



TEST_F(CiffComponentTest_1790, AddValidTag_ReturnsUniquePtr_1790) {

    component.reset(new CiffComponent());

    const auto& result = component->add(crwDirs, testTagId);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(CiffComponentTest_1790, AddZeroTagId_ReturnsNonEmptyUniquePtr_1790) {

    uint16_t zeroTagId = 0;

    component.reset(new CiffComponent());

    const auto& result = component->add(crwDirs, zeroTagId);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(CiffComponentTest_1790, AddMaxTagId_ReturnsUniquePtr_1790) {

    uint16_t maxTagId = std::numeric_limits<uint16_t>::max();

    component.reset(new CiffComponent());

    const auto& result = component->add(crwDirs, maxTagId);

    EXPECT_NE(result.get(), nullptr);

}



} // namespace Internal

} // namespace Exiv2
