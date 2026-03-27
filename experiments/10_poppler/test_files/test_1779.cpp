#include <gtest/gtest.h>

#include <cstring>



// Mock or Stub for Attribute::Owner if necessary, but in this case, we treat it as a black box.

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



extern const OwnerMapEntry ownerMap[12];



static inline const OwnerMapEntry *getOwnerMapEntry(const char *name) {

    for (const OwnerMapEntry &entry : ownerMap) {

        if (strcmp(name, entry.name) == 0) {

            return &entry;

        }

    }

    return nullptr;

}



class StructElementTest_1779 : public ::testing::Test {};



TEST_F(StructElementTest_1779, GetOwnerMapEntry_ValidName_1779) {

    const OwnerMapEntry* entry = getOwnerMapEntry("HTML-3.20");

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->owner, Attribute::HTML_3_20);

}



TEST_F(StructElementTest_1779, GetOwnerMapEntry_FirstEntry_1779) {

    const OwnerMapEntry* entry = getOwnerMapEntry("XML-1.00");

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->owner, Attribute::XML_1_00);

}



TEST_F(StructElementTest_1779, GetOwnerMapEntry_LastEntry_1779) {

    const OwnerMapEntry* entry = getOwnerMapEntry("UserProperties");

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->owner, Attribute::UserProperties);

}



TEST_F(StructElementTest_1779, GetOwnerMapEntry_InvalidName_1779) {

    const OwnerMapEntry* entry = getOwnerMapEntry("NonExistent");

    EXPECT_EQ(entry, nullptr);

}



TEST_F(StructElementTest_1779, GetOwnerMapEntry_EmptyString_1779) {

    const OwnerMapEntry* entry = getOwnerMapEntry("");

    EXPECT_EQ(entry, nullptr);

}
