#include <gtest/gtest.h>
#include "mm.h"

TEST(MemoryManager, Init)
{
  memory_manager *mm;
  mm = mm_create(1000);

  char* s = (char*)mm_alloc(mm, 5);
  memset(s, '1', 5);
  char* s2 = (char*)mm_alloc(mm, 8);
  memset(s2, '2', 8);
  char* s3 = (char*)mm_alloc(mm, 8);
  memset(s3, '3', 8);

  EXPECT_EQ(s[4], '1');
  EXPECT_EQ(s2[7], '2');
  EXPECT_EQ(s3[0], '3');
  EXPECT_EQ(s3[0], s2[8]);
  EXPECT_EQ(&s3[0], &s2[8]);
  mm_destroy(mm);
}

TEST(MemoryManager, AddNewBlk)
{
  memory_manager *mm;
  mm = mm_create(1000);

  char* s = (char*)mm_alloc(mm, 2000);
  memset(s, '1', 2000);

  EXPECT_EQ(s[1999], '1');
  mm_destroy(mm);
}
