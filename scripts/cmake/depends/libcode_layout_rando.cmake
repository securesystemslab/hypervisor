#
# Bareflank Hypervisor
# Copyright (C) 2015 Assured Information Security, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

if((ENABLE_BUILD_VMM OR ENABLE_BUILD_TEST) AND NOT WIN32 AND ENABLE_CODE_LAYOUT_RANDO)
    message(STATUS "Including dependency: libcode_layout_rando")

    download_dependency(
        libcode_layout_rando
        GIT_REPOSITORY "file:///home/matt/SSLab/compiler-rt"
        GIT_TAG "code_layout_rando_70"
    )

    generate_flags(
        vmm
        NOWARNINGS
    )

    list(APPEND LIBCODE_LAYOUT_RANDO_CONFIGURE_FLAGS
        -DCOMPILER_RT_BUILD_BUILTINS=OFF
        -DCOMPILER_RT_BUILD_XRAY=OFF
        -DCOMPILER_RT_BUILD_LIBFUZZER=OFF
        -DCOMPILER_RT_BUILD_PROFILE=OFF
        -DCOMPILER_RT_HAS_FNO_RTTI_FLAG=OFF
	-DCOMPILER_RT_SANITIZERS_TO_BUILD=code_layout_rando
	-DCMAKE_TOOLCHAIN_FILE=${CRT_TOOLCHAIN_PATH}
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        # -DBUILD_SHARED_LIBS=OFF
    )

    add_dependency(
        libcode_layout_rando vmm
        CMAKE_ARGS  ${LIBCODE_LAYOUT_RANDO_CONFIGURE_FLAGS}
        DEPENDS     newlib_${VMM_PREFIX}
        DEPENDS     libcxx_${VMM_PREFIX}
        DEPENDS     libcxxabi_${VMM_PREFIX}
    )
endif()
