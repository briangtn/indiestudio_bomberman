#
# A CMake module to find Irrkland for the project B-YEP-400 IndieStudio
#
# This CMake module is designed to work on Fedora28 and Windows10. We will not
# provide support for other distributions. We will use this module to compile
# your project during our tests.
#
# You must provide the path to this module to CMake by setting
# CMAKE_MODULE_PATH variable to its location.
#
# Once done this module will define:
#  Irrklang_FOUND - system has Irrklang
#  Irrklang_INCLUDE_DIRS - the Irrklang include directory
#  Irrklang_LIBRARIES - Link these to use Irrklang
#

IF (NOT Irrklang_INCLUDE_DIRS OR NOT Irrklang_LIBRARIES)
  FIND_PATH(Irrklang_INCLUDE_DIRS
    NAMES
      irrKlang.h
    PATHS
      /usr/include/Irrklang/        # Default Fedora28 system include path
      /usr/local/include/Irrklang/  # Default Fedora28 local include path
      ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
      ${Irrklang_DIR}/include/      # Irrklang root directory (if provided)
  )

  IF (MSVC)     # Windows
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  ELSE (MSVC)   # Linux
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  ENDIF(MSVC)

  FIND_LIBRARY(Irrklang_LIBRARIES
    NAMES
      IrrKlang
    PATHS
      /usr/lib64/                   # Default Fedora28 library path
      /usr/lib/                     # Some more Linux library path
      /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
      /usr/local/lib/               # Some more Linux library path
      /usr/local/lib64/             # Some more Linux library path
      ${CMAKE_MODULE_PATH}/         # Expected to contain the path to this file for Windows10
      ${Irrklang_DIR}/              # Irrklang root directory (if provided)
  )
ENDIF (NOT Irrklang_INCLUDE_DIRS OR NOT Irrklang_LIBRARIES)

IF (Irrklang_INCLUDE_DIRS AND Irrklang_LIBRARIES)
  SET(Irrklang_FOUND TRUE)
ELSE (Irrklang_INCLUDE_DIRS AND Irrklang_LIBRARIES)
  SET(Irrklang_FOUND FALSE)
ENDIF (Irrklang_INCLUDE_DIRS AND Irrklang_LIBRARIES)

IF (Irrklang_FIND_REQUIRED AND NOT Irrklang_FOUND)
  MESSAGE(FATAL_ERROR
    "  Irrklang not found.\n"
    "      Windows: Fill CMake variable CMAKE_MODULE_PATH to the provided directory.\n"
    "      Linux: Install Irrklang using the website (https://www.ambiera.com/irrklang/downloads.html).\n"
  )
ENDIF (Irrklang_FIND_REQUIRED AND NOT Irrklang_FOUND)
