#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)


#
## ERC_TARGET_RESOURCE to create or get embedded resource target
#

function(ERC_ADD_RESOURCES target_name )

  # @todo MADE IT SHARED for other acces with lib prefix

  #
  ##
  set(options ADD_INTO_IDE)
  set(oneValueArgs "")
  set(multiValueArgs "")
  cmake_parse_arguments(ARGUMENTS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
  #
  set(inputs_ercs_xmls_packages_filepath ${ARGUMENTS_UNPARSED_ARGUMENTS})
  set(ide_add_input_files_path           ${ARGUMENTS_ADD_INTO_IDE})

  #
  ##
  if(NOT TARGET ${target_name})
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "  Can't find <target_name> : ${target_name}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  string(MD5 erc_inventory    ${target_name})
  set(erc_inventory           "inventory_${erc_inventory}")

  #
  set(erc_target_generate      "erc_${erc_inventory}_generation")
  set(erc_target_lib           "erc_${erc_inventory}")

  #
  ##
  if(TARGET ${erc_target_generate})
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "  An resource as already set for this : ${target_name}\n"
      "   Please use variadic_args to pass all resources like :\n"
      "      erc_add_resources( target_name erc_file_res1 erc_file_res2 ... )\n"
      "\n"
      )
    return()
  endif()

  #
  ##
  set(fatal_error_msg)
  #
  if(NOT EXISTS ${ERC_BINARY_PACKAGER})
   set(fatal_error_msg "${fatal_error_msg}  Can't find executable embedded_resource_packager on variable ERC_BINARY_PACKAGER : ${ERC_BINARY_PACKAGER}\n")
  endif()
  #
  if(NOT inputs_ercs_xmls_packages_filepath OR inputs_ercs_xmls_packages_filepath EQUAL "")
    set(fatal_error_msg "${fatal_error_msg}  Need input(s) package(s) path(s) argument(s) for target : ${target_name} \n")
  endif()
  #
  if(fatal_error_msg)
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "${fatal_error_msg}\n"
      "\n"
    )
    return()
  endif()
  #
  set(fatal_error_msg_not_founds_inputs_ercs)
  foreach(test_exist_input_erc_xml_package_filepath IN ITEMS ${inputs_ercs_xmls_packages_filepath})
    set(test_exist_input_erc_xml_package_current_source_filepath "${CMAKE_CURRENT_SOURCE_DIR}/${input_erc_xml_package_filepath}")
    if(NOT EXISTS ${test_exist_input_erc_xml_package_filepath} AND NOT EXISTS ${input_erc_xml_package_current_source_filepath})
      set(fatal_error_msg_not_founds_inputs_ercs ${fatal_error_msg_not_founds_inputs_ercs} ${input_erc_xml_package_filepath})
    endif()
  endforeach()
  if(fatal_error_msg_not_founds_inputs_ercs)
    set(fatal_error_msg "${fatal_error_msg}  Can't find <inputs_ercs_xmls_packages_filepath> : ${fatal_error_msg_not_founds_inputs_ercs}\n")
  endif()
  #
  if(fatal_error_msg)
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "${fatal_error_msg}\n"
      "\n"
    )
    return()
  endif()

  #
  ##
  set(work_absolute_directory "${CMAKE_CURRENT_BINARY_DIR}/_erc")
  file(MAKE_DIRECTORY ${work_absolute_directory})

  #
  ##
  set(erc_cmake_target_information_args
    "--inventory-name" ${erc_inventory}
    "--input-packages" ${inputs_ercs_xmls_packages_filepath}
    "--work-dir" ${work_absolute_directory}
    "--get-for-cmake-target"
  )
  set(erc_cmake_target_information)
  set(erc_cmake_target_information_result)
  set(erc_cmake_target_information_result_error_msg)
  execute_process(
    COMMAND           ${ERC_BINARY_PACKAGER}
    ARGS              ${erc_cmake_target_information_args}
    OUTPUT_VARIABLE   erc_cmake_target_information
    RESULT_VARIABLE   erc_cmake_target_information_result
    ERROR_VARIABLE    erc_cmake_target_information_result_error_msg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  #
  if(NOT ${erc_cmake_target_information_result} EQUAL "0")
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "   ERC_BINARY_PACKAGER Can't get information of package to make target\n"
      "   ProgramPath : ${ERC_BINARY_PACKAGER}\n"
      "   Arguments   : ${erc_cmake_target_information_args}\n"
      "   ErrorResult : ${erc_cmake_target_information_result}\n"
      "   ErrorMessage: ${erc_cmake_target_information_result_error_msg}\n"
      "   Message     : ${erc_cmake_target_information}\n"
      "\n"
    )
    return()
  endif()

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
  ##
  if(NOT input_files_path OR NOT generated_files_path)
    message(FATAL_ERROR
      " [ERC_ADD_RESOURCES]\n"
      "   ERC_BINARY_PACKAGER Not returns good information of package to make target\n"
      "   need input_files_path or generated_files_path\n"
      "   See input erc erc_cmake_target_information :"
      "${erc_cmake_target_information}"
      "\n"
    )
    return()
  endif()

  #
  ##
  if(erc_xml_not_found_files OR erc_xml_not_found_dirs)
    set(warnings_msg)
    if(erc_xml_not_found_files)
      set(warnings_msg "${warnings_msg}   Not founds file(s) : ${erc_xml_not_found_files}\n")
    endif()
    if(erc_xml_not_found_dirs)
      set(warnings_msg "${warnings_msg}   Not founds directorie(s) : ${erc_xml_not_found_dirs}\n")
    endif()
    #
    message(WARNING "\n [ERC_ADD_RESOURCES]\n"
      "   On target : ${target_name}\n"
      "   From(s) : ${inputs_ercs_xmls_packages_filepath}\n"
      "${warnings_msg}\n"
    )
  endif()

  #
  ##
  set(erc_target_generate_args
    "--inventory-name" ${erc_inventory}
    "--input-packages" ${inputs_ercs_xmls_packages_filepath}
    "--work-dir" ${work_absolute_directory}
  )
  #
  add_custom_target(
    ${erc_target_generate} ALL
    COMMAND ${ERC_BINARY_PACKAGER}
    ARGS ${erc_target_generate_args}
    BYPRODUCTS ${generated_files_path}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Executing EmbeddedResource for target '${target_name}' with erc_package(s) : ${inputs_ercs_xmls_packages_filepath}"
    VERBATIM
  )

  #add_custom_command(
  #  OUTPUT ${generated_files_path}
  #  COMMAND ${ERC_BINARY_PACKAGER}
  #  ARGS ${erc_target_generate_args}
  #  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #  COMMENT "Executing EmbeddedResource for target '${target_name}' with erc_package(s) : ${inputs_ercs_xmls_packages_filepath}"
  #  VERBATIM
  #)

  ## debug : message(STATUS "erc_target_generate_args ${erc_target_generate_args}")

  #
  ##
  set_source_files_properties(${generated_files_path} PROPERTIES
    #LABELS ${input_files_path} ( @todo need same list witn inventory ... etc)
    COMPILE_FLAGS "-s -O3" LANGUAGE CXX
  )
  ## debug : list(GET generated_files_path 0 first_element_of_generated_files_path )
  ## debug : get_source_file_property(first_element_of_generated_files_path_property ${first_element_of_generated_files_path} COMPILE_FLAGS)
  ## debug : message(STATUS "COMPILE_FLAGS of ${first_element_of_generated_files_path} : ${first_element_of_generated_files_path_property}")

  #
  ##
  target_compile_definitions(${target_name} PRIVATE "-DERC_INVENTORY_PACKAGE_EXTERN_NAME=${erc_inventory}")
  target_sources(${target_name} PRIVATE ${generated_files_path})
  # (ambe freeze cmake ? ) :
  add_dependencies(${target_name} ${erc_target_generate})

  #debug :
  ##add_dependencies(${target_name} ${PROJECT_EMBEDDEDRESOURCE_PROGRAM})

  #
  ##
  set_source_files_properties(${inputs_ercs_xmls_packages_filepath} PROPERTIES HEADER_FILE_ONLY ON)
  target_sources(${target_name} PRIVATE ${inputs_ercs_xmls_packages_filepath})

  #
  ##
  if(ide_add_input_files_path)
    set_source_files_properties(${input_files_path} PROPERTIES HEADER_FILE_ONLY ON)
    target_sources(${target_name} PRIVATE ${input_files_path})
  endif()

endfunction()

