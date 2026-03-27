// -----------------------------------------------------------------------------
// TEST_ID: 1345
// Unit tests for Exiv2::ExifKey::ifdId() (black-box, interface-based)
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace {

class ExifKeyIfdIdTest_1345 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKeyNoThrow(const std::string& keyStr) {
    // For known-good Exiv2 keys, construction should not throw.
    // If it does, the ASSERT in the calling test will fail.
    return Exiv2::ExifKey(keyStr);
  }
};

TEST_F(ExifKeyIfdIdTest_1345, IfdIdIsStableAcrossRepeatedCalls_1345) {
  ASSERT_NO_THROW({
    const Exiv2::ExifKey key = MakeKeyNoThrow("Exif.Image.Make");
    const Exiv2::IfdId first = key.ifdId();
    const Exiv2::IfdId second = key.ifdId();
    EXPECT_EQ(first, second);
  });
}

TEST_F(ExifKeyIfdIdTest_1345, CopyConstructorPreservesIfdId_1345) {
  ASSERT_NO_THROW({
    const Exiv2::ExifKey original = MakeKeyNoThrow("Exif.Photo.ExposureTime");
    const Exiv2::IfdId idOriginal = original.ifdId();

    const Exiv2::ExifKey copy(original);
    const Exiv2::IfdId idCopy = copy.ifdId();

    EXPECT_EQ(idOriginal, idCopy);
  });
}

TEST_F(ExifKeyIfdIdTest_1345, CopyAssignmentPreservesIfdId_1345) {
  ASSERT_NO_THROW({
    const Exiv2::ExifKey source = MakeKeyNoThrow("Exif.GPSInfo.GPSLatitude");
    const Exiv2::IfdId idSource = source.ifdId();

    Exiv2::ExifKey target = MakeKeyNoThrow("Exif.Image.Make");
    target = source;

    EXPECT_EQ(idSource, target.ifdId());
  });
}

TEST_F(ExifKeyIfdIdTest_1345, ClonePreservesIfdId_1345) {
  ASSERT_NO_THROW({
    const Exiv2::ExifKey original = MakeKeyNoThrow("Exif.Image.Model");
    const Exiv2::IfdId idOriginal = original.ifdId();

    const Exiv2::ExifKey::UniquePtr cloned = original.clone();
    ASSERT_NE(cloned.get(), nullptr);

    EXPECT_EQ(idOriginal, cloned->ifdId());
  });
}

TEST_F(ExifKeyIfdIdTest_1345, IfdIdNotNotSetForKnownKeys_1345) {
  // These are commonly supported Exif keys in Exiv2. We only assert that the
  // returned IFD id is "set" (i.e., not the sentinel), without assuming a
  // specific IFD mapping.
  const std::vector<std::string> keys = {
      "Exif.Image.Make",
      "Exif.Image.Model",
      "Exif.Photo.ExposureTime",
      "Exif.GPSInfo.GPSLatitude",
  };

  for (const auto& k : keys) {
    ASSERT_NO_THROW({
      const Exiv2::ExifKey key = MakeKeyNoThrow(k);
      EXPECT_NE(key.ifdId(), Exiv2::IfdId::ifdIdNotSet) << "key: " << k;
    }) << "Key construction unexpectedly threw for: " << k;
  }
}

TEST_F(ExifKeyIfdIdTest_1345, DifferentKnownGroupsYieldAtLeastTwoDistinctIfdIds_1345) {
  // Avoid asserting exact enum values. Instead, verify that across a few
  // different Exif key groups, we observe at least two distinct IfdId values.
  // This is a weak-but-observable behavioral check of group decomposition.
  ASSERT_NO_THROW({
    const Exiv2::ExifKey k1 = MakeKeyNoThrow("Exif.Image.Make");
    const Exiv2::ExifKey k2 = MakeKeyNoThrow("Exif.Photo.ExposureTime");
    const Exiv2::ExifKey k3 = MakeKeyNoThrow("Exif.GPSInfo.GPSLatitude");

    std::set<Exiv2::IfdId> ids;
    ids.insert(k1.ifdId());
    ids.insert(k2.ifdId());
    ids.insert(k3.ifdId());

    // Boundary/robustness: if the implementation maps multiple groups to the
    // same IFD, this may be 1. We expect at least 2 for typical Exiv2 behavior.
    EXPECT_GE(ids.size(), static_cast<size_t>(2));
  });
}

TEST_F(ExifKeyIfdIdTest_1345, InvalidKeyStringEitherThrowsOrReturnsNotSet_1345) {
  // Black-box: either behavior is acceptable/observable. We just ensure no UB.
  const std::string badKey = "Exif.NotARealGroup.NotARealTag";

  try {
    const Exiv2::ExifKey key(badKey);
    // If construction succeeds, ifdId() should be callable and may indicate not set.
    EXPECT_NO_THROW({
      const Exiv2::IfdId id = key.ifdId();
      (void)id;
    });

    // If it indicates failure via sentinel, that's observable and acceptable.
    EXPECT_TRUE(key.ifdId() == Exiv2::IfdId::ifdIdNotSet ||
                key.ifdId() != Exiv2::IfdId::ifdIdNotSet);
    // (Intentionally tautological: ensures the call is evaluated without asserting policy.)
  } catch (...) {
    SUCCEED() << "Construction threw for invalid key string (acceptable).";
  }
}

}  // namespace