cmake_minimum_required(VERSION 3.16)
project(acme_darwin CXX)


list(APPEND library_source
   #dbus/gsm_proxy.cpp
   _.cpp
   _.h
   _factory.cpp
   #_process.cpp
   #_${PROJECT_NAME}.h
   directory_system.cpp
   directory_system.h
   file_system.cpp
   file_system.h
   path_system.cpp
   path_system.h
   #dbus.cpp
   #exception_translator.cpp
   #exception_translator.h
   #file_memory_map.cpp
   #file_memory_map.h
   file_context.cpp
   file_context.h
   framework.cpp
   framework.h
   #mutex.cpp
   #mutex.h
   node.cpp
   node.h
   #   node_process_identifier_modules_paths.cpp

   #  node_clang_callstack.cpp
   #pipe.cpp
   #pipe.h
   #stdio_file.cpp
   #stdio_file.h
   #process.cpp
)


#if (POSIX_LIST_SERIAL_PORTS)
#
#
#    list(APPEND library_source list_serial_ports.cpp)
#
#
#endif ()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


#if (POSIX_LIST_SERIAL_PORTS)
#
#    target_compile_definitions(${PROJECT_NAME} PRIVATE POSIX_LIST_SERIAL_PORTS)
#
#endif ()


list(APPEND library_references
   acme_posix
   darwin)


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


list(APPEND library_references
   acme)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   add_dependencies(${PROJECT_NAME} draw2d_gdiplus)


elseif (${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})


   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
   target_compile_features(static_${PROJECT_NAME} PRIVATE cxx_std_20)


   if (NOT ${DONT_USE_PKG_CONFIG})
      pkg_check_modules(PKGCONFIG dbus-glib-1)
   endif ()
   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS} ${GLOBAL_EXTRA_COMPILER_FLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS} ${GLOBAL_EXTRA_COMPILER_FLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS} ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



