#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)




#
## ERC_TARGET_RESOURCE to create or get embedded resource target
#


function(ERC_ADD_RESOURCES target_name )

  # MADE IT SHARED for other acces with lib prefix

  #
  ##
  set(options ADD_INTO_IDE)
  set(oneValueArgs "")
  set(multiValueArgs "")
  cmake_parse_arguments(ARGUMENTS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
  #
  set(input_erc_xml_package_filepath ${ARGUMENTS_UNPARSED_ARGUMENTS})
  set(ide_add_scanned_files              ${ARGUMENTS_ADD_INTO_IDE})

  #set(inputs_ercs_xmls_packages_filepath ${ARGN})

  #
  ##
  if(NOT TARGET ${target_name})
    message(FATAL_ERROR
      "[ERC_ADD_RESSOURCE]\n"
      "Can't find <target_name> : ${target_name}\n"
      "\n"
    )
    return()
  endif()


  #
  ##
  set(fatal_error_msg)

  #
  if(NOT EXISTS ${ERC_BINARY_PACKAGER})
   set(fatal_error_msg "${fatal_error_msg}Can't find executable embedded_resource_packager on variable ERC_BINARY_PACKAGER : ${ERC_BINARY_PACKAGER}\n")
  endif()
  if(NOT EXISTS ${input_erc_xml_package_filepath})
    set(fatal_error_msg "${fatal_error_msg}Can't find <input_erc_xml_package_filepath> : ${input_erc_xml_package_filepath}\n")
  endif()
  #
  if(${fatal_error_msg})
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "${fatal_error_msg}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  string(MD5 erc_inventory    ${target_name})
  set(erc_inventory           "inventory_${erc_inventory}")

  #
  ##
  set(work_absolute_directory "${CMAKE_CURRENT_BINARY_DIR}/embedded_resource_generation")
  file(MAKE_DIRECTORY ${work_absolute_directory})

  #
  ##
  set(erc_cmake_target_information)
  set(erc_cmake_target_information_result)
  set(erc_cmake_target_information_result_error_msg)
  execute_process(
    COMMAND           ${ERC_BINARY_PACKAGER}
    ARGS              "--inventory-name" ${erc_inventory}
                      "--input-package" ${input_erc_xml_package_filepath}
                      "--work-dir" ${work_absolute_directory}
                      "--get-for-cmake-target"
    OUTPUT_VARIABLE   erc_cmake_target_information
    RESULT_VARIABLE   erc_cmake_target_information_result
    ERROR_VARIABLE    erc_cmake_target_information_result_error_msg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #  WORKING_DIRECTORY ${work_absolute_directory}
  )
  #
  if(NOT ${erc_cmake_target_information_result} EQUAL "0")
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "  ERC_BINARY_PACKAGER Can't get information of package to make target\n"
      "  ProgramPath : ${ERC_BINARY_PACKAGER}\n"
      "  Argument    : ${ARGN}\n"
      "  ErrorResult : ${erc_cmake_target_information_result}\n"
      "  ErrorMessage: ${erc_cmake_target_information_result_error_msg}\n"
      "  Message     : ${erc_cmake_target_information}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  #get_filename_component(input_erc_xml_package_filepath_realpath "${input_erc_xml_package_filepath}" REALPATH)
  #string(SHA256 input_erc_xml_package_filepath_realpath_hash ${input_erc_xml_package_filepath_realpath})
  #set(erc_target "erc_package_${input_erc_xml_package_filepath_realpath_hash}")


  message(STATUS "-- erc_cmake_target_information -- ")
  message(STATUS "${erc_cmake_target_information}")
  message(STATUS "--")

  #
  ##
  string( REGEX MATCH
    "InputFiles:([^\n]+)\nGeneratedFiles:([^\n]+)\nNotFoundModelFiles:([^\n]*)\nNotFoundModelDirs:([^\n]*)\n"
    erc_cmake_target_information_parsed
    "${erc_cmake_target_information}"
  )
  #
  set(erc_cmake_target_information_parsed_nb ${CMAKE_MATCH_COUNT})
  #
  #set(erc_package            ${CMAKE_MATCH_1})
  set(input_files_path        ${CMAKE_MATCH_1})
  set(generated_files_path    ${CMAKE_MATCH_2})
  set(erc_xml_not_found_files ${CMAKE_MATCH_3})
  set(erc_xml_not_found_dirs  ${CMAKE_MATCH_4})

  #
  #string(SHA1 erc_target ${erc_package})
  set(erc_target_generate      "erc_${erc_inventory}_generation")
  set(erc_target_lib           "erc_${erc_inventory}")


  #
  ##
  if(NOT input_files_path OR NOT generated_files_path)
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "  ERC_BINARY_PACKAGER Not returns good information of package to make target\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  if(erc_xml_not_found_files OR erc_xml_not_found_dirs)
    set(warnings_msg)
    if(erc_xml_not_found_files)
      set(warnings_msg "${warnings_msg}  Not founds file(s) : ${erc_xml_not_found_files}\n")
    endif()
    if(erc_xml_not_found_dirs)
      set(warnings_msg "${warnings_msg}  Not founds directorie(s) : ${erc_xml_not_found_dirs}\n")
    endif()
    #
    message(WARNING "\n[ERC_TARGET_RESOURCE]\n"
      "  From : ${input_erc_xml_package_filepath}\n"
      "${warnings_msg}\n"
    )
  endif()

  #
  ##
  if(NOT TARGET ${erc_target_generate} AND NOT ${erc_target_lib})

   #
   ##
   add_custom_target(
     ${erc_target_generate} ALL
     COMMAND ${ERC_BINARY_PACKAGER}
     ARGS "--inventory-name" ${erc_inventory}
          "--input-packages" ${input_erc_xml_package_filepath}
          "--work-dir" ${work_absolute_directory}

     BYPRODUCTS ${generated_files_path}
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     COMMENT "Executing EmbeddedResource for file : ${input_erc_xml_package_filepath}"
     VERBATIM
   )

  #add_library(${erc_target_lib} OBJECT ${generated_files_path})
  #target_compile_definitions(${erc_target_lib} PRIVATE "-DERC_INVENTORY_PACKAGE_EXTERN_NAME=${erc_inventory}")
  #add_dependencies(${erc_target_lib} ${erc_target_generate})

  endif()


  #C
  ##
  target_sources(${target_name} PRIVATE ${generated_files_path})

  #message(STATUS "Link ${erc_target_lib} (${erc_package}) to ${target_name}")
  #target_link_libraries(${target_name} PRIVATE ${erc_target_lib})
  #target_include_directories(${target_name} PRIVATE ${work_absolute_directory})
  #add_dependencies(${target_name} ${erc_target_lib})

  target_compile_definitions(${target_name} PRIVATE "-DERC_INVENTORY_PACKAGE_EXTERN_NAME=${erc_inventory}")

  #debug :
  add_dependencies(${target_name} ${PROJECT_EMBEDDEDRESOURCE_PROGRAM})

  #
  ##
  set_source_files_properties(${input_erc_xml_package_filepath} PROPERTIES HEADER_FILE_ONLY ON)
  target_sources(${target_name} PRIVATE ${input_erc_xml_package_filepath})

  #
  if(ide_add_scanned_files)
    set_source_files_properties(${scanned_files_path} PROPERTIES HEADER_FILE_ONLY ON)
    target_sources(${target_name} PRIVATE ${scanned_files_path})
  endif()


# set(${output_target_name}               ${erc_target}           PARENT_SCOPE)
# set(${output_generated_files_path_list} ${generated_files_path} PARENT_SCOPE)
# set(${output_scanned_files_path_list}   ${input_files_path}     PARENT_SCOPE)


endfunction()






























#
## ERC_TARGET_RESOURCE to create or get embedded resource target
#

function(ERC_TARGET_RESOURCE_tesoo output_target_name output_generated_files_path_list output_scanned_files_path_list input_erc_xml_package_filepath)

  #
  ##
  set(fatal_error_msg)

  #
  if(NOT EXISTS ${ERC_BINARY_PACKAGER})
   set(fatal_error_msg "${fatal_error_msg}Can't find executable embedded_resource_packager on variable ERC_BINARY_PACKAGER : ${ERC_BINARY_PACKAGER}\n")
  endif()
  if(NOT EXISTS ${input_erc_xml_package_filepath})
    set(fatal_error_msg "${fatal_error_msg}Can't find <input_erc_xml_package_filepath> : ${input_erc_xml_package_filepath}\n")
  endif()
  #
  if(${fatal_error_msg})
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "${fatal_error_msg}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  set(work_absolute_directory "${CMAKE_CURRENT_BINARY_DIR}/embedded_resource_generation")
  file(MAKE_DIRECTORY ${work_absolute_directory})

  #
  ##
  set(erc_cmake_target_information)
  set(erc_cmake_target_information_result)
  set(erc_cmake_target_information_result_error_msg)
  execute_process(
    COMMAND           ${ERC_BINARY_PACKAGER}
    ARGS              "--input-package" ${input_erc_xml_package_filepath}
                      "--work-dir" ${work_absolute_directory}
                      "--get-for-cmake-target"
    OUTPUT_VARIABLE   erc_cmake_target_information
    RESULT_VARIABLE   erc_cmake_target_information_result
    ERROR_VARIABLE    erc_cmake_target_information_result_error_msg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #  WORKING_DIRECTORY ${work_absolute_directory}
  )
  #
  if(NOT ${erc_cmake_target_information_result} EQUAL "0")
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "  ERC_BINARY_PACKAGER Can't get information of package to make target\n"
      "  ProgramPath : ${ERC_BINARY_PACKAGER}\n"
      "  Argument    : ${ARGN}\n"
      "  ErrorResult : ${erc_cmake_target_information_result}\n"
      "  ErrorMessage: ${erc_cmake_target_information_result_error_msg}\n"
      "  Message     : ${erc_cmake_target_information}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  #get_filename_component(input_erc_xml_package_filepath_realpath "${input_erc_xml_package_filepath}" REALPATH)
  #string(SHA256 input_erc_xml_package_filepath_realpath_hash ${input_erc_xml_package_filepath_realpath})
  #set(erc_target "erc_package_${input_erc_xml_package_filepath_realpath_hash}")

  #
  ##
  string( REGEX MATCH
    "Package:([^\n]+)\nInputFiles:([^\n]+)\nGeneratedFiles:([^\n]+)\nNotFoundModelFiles:([^\n]*)\nNotFoundModelDirs:([^\n]*)\n"
    erc_cmake_target_information_parsed
    "${erc_cmake_target_information}"
  )
  #
  set(erc_cmake_target_information_parsed_nb ${CMAKE_MATCH_COUNT})
  #
  set(erc_target              "erc_${CMAKE_MATCH_1}")
  set(input_files_path        ${CMAKE_MATCH_2})
  set(generated_files_path    ${CMAKE_MATCH_3})
  set(erc_xml_not_found_files ${CMAKE_MATCH_4})
  set(erc_xml_not_found_dirs  ${CMAKE_MATCH_5})

  #
  ##
  if(NOT erc_target OR NOT input_files_path OR NOT generated_files_path)
    message(FATAL_ERROR
      "[ERC_TARGET_RESOURCE]\n"
      "  ERC_BINARY_PACKAGER Not returns good information of package to make target\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  if(erc_xml_not_found_files OR erc_xml_not_found_dirs)
    set(warnings_msg)
    if(erc_xml_not_found_files)
      set(warnings_msg "${warnings_msg}  Not founds file(s) : ${erc_xml_not_found_files}\n")
    endif()
    if(erc_xml_not_found_dirs)
      set(warnings_msg "${warnings_msg}  Not founds directorie(s) : ${erc_xml_not_found_dirs}\n")
    endif()
    #
    message(WARNING "\n[ERC_TARGET_RESOURCE]\n"
      "  From : ${input_erc_xml_package_filepath}\n"
      "${warnings_msg}\n"
    )
  endif()

  #
  ##
  if(NOT TARGET ${erc_target})

    #
    ##
    add_custom_target(
      ${erc_target} ALL
      COMMAND ${ERC_BINARY_PACKAGER}
      ARGS "--input-package" ${input_erc_xml_package_filepath}
           "--work-dir" ${work_absolute_directory}
      BYPRODUCTS ${generated_files_path}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Executing EmbeddedResource for file : ${input_erc_xml_package_filepath}"
      VERBATIM
    )

  endif()

  #
  ##
  set(${output_target_name}               ${erc_target}           PARENT_SCOPE)
  set(${output_generated_files_path_list} ${generated_files_path} PARENT_SCOPE)
  set(${output_scanned_files_path_list}   ${input_files_path}     PARENT_SCOPE)


endfunction()

#
## ERC_ADD_RESOURCES to add embedded resource on target
#

function(ERC_ADD_RESOURCES_tesoo target_name )

  # MADE IT SHARED for other acces with lib prefix

  #
  ##
  set(options ADD_INTO_IDE)
  set(oneValueArgs "")
  set(multiValueArgs "")
  cmake_parse_arguments(ARGUMENTS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
  #
  set(inputs_ercs_xmls_packages_filepath ${ARGUMENTS_UNPARSED_ARGUMENTS})
  set(ide_add_scanned_files              ${ARGUMENTS_ADD_INTO_IDE})

  #set(inputs_ercs_xmls_packages_filepath ${ARGN})

  #
  ##
  if(NOT TARGET ${target_name})
    message(FATAL_ERROR
      "[ERC_ADD_RESSOURCE]\n"
      "Can't find <target_name> : ${target_name}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  foreach(input_erc_xml_package_filepath IN ITEMS ${inputs_ercs_xmls_packages_filepath})

    #
    ##
    erc_target_resource(erc_target generated_files_path scanned_files_path ${input_erc_xml_package_filepath})

    #
    ##
    target_sources(${target_name} PRIVATE ${generated_files_path})
    add_dependencies(${target_name} ${erc_target})

    #
    ##
    set_source_files_properties(${input_erc_xml_package_filepath} PROPERTIES HEADER_FILE_ONLY ON)
    target_sources(${target_name} PRIVATE ${input_erc_xml_package_filepath})
    #
    if(ide_add_scanned_files)
      set_source_files_properties(${scanned_files_path} PROPERTIES HEADER_FILE_ONLY ON)
      target_sources(${target_name} PRIVATE ${scanned_files_path})
    endif()


  endforeach()

endfunction()

#
## ERC_RESSOURCE_LIBRARY to made an embedded resource library (for other mutiple target)
#

function(ERC_RESSOURCE_LIBRARY target_name lib_type)

  # lib_type is STATIC or SHARED

  # TODO

endfunction()
