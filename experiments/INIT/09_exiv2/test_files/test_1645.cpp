// File: test_tiffcopier_visitsizeentry_1645.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// These are internal headers in the Exiv2 codebase (per prompt paths).
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using ::testing::_;
using ::testing::StrictMock;

namespace {

// A strict mock visitor to verify external interaction via the visitor interface.
// (We do not mock or simulate internal behavior of TiffCopier.)
class MockTiffVisitor : public Exiv2::Internal::TiffVisitor {
public:
  MOCK_METHOD(void, visitEntry, (Exiv2::Internal::TiffEntry*), (override));
  MOCK_METHOD(void, visitDataEntry, (Exiv2::Internal::TiffDataEntry*), (override));
  MOCK_METHOD(void, visitImageEntry, (Exiv2::Internal::TiffImageEntry*), (override));
  MOCK_METHOD(void, visitSizeEntry, (Exiv2::Internal::TiffSizeEntry*), (override));
  MOCK_METHOD(void, visitDirectory, (Exiv2::Internal::TiffDirectory*), (override));
  MOCK_METHOD(void, visitSubIfd, (Exiv2::Internal::TiffSubIfd*), (override));
  MOCK_METHOD(void, visitMnEntry, (Exiv2::Internal::TiffMnEntry*), (override));
  MOCK_METHOD(void, visitIfdMakernote, (Exiv2::Internal::TiffIfdMakernote*), (override));
  MOCK_METHOD(void, visitBinaryArray, (Exiv2::Internal::TiffBinaryArray*), (override));
  MOCK_METHOD(void, visitBinaryElement, (Exiv2::Internal::TiffBinaryElement*), (override));
};

}  // namespace

// -------------------------
// TiffSizeEntry getters
// -------------------------

TEST(TiffSizeEntryTest_1645, GettersReturnCtorValues_1645) {
  using namespace Exiv2::Internal;

  const uint16_t tag = 0x0100;
  const IfdId group = static_cast<IfdId>(0);
  const uint16_t dtTag = 0x0101;
  const IfdId dtGroup = static_cast<IfdId>(1);

  TiffSizeEntry entry(tag, group, dtTag, dtGroup);

  EXPECT_EQ(entry.dtTag(), dtTag);
  EXPECT_EQ(entry.dtGroup(), dtGroup);
}

TEST(TiffSizeEntryTest_1645, GettersHandleBoundaryValues_1645) {
  using namespace Exiv2::Internal;

  const uint16_t tag = 0;
  const IfdId group = static_cast<IfdId>(0);
  const uint16_t dtTag = std::numeric_limits<uint16_t>::max();
  const IfdId dtGroup = static_cast<IfdId>(std::numeric_limits<int>::max());

  TiffSizeEntry entry(tag, group, dtTag, dtGroup);

  EXPECT_EQ(entry.dtTag(), dtTag);
  EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// -------------------------
// External interaction via accept() -> visitor.visitSizeEntry(...)
// -------------------------

TEST(TiffSizeEntryTest_1645, AcceptInvokesVisitSizeEntryOnVisitor_1645) {
  using namespace Exiv2::Internal;

  TiffSizeEntry entry(/*tag=*/0x0100,
                      /*group=*/static_cast<IfdId>(0),
                      /*dtTag=*/0x0101,
                      /*dtGroup=*/static_cast<IfdId>(1));

  StrictMock<MockTiffVisitor> visitor;
  EXPECT_CALL(visitor, visitSizeEntry(&entry)).Times(1);

  // We rely only on the public interface: typical Exiv2 components expose accept().
  // If your build uses a different public entry point, adjust this call accordingly.
  entry.accept(visitor);
}

// -------------------------
// TiffCopier::visitSizeEntry smoke/boundary behavior
// ----------------_toggle
// -------------------------

TEST(TiffCopierTest_1645, VisitSizeEntryDoesNotThrowWithMinimalConstruction_1645) {
  using namespace Exiv2::Internal;

  // Construct with minimal/neutral arguments (nullptrs + empty groups).
  // This test treats implementation as a black box and only checks observable behavior:
  // calling visitSizeEntry should be callable and not throw exceptions.
  PrimaryGroups primaryGroups;
  TiffCopier copier(/*pRoot=*/nullptr,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/std::move(primaryGroups));

  TiffSizeEntry entry(/*tag=*/0x0100,
                      /*group=*/static_cast<IfdId>(0),
                      /*dtTag=*/0x0101,
                      /*dtGroup=*/static_cast<IfdId>(1));

  EXPECT_NO_THROW(copier.visitSizeEntry(&entry));
}

TEST(TiffCopierTest_1645, VisitSizeEntryAcceptsBoundaryTagValues_1645) {
  using namespace Exiv2::Internal;

  PrimaryGroups primaryGroups;
  TiffCopier copier(/*pRoot=*/nullptr,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/std::move(primaryGroups));

  TiffSizeEntry entryMin(/*tag=*/0,
                         /*group=*/static_cast<IfdId>(0),
                         /*dtTag=*/0,
                         /*dtGroup=*/static_cast<IfdId>(0));

  TiffSizeEntry entryMax(/*tag=*/std::numeric_limits<uint16_t>::max(),
                         /*group=*/static_cast<IfdId>(1),
                         /*dtTag=*/std::numeric_limits<uint16_t>::max(),
                         /*dtGroup=*/static_cast<IfdId>(2));

  EXPECT_NO_THROW(copier.visitSizeEntry(&entryMin));
  EXPECT_NO_THROW(copier.visitSizeEntry(&entryMax));
}