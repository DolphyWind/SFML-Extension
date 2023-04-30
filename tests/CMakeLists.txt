include(CTest)
enable_testing()

function(run_test exec_name src_name)    
    add_executable(${exec_name} ${src_name})
    target_link_libraries(${exec_name} sfml-graphics sfml-system sfml-window sfml-audio SFEX)
    add_test(NAME ${exec_name} COMMAND ${exec_name})
endfunction(run_test)

run_test(Vector2Test vector2test.cpp)
# add_executable(Vector2Test vector2test.cpp)
# target_link_libraries(Vector2Test sfml-graphics sfml-system sfml-window sfml-audio SFEX)
# add_test(NAME Vector2Test COMMAND Vector2Test)