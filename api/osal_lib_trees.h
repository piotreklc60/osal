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

#ifndef OSAL_LIB_TREES_H_
#define OSAL_LIB_TREES_H_

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

#ifndef OSAL_LIB_LISTS_H_
#include "osal_lib_lists.h"
#endif

/** @defgroup Trees Operating System Abstraction Layer - universal library for manipulating trees (lists with child-lists)
 *  @brief searching, inserting, removing objects
 *  @{
 */

#ifndef OSAL_TREE_SUPPORT_LEAFS_REMOVING
#define OSAL_TREE_SUPPORT_LEAFS_REMOVING           OSAL_FEATURE_PRESENT
#endif

#ifndef OSAL_TREE_CHECK_NEXT_LEAF
#define OSAL_TREE_CHECK_NEXT_LEAF(_first_leaf, _current_leaf)     OSAL_CHECK_PTR(OSAL_List_XT, ((OSAL_Tree_XT*)(_current_leaf))->list.next)
#endif

#ifndef OSAL_TREE_CHECK_PREVIOUS_LEAF
#define OSAL_TREE_CHECK_PREVIOUS_LEAF(_first_leaf, _current_leaf) OSAL_CHECK_PTR(OSAL_List_XT, ((OSAL_Tree_XT*)(_current_leaf))->list.previous)
#endif

#ifndef OSAL_TREE_CHECK_CHILD_LEAF
#define OSAL_TREE_CHECK_CHILD_LEAF(_first_leaf, _current_leaf)    OSAL_CHECK_PTR(OSAL_Tree_XT, ((OSAL_Tree_XT*)(_current_leaf))->branch_first)
#endif

#ifndef OSAL_TREE_GET_NEXT_LEAF
#define OSAL_TREE_GET_NEXT_LEAF(_first_leaf, _current_leaf)       ((OSAL_Tree_XT*)(_current_leaf))->list.next
#endif

#ifndef OSAL_TREE_GET_PREVIOUS_LEAF
#define OSAL_TREE_GET_PREVIOUS_LEAF(_first_leaf, _current_leaf)   ((OSAL_Tree_XT*)(_current_leaf))->list.previous
#endif

#ifndef OSAL_TREE_GET_CHILD_LEAF
#define OSAL_TREE_GET_CHILD_LEAF(_first_leaf, _current_leaf)      ((OSAL_Tree_XT*)(_current_leaf))->branch_first
#endif

/**
 * @brief structure defining core element of the tree element (leaf). Tree can has different size, containing different elements,
 * however on the begining of it there must be located OSAL_List_XT structure.
 * Each tree leaf must also have field to identify each leaf (for example number, string or something vendor specific)
 * but these elements are not in the core element (OSAL_List_XT) so list structure must contain it in its part.
 */
typedef struct OSAL_Tree_eXtendedTag
{
   OSAL_List_XT list;
#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)
   struct OSAL_Tree_eXtendedTag *parent;
#endif
   struct OSAL_Tree_eXtendedTag *branch_first;
} OSAL_Tree_XT;

typedef enum
{
   OSAL_TREE_LEAF_COMPARE_NOT_MATCH = 0,
   OSAL_TREE_LEAF_COMPARE_MATCH     = 1,
   OSAL_TREE_LEAF_COMPARE_BRANCH    = 2
} OSAL_Tree_Vendor_Compare_Result_ET;

typedef OSAL_Tree_Vendor_Compare_Result_ET (*OSAL_Tree_Vendor_Compare_HT)(OSAL_Tree_XT *leaf, void *params);

typedef enum
{
   OSAL_TREE_LEAF_ADD_DIRECTLY = 0,
   OSAL_TREE_LEAF_ADD_BRANCH   = 1
} OSAL_Tree_Vendor_Add_Analyzer_Result_ET;

typedef OSAL_Tree_Vendor_Add_Analyzer_Result_ET (*OSAL_Tree_Vendor_Add_Analyzer_HT)(OSAL_Tree_XT *list_first_leaf, void *params);

/**
 * allocates new leaf - element which inherits from OSAL_Tree_XT type.
 */
typedef void* (*OSAL_Tree_Allocate_Sub_Branch_Vendor_HT)(OSAL_Tree_XT *list_first_leaf, void *params);

/**
 * allocates new leaf - element which inherits from OSAL_Tree_XT type.
 */
typedef void* (*OSAL_Tree_Allocate_Sub_Branch_String_HT)(OSAL_Tree_XT *list_first_leaf, const char *string, uint32_t offset, uint32_t string_len, uint32_t id_offset);

/**
 * frees leaf - element which inherits from OSAL_Tree_XT type.
 * This function is called for every removed leaf, it is up to this function how / which element shall be freed.
 */
typedef OSAL_List_Free_Leaf_HT OSAL_Tree_Free_Leaf_HT;

/**
 * @brief for initializing list object.
 *
 * @param leaf pointer to the list leaf object to be initialized.
 */
void OSAL_Tree_Leaf_Init(void *leaf);

