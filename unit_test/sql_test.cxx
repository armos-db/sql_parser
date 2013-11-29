#include <gtest/gtest.h>
#include "sql_parser.h"

TEST(LexcialTest, Integer)
{
  int ret;

  ret = parse_sql("0", 1, NULL);
  EXPECT_EQ(ret, 0);
}
