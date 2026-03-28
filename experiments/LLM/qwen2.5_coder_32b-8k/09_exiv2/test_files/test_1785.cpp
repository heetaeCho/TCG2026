#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/crwimage_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;



TEST_F(CiffComponentTest_1785, DataLocation_ReturnsValueData_ForTagWithMask0x0000_1785) {

    CiffComponent component;

    EXPECT_EQ(component.dataLocation(0x0000), DataLocId::valueData);

}



TEST_F(CiffComponentTest_1785, DataLocation_ReturnsDirectoryData_ForTagWithMask0x4000_1785) {

    CiffComponent component;

    EXPECT_EQ(component.dataLocation(0x4000), DataLocId::directoryData);

}



TEST_F(CiffComponentTest_1785, DataLocation_ThrowsError_ForTagWithOtherMasks_1785) {

    CiffComponent component;

    EXPECT_THROW({

        component.dataLocation(0xC000);

    }, Exiv2::Error);



    EXPECT_THROW({

        component.dataLocation(0x8000);

    }, Exiv2::Error);



    EXPECT_THROW({

        component.dataLocation(0xA000);

    }, Exiv2::Error);

}



TEST_F(CiffComponentTest_1785, DataLocation_ReturnsValueData_ForTagWithinRange0x0000To0x3FFF_1785) {

    CiffComponent component;

    EXPECT_EQ(component.dataLocation(0x3FFF), DataLocId::valueData);

}



TEST_F(CiffComponentTest_1785, DataLocation_ReturnsDirectoryData_ForTagWithinRange0x4000To0x7FFF_1785) {

    CiffComponent component;

    EXPECT_EQ(component.dataLocation(0x4000), DataLocId::directoryData);

}



TEST_F(CiffComponentTest_1785, DataLocation_ThrowsError_ForTagWithinRange0x8000To0xFFFF_1785) {

    CiffComponent component;

    EXPECT_THROW({

        component.dataLocation(0x8000);

    }, Exiv2::Error);



    EXPECT_THROW({

        component.dataLocation(0xC000);

    }, Exiv2::Error);



    EXPECT_THROW({

        component.dataLocation(0xFFFF);

    }, Exiv2::Error);

}
