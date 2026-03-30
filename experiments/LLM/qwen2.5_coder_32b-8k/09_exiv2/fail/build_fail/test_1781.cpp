#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class CiffComponentTest_1781 : public ::testing::Test {

protected:

    CiffComponent component{0x0001, 0x0002};

};



TEST_F(CiffComponentTest_1781, PrintOutputVerification_1781) {

    std::ostringstream os;

    component.print(os, littleEndian, "prefix");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CiffComponentTest_1781, SetAndGetDir_1781) {

    component.setDir(0x0003);

    EXPECT_EQ(component.dir(), 0x0003);

}



TEST_F(CiffComponentTest_1781, GetTag_1781) {

    EXPECT_EQ(component.tag(), 0x0001);

}



TEST_F(CiffComponentTest_1781, SetAndGetOffset_1781) {

    component.setOffset(100);

    EXPECT_EQ(component.offset(), 100);

}



TEST_F(CiffComponentTest_1781, SetAndGetSize_1781) {

    component.setSize(200);

    EXPECT_EQ(component.size(), 200);

}



TEST_F(CiffComponentTest_1781, EmptyCheckInitially_1781) {

    EXPECT_TRUE(component.empty());

}



TEST_F(CiffComponentTest_1781, TypeIdStaticFunction_1781) {

    auto typeId = CiffComponent::typeId(0x0001);

    EXPECT_NE(typeId, TypeId::invalidTypeId); // Assuming valid type ID is not invalid

}



TEST_F(CiffComponentTest_1781, DataLocationStaticFunction_1781) {

    auto dataLocId = CiffComponent::dataLocation(0x0001);

    EXPECT_NE(dataLocId, DataLocId::invalidDataLocId); // Assuming valid data location ID is not invalid

}



TEST_F(CiffComponentTest_1781, BoundaryConditionTagAndDir_1781) {

    CiffComponent boundaryComponent{0xFFFF, 0xFFFF};

    EXPECT_EQ(boundaryComponent.tag(), 0xFFFF);

    EXPECT_EQ(boundaryComponent.dir(), 0xFFFF);

}
