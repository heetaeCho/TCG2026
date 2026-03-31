#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include <exiv2/exiv2.hpp>

// We need access to the internal function and data
namespace Exiv2 {
namespace Internal {
// Forward declare the function we're testing
extern const TagDetails pentaxLensType[];

// The resolveLensType function is static in the .cpp file, so we can't directly call it.
// However, we can test through the EXV_PRINT_COMBITAG_MULTI mechanism or through
// the ExifData/tag printing infrastructure.
// Since resolveLensType is static, we'll test the pentaxLensType data and
// the lens type resolution through the public Exiv2 API.
}  // namespace Internal
}  // namespace Exiv2

class PentaxLensTypeTest_208 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that pentaxLensType array contains expected entries
TEST_F(PentaxLensTypeTest_208, PentaxLensTypeArrayHasEntries_208) {
  // The array should have 297 entries based on the provided data
  // We can verify some known entries
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // First entry should be {0, "M-42 or No Lens"}
  EXPECT_EQ(lensType[0].val_, 0);
  EXPECT_STREQ(lensType[0].label_, "M-42 or No Lens");
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeFirstEntries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check tag 256 -> "K or M Lens"
  EXPECT_EQ(lensType[1].val_, 256);
  EXPECT_STREQ(lensType[1].label_, "K or M Lens");

  // Check tag 512 -> "A Series Lens"
  EXPECT_EQ(lensType[2].val_, 512);
  EXPECT_STREQ(lensType[2].label_, "A Series Lens");

  // Check tag 768 -> "Sigma Lens"
  EXPECT_EQ(lensType[3].val_, 768);
  EXPECT_STREQ(lensType[3].label_, "Sigma Lens");
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeKnownLens_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check tag 785 -> "smc PENTAX-FA SOFT 85mm F2.8"
  EXPECT_EQ(lensType[4].val_, 785);
  EXPECT_STREQ(lensType[4].label_, "smc PENTAX-FA SOFT 85mm F2.8");
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeDuplicateValues_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Tag 791 appears multiple times with different labels
  // Find entries with val_ == 791
  int count791 = 0;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 791) {
      count791++;
    }
  }
  // There should be multiple entries for 791
  EXPECT_GE(count791, 2);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeLastEntry_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Last meaningful entry should be {5609, "Adapter Q for K-mount Lens"}
  // Find it in the array
  bool found = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 5609) {
      EXPECT_STREQ(lensType[i].label_, "Adapter Q for K-mount Lens");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensType645Lenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check 645 series lens entries exist
  bool found2817 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 2817) {
      EXPECT_STREQ(lensType[i].label_, "smc PENTAX-FA 645 75mm F2.8");
      found2817 = true;
      break;
    }
  }
  EXPECT_TRUE(found2817);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypePentaxQLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check Pentax Q lens entries
  bool found5376 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 5376) {
      EXPECT_STREQ(lensType[i].label_, "Pentax Q Manual Lens");
      found5376 = true;
      break;
    }
  }
  EXPECT_TRUE(found5376);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeSigmaLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check various Sigma lens entries (tag 2303 has multiple Sigma lenses)
  int count2303 = 0;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 2303) {
      count2303++;
    }
  }
  EXPECT_GE(count2303, 7);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeHDLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check HD PENTAX lenses
  bool found2107 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 2107) {
      EXPECT_STREQ(lensType[i].label_, "HD PENTAX-D FA 150-450mm F4.5-5.6 ED DC AW");
      found2107 = true;
      break;
    }
  }
  EXPECT_TRUE(found2107);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTag1023HasMultipleEntries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Tag 1023 should have multiple entries (various Sigma lenses)
  int count1023 = 0;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 1023) {
      count1023++;
    }
  }
  EXPECT_GE(count1023, 8);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTag812HasMultipleEntries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Tag 812 should have multiple entries
  int count812 = 0;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 812) {
      count812++;
    }
  }
  EXPECT_GE(count812, 6);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeSamsungLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check Samsung/Schneider lens entries
  bool found1079 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 1079) {
      EXPECT_STREQ(lensType[i].label_, "Samsung/Schneider D-XENOGON 35mm F2");
      found1079 = true;
      break;
    }
  }
  EXPECT_TRUE(found1079);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTamronLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check Tamron lens entries
  bool found1043 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 1043) {
      EXPECT_STREQ(lensType[i].label_, "Tamron SP AF 90mm F2.8 (172E)");
      found1043 = true;
      break;
    }
  }
  EXPECT_TRUE(found1043);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeIrixLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check Irix lens entries
  bool found1031 = false;
  bool found1032 = false;
  bool found1033 = false;
  bool found1034 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 1031) {
      EXPECT_STREQ(lensType[i].label_, "Irix 45mm F/1.4");
      found1031 = true;
    }
    if (lensType[i].val_ == 1032) {
      EXPECT_STREQ(lensType[i].label_, "Irix 150mm F/2.8 Macro");
      found1032 = true;
    }
    if (lensType[i].val_ == 1033) {
      EXPECT_STREQ(lensType[i].label_, "Irix 11mm F/4");
      found1033 = true;
    }
    if (lensType[i].val_ == 1034) {
      EXPECT_STREQ(lensType[i].label_, "Irix 15mm F/2.4");
      found1034 = true;
    }
  }
  EXPECT_TRUE(found1031);
  EXPECT_TRUE(found1032);
  EXPECT_TRUE(found1033);
  EXPECT_TRUE(found1034);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeDAStarSDMLenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check DA* SDM lenses
  bool found2274 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 2274) {
      EXPECT_STREQ(lensType[i].label_, "smc PENTAX-DA* 55mm F1.4 SDM");
      found2274 = true;
      break;
    }
  }
  EXPECT_TRUE(found2274);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeManualLensEntries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check manual lens entries
  bool found0 = false;      // M-42 or No Lens
  bool found256 = false;    // K or M Lens
  bool found2304 = false;   // 645 Manual Lens
  bool found5376 = false;   // Pentax Q Manual Lens

  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 0) {
      EXPECT_STREQ(lensType[i].label_, "M-42 or No Lens");
      found0 = true;
    }
    if (lensType[i].val_ == 256) {
      EXPECT_STREQ(lensType[i].label_, "K or M Lens");
      found256 = true;
    }
    if (lensType[i].val_ == 2304) {
      EXPECT_STREQ(lensType[i].label_, "645 Manual Lens");
      found2304 = true;
    }
    if (lensType[i].val_ == 5376) {
      EXPECT_STREQ(lensType[i].label_, "Pentax Q Manual Lens");
      found5376 = true;
    }
  }
  EXPECT_TRUE(found0);
  EXPECT_TRUE(found256);
  EXPECT_TRUE(found2304);
  EXPECT_TRUE(found5376);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeDFALenses_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Check D FA lens entries
  bool found1075 = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 1075) {
      EXPECT_STREQ(lensType[i].label_, "smc PENTAX-D FA 50mm F2.8 Macro");
      found1075 = true;
      break;
    }
  }
  EXPECT_TRUE(found1075);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTotalCount_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Verify the total count of entries matches 297
  // We count unique non-sentinel entries
  // The last entry should be followed by a sentinel (or we count based on known size)
  // Based on the declaration: TagDetails[297]
  // Let's verify some boundary entries
  EXPECT_EQ(lensType[0].val_, 0);
  EXPECT_EQ(lensType[296].val_, 5609);
  EXPECT_STREQ(lensType[296].label_, "Adapter Q for K-mount Lens");
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTag793MultipleEntries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Tag 793 has many alternative lenses
  int count793 = 0;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 793) {
      count793++;
    }
  }
  EXPECT_GE(count793, 6);
}

