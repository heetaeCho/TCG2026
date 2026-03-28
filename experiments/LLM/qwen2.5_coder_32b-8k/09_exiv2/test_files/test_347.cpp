#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement* object), (override));

};



class TiffBinaryElementTest_347 : public ::testing::Test {

protected:

    TiffBinaryElement element;

    MockTiffVisitor mockVisitor;

};



TEST_F(TiffBinaryElementTest_347, DoAcceptCallsVisitBinaryElement_347) {

    EXPECT_CALL(mockVisitor, visitBinaryElement(&element));

    element.doAccept(mockVisitor);

}



TEST_F(TiffBinaryElementTest_347, SetAndGetElDef_347) {

    ArrayDef def = {10, ttUndefined, 20};

    element.setElDef(def);

    EXPECT_EQ(element.elDef()->count, def.count);

    EXPECT_EQ(element.elDef()->type, def.type);

    EXPECT_EQ(element.elDef()->size, def.size);

}



TEST_F(TiffBinaryElementTest_347, SetAndGetElByteOrder_347) {

    ByteOrder byteOrder = littleEndian;

    element.setElByteOrder(byteOrder);

    EXPECT_EQ(element.elByteOrder(), byteOrder);

}
