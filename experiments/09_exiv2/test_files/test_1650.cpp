#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class MockTiffBinaryElement : public TiffBinaryElement {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));

};



TEST_F(TiffCopierTest_1650, VisitBinaryElement_CallsCopyObject_1650) {

    MockTiffBinaryElement mockBinaryElement;

    TiffCopier copier(nullptr, 0, nullptr, {});



    EXPECT_CALL(mockBinaryElement, doAccept(testing::_))

        .WillOnce(testing::Invoke([&mockBinaryElement](TiffVisitor& visitor) {

            visitor.copyObject(&mockBinaryElement);

        }));



    copier.visitBinaryElement(&mockBinaryElement);

}
