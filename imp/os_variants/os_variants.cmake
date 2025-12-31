# ---------------------------------------- LICENSE SECTION -------------------------------------------------------------------
#
# Copyright (c) 2024 Piotr Wojtowicz
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

add_library(osal_os_variant_lib INTERFACE)

# -----------------------------------------------------------------------------------------------------------------------------
# ------------------------------------- files paths ---------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------------------------------
# files paths
set(OSAL_OS_VARIANT_PATH ${CMAKE_CURRENT_LIST_DIR})

# -----------------------------------------------------------------------------------------------------------------------------
# ------------------------------------- BUFF CORE source files ----------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------------------------------

target_include_directories(osal_os_variant_lib INTERFACE
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/inc/
)

target_sources(osal_os_variant_lib INTERFACE
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_alloc.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_context.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_invoke.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_message.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_mutex.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_semaphore.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_thread.c
    ${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/src/osal_time.c
)

include(${OSAL_OS_VARIANT_PATH}/${OSAL_OS_VARIANT}/hw_variant/hw_variants.cmake)

target_link_libraries(osal_os_variant_lib INTERFACE osal_hw_variant_lib)
