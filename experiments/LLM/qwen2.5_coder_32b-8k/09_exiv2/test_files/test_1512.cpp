#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



namespace Exiv2 {

namespace Internal {



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdInterOperability;

};



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_ReturnsNonNullPointer_1512) {

    auto makernote = newOlympusMn2(tag, group, mnGroup);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_CreatesUniqueInstance_1512) {

    auto makernote1 = newOlympusMn2(tag, group, mnGroup);

    auto makernote2 = newOlympusMn2(tag, group, mnGroup);

    EXPECT_NE(makernote1.get(), makernote2.get());

}



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_HasCorrectTag_1512) {

    auto makernote = newOlympusMn2(tag, group, mnGroup);

    EXPECT_EQ(makernote->tag(), tag);

}



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_HasCorrectGroup_1512) {

    auto makernote = newOlympusMn2(tag, group, mnGroup);

    EXPECT_EQ(makernote->group(), group);

}



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_HasCorrectMnGroup_1512) {

    auto makernote = newOlympusMn2(tag, group, mnGroup);

    EXPECT_EQ(makernote->mnGroup(), mnGroup);

}



TEST_F(TiffIfdMakernoteTest_1512, NewOlympusMn2_HasCorrectHeaderType_1512) {

    auto makernote = newOlympusMn2(tag, group, mnGroup);

    EXPECT_EQ(typeid(*makernote->header()), typeid(OlympusMnHeader));

}



} // namespace Internal

} // namespace Exiv2
