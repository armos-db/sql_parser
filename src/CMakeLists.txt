# Copyright (C) 2013 Louis Hust. All Rights Reserved.

# add the executable
ADD_EXECUTABLE(sql_parser sql_parser.c)

# add the install targets
install (TARGETS sql_parser DESTINATION bin)
