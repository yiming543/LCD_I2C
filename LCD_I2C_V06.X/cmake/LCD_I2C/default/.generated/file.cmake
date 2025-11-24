# The following variables contains the files used by the different stages of the build process.
set(LCD_I2C_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${LCD_I2C_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${LCD_I2C_default_default_XC8_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(LCD_I2C_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${LCD_I2C_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${LCD_I2C_default_default_XC8_FILE_TYPE_assemblePreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(LCD_I2C_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Key.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../RelayControl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../TimerEven.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../eeprom.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../hd44780_i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/device_config.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/examples/i2c_master_example.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/i2c_master.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/interrupt_manager.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/mcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/pin_manager.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/tmr0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcc_generated_files/tmr1.c")
set_source_files_properties(${LCD_I2C_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(LCD_I2C_default_default_XC8_FILE_TYPE_link)
set(LCD_I2C_default_image_name "default.elf")
set(LCD_I2C_default_image_base_name "default")

# The output directory of the final image.
set(LCD_I2C_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/LCD_I2C")

# The full path to the final image.
set(LCD_I2C_default_full_path_to_image ${LCD_I2C_default_output_dir}/${LCD_I2C_default_image_name})
