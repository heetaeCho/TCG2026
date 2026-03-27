#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry* object), (override));

};



class TiffSizeEntryTest_341 : public ::testing::Test {

protected:

    uint16_t tag = 1;

    IfdId group = ifd0Id;

    uint16_t dtTag = 2;

    IfdId dtGroup = ifd1Id;

    TiffSizeEntry entry{tag, group, dtTag, dtGroup};

};



TEST_F(TiffSizeEntryTest_341, ConstructorInitializesValues_341) {

    EXPECT_EQ(entry.dtTag(), dtTag);

    EXPECT_EQ(entry.dtGroup(), dtGroup);

}



TEST_F(TiffSizeEntryTest_341, DoAcceptCallsVisitSizeEntryOnVisitor_341) {

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visitSizeEntry(&entry)).Times(1);

    entry.doAccept(mockVisitor);

}
