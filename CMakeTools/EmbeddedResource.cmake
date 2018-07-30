#
# EmbeddedResource project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)

#
## ERC_ADD_RESSOURCE to add embedded resource on target
#

function(ERC_ADD_RESSOURCE target_name input_erc_xml_package_filepath)

  #

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

  ## #
  ## ##
  ## message(STATUS "[ERC_ADD_RESSOURCE]]")
  ## message(STATUS "  target_name : ${target_name}")
  ## message(STATUS "  input_erc_xml_package_filepath : ${input_erc_xml_package_filepath}")

  #
  ##
  #set(work_directory "erc_generation")
  #file(MAKE_DIRECTORY "${work_relative_directory}/")
  #set(work_relative_directory "erc_generation")
  set(erc_target "${target_name}_erc_generation")
  #set(erc_target "${input_erc_xml_package_filepath}")
  set(work_absolute_directory "${CMAKE_CURRENT_BINARY_DIR}/embedded_rc_generation")
  file(MAKE_DIRECTORY ${work_absolute_directory})

  #
  ##
  ##FUNCTION(PREPEND var prefix)
  ##  SET(listVar "")
  ##  FOREACH(f ${ARGN})
  ##    LIST(APPEND listVar "${prefix}/${f}")
  ##  ENDFOREACH(f)
  ##  SET(${var} "${listVar}" PARENT_SCOPE)
  ##ENDFUNCTION(PREPEND)


  ## file(MAKE_DIRECTORY ${work_relative_directory})

  # set(outfile "${work_relative_directory}/erc_yop.cpp")


  #
  #set(ERC_BINARY_PACKAGER "R:/C/libdb/cpp-embedded-resource/builds/embedded_resource_packager.exe")

  #
  ##
 ## set(build_files)
 ## set(build_files_result)
 ## set(build_files_result_error_msg)
 ## execute_process(
 ##   COMMAND ${ERC_BINARY_PACKAGER}
 ##   ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_relative_directory} "--return-build-files-path"
 ##   OUTPUT_VARIABLE build_files
 ##   RESULT_VARIABLE build_files_result
 ##   ERROR_VARIABLE build_files_result_error_msg
 ##   WORKING_DIRECTORY ${work_relative_directory}
 ## )

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

  #
  #separate_arguments(build_files)
  #set(build_files_relative_path)
  #PREPEND(build_files_relative_path ${work_relative_directory} ${build_files})
  message(STATUS "  files_path :  ${files_path}\n")
  message(STATUS "  files_path_to_build :  ${files_path_to_build}\n")

  #
  ##
  #set(build_files_path_list  ${build_files_path})
  #separate_arguments(build_files_path_list)
  #string(REPLACE "\"" "" build_files_path_list ${build_files_path_list})
  #string(REGEX MATCHALL "^\"(.+)\"$" build_files_path_list ${build_files_path_list})
  #string(REGEX MATCHALL "([^\ \" ]+\"\ |\"[^\ \"]+\"$)" build_files_path_list "${build_files_path}")
  #string(REGEX MATCHALL "([^\ ]+\ |[^\ ]+$)" build_files_path_list "${build_files_path}")
  #string(REGEX MATCHALL "\\\"([^\\\"]+)\\\"\ |\\\"([^\\\"]+)\\\"$" build_files_path_list "${build_files_path}")
  #string(REGEX MATCHALL "\\\"(.+)\\\"\ |\\\"(.+)\\\"$" build_files_path_list ${build_files_path})
  #string(REGEX MATCHALL "\"([^\"]+)\" |\"([^\"]+)\"$" build_files_path_list ${build_files_path})
  #string(REGEX MATCHALL "([^\"]+) |([^\"]+)" build_files_path_list ${build_files_path})
  #string(REGEX MATCHALL "([^\"]+)" build_files_path_list ${build_files_path})
  #string(REPLACE "\" \"" "\";\"" build_files_path_list ${build_files_path})
  #message(STATUS "  build_files_path_list :  ${build_files_path_list} ")
  #message(STATUS "  build_files_path :  ${build_files_path} ")

  #
  ##
  ## add_custom_target(
  ##   ${erc_target} ALL
  ##   COMMAND ${ERC_BINARY_PACKAGER}
  ##   ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
  ##   BYPRODUCTS ${build_files_path}
  ##   WORKING_DIRECTORY ${work_absolute_directory}
  ##   # SOURCES ${build_files_path}
  ##   # DEPENDS ${input_erc_xml_package_filepath}
  ##   VERBATIM
  ## )

  #
  ##
