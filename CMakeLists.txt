cmake_minimum_required(VERSION 3.13...3.21)

project(MyProj VERSION 2.4.3)

set(CMAKE_RULE_MESSAGES OFF)
set(GENERATED_DIR .generated)

# generator needed for build
add_executable(generator generator.cpp)

add_custom_command(
  OUTPUT ${GENERATED_DIR}/generated.cpp
  COMMAND generator ${CMAKE_CURRENT_SOURCE_DIR}/someInputFile.cpp.in ${GENERATED_DIR}/generated.cpp
  DEPENDS generator someInputFile.cpp.in
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(fmt REQUIRED)

# example
add_executable(myapp ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED_DIR}/generated.cpp)
target_link_libraries(myapp PRIVATE fmt::fmt)
set_property(TARGET myapp PROPERTY CXX_STANDARD 20)

find_program(DOT dot REQUIRED)

# create a long text
set(TEXT 0123456789ABCDEF)
foreach(I RANGE 6)
  list(APPEND TEXT ${TEXT})
endforeach()

add_custom_command(
  OUTPUT generate
  COMMAND ${CMAKE_COMMAND} --graphviz=${GENERATED_DIR}/${CMAKE_PROJECT_NAME}.dot ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DOT} -Tsvg ${GENERATED_DIR}/${CMAKE_PROJECT_NAME}.dot -o ${GENERATED_DIR}/${CMAKE_PROJECT_NAME}.svg
  COMMAND ${CMAKE_COMMAND} -E echo ${TEXT} > generate
  DEPENDS generator
  COMMENT "generates generate"
)

add_custom_target(gen DEPENDS generate)

if("${CMAKE_MAKE_PROGRAM}" MATCHES ".*ninja")
  find_program(PERL perl REQUIRED)

  add_custom_command(TARGET gen POST_BUILD
    COMMAND ${CMAKE_MAKE_PROGRAM} -t graph | ${PERL} -p -e 's/rankdir="LR"/rankdir="BT"/;' > ${GENERATED_DIR}/deps.dot
    COMMAND ${DOT} -Tsvg -Nrotate=90 -Ncenter='true' -Nrankdir='BT' ${GENERATED_DIR}/deps.dot -o ${GENERATED_DIR}/deps.svg
    DEPENDS generate
    COMMENT "generates ninja dependency grap"
  )
endif()


add_custom_target(my-all-1 #XXX ALL
  COMMAND ${CMAKE_COMMAND} -E touch my-all-1
  DEPENDS generate
  COMMENT "depend on generate"
)

add_custom_target(my-all-2 #XXX ALL
  COMMAND ${CMAKE_COMMAND} -E touch my-all-2
  DEPENDS generate
  COMMENT "depend on generate"
)
