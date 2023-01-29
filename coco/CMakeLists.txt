if(${PLATFORM} STREQUAL "native")
	# native "board" for running on Windows, MacOS, Linux
	message("*** Board: native")
	add_library(coco-board-native)
	target_sources(coco-board-native
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			native/coco/board/config.hpp
		PRIVATE
			native/coco/board/debug.cpp
	)
	target_link_libraries(coco-board-native
		coco::coco
	)
	
	# install the component library
	install(TARGETS coco-board-native
		FILE_SET headers DESTINATION include/coco/board
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
elseif(${PLATFORM} STREQUAL "nrf52840")
	message("*** Board: nrf52dongle")
	add_library(coco-board-nrf52dongle)
	target_sources(coco-board-nrf52dongle
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			nrf52dongle/coco/board/config.hpp
		PRIVATE
			nrf52dongle/coco/board/debug.cpp
			nrf52dongle/coco/board/SystemInit.cpp
	)
	target_link_libraries(coco-board-nrf52dongle
		coco::coco
	)

	# install the component library
	install(TARGETS coco-board-nrf52dongle
		FILE_SET headers DESTINATION include/coco/board
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
	install(FILES nrf52dongle/link.ld nrf52dongle/nrf_common.ld DESTINATION include/coco/board/nrf52dongle)
elseif(${PLATFORM} STREQUAL "stm32f051x8")
	message("*** Board: stm32f051discovery")
	add_library(coco-board-stm32f051discovery)
	target_sources(coco-board-stm32f051discovery
		PUBLIC FILE_SET headers TYPE HEADERS FILES
			stm32f051discovery/coco/board/config.hpp
		PRIVATE
			stm32f051discovery/coco/board/debug.cpp
			stm32f051discovery/coco/board/SystemInit.cpp
	)
	target_link_libraries(coco-board-stm32f051discovery
		coco::coco
	)

	# install the component library
	install(TARGETS coco-board-stm32f051discovery
		FILE_SET headers DESTINATION include/coco/board
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
	install(FILES stm32f051discovery/link.ld DESTINATION include/coco/board/stm32f051discovery)
endif()
