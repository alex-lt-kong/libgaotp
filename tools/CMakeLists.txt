include_directories (${PROJECT_SOURCE_DIR}/src/) 

add_executable(gaotptool gaotptool.c)
target_link_libraries(gaotptool mycrypto gaotp m)

install(TARGETS gaotptool 
        LIBRARY DESTINATION bin
)