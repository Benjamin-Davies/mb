cmake_minimum_required(VERSION 3.10)

project(mb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost
  REQUIRED
  COMPONENTS program_options
  )

include_directories(src ${Boost_INCLUDE_DIRS})

add_executable(mb
  src/mb.cpp
  src/encodings.cpp
  src/options.cpp
  src/maildir/dir.cpp
  src/maildir/entry.cpp
  )

target_link_libraries(mb
  Boost::program_options
  )

install(TARGETS mb)
install(FILES mb.1 DESTINATION share/man/man1/)
