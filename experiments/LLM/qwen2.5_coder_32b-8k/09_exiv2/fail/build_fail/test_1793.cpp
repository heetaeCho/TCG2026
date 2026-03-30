#include <gtest/gtest.h>

#include "crwimage_int.hpp"



namespace Exiv2 {

namespace Internal {



class CiffComponentTest_1793 : public ::testing::Test {

protected:

    CrwDirs crwDirs;

    uint16_t tagId = 0x1234;

    CiffComponent component;

};



TEST_F(CiffComponentTest_1793, RemoveExistingTag_1793) {

    // Assuming add functionality works correctly

    component.add(crwDirs, tagId);

    EXPECT_NO_THROW(component.remove(crwDirs, tagId));

}



TEST_F(CiffComponentTest_1793, RemoveNonExistentTag_1793) {

    // No tag added, should not throw or have any observable effect

    EXPECT_NO_THROW(component.remove(crwDirs, tagId));

}



TEST_F(CiffComponentTest_1793, BoundaryCondition_MaxTagId_1793) {

    uint16_t maxTagId = std::numeric_limits<uint16_t>::max();

    component.add(crwDirs, maxTagId);

    EXPECT_NO_THROW(component.remove(crwDirs, maxTagId));

}



TEST_F(CiffComponentTest_1793, BoundaryCondition_MinTagId_1793) {

    uint16_t minTagId = std::numeric_limits<uint16_t>::min();

    component.add(crwDirs, minTagId);

    EXPECT_NO_THROW(component.remove(crwDirs, minTagId));

}



TEST_F(CiffComponentTest_1793, RemoveAfterMultipleAdds_1793) {

    uint16_t tagId1 = 0x1234;

    uint16_t tagId2 = 0x5678;

    component.add(crwDirs, tagId1);

    component.add(crwDirs, tagId2);

    EXPECT_NO_THROW(component.remove(crwDirs, tagId1));

    EXPECT_NO_THROW(component.remove(crwDirs, tagId2));

}



TEST_F(CiffComponentTest_1793, RemoveSameTagMultipleTimes_1793) {

    component.add(crwDirs, tagId);

    EXPECT_NO_THROW(component.remove(crwDirs, tagId));

    EXPECT_NO_THROW(component.remove(crwDirs, tagId)); // Should not throw even if the tag is already removed

}



}  // namespace Internal

}  // namespace Exiv2
