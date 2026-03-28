#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



using namespace testing;



// Mock class for Annot

class MockAnnot : public Annot {

public:

    MOCK_METHOD(void, setFlags, (guint flags), (override));

};



class PopplerAnnotTest_2068 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_annot = std::make_shared<MockAnnot>();

        poppler_annot = new PopplerAnnot();

        poppler_annot->annot = mock_annot;

    }



    void TearDown() override {

        delete poppler_annot;

    }



    PopplerAnnot* poppler_annot;

    std::shared_ptr<MockAnnot> mock_annot;

};



TEST_F(PopplerAnnotTest_2068, SetFlagsCallsSetFlagsOnInternalAnnot_2068) {

    EXPECT_CALL(*mock_annot, setFlags(42)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(42));

}



TEST_F(PopplerAnnotTest_2068, SetSameFlagsDoesNotCallSetFlagsOnInternalAnnot_2068) {

    EXPECT_CALL(*mock_annot, setFlags(42)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(42));

    

    // Setting the same flags should not call setFlags again

    EXPECT_CALL(*mock_annot, setFlags(42)).Times(0);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(42));

}



TEST_F(PopplerAnnotTest_2068, SetDifferentFlagsCallsSetFlagsOnInternalAnnotTwice_2068) {

    EXPECT_CALL(*mock_annot, setFlags(42)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(42));

    

    // Setting different flags should call setFlags again

    EXPECT_CALL(*mock_annot, setFlags(84)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(84));

}



TEST_F(PopplerAnnotTest_2068, SetZeroFlagsCallsSetFlagsOnInternalAnnot_2068) {

    EXPECT_CALL(*mock_annot, setFlags(0)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(0));

}



TEST_F(PopplerAnnotTest_2068, SetMaxFlagsCallsSetFlagsOnInternalAnnot_2068) {

    EXPECT_CALL(*mock_annot, setFlags(0xFFFFFFFF)).Times(1);

    poppler_annot_set_flags(poppler_annot, static_cast<PopplerAnnotFlag>(0xFFFFFFFF));

}
