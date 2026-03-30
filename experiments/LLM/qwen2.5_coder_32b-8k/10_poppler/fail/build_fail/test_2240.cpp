#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/OCGs.h"

#include "./TestProjects/poppler/poppler/Object.h"

#include "./TestProjects/poppler/poppler/Array.h"



using namespace testing;



class OCGsMock : public OCGs {

public:

    MOCK_METHOD(const Array*, getRBGroupsArray, (), (const, override));

    MOCK_METHOD(OptionalContentGroup*, findOcgByRef, (Ref ref), (override));



    OCGsMock(const Object& ocgObject, XRef* xref) : OCGs(ocgObject, xref) {}

};



class GetOptionalContentRBGroupsTest_2240 : public ::testing::Test {

protected:

    NiceMock<OCGsMock> mockOcg;

    Ref ref1 = {1, 0};

    Ref ref2 = {2, 0};

    OptionalContentGroup* ocg1 = new OptionalContentGroup();

    OptionalContentGroup* ocg2 = new OptionalContentGroup();



    GetOptionalContentRBGroupsTest_2240() : mockOcg(Object(), nullptr) {

        ON_CALL(mockOcg, findOcgByRef(ref1)).WillByDefault(Return(ocg1));

        ON_CALL(mockOcg, findOcgByRef(ref2)).WillByDefault(Return(ocg2));

    }



    ~GetOptionalContentRBGroupsTest_2240() {

        delete ocg1;

        delete ocg2;

    }

};



TEST_F(GetOptionalContentRBGroupsTest_2240, EmptyArray_ReturnsEmptyList_2240) {

    auto mockArray = std::make_unique<StrictMock<Array>>(nullptr);

    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(mockArray.get()));



    GList* result = get_optional_content_rbgroups(&mockOcg);



    EXPECT_EQ(result, nullptr);

}



TEST_F(GetOptionalContentRBGroupsTest_2240, SingleGroupWithTwoRefs_ReturnsNestedList_2240) {

    auto mockArray1 = std::make_unique<StrictMock<Array>>(nullptr);

    Object refObj1(ref1);

    Object refObj2(ref2);



    EXPECT_CALL(*mockArray1, getLength()).WillOnce(Return(2));

    EXPECT_CALL(*mockArray1, getNF(0)).WillOnce(ReturnRef(refObj1));

    EXPECT_CALL(*mockArray1, getNF(1)).WillOnce(ReturnRef(refObj2));



    auto mockRBGroupsArray = std::make_unique<StrictMock<Array>>(nullptr);

    EXPECT_CALL(*mockRBGroupsArray, getLength()).WillOnce(Return(1));

    EXPECT_CALL(*mockRBGroupsArray, get(0, _)).WillOnce(Return(Object(mockArray1.release())));



    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(mockRBGroupsArray.get()));



    GList* result = get_optional_content_rbgroups(&mockOcg);

    ASSERT_NE(result, nullptr);



    GList* innerList = static_cast<GList*>(result->data);

    ASSERT_EQ(g_list_length(innerList), 2);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(innerList->data), ocg1);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(g_list_nth_data(innerList, 1)), ocg2);



    g_list_free_full(result, [](void* l) { g_list_free_full(static_cast<GList*>(l), nullptr); });

}



