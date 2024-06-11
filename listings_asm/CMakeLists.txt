set(project_name "asm_listings")

set(asm
	listing_0037_single_register_mov
	listing_0038_many_register_mov
)

foreach(file ${asm})
	add_custom_command(
		OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file}
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${file}.asm
		COMMAND nasm -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.asm
	)

	list(APPEND asm_results ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${file})
endforeach()

add_custom_target(${project_name} ALL
	DEPENDS ${asm_results}
)

