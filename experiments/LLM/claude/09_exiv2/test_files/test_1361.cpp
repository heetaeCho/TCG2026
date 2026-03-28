#include <gtest/gtest.h>
#include "tags_int.hpp"
#include "tags.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class IopTagListTest_1361 : public ::testing::Test {
 protected:
  const TagInfo* tagList_;

  void SetUp() override {
    tagList_ = iopTagList();
  }
};

// Test that iopTagList returns a non-null pointer
TEST_F(IopTagListTest_1361, ReturnsNonNull_1361) {
  ASSERT_NE(tagList_, nullptr);
}

// Test the first tag: InteroperabilityIndex
TEST_F(IopTagListTest_1361, FirstTagIsInteroperabilityIndex_1361) {
  EXPECT_EQ(tagList_[0].tag_, 1);
  EXPECT_STREQ(tagList_[0].name_, "InteroperabilityIndex");
  EXPECT_STREQ(tagList_[0].title_, "Interoperability Index");
  EXPECT_EQ(tagList_[0].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[0].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[0].typeId_, asciiString);
  EXPECT_EQ(tagList_[0].count_, 0);
}

// Test the second tag: InteroperabilityVersion
TEST_F(IopTagListTest_1361, SecondTagIsInteroperabilityVersion_1361) {
  EXPECT_EQ(tagList_[1].tag_, 2);
  EXPECT_STREQ(tagList_[1].name_, "InteroperabilityVersion");
  EXPECT_STREQ(tagList_[1].title_, "Interoperability Version");
  EXPECT_EQ(tagList_[1].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[1].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[1].typeId_, undefined);
  EXPECT_EQ(tagList_[1].count_, -1);
}

// Test the third tag: RelatedImageFileFormat
TEST_F(IopTagListTest_1361, ThirdTagIsRelatedImageFileFormat_1361) {
  EXPECT_EQ(tagList_[2].tag_, 4096);
  EXPECT_STREQ(tagList_[2].name_, "RelatedImageFileFormat");
  EXPECT_STREQ(tagList_[2].title_, "Related Image File Format");
  EXPECT_EQ(tagList_[2].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[2].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[2].typeId_, asciiString);
  EXPECT_EQ(tagList_[2].count_, 0);
}

// Test the fourth tag: RelatedImageWidth
TEST_F(IopTagListTest_1361, FourthTagIsRelatedImageWidth_1361) {
  EXPECT_EQ(tagList_[3].tag_, 4097);
  EXPECT_STREQ(tagList_[3].name_, "RelatedImageWidth");
  EXPECT_STREQ(tagList_[3].title_, "Related Image Width");
  EXPECT_EQ(tagList_[3].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[3].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[3].typeId_, unsignedLong);
  EXPECT_EQ(tagList_[3].count_, 1);
}

// Test the fifth tag: RelatedImageLength
TEST_F(IopTagListTest_1361, FifthTagIsRelatedImageLength_1361) {
  EXPECT_EQ(tagList_[4].tag_, 4098);
  EXPECT_STREQ(tagList_[4].name_, "RelatedImageLength");
  EXPECT_STREQ(tagList_[4].title_, "Related Image Length");
  EXPECT_EQ(tagList_[4].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[4].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[4].typeId_, unsignedLong);
  EXPECT_EQ(tagList_[4].count_, 1);
}

// Test the last/sentinel tag: UnknownIopTag
TEST_F(IopTagListTest_1361, LastTagIsUnknownSentinel_1361) {
  EXPECT_EQ(tagList_[5].tag_, 65535);
  EXPECT_STREQ(tagList_[5].name_, "(UnknownIopTag)");
  EXPECT_STREQ(tagList_[5].title_, "Unknown Exif Interoperability tag");
  EXPECT_EQ(tagList_[5].ifdId_, IfdId::iopId);
  EXPECT_EQ(tagList_[5].sectionId_, SectionId::iopTags);
  EXPECT_EQ(tagList_[5].typeId_, asciiString);
  EXPECT_EQ(tagList_[5].count_, -1);
}

