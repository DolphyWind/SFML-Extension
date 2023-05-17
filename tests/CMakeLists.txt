include(CTest)
enable_testing()

function(run_test exec_name src_name)    
    add_executable(${exec_name} ${src_name})
    target_link_libraries(${exec_name} sfml-graphics sfml-system sfml-window sfml-audio SFEX)
    add_test(NAME ${exec_name} COMMAND ${exec_name})
endfunction(run_test)

run_test(Vector2Test vector2test.cpp)
run_test(Vector3Test vector3test.cpp)
run_test(MultitypeTest multitype_test.cpp)