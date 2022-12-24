set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_library(MYCRYPTO_LIB mycrypto)
if(NOT MYCRYPTO_LIB)
  message(FATAL_ERROR "mycrypto library not found")
endif()

add_library(libgaotp libgaotp.c)

target_link_libraries(libgaotp mycrypto)

set_target_properties(libgaotp PROPERTIES PUBLIC_HEADER "libgaotp.h")

install(TARGETS libgaotp 
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION gaotp
)
