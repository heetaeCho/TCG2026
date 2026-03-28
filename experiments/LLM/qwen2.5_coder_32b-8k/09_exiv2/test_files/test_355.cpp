#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeSizeEntry, (const TiffSizeEntry* object, const Exifdatum* datum), (override));

};



class TiffSizeEntryTest_355 : public ::testing::Test {

protected:

    NiceMock<MockTiffEncoder> encoder_;

    std::unique_ptr<Exifdatum> exifdatum_;

    uint16_t tag_ = 0x00FE;

    IfdId group_ = ifdExif;

    uint16_t dtTag_ = 0x00FF;

    IfdId dtGroup_ = ifdExif;



    void SetUp() override {

        exifdatum_ = std::make_unique<Exifdatum>(ExifKey("Exif.Image.Artist"), new Value);

    }

};



TEST_F(TiffSizeEntryTest_355, DoEncodeCallsEncoder_355) {

    TiffSizeEntry tiffSizeEntry(tag_, group_, dtTag_, dtGroup_);

    EXPECT_CALL(encoder_, encodeSizeEntry(&tiffSizeEntry, exifdatum_.get()));

    tiffSizeEntry.doEncode(encoder_, exifdatum_.get());

}



TEST_F(TiffSizeEntryTest_355, DoEncodeWithNullExifdatum_355) {

    TiffSizeEntry tiffSizeEntry(tag_, group_, dtTag_, dtGroup_);

    EXPECT_CALL(encoder_, encodeSizeEntry(&tiffSizeEntry, nullptr));

    tiffSizeEntry.doEncode(encoder_, nullptr);

}



TEST_F(TiffSizeEntryTest_355, DttagAndDtgroupAccessors_355) {

    TiffSizeEntry tiffSizeEntry(tag_, group_, dtTag_, dtGroup_);

    EXPECT_EQ(tiffSizeEntry.dtTag(), dtTag_);

    EXPECT_EQ(tiffSizeEntry.dtGroup(), dtGroup_);

}
