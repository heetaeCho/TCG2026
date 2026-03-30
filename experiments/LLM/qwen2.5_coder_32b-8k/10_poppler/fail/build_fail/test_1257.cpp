#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Gfx.h"



using namespace testing;



class GfxTest : public ::testing::Test {

protected:

    class MockXRef : public XRef {

    public:

        MOCK_METHOD(void, someMethod, (), (override));

    };



    std::unique_ptr<MockXRef> mockXRef;

    Gfx* gfx;



    void SetUp() override {

        mockXRef = std::make_unique<MockXRef>();

        gfx = new Gfx(nullptr, nullptr, 0, nullptr, 0.0, 0.0, nullptr, nullptr, 0, nullptr, nullptr, mockXRef.get());

    }



    void TearDown() override {

        delete gfx;

    }

};



TEST_F(GfxTest_1257, GetXRef_ReturnsNonNullPointer_1257) {

    EXPECT_NE(gfx->getXRef(), nullptr);

}



TEST_F(GfxTest_1257, GetXRef_ReturnsSameInstance_1257) {

    XRef* xref1 = gfx->getXRef();

    XRef* xref2 = gfx->getXRef();

    EXPECT_EQ(xref1, xref2);

}
