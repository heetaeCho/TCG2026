#include <gtest/gtest.h>

// Include necessary headers
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for MnHeader
class MnHeaderTest_1433 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<MnHeader>();
    }

    std::unique_ptr<MnHeader> header_;
};

// Test that ifdOffset returns 0 by default
TEST_F(MnHeaderTest_1433, IfdOffsetReturnsZero_1433) {
    EXPECT_EQ(header_->ifdOffset(), 0u);
}

// Test that ifdOffset consistently returns the same value
TEST_F(MnHeaderTest_1433, IfdOffsetIsConsistent_1433) {
    size_t first_call = header_->ifdOffset();
    size_t second_call = header_->ifdOffset();
    EXPECT_EQ(first_call, second_call);
    EXPECT_EQ(first_call, 0u);
}

// Test that a newly constructed MnHeader has ifdOffset of 0
TEST_F(MnHeaderTest_1433, NewlyConstructedHeaderHasZeroIfdOffset_1433) {
    MnHeader fresh_header;
    EXPECT_EQ(fresh_header.ifdOffset(), 0u);
}

// Test that multiple instances all return 0 for ifdOffset
TEST_F(MnHeaderTest_1433, MultipleInstancesReturnZeroIfdOffset_1433) {
    MnHeader header1;
    MnHeader header2;
    MnHeader header3;
    EXPECT_EQ(header1.ifdOffset(), 0u);
    EXPECT_EQ(header2.ifdOffset(), 0u);
    EXPECT_EQ(header3.ifdOffset(), 0u);
}

// Test that ifdOffset return type is size_t (implicitly tested by assignment)
TEST_F(MnHeaderTest_1433, IfdOffsetReturnTypeIsSizeT_1433) {
    size_t offset = header_->ifdOffset();
    EXPECT_EQ(offset, static_cast<size_t>(0));
}
