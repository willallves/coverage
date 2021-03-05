add_executable(MaiorTests main_test.cpp)

target_link_libraries(MaiorTests
    ${GTEST_LIBRARIES}
    pthread
    maior
)

add_test(aaa_test MaiorTests)

add_executable(SqrtTests sqrt_test.cpp)

target_link_libraries(SqrtTests
    ${GTEST_LIBRARIES}
    pthread
    sqrt
) 

add_test(bbb_test SqrtTests)
