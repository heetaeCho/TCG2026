#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry*), (override));

    MOCK_METHOD(bool, go, (GoEvent event), (const override));

};



class TiffMnEntryTest_344 : public ::testing::Test {

protected:

    void SetUp() override {

        mnGroup_ = IfdId::rootIFD;

        tag_ = 0x1234;

        tiffMnEntry_ = std::make_unique<TiffMnEntry>(tag_, mnGroup_, mnGroup_);

        mockVisitor_ = std::make_unique<MockTiffVisitor>();

    }



    uint16_t tag_;

    IfdId mnGroup_;

    std::unique_ptr<TiffMnEntry> tiffMnEntry_;

    std::unique_ptr<MockTiffVisitor> mockVisitor_;

};



TEST_F(TiffMnEntryTest_344, AcceptVisitsSelfAndChild_344) {

    EXPECT_CALL(*mockVisitor_, visitMnEntry(tiffMnEntry_.get())).Times(1);

    tiffMnEntry_->accept(*mockVisitor_);

}



TEST_F(TiffMnEntryTest_344, AcceptDoesNotVisitChildIfGoKnownMakernoteIsFalse_344) {

    EXPECT_CALL(*mockVisitor_, go(GoEvent::geKnownMakernote)).WillOnce(testing::Return(false));

    EXPECT_CALL(*mockVisitor_, visitMnEntry(tiffMnEntry_.get())).Times(1);

    tiffMnEntry_->accept(*mockVisitor_);

}



TEST_F(TiffMnEntryTest_344, AcceptVisitsChildIfGoKnownMakernoteIsTrue_344) {

    EXPECT_CALL(*mockVisitor_, go(GoEvent::geKnownMakernote)).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockVisitor_, visitMnEntry(tiffMnEntry_.get())).Times(1);

    tiffMnEntry_->accept(*mockVisitor_);

}



TEST_F(TiffMnEntryTest_344, AcceptSetsChildToNullIfGoKnownMakernoteIsFalse_344) {

    EXPECT_CALL(*mockVisitor_, go(GoEvent::geKnownMakernote)).WillOnce(testing::Return(false));

    tiffMnEntry_->accept(*mockVisitor_);

    EXPECT_EQ(tiffMnEntry_->mn_.get(), nullptr);

}



TEST_F(TiffMnEntryTest_344, AcceptDoesNotSetChildToNullIfGoKnownMakernoteIsTrue_344) {

    auto mockMn = std::make_unique<TiffIfdMakernote>(tag_, mnGroup_);

    tiffMnEntry_->mn_ = std::move(mockMn);

    EXPECT_CALL(*mockVisitor_, go(GoEvent::geKnownMakernote)).WillOnce(testing::Return(true));

    tiffMnEntry_->accept(*mockVisitor_);

    EXPECT_NE(tiffMnEntry_->mn_.get(), nullptr);

}