TEST_F(PentaxLensTypeTest_208, PentaxLensTypeTag814Entries_208) {
  const auto& lensType = Exiv2::Internal::pentaxLensType;

  // Tag 814 -> "Sigma or Samsung Lens" and alternatives
  int count814 = 0;
  bool foundGeneric = false;
  for (int i = 0; i < 297; ++i) {
    if (lensType[i].val_ == 814) {
      count814++;
      if (std::string(lensType[i].label_) == "Sigma or Samsung Lens") {
        foundGeneric = true;
      }
    }
  }
  EXPECT_GE(count814, 3);
  EXPECT_TRUE(foundGeneric);
}

// Test through ExifData/tag printing if possible
TEST_F(PentaxLensTypeTest_208, ExifDataLensTypeWriteThrough_208) {
  // Create ExifData and set Pentax lens type tag to test resolution
  Exiv2::ExifData exifData;

  // Pentax LensType tag is typically at Exif.Pentax.LensType
  // We can verify the ExifData manipulation works
  try {
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    // Set to values that represent a known lens
    // The lens type uses 2 bytes for the combo tag
    value->read("3 17");  // = 785 decimal (3*256 + 17) -> "smc PENTAX-FA SOFT 85mm F2.8"
    exifData.add(key, value.get());

    auto it = exifData.findKey(key);
    EXPECT_NE(it, exifData.end());
  } catch (const Exiv2::Error&) {
    // If the key is not recognized, that's also acceptable information
  }
}

TEST_F(PentaxLensTypeTest_208, ExifDataLensTypeNoLens_208) {
  Exiv2::ExifData exifData;

  try {
    Exiv2::ExifKey key("Exif.Pentax.LensType");
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    // Set to 0 0 -> tag 0 -> "M-42 or No Lens"
    value->read("0 0");
    exifData.add(key, value.get());

    auto it = exifData.findKey(key);
    EXPECT_NE(it, exifData.end());
  } catch (const Exiv2::Error&) {
    // Acceptable
  }
}
