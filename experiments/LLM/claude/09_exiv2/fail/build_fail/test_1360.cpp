#include <gtest/gtest.h>
#include "exiv2/tags.h"
#include "tags_int.hpp"

using namespace Exiv2::Internal;

class MpfTagListTest_1360 : public ::testing::Test {
 protected:
  const TagInfo* tagList_ = nullptr;

  void SetUp() override {
    tagList_ = mpfTagList();
  }
};

TEST_F(MpfTagListTest_1360, ReturnsNonNullPointer_1360) {
  ASSERT_NE(tagList_, nullptr);
}

TEST_F(MpfTagListTest_1360, FirstTagIsMPFVersion_1360) {
  EXPECT_EQ(tagList_[0].tag_, 45056);
  EXPECT_STREQ(tagList_[0].name_, "MPFVersion");
  EXPECT_STREQ(tagList_[0].title_, "MPFVersion");
  EXPECT_STREQ(tagList_[0].desc_, "MPF Version");
}

TEST_F(MpfTagListTest_1360, SecondTagIsMPFNumberOfImages_1360) {
  EXPECT_EQ(tagList_[1].tag_, 45057);
  EXPECT_STREQ(tagList_[1].name_, "MPFNumberOfImages");
  EXPECT_STREQ(tagList_[1].title_, "MPFNumberOfImages");
  EXPECT_STREQ(tagList_[1].desc_, "MPF Number of Images");
}

TEST_F(MpfTagListTest_1360, ThirdTagIsMPFImageList_1360) {
  EXPECT_EQ(tagList_[2].tag_, 45058);
  EXPECT_STREQ(tagList_[2].name_, "MPFImageList");
  EXPECT_STREQ(tagList_[2].title_, "MPFImageList");
  EXPECT_STREQ(tagList_[2].desc_, "MPF Image List");
}

TEST_F(MpfTagListTest_1360, FourthTagIsMPFImageUIDList_1360) {
  EXPECT_EQ(tagList_[3].tag_, 45059);
  EXPECT_STREQ(tagList_[3].name_, "MPFImageUIDList");
  EXPECT_STREQ(tagList_[3].desc_, "MPF Image UID List");
}

TEST_F(MpfTagListTest_1360, FifthTagIsMPFTotalFrames_1360) {
  EXPECT_EQ(tagList_[4].tag_, 45060);
  EXPECT_STREQ(tagList_[4].name_, "MPFTotalFrames");
  EXPECT_STREQ(tagList_[4].desc_, "MPF Total Frames");
}

TEST_F(MpfTagListTest_1360, SixthTagIsMPFIndividualNum_1360) {
  EXPECT_EQ(tagList_[5].tag_, 45313);
  EXPECT_STREQ(tagList_[5].name_, "MPFIndividualNum");
  EXPECT_STREQ(tagList_[5].desc_, "MPF Individual Num");
}

TEST_F(MpfTagListTest_1360, SeventhTagIsMPFPanOrientation_1360) {
  EXPECT_EQ(tagList_[6].tag_, 45569);
  EXPECT_STREQ(tagList_[6].name_, "MPFPanOrientation");
  EXPECT_STREQ(tagList_[6].desc_, "MPFPanOrientation");
}

TEST_F(MpfTagListTest_1360, EighthTagIsMPFPanOverlapH_1360) {
  EXPECT_EQ(tagList_[7].tag_, 45570);
  EXPECT_STREQ(tagList_[7].name_, "MPFPanOverlapH");
  EXPECT_STREQ(tagList_[7].desc_, "MPF Pan Overlap Horizontal");
}

TEST_F(MpfTagListTest_1360, NinthTagIsMPFPanOverlapV_1360) {
  EXPECT_EQ(tagList_[8].tag_, 45571);
  EXPECT_STREQ(tagList_[8].name_, "MPFPanOverlapV");
  EXPECT_STREQ(tagList_[8].desc_, "MPF Pan Overlap Vertical");
}

TEST_F(MpfTagListTest_1360, TenthTagIsMPFBaseViewpointNum_1360) {
  EXPECT_EQ(tagList_[9].tag_, 45572);
  EXPECT_STREQ(tagList_[9].name_, "MPFBaseViewpointNum");
  EXPECT_STREQ(tagList_[9].desc_, "MPF Base Viewpoint Number");
}

TEST_F(MpfTagListTest_1360, EleventhTagIsMPFConvergenceAngle_1360) {
  EXPECT_EQ(tagList_[10].tag_, 45573);
  EXPECT_STREQ(tagList_[10].name_, "MPFConvergenceAngle");
  EXPECT_STREQ(tagList_[10].desc_, "MPF Convergence Angle");
}

TEST_F(MpfTagListTest_1360, TwelfthTagIsMPFBaselineLength_1360) {
  EXPECT_EQ(tagList_[11].tag_, 45574);
  EXPECT_STREQ(tagList_[11].name_, "MPFBaselineLength");
  EXPECT_STREQ(tagList_[11].desc_, "MPF Baseline Length");
}

TEST_F(MpfTagListTest_1360, ThirteenthTagIsMPFVerticalDivergence_1360) {
  EXPECT_EQ(tagList_[12].tag_, 45575);
  EXPECT_STREQ(tagList_[12].name_, "MPFVerticalDivergence");
  EXPECT_STREQ(tagList_[12].desc_, "MPF Vertical Divergence");
}