TEST_F(GetOptionalContentRBGroupsTest_2240, MultipleGroups_ReturnsMultipleNestedLists_2240) {

    auto mockArray1 = std::make_unique<StrictMock<Array>>(nullptr);

    Object refObj1(ref1);



    EXPECT_CALL(*mockArray1, getLength()).WillOnce(Return(1));

    EXPECT_CALL(*mockArray1, getNF(0)).WillOnce(ReturnRef(refObj1));



    auto mockArray2 = std::make_unique<StrictMock<Array>>(nullptr);

    Object refObj2(ref2);



    EXPECT_CALL(*mockArray2, getLength()).WillOnce(Return(1));

    EXPECT_CALL(*mockArray2, getNF(0)).WillOnce(ReturnRef(refObj2));



    auto mockRBGroupsArray = std::make_unique<StrictMock<Array>>(nullptr);

    EXPECT_CALL(*mockRBGroupsArray, getLength()).WillOnce(Return(2));

    EXPECT_CALL(*mockRBGroupsArray, get(0, _)).WillOnce(Return(Object(mockArray1.release())));

    EXPECT_CALL(*mockRBGroupsArray, get(1, _)).WillOnce(Return(Object(mockArray2.release())));



    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(mockRBGroupsArray.get()));



    GList* result = get_optional_content_rbgroups(&mockOcg);

    ASSERT_NE(result, nullptr);



    GList* innerList1 = static_cast<GList*>(result->data);

    EXPECT_EQ(g_list_length(innerList1), 1);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(innerList1->data), ocg1);



    GList* innerList2 = static_cast<GList*>(g_list_nth_data(result, 1));

    EXPECT_EQ(g_list_length(innerList2), 1);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(innerList2->data), ocg2);



    g_list_free_full(result, [](void* l) { g_list_free_full(static_cast<GList*>(l), nullptr); });

}



TEST_F(GetOptionalContentRBGroupsTest_2240, NonArrayElements_IgnoredInInnerArray_2240) {

    auto mockArray1 = std::make_unique<StrictMock<Array>>(nullptr);

    Object nonArrayObj(Object::error());

    Object refObj(ref1);



    EXPECT_CALL(*mockArray1, getLength()).WillOnce(Return(2));

    EXPECT_CALL(*mockArray1, getNF(0)).WillOnce(ReturnRef(nonArrayObj));

    EXPECT_CALL(*mockArray1, getNF(1)).WillOnce(ReturnRef(refObj));



    auto mockRBGroupsArray = std::make_unique<StrictMock<Array>>(nullptr);

    EXPECT_CALL(*mockRBGroupsArray, getLength()).WillOnce(Return(1));

    EXPECT_CALL(*mockRBGroupsArray, get(0, _)).WillOnce(Return(Object(mockArray1.release())));



    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(mockRBGroupsArray.get()));



    GList* result = get_optional_content_rbgroups(&mockOcg);

    ASSERT_NE(result, nullptr);



    GList* innerList = static_cast<GList*>(result->data);

    ASSERT_EQ(g_list_length(innerList), 1);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(innerList->data), ocg1);



    g_list_free_full(result, [](void* l) { g_list_free_full(static_cast<GList*>(l), nullptr); });

}



TEST_F(GetOptionalContentRBGroupsTest_2240, NonRefElements_IgnoredInInnerArray_2240) {

    auto mockArray1 = std::make_unique<StrictMock<Array>>(nullptr);

    Object nonRefObj(5);

    Object refObj(ref1);



    EXPECT_CALL(*mockArray1, getLength()).WillOnce(Return(2));

    EXPECT_CALL(*mockArray1, getNF(0)).WillOnce(ReturnRef(nonRefObj));

    EXPECT_CALL(*mockArray1, getNF(1)).WillOnce(ReturnRef(refObj));



    auto mockRBGroupsArray = std::make_unique<StrictMock<Array>>(nullptr);

    EXPECT_CALL(*mockRBGroupsArray, getLength()).WillOnce(Return(1));

    EXPECT_CALL(*mockRBGroupsArray, get(0, _)).WillOnce(Return(Object(mockArray1.release())));



    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(mockRBGroupsArray.get()));



    GList* result = get_optional_content_rbgroups(&mockOcg);

    ASSERT_NE(result, nullptr);



    GList* innerList = static_cast<GList*>(result->data);

    ASSERT_EQ(g_list_length(innerList), 1);

    EXPECT_EQ(static_cast<OptionalContentGroup*>(innerList->data), ocg1);



    g_list_free_full(result, [](void* l) { g_list_free_full(static_cast<GList*>(l), nullptr); });

}



TEST_F(GetOptionalContentRBGroupsTest_2240, NullArray_ReturnsEmptyList_2240) {

    EXPECT_CALL(mockOcg, getRBGroupsArray()).WillOnce(Return(nullptr));



    GList* result = get_optional_content_rbgroups(&mockOcg);



    EXPECT_EQ(result, nullptr);

}
