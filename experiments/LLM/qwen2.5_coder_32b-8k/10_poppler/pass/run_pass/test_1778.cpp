#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Attribute::Owner for testing purposes

namespace Attribute {

    enum Owner {

        XML_1_00,

        HTML_3_20,

        HTML_4_01,

        OEB_1_00,

        RTF_1_05,

        CSS_1_00,

        CSS_2_00,

        Layout,

        PrintField,

        Table,

        List,

        UserProperties

    };

}



struct OwnerMapEntry {

    Attribute::Owner owner;

    const char* name;

};



// Mocking the global variable ownerMap

const OwnerMapEntry ownerMap[12] = {

    {Attribute::XML_1_00, "XML-1.00"},

    {Attribute::HTML_3_20, "HTML-3.20"},

    {Attribute::HTML_4_01, "HTML-4.01"},

    {Attribute::OEB_1_00, "OEB-1.00"},

    {Attribute::RTF_1_05, "RTF-1.05"},

    {Attribute::CSS_1_00, "CSS-1.00"},

    {Attribute::CSS_2_00, "CSS-2.00"},

    {Attribute::Layout, "Layout"},

    {Attribute::PrintField, "PrintField"},

    {Attribute::Table, "Table"},

    {Attribute::List, "List"},

    {Attribute::UserProperties, "UserProperties"}

};



// Function under test

static inline const OwnerMapEntry *getOwnerMapEntry(Attribute::Owner owner) {

    for (const OwnerMapEntry &entry : ownerMap) {

        if (owner == entry.owner) {

            return &entry;

        }

    }

    return nullptr;

}



TEST(GetOwnerMapEntryTest_1778, ValidOwner_ReturnsCorrectEntry_1778) {

    const OwnerMapEntry* result = getOwnerMapEntry(Attribute::HTML_4_01);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->owner, Attribute::HTML_4_01);

    EXPECT_STREQ(result->name, "HTML-4.01");

}



TEST(GetOwnerMapEntryTest_1778, FirstOwner_ReturnsCorrectEntry_1778) {

    const OwnerMapEntry* result = getOwnerMapEntry(Attribute::XML_1_00);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->owner, Attribute::XML_1_00);

    EXPECT_STREQ(result->name, "XML-1.00");

}



TEST(GetOwnerMapEntryTest_1778, LastOwner_ReturnsCorrectEntry_1778) {

    const OwnerMapEntry* result = getOwnerMapEntry(Attribute::UserProperties);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->owner, Attribute::UserProperties);

    EXPECT_STREQ(result->name, "UserProperties");

}



TEST(GetOwnerMapEntryTest_1778, InvalidOwner_ReturnsNullptr_1778) {

    const OwnerMapEntry* result = getOwnerMapEntry(static_cast<Attribute::Owner>(999));

    EXPECT_EQ(result, nullptr);

}
