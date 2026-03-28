#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <cstdint>

// Declaration of the internal function we're testing
namespace Exiv2 {
namespace Internal {
const TagInfo* findTag(const TagInfo* pList, uint16_t tag);
}
}

namespace {

// Helper to create a minimal TagInfo for testing purposes
// TagInfo structure from exiv2 has: tag_, key_, title_, desc_, ifdId_, sectionId_, typeId_, count_, printFct_
// We rely on the actual struct definition from the project.

class FindTagTest_1660 : public ::testing::Test {
protected:
    // We'll build TagInfo arrays using the actual struct.
    // In exiv2, TagInfo is typically: {tag, name, title, desc, ifdId, sectionId, typeId, count, printFct}
    // The sentinel is typically {0xffff, ...}
};

TEST_F(FindTagTest_1660, FindExistingTagFirst_1660) {
    // Array with a few tags, search for the first one
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0002, "Tag2", "Tag2 Title", "Tag2 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0003, "Tag3", "Tag3 Title", "Tag3 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0001);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x0001);
    EXPECT_EQ(result, &list[0]);
}

TEST_F(FindTagTest_1660, FindExistingTagMiddle_1660) {
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0002, "Tag2", "Tag2 Title", "Tag2 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0003, "Tag3", "Tag3 Title", "Tag3 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0002);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x0002);
    EXPECT_EQ(result, &list[1]);
}

TEST_F(FindTagTest_1660, FindExistingTagLast_1660) {
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0002, "Tag2", "Tag2 Title", "Tag2 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0003, "Tag3", "Tag3 Title", "Tag3 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0003);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x0003);
    EXPECT_EQ(result, &list[2]);
}

TEST_F(FindTagTest_1660, TagNotFound_1660) {
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0002, "Tag2", "Tag2 Title", "Tag2 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0099);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FindTagTest_1660, EmptyListOnlySentinel_1660) {
    // List with only the sentinel entry
    Exiv2::TagInfo list[] = {
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0001);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FindTagTest_1660, SearchForZeroTag_1660) {
    Exiv2::TagInfo list[] = {
        {0x0000, "Tag0", "Tag0 Title", "Tag0 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0000);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x0000);
    EXPECT_EQ(result, &list[0]);
}

TEST_F(FindTagTest_1660, SearchForSentinelTagReturnsNull_1660) {
    // Searching for 0xffff should match the sentinel, but the function
    // stops when it hits 0xffff and returns nullptr for sentinel entries.
    // Actually, looking at the code: while (tag_ != 0xffff && tag_ != tag) pList++;
    // If tag == 0xffff, the loop stops at first entry with 0xffff, and then
    // returns pList since pList->tag_ == 0xffff is NOT != 0xffff, so the condition
    // `pList->tag_ != 0xffff` is false, so it returns nullptr.
    // Wait - re-reading: the while stops because tag_ == 0xffff (first condition) OR tag_ == tag.
    // If we search for 0xffff, when we hit sentinel: tag_ == 0xffff makes first condition fail AND
    // tag_ == tag (0xffff) also would make second condition true... but && short-circuits.
    // The loop exits. Then: return pList->tag_ != 0xffff ? pList : nullptr
    // pList->tag_ == 0xffff so returns nullptr.
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0xffff);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FindTagTest_1660, SingleElementList_1660) {
    Exiv2::TagInfo list[] = {
        {0x0042, "Tag42", "Tag42 Title", "Tag42 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0042);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x0042);
}

TEST_F(FindTagTest_1660, SingleElementListNotFound_1660) {
    Exiv2::TagInfo list[] = {
        {0x0042, "Tag42", "Tag42 Title", "Tag42 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0043);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FindTagTest_1660, LargeTagValue_1660) {
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1", "Tag1 Title", "Tag1 Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xfffe, "TagFFFE", "TagFFFE Title", "TagFFFE Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0xfffe);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0xfffe);
    EXPECT_EQ(result, &list[1]);
}

TEST_F(FindTagTest_1660, DuplicateTagsReturnsFirst_1660) {
    // If there are duplicate tags, the function should return the first match
    Exiv2::TagInfo list[] = {
        {0x0001, "Tag1A", "Tag1A Title", "Tag1A Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0001, "Tag1B", "Tag1B Title", "Tag1B Desc", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x0001);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &list[0]);
}

TEST_F(FindTagTest_1660, ManyElements_1660) {
    // Test with a larger list
    Exiv2::TagInfo list[] = {
        {0x0001, "T1", "T1", "T1", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0002, "T2", "T2", "T2", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0003, "T3", "T3", "T3", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0004, "T4", "T4", "T4", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0005, "T5", "T5", "T5", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0006, "T6", "T6", "T6", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0007, "T7", "T7", "T7", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0008, "T8", "T8", "T8", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x0009, "T9", "T9", "T9", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0x000a, "T10", "T10", "T10", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
        {0xffff, "(UnknownTag)", "Unknown Tag", "Unknown Tag", Exiv2::IfdId::ifd0Id, Exiv2::SectionId::sectionIdNotSet, Exiv2::unsignedShort, 1, nullptr},
    };

    // Find last real entry
    const Exiv2::TagInfo* result = Exiv2::Internal::findTag(list, 0x000a);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag_, 0x000a);
    EXPECT_EQ(result, &list[9]);

    // Not found
    const Exiv2::TagInfo* notFound = Exiv2::Internal::findTag(list, 0x00ff);
    EXPECT_EQ(notFound, nullptr);
}

} // anonymous namespace
