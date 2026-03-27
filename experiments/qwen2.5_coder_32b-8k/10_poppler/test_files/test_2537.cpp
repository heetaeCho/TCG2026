#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructTreeRoot.h"



using namespace testing;



class PopplerStructureElementIterTest_2537 : public ::testing::Test {

protected:

    PopplerDocument *document;

    StructTreeRoot *structTreeRootMock;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument *>(g_slice_new0(PopplerDocument));

        structTreeRootMock = new StrictMock<StructTreeRoot>();

        document->doc = structTreeRootMock;  // Assuming doc is a pointer to StructTreeRoot

    }



    void TearDown() override {

        g_object_unref(document);

        delete structTreeRootMock;

    }

};



TEST_F(PopplerStructureElementIterTest_2537, NewIteratorWithValidDocumentAndChildren_2537) {

    EXPECT_CALL(*structTreeRootMock, getNumChildren()).WillOnce(Return(1));

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);

    ASSERT_NE(iter, nullptr);

    g_slice_free(PopplerStructureElementIter, iter);

}



TEST_F(PopplerStructureElementIterTest_2537, NewIteratorWithValidDocumentNoChildren_2537) {

    EXPECT_CALL(*structTreeRootMock, getNumChildren()).WillOnce(Return(0));

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);

    ASSERT_EQ(iter, nullptr);

}



TEST_F(PopplerStructureElementIterTest_2537, NewIteratorWithNullDocument_2537) {

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(nullptr);

    ASSERT_EQ(iter, nullptr);

}



TEST_F(PopplerStructureElementIterTest_2537, NewIteratorWithStructTreeRootNull_2537) {

    document->doc = nullptr;

    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(document);

    ASSERT_EQ(iter, nullptr);

}