#  add_custom_target(
#    ${erc_target} ALL
#    #DEPENDS ${build_files_path}
#    BYPRODUCTS ${build_files_path}
#    COMMAND ${ERC_BINARY_PACKAGER}
#    ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
#    WORKING_DIRECTORY ${work_absolute_directory}
#    VERBATIM
#  )


  ## add_custom_command (
  ##    OUTPUT erc_gen ${files_path}
  ##    BYPRODUCTS ${files_path}
  ##    COMMAND ${ERC_BINARY_PACKAGER}
  ##    ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
  ##    WORKING_DIRECTORY ${work_absolute_directory}
  ##    VERBATIM
  ##    COMMENT "Generating EmbeddedResource from ${input_erc_xml_package_filepath}"
  ## )

  #add_library(${erc_target} STATIC)

  set( erc_args_current_xml_pakage
    "--input-package" ${input_erc_xml_package_filepath}
    "--work-dir" ${work_absolute_directory}
   )

  add_custom_target(
    ${erc_target} ALL
    COMMAND ${ERC_BINARY_PACKAGER}
    ARGS ${erc_args_current_xml_pakage}
    #ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
    #BYPRODUCTS ${files_path}
    #SOURCES ${files_path_to_build}
    #WORKING_DIRECTORY ${work_absolute_directory}
    # SOURCES ${build_files_path}
    # DEPENDS ${input_erc_xml_package_filepath}
    COMMENT "Executing EmbeddedResource for file : ${input_erc_xml_package_filepath}"
    VERBATIM
  )

  # add_custom_command(
  #   TARGET ${target_name} PRE_BUILD
  #  # TARGET ${erc_target} PRE_BUILD
  #  # OUTPUT ${files_path}
  #   COMMAND ${ERC_BINARY_PACKAGER}
  #   ARGS ${erc_args_current_xml_pakage}
  #   #ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
  #   # BYPRODUCTS ${files_path}
  #   WORKING_DIRECTORY ${work_absolute_directory}
  #   # SOURCES ${files_path}
  #   # DEPENDS ${input_erc_xml_package_filepath}
  #   VERBATIM
  # )

  #
  set_source_files_properties( ${files_path} PROPERTIES GENERATED OFF )
  set_source_files_properties( ${files_path_to_build} PROPERTIES GENERATED ON )
  #set_property(CACHE ${files_path} PROPERTY )

  #
  target_sources(${target_name} PUBLIC ${files_path})


  #add_dependencies(${erc_target} ${PROJECT_EMBEDDEDRESOURCE_PROGRAM})

  #
  #target_sources(${erc_target} PRIVATE ${files_path})
  #add_dependencies(${erc_target}_lib ${erc_target})
  #add_dependencies(${erc_target} ${PROJECT_EMBEDDEDRESOURCE_PROGRAM})

  #

  #target_sources(${target_name} PRIVATE ${files_path})
  #add_dependencies(${target_name} ${erc_target})


  ## #
  ## ##
  ## add_custom_command(
  ##   TARGET ${target_name}
  ##   PRE_BUILD
  ##   COMMAND ${ERC_BINARY_PACKAGER}
  ##   ARGS "--input-package" ${input_erc_xml_package_filepath} "--work-dir" ${work_absolute_directory}
  ##   # BYPRODUCTS ${files_path}
  ##   WORKING_DIRECTORY ${work_absolute_directory}
  ##   MAIN_DEPENDENCY ${input_erc_xml_package_filepath}
  ##   VERBATIM
  ## )
  ##
  ## #add_dependencies(${target_name} ${input_erc_xml_package_filepath})
  ## #target_sources(${target_name} PRIVATE ${files_path})

  #
  # WORKING_DIRECTORY ${work_absolute_directory}
  ##
  #DEPEND ${target_name}
  #add_custom_target(${target_name}_call_generate_embedded_files DEPENDS ${target_name}_generate_embedded_files)

  #
  ##
  ##message(STATUS "  ARGS : --input-package ${input_erc_xml_package_filepath} --work-dir ${work_absolute_directory}")
  ##message(STATUS "  embedded_resource_files : ${oFutfile}")

  #
  ##

  #add_library("${target_name}_erc" STATIC ${files_path})
  #add_dependencies(${target_name} ${target_name}_call_generate_embedded_files)


endfunction()


#
## ERC_RESSOURCE_LIBRARY to made an embedded resource library (for other mutiple target)
#

function(ERC_RESSOURCE_LIBRARY target_name lib_type)

  # lib_type is STATIC or SHARED

  # TODO

endfunction()
