#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "./TestProjects/exiv2/src/tiffimage_int.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_CONST_METHOD0(tag, uint16_t());

    MOCK_CONST_METHOD0(group, IfdId());

    MOCK_METHOD5(write, size_t(IoWrapper &, ByteOrder, size_t, size_t, size_t &));

    MOCK_METHOD0(clone, UniquePtr());

};



class MockTiffHeaderBase : public TiffHeaderBase {

public:

    MOCK_CONST_METHOD3(isImageTag, bool(uint16_t, IfdId, const PrimaryGroups&));

    MOCK_METHOD1(setByteOrder, void(ByteOrder));

    MOCK_METHOD1(setOffset, void(uint32_t));

};



class MockTiffCreator {

public:

    static std::unique_ptr<TiffComponent> create(uint32_t extendedTag, IfdId group) {

        return std::make_unique<MockTiffComponent>();

    }

    static TiffPath getPath(uint32_t extendedTag, IfdId group, uint32_t root) {

        return TiffPath();

    }

};



class TiffCopierTest : public ::testing::Test {

protected:

    NiceMock<MockTiffHeaderBase> header;

    PrimaryGroups primaryGroups;

    MockTiffComponent rootComponent;

    std::unique_ptr<TiffComponent> pRoot = &rootComponent;



    TiffCopier copier{pRoot.get(), 0, &header, std::move(primaryGroups)};

};



TEST_F(TiffCopierTest, CopyObject_ImageTag_1641) {

    auto mockObject = std::make_unique<NiceMock<MockTiffComponent>>();

    EXPECT_CALL(header, isImageTag(_, _, _)).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockObject, clone()).Times(1);

    EXPECT_CALL(rootComponent, addPath(_, _, _, _)).Times(1);



    copier.copyObject(mockObject.get());

}



TEST_F(TiffCopierTest, CopyObject_NonImageTag_1641) {

    auto mockObject = std::make_unique<NiceMock<MockTiffComponent>>();

    EXPECT_CALL(header, isImageTag(_, _, _)).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockObject, clone()).Times(0);

    EXPECT_CALL(rootComponent, addPath(_, _, _, _)).Times(0);



    copier.copyObject(mockObject.get());

}



TEST_F(TiffCopierTest, CopyObject_NullObject_1641) {

    EXPECT_CALL(header, isImageTag(_, _, _)).Times(0);

    EXPECT_CALL(rootComponent, addPath(_, _, _, _)).Times(0);



    copier.copyObject(nullptr);

}
