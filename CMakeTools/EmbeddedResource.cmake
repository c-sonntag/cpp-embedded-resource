#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

#
## ERC_ADD_RESSOURCE to add embedded resource on target
#

function(ERC_ADD_RESSOURCE target_name input_erc_xml_package_filepath)


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
  if(NOT DEFINED ${target_name})
    set(fatal_error_msg "${fatal_error_msg}Can't find <target_name> : ${target_name}\n")
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
  get_filename_component(input_erc_xml_package_filepath_realpath "${input_erc_xml_package_filepath}" REALPATH)
  string(SHA256 input_erc_xml_package_filepath_realpath_hash ${input_erc_xml_package_filepath_realpath})
  set(erc_target "erc_package_${input_erc_xml_package_filepath_realpath_hash}")
  #
  set(work_absolute_directory "${CMAKE_CURRENT_BINARY_DIR}/embedded_rc_generation")
  file(MAKE_DIRECTORY ${work_absolute_directory})

  #
  ##
  macro( erc_execute_process output_var )
    set(${output_var})
    set(${output_var}_result)
    set(${output_var}_result_error_msg)
    execute_process(
      COMMAND           ${ERC_BINARY_PACKAGER}
      ARGS              ${ARGN}
      OUTPUT_VARIABLE   ${output_var}
      RESULT_VARIABLE   ${output_var}_result
      ERROR_VARIABLE    ${output_var}_result_error_msg
      WORKING_DIRECTORY ${work_absolute_directory}
    )
    #
    if(NOT ${${output_var}_result} EQUAL "0")
      message(FATAL_ERROR
        "[ERC_ADD_RESSOURCE]\n"
        "  ERC_BINARY_PACKAGER can't return '${output_var}'\n"
        "  ProgramPath : ${ERC_BINARY_PACKAGER}\n"
        "  Argument    : ${ARGN}\n"
        "  ErrorResult : ${${output_var}_result}\n"
        "  ErrorMessage: ${${output_var}_result_error_msg}\n"
        "  Message     : ${${output_var}}\n"
        "\n"
      )
      return()
    endif()
  endmacro()

  #
  ##
  erc_execute_process(
    files_path
      "--input-package" ${input_erc_xml_package_filepath}
      "--work-dir" ${work_absolute_directory}
      "--return-build-files-path" "--cmake-list"
  )
  erc_execute_process(
    files_path_to_build
      "--input-package" ${input_erc_xml_package_filepath}
      "--work-dir" ${work_absolute_directory}
      "--return-build-files-path" "--return-only-generated" "--cmake-list"
  )

  set( erc_args_current_xml_pakage
    "--input-package" ${input_erc_xml_package_filepath}
    "--work-dir" ${work_absolute_directory}
   )

  add_custom_target(
    ${erc_target} ALL
    COMMAND ${ERC_BINARY_PACKAGER}
    ARGS "--input-package" ${input_erc_xml_package_filepath}
         "--work-dir" ${work_absolute_directory}
    BYPRODUCTS ${files_path}
    COMMENT "Executing EmbeddedResource for file : ${input_erc_xml_package_filepath}"
    VERBATIM
  )

  #
  target_sources(${target_name} PUBLIC ${files_path})
  add_dependencies(${target_name} ${erc_target})

  # Yes or no ? @todo
  add_dependencies(${erc_target} ${PROJECT_EMBEDDEDRESOURCE_PROGRAM})


endfunction()


#
## ERC_RESSOURCE_LIBRARY to made an embedded resource library (for other mutiple target)
#

function(ERC_RESSOURCE_LIBRARY target_name lib_type)

  # lib_type is STATIC or SHARED

  # TODO

endfunction()
