set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_library(MYCRYPTO_LIB mycrypto)
if(NOT MYCRYPTO_LIB)
  message(
    FATAL_ERROR "mycrypto library not found, follow the link to build it first: https://github.com/alex-lt-kong/libmycrypto"
  )
endif()

add_library(gaotp SHARED gaotp.c)

target_link_libraries(gaotp mycrypto)

set_target_properties(gaotp PROPERTIES PUBLIC_HEADER "gaotp.h")

install(TARGETS gaotp)
