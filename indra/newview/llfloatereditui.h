/** 
 * @file llfloatereditui.h
 * @author James Cook
 * @brief In-world UI editor
 *
 * Copyright (c) 2005-2007, Linden Research, Inc.
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

#ifndef LL_LLFLOATEREDITUI_H
#define LL_LLFLOATEREDITUI_H

#include "llfloater.h"

class LLLineEditor;
class LLSpinCtrl;

class LLFloaterEditUI : public LLFloater
{
public:
	LLFloaterEditUI();
	virtual ~LLFloaterEditUI();

	virtual void draw();
	void refresh();
	void refreshCore();

	void refreshView(LLView* view);
	void refreshButton(LLView* view);
	static void	navigateHierarchyButtonPressed(void*	data);
	static void show(void* unused = NULL);

	static BOOL handleKey(KEY key, MASK mask);

	static void onCommitLabel(LLUICtrl* ctrl, void* data);
	static void onCommitHeight(LLUICtrl* ctrl, void* data);
	static void onCommitWidth(LLUICtrl* ctrl, void* data);

protected:
	LLView* mLastView;

	LLLineEditor* mLabelLine;
	LLSpinCtrl* mWidthSpin;
	LLSpinCtrl* mHeightSpin;

	static LLFloaterEditUI* sInstance;
};

#endif
