#include <gtest/gtest.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1787 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1787, FindComponent_NormalOperation_1787) {

    uint16_t tagId = 0x1234;

    uint16_t dirId = 0x5678;

    CiffComponent* result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, nullptr); // Assuming default behavior returns nullptr if not found

}



TEST_F(CiffComponentTest_1787, FindComponent_BoundaryConditions_TagIdZero_1787) {

    uint16_t tagId = 0x0000;

    uint16_t dirId = 0x5678;

    CiffComponent* result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, nullptr); // Assuming default behavior returns nullptr if not found

}



TEST_F(CiffComponentTest_1787, FindComponent_BoundaryConditions_DirIdZero_1787) {

    uint16_t tagId = 0x1234;

    uint16_t dirId = 0x0000;

    CiffComponent* result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, nullptr); // Assuming default behavior returns nullptr if not found

}



TEST_F(CiffComponentTest_1787, FindComponent_BoundaryConditions_MaxValues_1787) {

    uint16_t tagId = 0xFFFF;

    uint16_t dirId = 0xFFFF;

    CiffComponent* result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, nullptr); // Assuming default behavior returns nullptr if not found

}



TEST_F(CiffComponentTest_1787, FindComponent_ExceptionalCases_NullPointer_1787) {

    uint16_t tagId = 0x1234;

    uint16_t dirId = 0x5678;

    // Since there's no way to induce an exception with the given interface,

    // we assume normal behavior and check for nullptr.

    CiffComponent* result = component.findComponent(tagId, dirId);

    EXPECT_EQ(result, nullptr); // Assuming default behavior returns nullptr if not found

}
