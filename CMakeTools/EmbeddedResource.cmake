#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)


#
## ERC_TARGET_RESOURCE to create or get embedded resource target
#

function(ERC_TARGET_RESOURCE output_target_name input_erc_xml_package_filepath)

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
      "[ERC_ADD_RESSOURCE]\n"
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
    WORKING_DIRECTORY ${work_absolute_directory}
  )
  #
  if(NOT ${erc_cmake_target_information_result} EQUAL "0")
    message(FATAL_ERROR
      "[ERC_ADD_RESSOURCE]\n"
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
  string( REGEX MATCH "Package:([^\n]+)" erc_target "${erc_cmake_target_information}")
  set(erc_target "erc_${CMAKE_MATCH_1}")
  string( REGEX MATCH "Files:([^\n]+)" files_path "${erc_cmake_target_information}")
  set(files_path ${CMAKE_MATCH_1})

  #
  ##
  if(NOT erc_target OR NOT files_path)
    message(FATAL_ERROR
      "[ERC_ADD_RESSOURCE]\n"
      "  ERC_BINARY_PACKAGER Not returns good information of package to make target\n"
      "\n"
    )
    return()
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
      BYPRODUCTS ${files_path}
      SOURCES    ${files_path}
      COMMENT "Executing EmbeddedResource for file : ${input_erc_xml_package_filepath}"
      VERBATIM
    )

    #
    ##
    set(${output_target_name} ${erc_target} PARENT_SCOPE)

  endif()

endfunction()

#
## ERC_ADD_RESSOURCE to add embedded resource on target
#

function(ERC_ADD_RESSOURCE target_name input_erc_xml_package_filepath)

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
  erc_target_resource(erc_target ${input_erc_xml_package_filepath})

  #
  ##
  get_target_property(files_path ${erc_target} SOURCES)
  target_sources(${target_name} PUBLIC ${files_path})
  add_dependencies(${target_name} ${erc_target})

endfunction()

#
## ERC_RESSOURCE_LIBRARY to made an embedded resource library (for other mutiple target)
#

function(ERC_RESSOURCE_LIBRARY target_name lib_type)

  # lib_type is STATIC or SHARED

  # TODO

endfunction()
