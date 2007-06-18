/** 
 * @file lscript_heap.h
 * @brief classes to manage script heap
 *
 * Copyright (c) 2002-2007, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlife.com/developers/opensource/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at http://secondlife.com/developers/opensource/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 */

#if 0

#ifndef LL_LSCRIPT_HEAP_H
#define LL_LSCRIPT_HEAP_H

#include "lscript_byteconvert.h"
//#include "vmath.h"
#include "v3math.h"
#include "llquaternion.h"

class LLScriptHeapEntry
{
public:
	LLScriptHeapEntry(U8 *entry);
	LLScriptHeapEntry(U8 *heap, S32 offset);
	~LLScriptHeapEntry();

	void addString(char *string);

	S32 mNext;
	U8	mType;
	S32 mRefCount;
	S32 mListOffset;
	U8  *mEntry;
	U8  *mData;
	U8  *mListEntry;
};

#endif

#endif

