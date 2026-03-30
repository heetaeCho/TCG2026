#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cairo/cairo.h>

#include "TestProjects/poppler/poppler/CairoOutputDev.cc"

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/Object.h"



class CairoSurfaceMock : public cairo_surface_t {

public:

    MOCK_METHOD(cairo_status_t, set_mime_data_mock, 

                (const char *mime_type, const unsigned char *data, size_t length,

                 cairo_destroy_func_t destroy, void *closure), ());

};



extern "C" {

cairo_status_t cairo_surface_set_mime_data(cairo_surface_t *surface, 

                                           const char *mime_type, 

                                           const unsigned char *data, 

                                           size_t length,

                                           cairo_destroy_func_t destroy, 

                                           void *closure) {

    auto mockSurface = static_cast<CairoSurfaceMock*>(surface);

    return mockSurface->set_mime_data_mock(mime_type, data, length, destroy, closure);

}

}



class CairoOutputDevTest_1929 : public ::testing::Test {

protected:

    Ref ref;

    CairoSurfaceMock surface;



    void SetUp() override {

        ref.num = 42;

        ref.gen = 6;

    }

};



TEST_F(CairoOutputDevTest_1929, NormalOperation_1929) {

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 8, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_SUCCESS));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", nullptr, ref);

    EXPECT_EQ(result, CAIRO_STATUS_SUCCESS);

}



TEST_F(CairoOutputDevTest_1929, WithPrefix_1929) {

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 14, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_SUCCESS));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", "prefix-", ref);

    EXPECT_EQ(result, CAIRO_STATUS_SUCCESS);

}



TEST_F(CairoOutputDevTest_1929, SurfaceSetMimeDataFailure_1929) {

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 8, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_NO_MEMORY));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", nullptr, ref);

    EXPECT_EQ(result, CAIRO_STATUS_NO_MEMORY);

}



TEST_F(CairoOutputDevTest_1929, BoundaryConditionNegativeNum_1929) {

    ref.num = -1;

    

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 8, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_SUCCESS));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", nullptr, ref);

    EXPECT_EQ(result, CAIRO_STATUS_SUCCESS);

}



TEST_F(CairoOutputDevTest_1929, BoundaryConditionNegativeGen_1929) {

    ref.gen = -1;

    

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 8, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_SUCCESS));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", nullptr, ref);

    EXPECT_EQ(result, CAIRO_STATUS_SUCCESS);

}



TEST_F(CairoOutputDevTest_1929, BoundaryConditionZeroNumAndGen_1929) {

    ref.num = 0;

    ref.gen = 0;

    

    EXPECT_CALL(surface, set_mime_data_mock("test/type", _, 4, gfree, _))

        .WillOnce(::testing::Return(CAIRO_STATUS_SUCCESS));

    

    cairo_status_t result = setMimeIdFromRef(&surface, "test/type", nullptr, ref);

    EXPECT_EQ(result, CAIRO_STATUS_SUCCESS);

}
