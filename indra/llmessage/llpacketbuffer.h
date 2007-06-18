/** 
 * @file llpacketbuffer.h
 * @brief definition of LLPacketBuffer class for implementing a
 * resend, drop, or delay in packet transmissions.
 *
 * Copyright (c) 2001-2007, Linden Research, Inc.
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

#ifndef LL_LLPACKETBUFFER_H
#define LL_LLPACKETBUFFER_H

#include "net.h"		// for NET_BUFFER_SIZE
#include "llhost.h"

class LLPacketBuffer
{
public:
	LLPacketBuffer(const LLHost &host, const char *datap, const S32 size);
	LLPacketBuffer(S32 hSocket);           // receive a packet
	~LLPacketBuffer();

	S32			getSize() const		{ return mSize; }
	const char	*getData() const	{ return mData; }
	LLHost		getHost() const		{ return mHost; }
	void init(S32 hSocket);
	void free();

protected:
	char	mData[NET_BUFFER_SIZE];        // packet data		/* Flawfinder : ignore */
	S32		mSize;          // size of buffer in bytes
	LLHost	mHost;         // source/dest IP and port
};

#endif


