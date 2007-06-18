/** 
 * @file llfloaterpermissionsmgr.cpp
 * @brief for user control of script permissions
 *
 * Copyright (c) 2003-2007, Linden Research, Inc.
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

#include "llviewerprecompiledheaders.h"

#include "llfloaterpermissionsmgr.h"

#include "llscrollcontainer.h"
#include "lltextbox.h"
#include "llbutton.h"
#include "llagent.h"
#include "llviewerobjectlist.h"
#include "llviewerregion.h"
#include "llstl.h"

// constants
const S32 MIN_PERM_MGR_WIDTH = 100;
const S32 MIN_PERM_MGR_HEIGHT = 100;
const S32 VPAD = 8;
const S32 HPAD = 8;
const S32 LINE = 16;

// statics
LLFloaterPermissionsMgr* LLFloaterPermissionsMgr::sInstance = NULL;

LLFloaterPermissionsMgr* LLFloaterPermissionsMgr::show()
{
	if (!sInstance)
	{
		sInstance = new LLFloaterPermissionsMgr();

		sInstance->open();	/* Flawfinder: ignore */
		gFloaterView->adjustToFitScreen(sInstance, TRUE);
	}
	else
	{
		sInstance->open();		/* Flawfinder: ignore */
	}

	return sInstance;
}

void LLFloaterPermissionsMgr::processPermissionsList(LLMessageSystem* msg, void**)
{
}

LLFloaterPermissionsMgr::LLFloaterPermissionsMgr() : LLFloater("floater_perm_mgr", "PermissionsManagerRect", "Permissions Manager", TRUE, MIN_PERM_MGR_WIDTH,
															MIN_PERM_MGR_HEIGHT)
{
	S32 y = mRect.getHeight() - VPAD - LINE;
	LLRect scrollable_container_rect(0, y, mRect.getWidth(), 0);
	LLRect permissions_rect(0, 0, mRect.getWidth() - HPAD - HPAD, 0);
	mPermissions = new LLPermissionsView(permissions_rect);
	mScroller = new LLScrollableContainerView(
				"permissions container",
				scrollable_container_rect,
				mPermissions
				);
	mScroller->setFollowsAll();
	mScroller->setReserveScrollCorner(TRUE);
	addChild(mScroller);
}

LLFloaterPermissionsMgr::~LLFloaterPermissionsMgr()
{
}


//
// LLPermissionsView
//

LLPermissionsView::LLPermissionsView(const LLRect &rect) : LLView("permissions_view", rect, TRUE, FOLLOWS_NONE)
{
}

EWidgetType LLPermissionsView::getWidgetType() const
{
	return WIDGET_TYPE_PERMISSIONS_VIEW;
}

LLString LLPermissionsView::getWidgetTag() const
{
	return LL_PERMISSIONS_VIEW_TAG;
}

void LLPermissionsView::clearPermissionsData() 
{
	deleteAllChildren();
	std::for_each(mPermData.begin(), mPermData.end(), DeletePairedPointer());
	mPermData.clear();
}

void LLPermissionsView::addPermissionsData(const LLString& object_name, const LLUUID& object_id, U32 permissions_flags) 
{
	// grow to make room for new element
	LLPermissionsData* perm_datap = new LLPermissionsData(object_id, permissions_flags);

	reshape(mRect.getWidth(), mRect.getHeight() + LINE + VPAD + BTN_HEIGHT + VPAD);
	S32 y = mRect.getHeight() - LINE - VPAD;
	LLRect label_rect(HPAD, y + LINE, mRect.getWidth(), y);
	LLTextBox* text = new LLTextBox("perm_label", label_rect, object_name.c_str());
	text->setFollows(FOLLOWS_LEFT | FOLLOWS_RIGHT | FOLLOWS_BOTTOM);
	addChild(text);

	y -= LINE + VPAD;

	LLRect btn_rect(HPAD, y + BTN_HEIGHT, 120, y);
	LLButton* button = new LLButton("Revoke permissions", btn_rect, "", revokePermissions, (void*)perm_datap);
	button->setFollows(FOLLOWS_LEFT | FOLLOWS_BOTTOM);
	addChild(button);

	btn_rect.set(HPAD + 120 + HPAD, y + BTN_HEIGHT, HPAD + 120 + HPAD + 120, y);
	button = new LLButton("Find in world", btn_rect, "", findObject, (void*)perm_datap);
	button->setFollows(FOLLOWS_LEFT | FOLLOWS_BOTTOM);
	addChild(button);

	mPermData.insert(std::make_pair(object_id, perm_datap));
}

void LLPermissionsView::revokePermissions(void *userdata)
{
	LLPermissionsData* perm_data = (LLPermissionsData*)userdata;
	if (perm_data)
	{
		LLViewerObject* objectp = gObjectList.findObject(perm_data->mObjectID);
		if (objectp)
		{
			LLMessageSystem* msg = gMessageSystem;
			msg->newMessageFast(_PREHASH_RevokePermissions);
			msg->nextBlockFast(_PREHASH_AgentData);
			msg->addUUIDFast(_PREHASH_AgentID, gAgent.getID());
			msg->addUUIDFast(_PREHASH_SessionID, gAgent.getSessionID());
			msg->nextBlockFast(_PREHASH_Data);
			msg->addUUIDFast(_PREHASH_ObjectID, perm_data->mObjectID);
			msg->addU32Fast(_PREHASH_ObjectPermissions, perm_data->mPermFlags);
			msg->sendReliable(objectp->getRegion()->getHost());
		}
	}
}

void LLPermissionsView::findObject(void *userdata)
{
}