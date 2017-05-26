#
# Source files
#

set(CHTMLTOPDF_SRCS
    chtmltopdf_app.cpp
    chtmltopdf_app.h
    chtmltopdf_handler.cpp
    chtmltopdf_handler.h
    )

set(CHTMLTOPDF_SRCS_LINUX
    chtmltopdf_linux.cpp
    )

set(CHTMLTOPDF_SRCS_WINDOWS
    chtmltopdf_win.cpp
    cefsimple.rc
    chtmltopdf.exe.manifest
    resource.h
    )

APPEND_PLATFORM_SOURCES(CHTMLTOPDF_SRCS)
source_group(chtmltopdf FILES ${CHTMLTOPDF_SRCS})

set(CHTMLTOPDF_RES_SRCS_WINDOWS
    res/cefsimple.ico
    res/small.ico
    )

APPEND_PLATFORM_SOURCES(CHTMLTOPDF_RES_SRCS)
source_group(chtmltopdf\\\\res FILES ${CHTMLTOPDF_RES_SRCS})

set(CHTMLTOPDF_SRCS
   ${CHTMLTOPDF_SRCS}
   ${CHTMLTOPDF_RES_SRCS}
   )

set(CEF_TARGET "chtmltopdf")
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")
SET_CEF_TARGET_OUT_DIR()

if(OS_LINUX)
    # Executable target.
    add_executable(${CEF_TARGET} ${CHTMLTOPDF_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
    add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
    target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

    # Set rpath so that libraries can be placed next to the executable.
    set_target_properties(${CEF_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
    set_target_properties(${CEF_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    set_target_properties(${CEF_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

    # Copy binary and resource files to the target output directory.
    COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")

    # Set SUID permissions on the chrome-sandbox target.
    SET_LINUX_SUID_PERMISSIONS("${CEF_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif()

if(OS_WINDOWS)
    # Executable target.
    add_executable(${CEF_TARGET} WIN32 ${CHTMLTOPDF_SRCS})
    add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
    target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

    # Add the custom manifest files to the executable.
    ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_TARGET}")

    COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
endif()

# TODO: Other OS support
