#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external collaborators if needed

class MockTiffDirectory : public Exiv2::Internal::TiffDirectory {

public:

    MOCK_METHOD(const byte*, start, (), (const, override));

    MOCK_METHOD(IfdId, group, (), (const, override));

    MOCK_METHOD(bool, hasNext, (), (const, override));

    MOCK_METHOD(void, addChild, (Exiv2::Internal::TiffComponent::SharedPtr), (override));

    MOCK_METHOD(void, addNext, (Exiv2::Internal::TiffComponent::UniquePtr), (override));

};



class MockTiffCreator {

public:

    static std::unique_ptr<Exiv2::Internal::TiffComponent> create(uint32_t extendedTag, Exiv2::IfdId group) {

        return nullptr;

    }

};



namespace Exiv2 {

namespace Internal {



TEST_F(MockTiffDirectoryTest_1703, NormalOperationWithEntries_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, false);

    const byte data[] = {0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));

    EXPECT_CALL(mockDir, addChild(::testing::_)).Times(2);



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, NormalOperationWithNextPointer_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, true);

    const byte data[] = {0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));

    EXPECT_CALL(mockDir, addChild(::testing::_)).Times(2);

    EXPECT_CALL(mockDir, addNext(::testing::_)).Times(1);



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, DirectoryExceedsDataBuffer_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, false);

    const byte data[] = {0x00, 0x02};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, TooManyEntries_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, false);

    const byte data[] = {0x01, 0x02};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, EntryOutsideDataBuffer_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, false);

    const byte data[] = {0x00, 0x02, 0xff, 0xff};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, NextPointerOutsideDataBuffer_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, true);

    const byte data[] = {0x00, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));

    EXPECT_CALL(mockDir, addChild(::testing::_)).Times(2);



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, NextPointerOutOfBounds_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, true);

    const byte data[] = {0x00, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));

    EXPECT_CALL(mockDir, addChild(::testing::_)).Times(2);



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, UnableToHandleTag_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, false);

    const byte data[] = {0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));



    // Mock TiffCreator to return nullptr for any tag

    EXPECT_CALL(MockTiffCreator::create(::testing::_, ::testing::_)).WillRepeatedly(::testing::Return(nullptr));



    reader.visitDirectory(&mockDir);

}



TEST_F(MockTiffDirectoryTest_1703, UnexpectedNextPointer_1703) {

    MockTiffDirectory mockDir(0, IfdId::root, true);

    const byte data[] = {0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01};

    TiffReader reader(data, sizeof(data), &mockDir, TiffRwState());



    EXPECT_CALL(mockDir, start()).WillOnce(::testing::Return(&data[2]));

    EXPECT_CALL(mockDir, group()).WillRepeatedly(::testing::Return(IfdId::root));

    EXPECT_CALL(mockDir, addChild(::testing::_)).Times(2);



    // Mock TiffCreator to return nullptr for the next pointer tag

    EXPECT_CALL(MockTiffCreator::create(Tag::next, ::testing::_)).WillOnce(::testing::Return(nullptr));



    reader.visitDirectory(&mockDir);

}



}  // namespace Internal

}  // namespace Exiv2
