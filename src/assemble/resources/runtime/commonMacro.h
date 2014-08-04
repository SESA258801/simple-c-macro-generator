/**
 * Copyright (C) 2014 Schneider Electric
 *
 * This file is part of "Mind Compiler" is free software: you can redistribute
 * it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: mind@ow2.org
 *
 * Authors: Julien TOUS
 * Contributors: Stephane SEYVOZ
 */

#ifndef COMMONMACRO_H_
#define COMMONMACRO_H_

/* Differentiate between Interfaces and Private methods implementation */
#define METH(...) METH_NUM_ARGS_IMPL(__VA_ARGS__, 2,1)(__VA_ARGS__)
#define METH_NUM_ARGS_IMPL(_1,_2,N,...) PREMANGLE##N
/* Differentiate between Interfaces and Private methods call */
#define CALL(...) CALL_NUM_ARGS_IMPL(__VA_ARGS__, 2,1)(__VA_ARGS__)
#define CALL_NUM_ARGS_IMPL(_1,_2,N,...) CALL##N
#define CALL1(METH_NAME) PREMANGLE1(METH_NAME)
#define CALL2(METH_NAME,METH_NAME) GET_MY_INTERFACE(ITF_NAME).METH_NAME

/* Introduce Definition name */
#define PREMANGLE2(ITF_NAME,METH_NAME) MANGLE3_HELPER( DEFINITION_NAME , ITF_NAME, METH_NAME)
#define PREMANGLE1(METH_NAME) MANGLE2_HELPER(DEFINITION_NAME, METH_NAME)
/* Extra step needed to expend DEFINITION_NAME */
#define MANGLE3_HELPER(DEF_NAME, ITF_NAME, METH_NAME) MANGLE3(DEF_NAME, ITF_NAME, METH_NAME)
#define MANGLE2_HELPER(DEF_NAME, METH_NAME) MANGLE2(DEF_NAME, METH_NAME)
/* Create a mangled name */
#define MANGLE3(DEF_NAME, ITF_NAME, METH_NAME) _component_##DEF_NAME##_interface_##ITF_NAME##_method_##METH_NAME
#define MANGLE2(DEF_NAME, METH_NAME) _component_##DEF_NAME##_private_method_##METH_NAME



#define PRIVATE PRIVATE_HELPER_HELPER(DEFINITION_NAME)
#define PRIVATE_HELPER_HELPER(DEF_NAME) PRIVATE_HELPER(DEF_NAME)
#define PRIVATE_HELPER(DEF_NAME) _component_##DEF_NAME##_private_data

#define IS_BOUND(interface) 1
#define IS_BOUND_COLLECTION(interface,index) 1

#define GET_COLLECTION_SIZE(ITF_NAME)  GET_COLLECTION_SIZE_HELPER_HELPER(DEFINITION_NAME, ITF_NAME)
#define GET_COLLECTION_SIZE_HELPER_HELPER(DEF_NAME, ITF_NAME) GET_COLLECTION_SIZE_HELPER(DEF_NAME, ITF_NAME)
#define GET_COLLECTION_SIZE_HELPER(DEF_NAME, ITF_NAME) _component_##DEF_NAME##_interface_##ITF_NAME##_size

#define ATTRIBUTE_STRUCT_NAME ATTRIBUTE_STRUCT_NAME_HELPER_HELPER(DEFINITION_NAME)
#define ATTRIBUTE_STRUCT_NAME_HELPER_HELPER(DEF_NAME) ATTRIBUTE_STRUCT_NAME_HELPER(DEF_NAME)
#define ATTRIBUTE_STRUCT_NAME_HELPER(DEF_NAME) _component_##DEF_NAME##_attribute

#define ATTR(ATTR_NAME) ATTR_HELPER(ATTRIBUTE_STRUCT_NAME, ATTR_NAME)
#define ATTR_HELPER(ATTR_STRUCT_NAME,ATTR_NAME) ATTR_STRUCT_NAME.ATTR_NAME


#define CONSTRUCTOR() CONSTRUCTOR_HELPER_HELPER(DEFINITION_NAME)
#define CONSTRUCTOR_HELPER_HELPER(DEF_NAME) CONSTRUCTOR_HELPER(DEF_NAME)
#define CONSTRUCTOR_HELPER(DEF_NAME) void _component_##DEF_NAME##_constructor_(void)

#define DESTRUCTOR() DESTRUCTOR_HELPER_HELPER(DEFINITION_NAME)
#define DESTRUCTOR_HELPER_HELPER(DEF_NAME) DESTRUCTOR_HELPER(DEF_NAME)
#define DESTRUCTOR_HELPER(DEF_NAME) void _component_##DEF_NAME##_destructor_(void)

#define GET_MY_INTERFACE(ITF_NAME) GET_MY_INTERFACE_HELPER_HELPER(DEFINITION_NAME,ITF_NAME)
#define GET_MY_INTERFACE_HELPER_HELPER(DEF_NAME,ITF_NAME) GET_MY_INTERFACE_HELPER(DEF_NAME, ITF_NAME)
#define GET_MY_INTERFACE_HELPER(DEF_NAME, ITF_NAME) _component_##DEF_NAME##_interface_##ITF_NAME

#define IS_BOUND_PTR(ITF_PTR_NAME) (ITF_PTR_NAME!=0)


#define CALL_PTR(...) CALL_PTR_NUM_ARGS_IMPL(__VA_ARGS__, 2,1)(__VA_ARGS__)
#define CALL_PTR_NUM_ARGS_IMPL(_1,_2,N,...) CALL_PTR##N

#define CALL_PTR2(ITF_PTR_NAME, METH_NAME) ITF_PTR_NAME.METH_NAME

#define CALL_PTR1(METH_NAME) METH_NAME
#define METH_PTR(METH_PTR_NAME) METH_PTR_NAME


#endif /* COMMONMACRO_H_ */
