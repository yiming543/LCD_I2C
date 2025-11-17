# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(LCD_I2C_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(LCD_I2C_default_default_XC8_FILE_TYPE_assemble)
add_library(LCD_I2C_default_default_XC8_assemble OBJECT ${LCD_I2C_default_default_XC8_FILE_TYPE_assemble})
    LCD_I2C_default_default_XC8_assemble_rule(LCD_I2C_default_default_XC8_assemble)
    list(APPEND LCD_I2C_default_library_list "$<TARGET_OBJECTS:LCD_I2C_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(LCD_I2C_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(LCD_I2C_default_default_XC8_assemblePreprocess OBJECT ${LCD_I2C_default_default_XC8_FILE_TYPE_assemblePreprocess})
    LCD_I2C_default_default_XC8_assemblePreprocess_rule(LCD_I2C_default_default_XC8_assemblePreprocess)
    list(APPEND LCD_I2C_default_library_list "$<TARGET_OBJECTS:LCD_I2C_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(LCD_I2C_default_default_XC8_FILE_TYPE_compile)
add_library(LCD_I2C_default_default_XC8_compile OBJECT ${LCD_I2C_default_default_XC8_FILE_TYPE_compile})
    LCD_I2C_default_default_XC8_compile_rule(LCD_I2C_default_default_XC8_compile)
    list(APPEND LCD_I2C_default_library_list "$<TARGET_OBJECTS:LCD_I2C_default_default_XC8_compile>")
endif()

add_executable(LCD_I2C_default_image_POtMoOPl ${LCD_I2C_default_library_list})

set_target_properties(LCD_I2C_default_image_POtMoOPl PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${LCD_I2C_default_output_dir})
set_target_properties(LCD_I2C_default_image_POtMoOPl PROPERTIES OUTPUT_NAME "default")
set_target_properties(LCD_I2C_default_image_POtMoOPl PROPERTIES SUFFIX ".elf")

target_link_libraries(LCD_I2C_default_image_POtMoOPl PRIVATE ${LCD_I2C_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
LCD_I2C_default_link_rule(LCD_I2C_default_image_POtMoOPl)



