#include <gtest/gtest.h>

#include <cstring>



// Assuming StructElement and its Type are defined somewhere in the actual codebase.

namespace poppler {

    class StructElement {

    public:

        enum class Type {

            Document,

            Part,

            Art,

            Sect,

            Div,

            BlockQuote,

            Caption,

            NonStruct,

            Index,

            Private,

            Span,

            Quote,

            Note,

            Reference,

            BibEntry,

            Code,

            Link,

            Annot,

            Ruby,

            RB,

            RT,

            RP,

            Warichu,

            WT,

            WP,

            P,

            H,

            H1,

            H2,

            H3,

            H4,

            H5,

            H6,

            L,

            LI,

            Lbl,

            LBody,

            Table,

            TR,

            TH,

            TD,

            THead,

            TFoot,

            TBody,

            Figure,

            Formula,

            Form,

            TOC,

            TOCI

        };



        enum ElementType {

            elementTypeGrouping,

            elementTypeInline,

            elementTypeUndefined,

            elementTypeBlock,

            elementTypeList,

            elementTypeTable,

            elementTypeTableCell,

            elementTypeIllustration

        };

    };



    struct AttributeMapEntry;



    struct TypeMapEntry {

        StructElement::Type type;

        const char* name;

        ElementType elementType;

        const AttributeMapEntry** attributes;

    };



    static inline const TypeMapEntry* getTypeMapEntry(const char* name) {

        for (const TypeMapEntry& entry : typeMap) {

            if (strcmp(name, entry.name) == 0) {

                return &entry;

            }

        }

        return nullptr;

    }



    extern const TypeMapEntry typeMap[49];

}



using namespace poppler;



TEST(getTypeMapEntryTest_1783, ValidNameReturnsCorrectEntry_1783) {

    const char* name = "Document";

    const TypeMapEntry* entry = getTypeMapEntry(name);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::Document);

    EXPECT_STREQ(entry->name, "Document");

}



TEST(getTypeMapEntryTest_1783, InvalidNameReturnsNullptr_1783) {

    const char* name = "NonExistent";

    const TypeMapEntry* entry = getTypeMapEntry(name);

    EXPECT_EQ(entry, nullptr);

}



TEST(getTypeMapEntryTest_1783, BoundaryConditionEmptyString_1783) {

    const char* name = "";

    const TypeMapEntry* entry = getTypeMapEntry(name);

    EXPECT_EQ(entry, nullptr);

}



TEST(getTypeMapEntryTest_1783, BoundaryConditionNullptr_1783) {

    const char* name = nullptr;

    const TypeMapEntry* entry = getTypeMapEntry(name);

    EXPECT_EQ(entry, nullptr);

}
