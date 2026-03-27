#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and namespaces are included

namespace Exiv2 { namespace Internal {



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visit, (const TiffComponent&), (override));

};



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

};



TEST_F(TiffComponentTest_228, SetStartAndGetStart_228) {

    TiffComponent component(0x123, IfdId::root);

    const byte data[] = { 0x01, 0x02, 0x03 };

    component.setStart(data);

    EXPECT_EQ(component.start(), data);

}



TEST_F(TiffComponentTest_228, TagAndGroupInitialization_228) {

    uint16_t tag = 0x456;

    IfdId group = IfdId::exif;

    TiffComponent component(tag, group);

    EXPECT_EQ(component.tag(), tag);

    EXPECT_EQ(component.group(), group);

}



TEST_F(TiffComponentTest_228, AcceptVisitor_228) {

    MockTiffVisitor mockVisitor;

    TiffComponent component(0x789, IfdId::sub);

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(component))).Times(1);

    component.accept(mockVisitor);

}



TEST_F(TiffComponentTest_228, WriteDataReturnsZero_228) {

    MockIoWrapper mockIo;

    TiffComponent component(0xABC, IfdId::gps);

    size_t offset = 0, dataIdx = 0, imageIdx = 0;

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(0); // Expect no writes

    EXPECT_EQ(component.writeData(mockIo, ByteOrder::bigEndian, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffComponentTest_228, WriteImageReturnsZero_228) {

    MockIoWrapper mockIo;

    TiffComponent component(0xDEF, IfdId::interoperability);

    EXPECT_CALL(mockIo, write(::testing::_, ::testing::_)).Times(0); // Expect no writes

    EXPECT_EQ(component.writeImage(mockIo, ByteOrder::littleEndian), 0);

}



TEST_F(TiffComponentTest_228, SizeMethodsReturnZeroByDefault_228) {

    TiffComponent component(0x135, IfdId::thumbnail);

    EXPECT_EQ(component.size(), 0);

    EXPECT_EQ(component.count(), 0);

    EXPECT_EQ(component.sizeData(), 0);

    EXPECT_EQ(component.sizeImage(), 0);

}



TEST_F(TiffComponentTest_228, CloneReturnsNonNullPointer_228) {

    TiffComponent component(0x246, IfdId::root);

    auto clone = component.clone();

    EXPECT_NE(clone.get(), nullptr);

}



}} // namespace Exiv2::Internal
