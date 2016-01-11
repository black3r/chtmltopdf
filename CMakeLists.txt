#
# Source files
#

set(CHTMLTOPDF_SRCS
    chtmltopdf_app.cpp
    chtmltopdf_app.h
    chtmltopdf_linux.cpp
    chtmltopdf_handler.cpp
    chtmltopdf_handler.h
    )

set(CHTMLTOPDF_SRCS_LINUX
    )

APPEND_PLATFORM_SOURCES(CHTMLTOPDF_SRCS)
source_group(chtmltopdf FILES ${CHTMLTOPDF_SRCS})

set(CEF_TARGET "chtmltopdf")
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")
SET_CEF_TARGET_OUT_DIR()

if(OS_LINUX)
    # Executable target.
    add_executable(${CEF_TARGET} ${CHTMLTOPDF_SRCS})
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

# TODO: Other OS support