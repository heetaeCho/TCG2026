#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/OptionalContent.h"

#include "./TestProjects/poppler/glib/poppler-document.cc"



using namespace testing;



// Mock class for XRef as it's a dependency of OCGs

class MockXRef : public XRef {

public:

    MOCK_METHOD(bool, ok, (), (const));

};



class GetOptionalContentItemsTest_2243 : public Test {

protected:

    std::unique_ptr<MockXRef> mock_xref;

    std::unique_ptr<OCGs> ocgs;



    void SetUp() override {

        mock_xref = std::make_unique<MockXRef>();

        Object dummyObject; // Assuming a default constructor for Object is available

        ocgs = std::make_unique<OCGs>(dummyObject, mock_xref.get());

    }

};



TEST_F(GetOptionalContentItemsTest_2243, NoOrderArray_ReturnsReversedOcgsList_2243) {

    // Arrange

    OptionalContentGroup dummyOcg1;

    OptionalContentGroup dummyOcg2;



    ocgs->getOCGs()[Ref()] = std::make_unique<OptionalContentGroup>(dummyOcg1);

    ocgs->getOCGs()[Ref(1, 0)] = std::make_unique<OptionalContentGroup>(dummyOcg2);



    // Act

    GList* items = get_optional_content_items(ocgs.get());



    // Assert

    EXPECT_EQ(g_list_length(items), 2);

    EXPECT_TRUE(GPOINTER_TO_INT(g_list_nth_data(items, 0)) == &dummyOcg1); // Reversed order

    EXPECT_TRUE(GPOINTER_TO_INT(g_list_nth_data(items, 1)) == &dummyOcg2);



    g_list_free_full(items, g_free);

}



TEST_F(GetOptionalContentItemsTest_2243, ValidOrderArray_ReturnsSortedOcgsList_2243) {

    // Arrange

    OptionalContentGroup dummyOcg1;

    OptionalContentGroup dummyOcg2;



    ocgs->getOCGs()[Ref()] = std::make_unique<OptionalContentGroup>(dummyOcg1);

    ocgs->getOCGs()[Ref(1, 0)] = std::make_unique<OptionalContentGroup>(dummyOcg2);



    Array orderArray;

    Ref ref1(), ref2(1, 0);

    orderArray.add(ref1);

    orderArray.add(ref2);



    EXPECT_CALL(*ocgs, getOrderArray()).WillRepeatedly(Return(&orderArray));



    // Act

    GList* items = get_optional_content_items(ocgs.get());



    // Assert

    EXPECT_EQ(g_list_length(items), 2);

    EXPECT_TRUE(GPOINTER_TO_INT(g_list_nth_data(items, 0)) == &dummyOcg1); // Sorted order

    EXPECT_TRUE(GPOINTER_TO_INT(g_list_nth_data(items, 1)) == &dummyOcg2);



    g_list_free_full(items, g_free);

}



TEST_F(GetOptionalContentItemsTest_2243, EmptyOCGs_ReturnsEmptyList_2243) {

    // Arrange

    EXPECT_CALL(*ocgs, getOrderArray()).WillRepeatedly(Return(nullptr));



    // Act

    GList* items = get_optional_content_items(ocgs.get());



    // Assert

    EXPECT_EQ(g_list_length(items), 0);



    g_list_free_full(items, g_free);

}
