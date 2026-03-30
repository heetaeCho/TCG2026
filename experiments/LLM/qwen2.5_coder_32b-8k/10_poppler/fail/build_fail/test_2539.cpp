#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    struct _PopplerStructureElementIter;

    typedef struct _PopplerStructureElementIter PopplerStructureElementIter;

    struct _PopplerStructureElement;

    typedef struct _PopplerStructureElement PopplerStructureElement;



    PopplerStructureElement *poppler_structure_element_iter_get_element(PopplerStructureElementIter *iter);

}



class MockStructElement : public StructElement {

public:

    MOCK_METHOD(unsigned, getNumChildren, (), (const, override));

    MOCK_METHOD(const StructElement*, getChild, (int i), (const, override));

};



class MockStructTreeRoot : public StructTreeRoot {

public:

    MockStructTreeRoot(PDFDoc* docA, const Dict& rootDict) : StructTreeRoot(docA, rootDict) {}

    MOCK_METHOD(unsigned, getNumChildren, (), (const, override));

    MOCK_METHOD(const StructElement*, getChild, (int i), (const, override));

};



class PopplerStructureElementIterTest_2539 : public ::testing::Test {

protected:

    void SetUp() override {

        iter.is_root = 1;

        iter.root = &mockRoot;

        iter.index = 0;

    }



    MockStructTreeRoot mockRoot{nullptr, Dict()};

    PopplerStructureElementIter iter;

};



TEST_F(PopplerStructureElementIterTest_2539, GetElement_NormalOperation_Root_2539) {

    auto* mockChild = new MockStructElement();

    EXPECT_CALL(mockRoot, getChild(0)).WillOnce(::testing::Return(mockChild));



    PopplerStructureElement* result = poppler_structure_element_iter_get_element(&iter);

    EXPECT_NE(result, nullptr);



    delete result;

}



TEST_F(PopplerStructureElementIterTest_2539, GetElement_NormalOperation_NonRoot_2539) {

    MockStructElement mockParent;

    iter.is_root = 0;

    iter.elem = &mockParent;



    auto* mockChild = new MockStructElement();

    EXPECT_CALL(mockParent, getChild(0)).WillOnce(::testing::Return(mockChild));



    PopplerStructureElement* result = poppler_structure_element_iter_get_element(&iter);

    EXPECT_NE(result, nullptr);



    delete result;

}



TEST_F(PopplerStructureElementIterTest_2539, GetElement_BoundaryCondition_IndexOutOfBound_Root_2539) {

    iter.index = mockRoot.getNumChildren();

    EXPECT_CALL(mockRoot, getChild(iter.index)).WillOnce(::testing::Return(nullptr));



    PopplerStructureElement* result = poppler_structure_element_iter_get_element(&iter);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementIterTest_2539, GetElement_BoundaryCondition_IndexOutOfBound_NonRoot_2539) {

    MockStructElement mockParent;

    iter.is_root = 0;

    iter.elem = &mockParent;



    iter.index = mockParent.getNumChildren();

    EXPECT_CALL(mockParent, getChild(iter.index)).WillOnce(::testing::Return(nullptr));



    PopplerStructureElement* result = poppler_structure_element_iter_get_element(&iter);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementIterTest_2539, GetElement_ExceptionalCase_NullIterator_2539) {

    PopplerStructureElement* result = poppler_structure_element_iter_get_element(nullptr);

    EXPECT_EQ(result, nullptr);

}
