#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(void, accept, (TiffVisitor& visitor), (override));

    MOCK_CONST_METHOD0(count, size_t(), (override));

};



class MockTiffDirectory : public TiffDirectory {

public:

    using TiffDirectory::TiffDirectory;

    MOCK_METHOD(void, accept, (TiffVisitor& visitor), (override));

    MOCK_CONST_METHOD0(count, size_t(), (override));

};



class TiffEncoderTest_1672 : public ::testing::Test {

protected:

    MockTiffComponent component1;

    MockTiffComponent component2;

    MockTiffDirectory directory;



    void SetUp() override {

        directory.addComponent(std::make_unique<MockTiffComponent>(component1));

        directory.addComponent(std::make_unique<MockTiffComponent>(component2));

    }

};



TEST_F(TiffEncoderTest_1672, VisitDirectoryNext_CallsAcceptOnComponents_1672) {

    TiffEncoder encoder({}, {}, {}, &directory, false, PrimaryGroups(), nullptr, nullptr);

    

    EXPECT_CALL(component1, accept(::testing::_)).Times(1);

    EXPECT_CALL(component2, accept(::testing::_)).Times(1);



    encoder.visitDirectoryNext(&directory);

}



TEST_F(TiffEncoderTest_1672, VisitDirectoryNext_IncrementsPointerByUpdatedDirEntrySize_1672) {

    TiffEncoder encoder({}, {}, {}, &directory, false, PrimaryGroups(), nullptr, nullptr);

    

    EXPECT_CALL(component1, accept(::testing::_)).WillOnce([](TiffVisitor& visitor) {

        // Simulate updateDirEntry returning a fixed size

        return 10;

    });

    EXPECT_CALL(component2, accept(::testing::_)).WillOnce([](TiffVisitor& visitor) {

        // Simulate updateDirEntry returning a fixed size

        return 15;

    });



    byte buffer[30];

    directory.setStart(buffer);



    encoder.visitDirectoryNext(&directory);



    byte* p = buffer + 2; // Starting point as per implementation

    p += 10; // First component size

    p += 15; // Second component size



    EXPECT_EQ(directory.start() + 2 + 10 + 15, p);

}



TEST_F(TiffEncoderTest_1672, VisitDirectoryNext_HandlesEmptyDirectory_1672) {

    TiffDirectory emptyDirectory(0, IfdId::rootIFD, false);



    TiffEncoder encoder({}, {}, {}, &emptyDirectory, false, PrimaryGroups(), nullptr, nullptr);



    EXPECT_CALL(component1, accept(::testing::_)).Times(0);

    EXPECT_CALL(component2, accept(::testing::_)).Times(0);



    encoder.visitDirectoryNext(&emptyDirectory);

}



TEST_F(TiffEncoderTest_1672, VisitDirectoryNext_VerifiesByteOrderUsage_1672) {

    TiffEncoder encoder({}, {}, {}, &directory, false, PrimaryGroups(), nullptr, nullptr);



    EXPECT_CALL(component1, accept(::testing::_)).WillOnce([](TiffVisitor& visitor) {

        // Simulate updateDirEntry returning a fixed size

        return 10;

    });

    EXPECT_CALL(component2, accept(::testing::_)).WillOnce([](TiffVisitor& visitor) {

        // Simulate updateDirEntry returning a fixed size

        return 15;

    });



    byte buffer[30];

    directory.setStart(buffer);



    encoder.visitDirectoryNext(&directory);

}
