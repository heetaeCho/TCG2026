#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



namespace Exiv2 {

namespace Internal {



class TagInfoTest : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(TagInfoTest_1366, ValidIfdId_ReturnsTagListPointer_1366) {

    const TagInfo* result = tagList(IfdId::ifd0Id);

    EXPECT_NE(result, nullptr);

}



TEST_F(TagInfoTest_1366, UnknownIfdId_ReturnsNullptr_1366) {

    const TagInfo* result = tagList(static_cast<IfdId>(-1)); // Invalid IfdId

    EXPECT_EQ(result, nullptr);

}



TEST_F(TagInfoTest_1366, BoundaryIfdId_Start_ReturnsTagListPointer_1366) {

    const TagInfo* result = tagList(IfdId::ifd0Id); // First valid IfdId

    EXPECT_NE(result, nullptr);

}



TEST_F(TagInfoTest_1366, BoundaryIfdId_End_ReturnsTagListPointer_1366) {

    const TagInfo* result = tagList(IfdId::lastId - 1); // Last valid IfdId

    EXPECT_NE(result, nullptr);

}



TEST_F(TagInfoTest_1366, InvalidIfdId_OutOfBounds_ReturnsNullptr_1366) {

    const TagInfo* result = tagList(static_cast<IfdId>(127)); // Out of bounds IfdId

    EXPECT_EQ(result, nullptr);

}



}  // namespace Internal

}  // namespace Exiv2