/**
 * @brief Searches tree leaf by its text describing.
 *
 * @param first_leaf first leaf of the tree (starting element of the tree).
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * @param id_string ASCII string identifier of the element to be found.
 * @param branch_separator character which is recognized in id_string as separators between parent and child branches,
 * for example if we want to separate parents with childs by dot (building.home) then this string should be ".".
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_Tree_Find_By_String(void *first_leaf, uint32_t id_offset, const char *id_string, char branch_separator);

/**
 * @brief Searches tree leaf by its vendor specific identifier.
 *
 * @param first_leaf first leaf of the tree (starting element of the tree).
 * @param compare vendor specific function for comparing leaf identifier.
 * If compare function returns OSAL_TREE_LEAF_COMPARE_MATCH them it means element has been found.
 * If compare function returns OSAL_TREE_LEAF_COMPARE_BRANCH then leafs of branch must be analyzed (child leafs).
 * If compare function returns OSAL_TREE_LEAF_COMPARE_NOT_MATCH then next leaf should be analyzed and all child leafs on the branch should be skipped.
 * @param params parameters to be provided to @see compare function.
 * @result pointer to the found leaf or OSAL_MAKE_INVALID_PTR(void) if leaf with requested identifier has not been found.
 */
void *OSAL_Tree_Find_By_Vendor(void *first_leaf, OSAL_Tree_Vendor_Compare_HT compare, void *params);

/**
 * @brief Add new tree leaf by its text describing. Order is specified by @see order_growing parameter.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the tree (starting element of the tree).
 * @param new_leaf pointer to new leaf to be added to the tree.
 * @param id_offset number of bytes from the begining of the leaf where leaf identifier is located.
 * @param offset number of bytes on the begining of identifier string of each leaf we have to skip in the searching procedure.
 * @param full_path item path in the tree, each branches separated by branch_separators char. If new_leaf ID is not set, this function will correct it.
 * If not valid pointer provided then it will be taken out from new_leaf.
 * @param branch_separator character which is recognized in id_string as separators between parent and child branches,
 * for example if we want to separate parents with childs by dot (building.home) then this string should be ".".
 * @param sub_branch_allocator function called to allocate sub-branch.
 * @param order_growing if OSAL_TRUE then order is growing in identifier ASCII values (alphabetical), OSAL_FALSE otherwise.
 * @result offset in full_path at which leaf name is located.
 */
uint32_t OSAL_Tree_Add_By_String(
   void                                   *first_leaf_ptr,
   void                                   *new_leaf,
   uint32_t                                id_offset,
   uint32_t                                offset,
   const char                             *full_path,
   char                                    branch_separator,
   OSAL_Tree_Allocate_Sub_Branch_String_HT sub_branch_allocator,
   OSAL_Bool_DT                            order_growing);

/**
 * @brief Add new tree leaf by its vendor specific identifier. Order is also vendor specific
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the tree (starting element of the tree).
 * @param new_leaf pointer to new leaf to be added to the tree.
 * @param search_compare vendor specific function for comparing leaf identifier.
 * If compare function returns OSAL_TREE_LEAF_COMPARE_MATCH them it means element has been found.
 * If compare function returns OSAL_TREE_LEAF_COMPARE_BRANCH then leafs of branch must be analyzed (child leafs).
 * If compare function returns OSAL_TREE_LEAF_COMPARE_NOT_MATCH then next leaf should be analyzed and all child leafs on the branch should be skipped.
 * @param add_compare vendor specific function for comparing leaf identifier. If compare function returns OSAL_TRUE them it means new leaf has to be stored BEFORE current one.
 * It is used to add an item in the list on the specific place(to ensure proper order of elements).
 * @param add_analyzer function called to say if new item should be added directly into the current branch or sub-branch should be created.
 * @param sub_branch_allocator function called to allocate sub-branch.
 * @param params parameters to be provided to @see search_compare, @see add_compare, @see add_analyzer and @see sub_branch_allocator functions.
 */
void OSAL_Tree_Add_By_Vendor(
   void                                   *first_leaf_ptr,
   void                                   *new_leaf,
   OSAL_Tree_Vendor_Compare_HT             search_compare,
   OSAL_List_Vendor_Compare_HT             add_compare,
   OSAL_Tree_Vendor_Add_Analyzer_HT        add_analyzer,
   OSAL_Tree_Allocate_Sub_Branch_Vendor_HT sub_branch_allocator,
   void                                   *params);

#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)

/**
 * @brief Removes tree leaf and its all syb-leafs (removes whole branch if "leaf" param points to a branch.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the tree (starting element of the tree).
 * @param leaf pointer to the leaf to be removed from the tree.
 * @param free_func handler to user-defined function called to free memory occupied by the leaf.
 * It is called after leaf has been detached from the tree.
 * If OSAL_MAKE_INVALID_HANDLER(OSAL_Tree_Free_Leaf_HT) is provided then leaf is only removed from the list without freeing step.
 */
void OSAL_Tree_Remove_Leaf(void *first_leaf_ptr, void *leaf, OSAL_Tree_Free_Leaf_HT free_func);

/**
 * @brief Removes tree all elements.
 *
 * @param first_leaf_ptr pointer to the variable holding pointer to first leaf of the tree (starting element of the tree).
 * @param free_func handler to user-defined function called to free memory occupied by the leaf.
 * It is called after leaf has been detached from the tree.
 * If OSAL_MAKE_INVALID_HANDLER(OSAL_Tree_Free_Leaf_HT) is provided then leaf is only removed from the list without freeing step.
 */
void OSAL_Tree_Clear_List(void *first_leaf_ptr, OSAL_Tree_Free_Leaf_HT free_func);

#endif

/** @} */ // end of Trees

#endif

