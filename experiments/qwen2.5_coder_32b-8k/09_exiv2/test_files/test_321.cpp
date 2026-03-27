#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::NiceMock;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(TiffComponent*, addPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, UniquePtr object), (override));

    MOCK_METHOD(TiffComponent*, addChild, (SharedPtr tiffComponent), (override));

};



class MockTiffDirectory : public TiffDirectory {

public:

    using TiffDirectory::TiffDirectory;

    MOCK_METHOD(TiffComponent*, addPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, UniquePtr object), (override));

};



class TiffSubIfdTest : public ::testing::Test {

protected:

    TiffSubIfd subifd{123, IfdId::subIfd0, IfdId::exif};

    NiceMock<MockTiffComponent> mockRoot;

    NiceMock<MockTiffDirectory> mockDirectory{456, IfdId::subIfd0};

};



TEST_F(TiffSubIfdTest_321, EmptyPath_ReturnsThis_321) {

    TiffPath tiffPath;

    auto result = subifd.doAddPath(789, tiffPath, &mockRoot, nullptr);

    EXPECT_EQ(result, &subifd);

}



TEST_F(TiffSubIfdTest_321, SingleItemPath_ReturnsAddedChild_321) {

    TiffPath tiffPath;

    TiffPathItem item{789, IfdId::subIfd0};

    tiffPath.push(item);



    EXPECT_CALL(mockRoot, addChild(::testing::_))

        .WillOnce(::testing::Return(&mockDirectory));



    auto result = subifd.doAddPath(123, tiffPath, &mockRoot, nullptr);

    EXPECT_EQ(result, &mockDirectory);

}



TEST_F(TiffSubIfdTest_321, MultipleItemsPath_ReturnsChildAddedToMatchingGroup_321) {

    TiffPath tiffPath;

    TiffPathItem item1{789, IfdId::subIfd0};

    TiffPathItem item2{456, IfdId::subIfd0};

    tiffPath.push(item1);

    tiffPath.push(item2);



    EXPECT_CALL(mockDirectory, addPath(::testing::_, ::testing::Ref(tiffPath), &mockRoot, nullptr))

        .WillOnce(::testing::Return(&mockDirectory));



    auto result = subifd.doAddPath(123, tiffPath, &mockRoot, nullptr);

    EXPECT_EQ(result, &mockDirectory);

}



TEST_F(TiffSubIfdTest_321, NoMatchingGroup_ReturnsNewChildAdded_321) {

    TiffPath tiffPath;

    TiffPathItem item{789, IfdId::subIfd0};

    tiffPath.push(item);



    EXPECT_CALL(mockRoot, addChild(::testing::_))

        .WillOnce(::testing::Return(&mockDirectory));



    auto result = subifd.doAddPath(123, tiffPath, &mockRoot, nullptr);

    EXPECT_EQ(result, &mockDirectory);

}



TEST_F(TiffSubIfdTest_321, ObjectProvided_ReturnsAddedObjectToNewChild_321) {

    TiffPath tiffPath;

    TiffPathItem item{789, IfdId::subIfd0};

    tiffPath.push(item);



    auto mockObject = std::make_unique<MockTiffComponent>();

    EXPECT_CALL(mockRoot, addChild(::testing::_))

        .WillOnce(::testing::Return(&mockDirectory));



    EXPECT_CALL(mockDirectory, addPath(::testing::_, ::testing::Ref(tiffPath), &mockRoot, nullptr))

        .WillOnce(::testing::Return(mockObject.get()));



    auto result = subifd.doAddPath(123, tiffPath, &mockRoot, std::move(mockObject));

    EXPECT_EQ(result, mockObject.get());

}



TEST_F(TiffSubIfdTest_321, CountUpdatedAfterAddingChild_321) {

    TiffPath tiffPath;

    TiffPathItem item{789, IfdId::subIfd0};

    tiffPath.push(item);



    EXPECT_CALL(mockRoot, addChild(::testing::_))

        .WillOnce(::testing::Return(&mockDirectory));



    subifd.doAddPath(123, tiffPath, &mockRoot, nullptr);

    EXPECT_EQ(subifd.count(), 1);

}
