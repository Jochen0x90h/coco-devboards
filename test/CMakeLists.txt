# Generate a test for a board
# TEST the test application, implemented in ${TEST}.cpp
# BOARD_LIB a library for a board containing SystemInit() and a linker script for embedded platforms
function(board_test TEST BOARD_LIB)
    # check if board library exists for the current platform
    if(TARGET ${BOARD_LIB})
        string(REGEX REPLACE ".*\\:" "" BOARD ${BOARD_LIB})
        set(NAME "${TEST}-${BOARD}")
        message("*** Test ${TEST} on board ${BOARD}")

        add_executable(${NAME}
            ${TEST}.cpp
        )
        target_include_directories(${NAME}
            PRIVATE
                ../
        )
        target_link_libraries(${NAME}
            ${BOARD_LIB}
        )
        target_link_directories(${NAME}
            PRIVATE
                ../coco/${BOARD}
        )
        target_link_options(${NAME}
            PUBLIC
                LINKER:-T${BOARD}.ld
        )

        # generate hex file for flashing the target
        if(${CMAKE_CROSSCOMPILING})
            #message("*** Generate Hex for ${NAME} using ${CMAKE_OBJCOPY}")
            add_custom_command(TARGET ${NAME}
                POST_BUILD
                COMMAND ${CMAKE_OBJCOPY} -O ihex ${NAME} ${NAME}.hex
            )
        endif()
    endif()
endfunction()

#board_test(SleepTest native) # implemented in coco-loop
#board_test(SleepTest emu) # implemented in coco-loop
board_test(SleepTest nrf52dongle)
board_test(SleepTest canable02)
board_test(SleepTest stm32f0discovery)
board_test(SleepTest stm32f3348discovery)
board_test(SleepTest stm32f401nucleo)
board_test(SleepTest stm32c031nucleo)
board_test(SleepTest stm32g431nucleo)
board_test(SleepTest stm32g474nucleo)
