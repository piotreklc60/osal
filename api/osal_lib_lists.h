/** ---------------------------------------- LICENSE SECTION -------------------------------------------------------------------
 *
 * Copyright (c) 2025 Piotr Wojtowicz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */

#ifndef OSAL_LIB_LISTS_H_
#define OSAL_LIB_LISTS_H_

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

/** @defgroup Lists Operating System Abstraction Layer - universal library for manipulating lists
 *  @brief searching, inserting, removing objects
 *  @{
 */

#ifndef OSAL_LIST_CHECK_NEXT_LEAF
#define OSAL_LIST_CHECK_NEXT_LEAF(_first_leaf, _current_leaf)     OSAL_CHECK_PTR(OSAL_List_XT, ((OSAL_List_XT*)(_current_leaf))->next)
#endif

#ifndef OSAL_LIST_CHECK_PREVIOUS_LEAF
#define OSAL_LIST_CHECK_PREVIOUS_LEAF(_first_leaf, _current_leaf) OSAL_CHECK_PTR(OSAL_List_XT, ((OSAL_List_XT*)(_current_leaf))->previous)
#endif

#ifndef OSAL_LIST_GET_NEXT_LEAF
#define OSAL_LIST_GET_NEXT_LEAF(_first_leaf, _current_leaf)       ((OSAL_List_XT*)(_current_leaf))->next
#endif

#ifndef OSAL_LIST_GET_PREVIOUS_LEAF
#define OSAL_LIST_GET_PREVIOUS_LEAF(_first_leaf, _current_leaf)   ((OSAL_List_XT*)(_current_leaf))->previous
#endif

/**
 * @brief structure defining core element of the list element (leaf). List can has different size, however on the begining of it
 * there must be located OSAL_List_XT structure.
 * Each list leaf must also have field to identify each leaf (for example number, string or something vendor specific)
 * but these elements are not in the core element (OSAL_List_XT) so list structure must contain it in its part.
 */
typedef struct OSAL_List_eXtendedTag
{
   struct OSAL_List_eXtendedTag *previous;
   struct OSAL_List_eXtendedTag *next;
} OSAL_List_XT;

typedef OSAL_Bool_DT (*OSAL_List_Vendor_Compare_HT)(OSAL_List_XT *leaf, void *params);

/**
 * frees leaf - element which inherits from OSAL_List_XT type.
 * This function is called for every removed leaf, it is up to this function how / which element shall be freed.
 */
typedef void (*OSAL_List_Free_Leaf_HT)(void *leaf);

/**
 * @brief for initializing list object.
 *
 * @param leaf pointer to the list leaf object to be initialized.
 */
void OSAL_List_Leaf_Init(void *leaf);

