#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included and namespaces are properly handled



class OCGsMock : public OCGs {

public:

    MOCK_METHOD(const OptionalContentGroup*, findOcgByRef, (Ref ref), (const, override));

};



using ::testing::Return;

using ::testing::_;



TEST_F(PopplerDocumentTest_2242, EmptyOrderArray_ReturnsEmptyList_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array emptyOrder(nullptr);



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &emptyOrder);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2242, SingleDictInOrder_ReturnsSingleLayer_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref(1, 0);

    OptionalContentGroup* ocg = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref)).WillOnce(Return(ocg));



    Object dictObj(new Dict());

    dictObj.dictAdd("Ref", Object(ref));

    order.add(std::move(dictObj));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);

    Layer* layer = static_cast<Layer*>(result->data);

    EXPECT_EQ(layer->oc, ocg);



    g_list_free_full(result, [](void* item) { delete static_cast<Layer*>(item); });

}



TEST_F(PopplerDocumentTest_2242, NestedArrayInOrder_ReturnsNestedLayers_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref(1, 0);

    OptionalContentGroup* ocg = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref)).WillOnce(Return(ocg));



    Object dictObj(new Dict());

    dictObj.dictAdd("Ref", Object(ref));

    order.add(std::move(dictObj));



    Array nestedOrder(nullptr);

    Object nestedArrayObj(&nestedOrder);

    order.add(std::move(nestedArrayObj));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);



    Layer* parentLayer = static_cast<Layer*>(result->data);

    EXPECT_EQ(parentLayer->oc, ocg);

    EXPECT_NE(parentLayer->kids, nullptr);



    g_list_free_full(result, [](void* item) {

        auto layer = static_cast<Layer*>(item);

        g_list_free(layer->kids);

        delete layer;

    });

}



TEST_F(PopplerDocumentTest_2242, StringInOrder_SetsLabelForLastLayer_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref(1, 0);

    OptionalContentGroup* ocg = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref)).WillOnce(Return(ocg));



    Object dictObj(new Dict());

    dictObj.dictAdd("Ref", Object(ref));

    order.add(std::move(dictObj));



    std::string label = "TestLabel";

    Object stringObj(label);

    order.add(std::move(stringObj));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);



    Layer* layer = static_cast<Layer*>(result->data);

    EXPECT_EQ(layer->oc, ocg);

    EXPECT_STREQ(layer->label, label.c_str());



    g_list_free_full(result, [](void* item) { delete static_cast<Layer*>(item); });

}



TEST_F(PopplerDocumentTest_2242, MultipleDictsInOrder_ReturnsMultipleLayers_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref1(1, 0), ref2(2, 0);

    OptionalContentGroup* ocg1 = new OptionalContentGroup();

    OptionalContentGroup* ocg2 = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref1)).WillOnce(Return(ocg1));

    EXPECT_CALL(mockOcgs, findOcgByRef(ref2)).WillOnce(Return(ocg2));



    Object dictObj1(new Dict());

    dictObj1.dictAdd("Ref", Object(ref1));

    order.add(std::move(dictObj1));



    Object dictObj2(new Dict());

    dictObj2.dictAdd("Ref", Object(ref2));

    order.add(std::move(dictObj2));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);



    Layer* layer1 = static_cast<Layer*>(result->data);

    Layer* layer2 = static_cast<Layer*>(g_list_nth_data(result, 1));

    EXPECT_EQ(layer1->oc, ocg1);

    EXPECT_EQ(layer2->oc, ocg2);



    g_list_free_full(result, [](void* item) { delete static_cast<Layer*>(item); });

}



TEST_F(PopplerDocumentTest_2242, NestedEmptyArrayInOrder_ReturnsSingleLayerWithoutKids_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref(1, 0);

    OptionalContentGroup* ocg = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref)).WillOnce(Return(ocg));



    Object dictObj(new Dict());

    dictObj.dictAdd("Ref", Object(ref));

    order.add(std::move(dictObj));



    Array nestedOrder(nullptr);

    Object nestedArrayObj(&nestedOrder);

    order.add(std::move(nestedArrayObj));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);



    Layer* parentLayer = static_cast<Layer*>(result->data);

    EXPECT_EQ(parentLayer->oc, ocg);

    EXPECT_EQ(parentLayer->kids, nullptr);



    g_list_free_full(result, [](void* item) { delete static_cast<Layer*>(item); });

}



TEST_F(PopplerDocumentTest_2242, InvalidObjectInOrder_IgnoresInvalidItems_2242) {

    OCGsMock mockOcgs(Object(), nullptr);

    Array order(nullptr);



    Ref ref(1, 0);

    OptionalContentGroup* ocg = new OptionalContentGroup();

    EXPECT_CALL(mockOcgs, findOcgByRef(ref)).WillOnce(Return(ocg));



    Object dictObj(new Dict());

    dictObj.dictAdd("Ref", Object(ref));

    order.add(std::move(dictObj));



    Object invalidObj;

    order.add(std::move(invalidObj));



    GList* result = get_optional_content_items_sorted(&mockOcgs, nullptr, &order);

    EXPECT_NE(result, nullptr);



    Layer* layer = static_cast<Layer*>(result->data);

    EXPECT_EQ(layer->oc, ocg);



    g_list_free_full(result, [](void* item) { delete static_cast<Layer*>(item); });

}
