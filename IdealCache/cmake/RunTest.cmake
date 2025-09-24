execute_process(COMMAND "${TEST_PROGRAM}"
    INPUT_FILE "${TEST_INPUT}"
    OUTPUT_FILE "${TEST_OUTPUT}"
    RESULT_VARIABLE program_result
)

if(program_result)
    message(FATAL_ERROR "Test program failed with result: ${program_result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files
    "${TEST_EXPECTED}" "${TEST_OUTPUT}"
    RESULT_VARIABLE compare_result
)

if(compare_result)
    message(FATAL_ERROR "Test failed: ${TEST_INPUT}. Output in ${TEST_OUTPUT}")
endif()

message("Test passed: ${TEST_INPUT}")
