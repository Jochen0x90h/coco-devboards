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
	message("*** Board: stm32f401nucleo")
	add_library(stm32f401nucleo)
	target_sources(stm32f401nucleo
		PUBLIC FILE_SET headers TYPE HEADERS FILES
		stm32f401nucleo/coco/board/config.hpp
		PRIVATE
			stm32f401nucleo/coco/board/debug.cpp
			stm32f401nucleo/coco/board/SystemInit.cpp
	)
	target_include_directories(stm32f401nucleo
		PRIVATE
			stm32f401nucleo/
	)
	target_link_libraries(stm32f401nucleo
		coco::coco
	)

	# install the component library
	install(TARGETS stm32f401nucleo
		FILE_SET headers DESTINATION include/coco/board
	)
	install(FILES stm32f401nucleo/stm32f401nucleo.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32c031xx")
	message("*** Board: stm32gc031nucleo")
	add_library(stm32c031nucleo)
	target_sources(stm32c031nucleo
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			stm32c031nucleo/coco/board/config.hpp
		PRIVATE
			stm32c031nucleo/coco/board/debug.cpp
			stm32c031nucleo/coco/board/SystemInit.cpp
	)
	target_include_directories(stm32c031nucleo
		PRIVATE
			stm32c031nucleo/
	)
	target_link_libraries(stm32c031nucleo
		coco::coco
	)

	# install the component library
	install(TARGETS stm32c031nucleo
		FILE_SET headers DESTINATION include/coco/board
	)
	install(FILES stm32c031nucleo/stm32c031nucleo.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g431xx")
	message("*** Board: stm32g431nucleo")
	add_library(stm32g431nucleo)
	target_sources(stm32g431nucleo
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			stm32g431nucleo/coco/board/config.hpp
		PRIVATE
			stm32g431nucleo/coco/board/debug.cpp
			stm32g431nucleo/coco/board/SystemInit.cpp
	)
	target_include_directories(stm32g431nucleo
		PRIVATE
			stm32g431nucleo/
	)
	target_link_libraries(stm32g431nucleo
		coco::coco
	)

	# install the component library
	install(TARGETS stm32g431nucleo
		FILE_SET headers DESTINATION include/coco/board
	)
	install(FILES stm32g431nucleo/stm32g431nucleo.ld DESTINATION lib)
elseif(${PLATFORM} STREQUAL "stm32g474xx")
	message("*** Board: stm32g474nucleo")
	add_library(stm32g474nucleo)
	target_sources(stm32g474nucleo
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			stm32g474nucleo/coco/board/config.hpp
		PRIVATE
			stm32g431nucleo/coco/board/debug.cpp
			stm32g474nucleo/coco/board/SystemInit.cpp
	)
	target_include_directories(stm32g474nucleo
		PRIVATE
			stm32g474nucleo/
	)
	target_link_libraries(stm32g474nucleo
		coco::coco
	)

	# install the component library
	install(TARGETS stm32g474nucleo
		FILE_SET headers DESTINATION include/coco/board
	)
	install(FILES stm32g474nucleo/stm32g474nucleo.ld DESTINATION lib)
else()
    # default dummy board for native platforms (Windows, MacOS, Linux)
	message("*** Board: ${PLATFORM}")
	add_library(native)
	target_sources(native
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			native/coco/board/config.hpp # empty config file
		PRIVATE
			native/coco/board/dummy.cpp # needed so that it compiles
	)
	target_link_libraries(native
		coco::coco
	)

	# install the component library
	install(TARGETS native
		FILE_SET headers DESTINATION include/coco/board
	)
endif()
