#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming StructElement and its Type are defined somewhere in the header files.

namespace poppler {

    class StructElement {

    public:

        enum class Type;

        static inline const TypeMapEntry *getTypeMapEntry(Type type);

    };



    struct TypeMapEntry {

        StructElement::Type type;

        ElementType elementType;

        const AttributeMapEntry **attributes;

    };

}



// Mocking or any setup if necessary

using namespace poppler;



// Test Fixture

class StructElementTest_1782 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed

};



// Normal operation tests



TEST_F(StructElementTest_1782, GetValidTypeMapEntry_Document_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::Document);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::Document);

}



TEST_F(StructElementTest_1782, GetValidTypeMapEntry_Part_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::Part);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::Part);

}



TEST_F(StructElementTest_1782, GetValidTypeMapEntry_Span_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::Span);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::Span);

}



TEST_F(StructElementTest_1782, GetValidTypeMapEntry_H6_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::H6);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::H6);

}



// Boundary conditions tests



TEST_F(StructElementTest_1782, GetFirstTypeMapEntry_Document_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::Document);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::Document);

}



TEST_F(StructElementTest_1782, GetLastTypeMapEntry_TOCI_1782) {

    const auto* entry = StructElement::getTypeMapEntry(StructElement::Type::TOCI);

    ASSERT_NE(entry, nullptr);

    EXPECT_EQ(entry->type, StructElement::Type::TOCI);

}



// Exceptional or error cases



TEST_F(StructElementTest_1782, GetInvalidTypeMapEntry_OutOfRange_1782) {

    const auto* entry = StructElement::getTypeMapEntry(static_cast<StructElement::Type>(999));

    EXPECT_EQ(entry, nullptr);

}



// Assuming there are no external collaborators to mock for this function


