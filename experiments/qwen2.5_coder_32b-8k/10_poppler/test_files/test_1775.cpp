#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Attribute::Owner and ownerMap are defined in a header file.

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



const struct OwnerMapEntry {

    Attribute::Owner owner;

    const char* name;

};



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



// Mock class to wrap the static function for testing

class OwnerPriorityChecker {

public:

    virtual ~OwnerPriorityChecker() = default;

    virtual bool hasMorePriority(Attribute::Owner a, Attribute::Owner b) const {

        return ownerHasMorePriority(a, b);

    }

};



TEST(OwnerPriorityCheckerTest_1775, XMLHasLowerPriorityThanHTML320_1775) {

    OwnerPriorityChecker checker;

    EXPECT_FALSE(checker.hasMorePriority(Attribute::XML_1_00, Attribute::HTML_3_20));

}



TEST(OwnerPriorityCheckerTest_1775, HTML401HasHigherPriorityThanOEB100_1775) {

    OwnerPriorityChecker checker;

    EXPECT_TRUE(checker.hasMorePriority(Attribute::HTML_4_01, Attribute::OEB_1_00));

}



TEST(OwnerPriorityCheckerTest_1775, SameOwnerReturnsFalse_1775) {

    OwnerPriorityChecker checker;

    EXPECT_FALSE(checker.hasMorePriority(Attribute::RTF_1_05, Attribute::RTF_1_05));

}



TEST(OwnerPriorityCheckerTest_1775, LayoutHasLowerPriorityThanCSS200_1775) {

    OwnerPriorityChecker checker;

    EXPECT_TRUE(checker.hasMorePriority(Attribute::Layout, Attribute::CSS_2_00));

}



TEST(OwnerPriorityCheckerTest_1775, UserPropertiesHasHighestPriority_1775) {

    OwnerPriorityChecker checker;

    for (int i = 0; i < 11; ++i) { // Exclude the last element which is UserProperties

        EXPECT_TRUE(checker.hasMorePriority(static_cast<Attribute::Owner>(i), Attribute::UserProperties));

    }

}



TEST(OwnerPriorityCheckerTest_1775, PrintFieldHasLowerPriorityThanTable_1775) {

    OwnerPriorityChecker checker;

    EXPECT_TRUE(checker.hasMorePriority(Attribute::PrintField, Attribute::Table));

}
