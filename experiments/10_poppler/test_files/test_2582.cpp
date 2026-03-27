#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



// Mocking external collaborators if needed

class MockPopplerStructureElement {

public:

    MOCK_METHOD(bool, poppler_structure_element_is_inline, (), (const));

};



TEST(PopplerStructureElementTest_2582, GetRubyPositionInline_2582) {

    PopplerStructureElement element;

    element.elem = new StructElement(); // Assuming default constructor exists



    EXPECT_CALL(*reinterpret_cast<MockPopplerStructureElement*>(&element), poppler_structure_element_is_inline())

        .WillOnce(testing::Return(true));



    auto result = poppler_structure_element_get_ruby_position(&element);



    EXPECT_EQ(result, EnumNameValue<PopplerStructureRubyPosition>::values[0].value);

}



TEST(PopplerStructureElementTest_2582, GetRubyPositionNotInline_2582) {

    PopplerStructureElement element;

    element.elem = new StructElement(); // Assuming default constructor exists



    EXPECT_CALL(*reinterpret_cast<MockPopplerStructureElement*>(&element), poppler_structure_element_is_inline())

        .WillOnce(testing::Return(false));



    auto result = poppler_structure_element_get_ruby_position(&element);



    EXPECT_EQ(result, EnumNameValue<PopplerStructureRubyPosition>::values[0].value);

}

```


