if(${PLATFORM} STREQUAL "nrf52840")
    message("*** Board: nrf52dongle")
    add_library(nrf52dongle)
    target_sources(nrf52dongle
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nrf52dongle/coco/board/config.hpp
        PRIVATE
            nrf52dongle/coco/board/debug.cpp
            nrf52dongle/coco/board/SystemInit.cpp
    )
    target_include_directories(nrf52dongle
        PRIVATE
            nrf52dongle/
    )
    target_link_libraries(nrf52dongle
        coco::coco
    )

    # install the component library
    install(TARGETS nrf52dongle
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nrf52dongle/nrf52dongle.ld nrf52dongle/nrf_common.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32f042x6")
    message("*** Board: canable 0.2") # LEDs on GPIOB0 and 1 (similar to cantact)
    add_library(canable02)
    target_sources(canable02
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            canable02/coco/board/config.hpp
        PRIVATE
            canable02/coco/board/debug.cpp
            canable02/coco/board/SystemInit.cpp
    )
    target_include_directories(canable02
        PRIVATE
            canable02/
    )
    target_link_libraries(canable02
        coco::coco
    )

    # install the component library
    install(TARGETS canable02
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES canable02/canable02.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32f051x8")
    message("*** Board: stm32f0discovery")
    add_library(stm32f0discovery)
    target_sources(stm32f0discovery
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            stm32f0discovery/coco/board/config.hpp
        PRIVATE
            stm32f0discovery/coco/board/debug.cpp
            stm32f0discovery/coco/board/SystemInit.cpp
    )
    target_include_directories(stm32f0discovery
        PRIVATE
            stm32f0discovery/
    )
    target_link_libraries(stm32f0discovery
        coco::coco
    )

    # install the component library
    install(TARGETS stm32f0discovery
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES stm32f0discovery/stm32f0discovery.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32f334x8")
    message("*** Board: stm32f3348discovery")
    add_library(stm32f3348discovery)
    target_sources(stm32f3348discovery
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            stm32f3348discovery/coco/board/config.hpp
        PRIVATE
            stm32f3348discovery/coco/board/debug.cpp
            stm32f3348discovery/coco/board/SystemInit.cpp
    )
    target_include_directories(stm32f3348discovery
        PRIVATE
            stm32f3348discovery/
    )
    target_link_libraries(stm32f3348discovery
        coco::coco
    )

    # install the component library
    install(TARGETS stm32f3348discovery
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES stm32f3348discovery/stm32f3348discovery.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32f401xe")
    message("*** Board: nucleo-f401re")
    add_library(nucleo-f401re)
    target_sources(nucleo-f401re
        PUBLIC FILE_SET headers TYPE HEADERS FILES
        nucleo-f401re/coco/board/config.hpp
        PRIVATE
            nucleo-f401re/coco/board/debug.cpp
            nucleo-f401re/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-f401re
        PRIVATE
            nucleo-f401re/
    )
    target_link_libraries(nucleo-f401re
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-f401re
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-f401re/nucleo-f401re.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32c031xx")
    message("*** Board: nucleo-c031c6")
    add_library(nucleo-c031c6)
    target_sources(nucleo-c031c6
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-c031c6/coco/board/config.hpp
        PRIVATE
            nucleo-c031c6/coco/board/debug.cpp
            nucleo-c031c6/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-c031c6
        PRIVATE
            nucleo-c031c6/
    )
    target_link_libraries(nucleo-c031c6
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-c031c6
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-c031c6/nucleo-c031c6.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g0b1xx")
    message("*** Board: nucleo-g0b1re")
    add_library(nucleo-g0b1re)
    target_sources(nucleo-g0b1re
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-g0b1re/coco/board/config.hpp
        PRIVATE
            nucleo-g0b1re/coco/board/debug.cpp
            nucleo-g0b1re/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-g0b1re
        PRIVATE
            nucleo-g0b1re/
    )
    target_link_libraries(nucleo-g0b1re
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-g0b1re
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-g0b1re/nucleo-g0b1re.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g431xx")
    message("*** Board: nucleo-g431rb")
    add_library(nucleo-g431rb)
    target_sources(nucleo-g431rb
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-g431rb/coco/board/config.hpp
        PRIVATE
            nucleo-g431rb/coco/board/debug.cpp
            nucleo-g431rb/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-g431rb
        PRIVATE
            nucleo-g431rb/
    )
    target_link_libraries(nucleo-g431rb
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-g431rb
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-g431rb/nucleo-g431rb.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g474xx")
    message("*** Board: nucleo-g474re")
    add_library(nucleo-g474re)
    target_sources(nucleo-g474re
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-g474re/coco/board/config.hpp
        PRIVATE
            nucleo-g431rb/coco/board/debug.cpp # use debug.cpp from g431
            nucleo-g474re/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-g474re
        PRIVATE
            nucleo-g474re/
    )
    target_link_libraries(nucleo-g474re
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-g474re
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-g474re/nucleo-g474re.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g491xx")
    message("*** Board: nucleo-g491re")
    add_library(nucleo-g491re)
    target_sources(nucleo-g491re
        PUBLIC FILE_SET headers TYPE HEADERS FILES
        nucleo-g491re/coco/board/config.hpp
        PRIVATE
            nucleo-g431rb/coco/board/debug.cpp # use debug.cpp from g431
            nucleo-g491re/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-g491re
        PRIVATE
            nucleo-g491re/
    )
    target_link_libraries(nucleo-g491re
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-g491re
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-g491re/nucleo-g491re.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32h503xx")
    message("*** Board: nucleo-h503rb")
    add_library(nucleo-h503rb)
    target_sources(nucleo-h503rb
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-h503rb/coco/board/config.hpp
        PRIVATE
            nucleo-h503rb/coco/board/debug.cpp
            nucleo-h503rb/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-h503rb
        PRIVATE
            nucleo-h503rb/
    )
    target_link_libraries(nucleo-h503rb
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-h503rb
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-h503rb/nucleo-h503rb.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32h563xx")
    message("*** Board: nucleo-h563zi")
    add_library(nucleo-h563zi)
    target_sources(nucleo-h563zi
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-h563zi/coco/board/config.hpp
        PRIVATE
            nucleo-h503rb/coco/board/debug.cpp # use debug.cpp from h503
            nucleo-h563zi/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-h563zi
        PRIVATE
            nucleo-h563zi/
    )
    target_link_libraries(nucleo-h563zi
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-h563zi
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-h563zi/nucleo-h563zi.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32u385xx")
    message("*** Board: nucleo-u385rg-q")
    add_library(nucleo-u385rg-q)
    target_sources(nucleo-u385rg-q
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            nucleo-u385rg-q/coco/board/config.hpp
        PRIVATE
            nucleo-u385rg-q/coco/board/debug.cpp
            nucleo-u385rg-q/coco/board/SystemInit.cpp
    )
    target_include_directories(nucleo-u385rg-q
        PRIVATE
            nucleo-u385rg-q/
    )
    target_link_libraries(nucleo-u385rg-q
        coco::coco
    )

    # install the component library
    install(TARGETS nucleo-u385rg-q
        FILE_SET headers DESTINATION include/coco/board
    )
    install(FILES nucleo-u385rg-q/nucleo-u385rg-q.ld DESTINATION lib)
elseif(NOT ${CMAKE_CROSSCOMPILING})
    # default dummy board for native platforms (Windows, MacOS, Linux)
    message("*** Board: ${PLATFORM}")
    add_library(${PLATFORM})
    target_sources(${PLATFORM}
        PUBLIC FILE_SET headers TYPE HEADERS FILES
            native/coco/board/config.hpp # empty config file
        PRIVATE
            native/coco/board/dummy.cpp # needed so that it compiles
    )
    target_link_libraries(${PLATFORM}
        coco::coco
    )

    # install the component library
    install(TARGETS ${PLATFORM}
        FILE_SET headers DESTINATION include/coco/board
    )
else()
    # microcontrollers without development board
    message("*** No board available for ${PLATFORM}")
endif()