/**
 * @brief Searches list leaf by its number.
 *
 * @param first_leaf first leaf of the list (starting element of the list).
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * USER MUST ENSURE it is offset properly aligned for uint32_t for the curent architecture.
 * @param id_mask specifies the mask will be added to the read ID - it is useful if identifier is stored on a location smaller than uint32_t (this function always reads uint32_t).
 * @param id_number numerical identifier of the element to be found.
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_List_Find_By_Number(void *first_leaf, uint32_t id_offset, uint_fast8_t id_mask, uint32_t id_number);

/**
 * @brief Searches list leaf by its text describing.
 *
 * @param first_leaf first leaf of the list (starting element of the list).
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * @param id_string ASCII string identifier of the element to be found.
 * @param offset number of bytes on the begining of identifier string of each leaf we have to skip in the searching procedure. It is also applied to id_string.
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_List_Find_By_String(void *first_leaf, uint32_t id_offset, const char *id_string, uint32_t offset);

/**
 * @brief Searches list leaf by its text describing.
 *
 * @param first_leaf first leaf of the list (starting element of the list).
 * @param id_offset number of bytes from the begining of the list where leaf identifier is located.
 * @param id_string ASCII string identifier of the element to be found.
 * @param terminate_char character which met in id_string will terminate searching giving positive result.
 * For example, id_string points to string "building.small", terminate chars contain "." then element of the list "building" will match the search.
 * @param offset number of bytes on the begining of identifier string of each leaf we have to skip in the searching procedure. It is also applied to id_string.
 * @param ret_offset if provided valid pointer, to this variable there will be returned offset in the id_string at which function ended comparison (with or without success).
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_List_Find_By_String_Terminated(void *first_leaf, uint32_t id_offset, const char *id_string, char terminate_chars, uint32_t offset, uint32_t *ret_offset);

/**
 * @brief Searches list leaf by its vendor specific identifier.
 *
 * @param first_leaf first leaf of the list (starting element of the list).
 * @param compare vendor specific function for comparing leaf identifier. If compare function returns OSAL_TRUE them it means element has been found.
 * @param params parameters to be provided to @see compare function.
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_List_Find_By_Vendor(void *first_leaf, OSAL_List_Vendor_Compare_HT compare, void *params);

/**
 * @brief Add new list leaf by its number. Order is specified by @see order_growing parameter.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the list (starting element of the list).
 * @param new_leaf pointer to new leaf to be added to the list.
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * USER MUST ENSURE it is offset properly aligned for uint32_t for the curent architecture.
 * @param id_mask specifies the mask will be added to the read ID - it is useful if identifier is stored on a location smaller than uint32_t (this function always reads uint32_t).
 * @param order_growing if OSAL_TRUE then order is growing in identifier values (from smalest to bigest), OSAL_FALSE otherwise (from bigest to smalest).
 */
void OSAL_List_Add_By_Number(void *first_leaf_ptr, void *new_leaf, uint32_t id_offset, uint_fast8_t id_mask, OSAL_Bool_DT order_growing);

/**
 * @brief Add new list leaf by its text describing. Order is specified by @see order_growing parameter.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the list (starting element of the list).
 * @param new_leaf pointer to new leaf to be added to the list.
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * @param offset number of bytes on the begining of identifier string of each leaf we have to skip in the searching procedure. It is also applied to id_string.
 * @param order_growing if OSAL_TRUE then order is growing in identifier ASCII values (alphabetical), OSAL_FALSE otherwise.
 */
void OSAL_List_Add_By_String(void *first_leaf_ptr, void *new_leaf, uint32_t id_offset, uint32_t offset, OSAL_Bool_DT order_growing);

/**
 * @brief Add new list leaf by its vendor specific identifier. Order is also vendor specific
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the list (starting element of the list).
 * @param new_leaf pointer to new leaf to be added to the list.
 * @param compare vendor specific function for comparing leaf identifier. If compare function returns OSAL_TRUE them it means new leaf has to be stored BEFORE current one.
 * @param params parameters to be provided to @see compare function.
 */
void OSAL_List_Add_By_Vendor(void *first_leaf_ptr, void *new_leaf, OSAL_List_Vendor_Compare_HT compare, void *params);

/**
 * @brief Removes list leaf.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the list (starting element of the list).
 * @param leaf pointer to the leaf to be removed from the list.
 * @param free_func handler to user-defined function called to free memory occupied by the leaf.
 * It is called after leaf has been detached from the tree.
 * If OSAL_MAKE_INVALID_HANDLER(OSAL_Tree_Free_Leaf_HT) is provided then leaf is only removed from the list without freeing step.
 */
void OSAL_List_Remove_Leaf(void *first_leaf_ptr, void *leaf, OSAL_List_Free_Leaf_HT free_func);

/**
 * @brief Removes list all elements.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the list (starting element of the list).
 * @param free_func handler to user-defined function called to free memory occupied by the leaf.
 * It is called after leaf has been detached from the tree.
 * If OSAL_MAKE_INVALID_HANDLER(OSAL_Tree_Free_Leaf_HT) is provided then leaf is only removed from the list without freeing step.
 */
void OSAL_List_Clear_List(void *first_leaf_ptr, OSAL_List_Free_Leaf_HT free_func);


/** @} */ // end of Lists

#endif