TEST_F(MpfTagListTest_1360, FourteenthTagIsMPFAxisDistanceX_1360) {
  EXPECT_EQ(tagList_[13].tag_, 45576);
  EXPECT_STREQ(tagList_[13].name_, "MPFAxisDistanceX");
  EXPECT_STREQ(tagList_[13].desc_, "MPF Axis Distance X");
}

TEST_F(MpfTagListTest_1360, FifteenthTagIsMPFAxisDistanceY_1360) {
  EXPECT_EQ(tagList_[14].tag_, 45577);
  EXPECT_STREQ(tagList_[14].name_, "MPFAxisDistanceY");
  EXPECT_STREQ(tagList_[14].desc_, "MPF Axis Distance Y");
}

TEST_F(MpfTagListTest_1360, SixteenthTagIsMPFAxisDistanceZ_1360) {
  EXPECT_EQ(tagList_[15].tag_, 45578);
  EXPECT_STREQ(tagList_[15].name_, "MPFAxisDistanceZ");
  EXPECT_STREQ(tagList_[15].desc_, "MPF Axis Distance Z");
}

TEST_F(MpfTagListTest_1360, SeventeenthTagIsMPFYawAngle_1360) {
  EXPECT_EQ(tagList_[16].tag_, 45579);
  EXPECT_STREQ(tagList_[16].name_, "MPFYawAngle");
  EXPECT_STREQ(tagList_[16].desc_, "MPF Yaw Angle");
}

TEST_F(MpfTagListTest_1360, EighteenthTagIsMPFPitchAngle_1360) {
  EXPECT_EQ(tagList_[17].tag_, 45580);
  EXPECT_STREQ(tagList_[17].name_, "MPFPitchAngle");
  EXPECT_STREQ(tagList_[17].desc_, "MPF Pitch Angle");
}

TEST_F(MpfTagListTest_1360, NineteenthTagIsMPFRollAngle_1360) {
  EXPECT_EQ(tagList_[18].tag_, 45581);
  EXPECT_STREQ(tagList_[18].name_, "MPFRollAngle");
  EXPECT_STREQ(tagList_[18].desc_, "MPF Roll Angle");
}

TEST_F(MpfTagListTest_1360, LastTagIsUnknownMpfTag_1360) {
  EXPECT_EQ(tagList_[19].tag_, 65535);
  EXPECT_STREQ(tagList_[19].name_, "(UnknownMpfTag)");
  EXPECT_STREQ(tagList_[19].title_, "Unknown MPF tag");
  EXPECT_STREQ(tagList_[19].desc_, "Unknown MPF tag");
}

TEST_F(MpfTagListTest_1360, TotalTagCountIs20_1360) {
  // Verify we have exactly 20 tags by checking the last entry is at index 19
  // and it is the sentinel/unknown tag with tag id 65535
  int count = 0;
  while (tagList_[count].tag_ != 65535) {
    count++;
    // Safety guard to avoid infinite loop
    ASSERT_LT(count, 100) << "Did not find sentinel tag within expected range";
  }
  EXPECT_EQ(count, 19);  // 19 valid tags before the sentinel at index 19
}

TEST_F(MpfTagListTest_1360, AllTagsBelongToMpfIfd_1360) {
  for (int i = 0; i < 20; ++i) {
    EXPECT_EQ(tagList_[i].ifdId_, IfdId::mpfId)
        << "Tag at index " << i << " does not belong to mpfId";
  }
}

TEST_F(MpfTagListTest_1360, AllTagsBelongToMpfSection_1360) {
  for (int i = 0; i < 20; ++i) {
    EXPECT_EQ(tagList_[i].sectionId_, SectionId::mpfTags)
        << "Tag at index " << i << " does not belong to mpfTags section";
  }
}

TEST_F(MpfTagListTest_1360, ConsecutiveCallsReturnSamePointer_1360) {
  const TagInfo* first = mpfTagList();
  const TagInfo* second = mpfTagList();
  EXPECT_EQ(first, second);
}

TEST_F(MpfTagListTest_1360, MPFVersionTagHasCountZero_1360) {
  // MPFVersion count_ is 0
  EXPECT_EQ(tagList_[0].count_, 0);
}

TEST_F(MpfTagListTest_1360, MPFNumberOfImagesHasCountMinusOne_1360) {
  // MPFNumberOfImages count_ is -1
  EXPECT_EQ(tagList_[1].count_, -1);
}

TEST_F(MpfTagListTest_1360, MPFTotalFramesHasCountOne_1360) {
  EXPECT_EQ(tagList_[4].count_, 1);
}

TEST_F(MpfTagListTest_1360, UnknownTagHasCountMinusOne_1360) {
  EXPECT_EQ(tagList_[19].count_, -1);
}

TEST_F(MpfTagListTest_1360, TagsHaveNonNullNames_1360) {
  for (int i = 0; i < 20; ++i) {
    EXPECT_NE(tagList_[i].name_, nullptr) << "Tag at index " << i << " has null name";
    EXPECT_NE(tagList_[i].title_, nullptr) << "Tag at index " << i << " has null title";
    EXPECT_NE(tagList_[i].desc_, nullptr) << "Tag at index " << i << " has null desc";
  }
}

TEST_F(MpfTagListTest_1360, TagIdsAreInNonDecreasingOrder_1360) {
  for (int i = 1; i < 20; ++i) {
    EXPECT_GE(tagList_[i].tag_, tagList_[i - 1].tag_)
        << "Tag at index " << i << " has id less than previous tag";
  }
}