// Test that all tags in the list have iopId as their IFD ID
TEST_F(IopTagListTest_1361, AllTagsHaveIopIfdId_1361) {
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(tagList_[i].ifdId_, IfdId::iopId) << "Tag index " << i << " has wrong IFD ID";
  }
}

// Test that all tags in the list have iopTags as their section ID
TEST_F(IopTagListTest_1361, AllTagsHaveIopSectionId_1361) {
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(tagList_[i].sectionId_, SectionId::iopTags) << "Tag index " << i << " has wrong section ID";
  }
}

// Test that tag descriptions are non-empty strings
TEST_F(IopTagListTest_1361, AllTagsHaveNonEmptyDescriptions_1361) {
  for (int i = 0; i < 6; ++i) {
    ASSERT_NE(tagList_[i].desc_, nullptr) << "Tag index " << i << " has null description";
    EXPECT_GT(strlen(tagList_[i].desc_), 0u) << "Tag index " << i << " has empty description";
  }
}

// Test that tag names are non-empty strings
TEST_F(IopTagListTest_1361, AllTagsHaveNonEmptyNames_1361) {
  for (int i = 0; i < 6; ++i) {
    ASSERT_NE(tagList_[i].name_, nullptr) << "Tag index " << i << " has null name";
    EXPECT_GT(strlen(tagList_[i].name_), 0u) << "Tag index " << i << " has empty name";
  }
}

// Test that tag titles are non-empty strings
TEST_F(IopTagListTest_1361, AllTagsHaveNonEmptyTitles_1361) {
  for (int i = 0; i < 6; ++i) {
    ASSERT_NE(tagList_[i].title_, nullptr) << "Tag index " << i << " has null title";
    EXPECT_GT(strlen(tagList_[i].title_), 0u) << "Tag index " << i << " has empty title";
  }
}

// Test that calling iopTagList multiple times returns the same pointer (static data)
TEST_F(IopTagListTest_1361, ConsistentPointerOnMultipleCalls_1361) {
  const TagInfo* first = iopTagList();
  const TagInfo* second = iopTagList();
  EXPECT_EQ(first, second);
}

// Test that the print function pointers are not null
TEST_F(IopTagListTest_1361, AllTagsHaveNonNullPrintFunction_1361) {
  for (int i = 0; i < 6; ++i) {
    EXPECT_NE(tagList_[i].printFct_, nullptr) << "Tag index " << i << " has null print function";
  }
}

// Test tag numbers are in expected order (ascending except the sentinel)
TEST_F(IopTagListTest_1361, TagNumbersAreInExpectedValues_1361) {
  EXPECT_EQ(tagList_[0].tag_, 1);
  EXPECT_EQ(tagList_[1].tag_, 2);
  EXPECT_EQ(tagList_[2].tag_, 4096);
  EXPECT_EQ(tagList_[3].tag_, 4097);
  EXPECT_EQ(tagList_[4].tag_, 4098);
  EXPECT_EQ(tagList_[5].tag_, 65535);
}

// Boundary: Verify first tag description content matches known specification text
TEST_F(IopTagListTest_1361, FirstTagDescriptionContainsR98_1361) {
  std::string desc(tagList_[0].desc_);
  EXPECT_NE(desc.find("R98"), std::string::npos);
}

// Test count values for specific tags
TEST_F(IopTagListTest_1361, CountValuesAreCorrect_1361) {
  // InteroperabilityIndex: count = 0
  EXPECT_EQ(tagList_[0].count_, 0);
  // InteroperabilityVersion: count = -1
  EXPECT_EQ(tagList_[1].count_, -1);
  // RelatedImageFileFormat: count = 0
  EXPECT_EQ(tagList_[2].count_, 0);
  // RelatedImageWidth: count = 1
  EXPECT_EQ(tagList_[3].count_, 1);
  // RelatedImageLength: count = 1
  EXPECT_EQ(tagList_[4].count_, 1);
  // Unknown sentinel: count = -1
  EXPECT_EQ(tagList_[5].count_, -1);
}
