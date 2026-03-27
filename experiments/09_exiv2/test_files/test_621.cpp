#include <gtest/gtest.h>

#include "fujimn_int.hpp"



class FujiMakerNoteTest_621 : public ::testing::Test {

protected:

    using TagListType = decltype(Exiv2::Internal::FujiMakerNote::tagList());

};



TEST_F(FujiMakerNoteTest_621, TagList_ReturnsValidPointer_621) {

    const auto* tagList = Exiv2::Internal::FujiMakerNote::tagList();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(FujiMakerNoteTest_621, TagList_IsConstexprAccessible_621) {

    constexpr const auto* tagList = Exiv2::Internal::FujiMakerNote::tagList();

    EXPECT_NE(tagList, nullptr);

}
