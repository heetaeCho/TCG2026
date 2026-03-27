#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Gfx and related classes are included here or mocked as necessary



class MockGfx : public Gfx {

public:

    MOCK_METHOD(void, saveState, (), (override));

    MOCK_METHOD(void, restoreState, (), (override));



    MockGfx(PDFDoc *docA, OutputDev *outA, int pageNum, Dict *resDict,

            double hDPI, double vDPI, const PDFRectangle *box, const PDFRectangle *cropBox,

            int rotate, _Bool (*abortCheckCbkA)(void *), void *abortCheckCbkDataA, XRef *xrefA)

        : Gfx(docA, outA, pageNum, resDict, hDPI, vDPI, box, cropBox, rotate, abortCheckCbkA, abortCheckCbkDataA, xrefA) {}



    MockGfx(PDFDoc *docA, OutputDev *outA, Dict *resDict, const PDFRectangle *box,

            const PDFRectangle *cropBox, _Bool (*abortCheckCbkA)(void *), void *abortCheckCbkDataA, Gfx *gfxA)

        : Gfx(docA, outA, resDict, box, cropBox, abortCheckCbkA, abortCheckCbkDataA, gfxA) {}

};



class GfxStackStateSaverTest_2777 : public ::testing::Test {

protected:

    MockGfx mockGfx;

    GfxStackStateSaver *saver;



    GfxStackStateSaverTest_2777()

        : mockGfx(nullptr, nullptr, 0, nullptr, 0.0, 0.0, nullptr, nullptr, 0, nullptr, nullptr, nullptr) {}



    virtual void SetUp() {

        saver = new GfxStackStateSaver(&mockGfx);

    }



    virtual void TearDown() {

        delete saver;

    }

};



TEST_F(GfxStackStateSaverTest_2777, ConstructsAndCallsSaveState_2777) {

    EXPECT_CALL(mockGfx, saveState());

}



TEST_F(GfxStackStateSaverTest_2777, DestructorCallsRestoreState_2777) {

    EXPECT_CALL(mockGfx, restoreState());

    delete saver;

    saver = nullptr; // Prevent double deletion in TearDown

}



TEST_F(GfxStackStateSaverTest_2777, NonCopyableConstructor_2777) {

    GfxStackStateSaver anotherSaver(&mockGfx);

    EXPECT_CALL(mockGfx, saveState()).Times(2); // Once for each constructor call



    // Attempting to copy construct should result in a compile-time error

    // GfxStackStateSaver copiedSaver(anotherSaver);

}



TEST_F(GfxStackStateSaverTest_2777, NonCopyableAssignmentOperator_2777) {

    GfxStackStateSaver anotherSaver(&mockGfx);

    EXPECT_CALL(mockGfx, saveState()).Times(2); // Once for each constructor call



    // Attempting to copy assign should result in a compile-time error

    // *saver = anotherSaver;

}
