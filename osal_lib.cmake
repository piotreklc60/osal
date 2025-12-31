# ---------------------------------------- LICENSE SECTION -------------------------------------------------------------------
#
# Copyright (c) 2025 Piotr Wojtowicz
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# -----------------------------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.22)

add_library(osal_lib INTERFACE)

#
# This library requires 2 definitions to be provided on CMAKE level:
# OSAL_OS_VARIANT - currently possible values:
#    - "freertos"
# OSAL_HW_VARIANT - currently possible values:
#    - "cortex-m3"
#

# -----------------------------------------------------------------------------------------------------------------------------
# ------------------------------------- files paths ---------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------------------------------
# files paths
set(OSAL_PATH ${CMAKE_CURRENT_LIST_DIR})

# -----------------------------------------------------------------------------------------------------------------------------
# ------------------------------------- BUFF CORE source files ----------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------------------------------

target_include_directories(osal_lib INTERFACE
    ${OSAL_PATH}/api/
    ${OSAL_PATH}/imp/common/inc/
    ${OSAL_PATH}/imp/os_variants/${OSAL_OS_VARIANT}/inc/
)

target_sources(osal_lib INTERFACE
    ${OSAL_PATH}/imp/common/src/osal_lib_lists.c
    ${OSAL_PATH}/imp/common/src/osal_lib_trees.c
)

include(${OSAL_PATH}/imp/os_variants/os_variants.cmake)

target_link_libraries(osal_lib INTERFACE osal_os_variant_lib)
