#include <gtest/gtest.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1763 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1763, DefaultConstructorInitializesTagAndDir_1763) {

    EXPECT_EQ(component.tag(), 0);

    EXPECT_EQ(component.dir(), 0);

}



TEST_F(CiffComponentTest_1763, ParameterizedConstructorSetsTagAndDir_1763) {

    CiffComponent component(0x4567, 0x89AB);

    EXPECT_EQ(component.tag(), 0x4567);

    EXPECT_EQ(component.dir(), 0x89AB);

}



TEST_F(CiffComponentTest_1763, TagIdReturnsLower15BitsOfTag_1763) {

    CiffComponent component(0xCDEF, 0x89AB);

    EXPECT_EQ(component.tagId(), 0x4DEF); // 0xCDEF & 0x3FFF = 0x4DEF

}



TEST_F(CiffComponentTest_1763, SetDirUpdatesDirectoryValue_1763) {

    component.setDir(0x1234);

    EXPECT_EQ(component.dir(), 0x1234);

}



TEST_F(CiffComponentTest_1763, TagReturnsInitialTagValue_1763) {

    CiffComponent component(0xABCD, 0x89AB);

    EXPECT_EQ(component.tag(), 0xABCD);

}



TEST_F(CiffComponentTest_1763, EmptyReturnsTrueInitially_1763) {

    EXPECT_TRUE(component.empty());

}



TEST_F(CiffComponentTest_1763, AddAndFindComponentWorkTogether_1763) {

    auto newComponent = std::make_unique<CiffComponent>(0x4567, 0x89AB);

    component.add(std::move(newComponent));

    CiffComponent* foundComponent = component.findComponent(0x4567, 0x89AB);

    EXPECT_NE(foundComponent, nullptr);

    EXPECT_EQ(foundComponent->tag(), 0x4567);

}



TEST_F(CiffComponentTest_1763, RemoveComponentRemovesCorrectly_1763) {

    auto newComponent = std::make_unique<CiffComponent>(0x4567, 0x89AB);

    component.add(std::move(newComponent));

    component.remove(component.dir(), 0x4567);

    CiffComponent* foundComponent = component.findComponent(0x4567, 0x89AB);

    EXPECT_EQ(foundComponent, nullptr);

}



TEST_F(CiffComponentTest_1763, ReadDoesNotCrashWithNullData_1763) {

    component.read(nullptr, 0, 0, littleEndian);

    // No assertion as the function should not crash

}



TEST_F(CiffComponentTest_1763, WriteReturnsZeroForEmptyComponent_1763) {

    Blob blob;

    size_t result = component.write(blob, littleEndian, 0);

    EXPECT_EQ(result, 0);

}



TEST_F(CiffComponentTest_1763, WriteValueDataReturnsZeroForEmptyComponent_1763) {

    Blob blob;

    size_t result = component.writeValueData(blob, 0);

    EXPECT_EQ(result, 0);

}
