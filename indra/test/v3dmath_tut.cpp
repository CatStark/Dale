/**
 * @file v3dmath_tut.cpp
 * @author Adroit
 * @date March 2007
 * @brief v3dmath test cases.
 *
 * Copyright (c) 2007-2007, Linden Research, Inc.
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
 
#include <tut/tut.h>
#include "lltut.h"
#include "llquaternion.h"
#include "m3math.h"
#include "v4math.h"
#include "llsd.h"
#include "v3dmath.h"
#include "v3dmath.h"

namespace tut
{
	struct v3dmath_data
	{
	};
	typedef test_group<v3dmath_data> v3dmath_test;
	typedef v3dmath_test::object v3dmath_object;
	tut::v3dmath_test v3dmath_testcase("v3dmath");

	template<> template<>
	void v3dmath_object::test<1>()
	{
		LLVector3d vec3D;
		ensure("1:LLVector3d:Fail to initialize ", ((0 == vec3D.mdV[VX]) && (0 == vec3D.mdV[VY]) && (0 == vec3D.mdV[VZ])));
		F64 x = 2.32f, y = 1.212f, z = -.12f;
		LLVector3d vec3Da(x,y,z);
		ensure("2:LLVector3d:Fail to initialize ", ((2.32f == vec3Da.mdV[VX]) && (1.212f == vec3Da.mdV[VY]) && (-.12f == vec3Da.mdV[VZ])));
		const F64 vec[3] = {1.2f ,3.2f, -4.2f};
		LLVector3d vec3Db(vec);
		ensure("3:LLVector3d:Fail to initialize ", ((1.2f == vec3Db.mdV[VX]) && (3.2f == vec3Db.mdV[VY]) && (-4.2f == vec3Db.mdV[VZ])));
		LLVector3 vec3((F32)x,(F32)y,(F32)z);
		LLVector3d vec3Dc(vec3);
		ensure_equals("4:LLVector3d Fail to initialize",vec3Da,vec3Dc);
	}

	template<> template<>
	void v3dmath_object::test<2>()
	{
		S32 a = -235;
		LLSD llsd(a);
		LLVector3d vec3d(llsd);
		LLSD sd = vec3d.getValue();
		LLVector3d vec3da(sd);
		ensure("1:getValue:Fail ", (vec3d == vec3da));
	}

	template<> template<>
	void v3dmath_object::test<3>()
	{
		F64 a = 232345521.411132;
		LLSD llsd(a);
		LLVector3d vec3d;
		vec3d.setValue(llsd);
		LLSD sd = vec3d.getValue();
		LLVector3d vec3da(sd);
		ensure("1:setValue:Fail to initialize ", (vec3d == vec3da));
	}

	template<> template<>
	void v3dmath_object::test<4>()
	{
		F64 a[3] = {222231.43222, 12345.2343, -434343.33222};
		LLSD llsd;
		llsd[0] = a[0];
		llsd[1] = a[1];
		llsd[2] = a[2];
		LLVector3d vec3D;
		vec3D = llsd;
		ensure("1:operator=:Fail to initialize ", ((llsd[0].asReal()== vec3D.mdV[VX]) && (llsd[1].asReal() == vec3D.mdV[VY]) && (llsd[2].asReal() == vec3D.mdV[VZ])));
	}
	
	template<> template<>
	void v3dmath_object::test<5>()
	{
		F64 x = 2.32f, y = 1.212f, z = -.12f;
		LLVector3d vec3D(x,y,z);
		vec3D.clearVec();
		ensure("1:clearVec:Fail to initialize ", ((0 == vec3D.mdV[VX]) && (0 == vec3D.mdV[VY]) && (0 == vec3D.mdV[VZ])));
		vec3D.setVec(x,y,z);
		ensure("2:setVec:Fail to initialize ", ((x == vec3D.mdV[VX]) && (y == vec3D.mdV[VY]) && (z == vec3D.mdV[VZ])));
		vec3D.zeroVec();
		ensure("3:zeroVec:Fail to initialize ", ((0 == vec3D.mdV[VX]) && (0 == vec3D.mdV[VY]) && (0 == vec3D.mdV[VZ])));
		vec3D.clearVec();
		LLVector3 vec3((F32)x,(F32)y,(F32)z);
		vec3D.setVec(vec3);
		ensure("4:setVec:Fail to initialize ", ((x == vec3D.mdV[VX]) && (y == vec3D.mdV[VY]) && (z == vec3D.mdV[VZ])));
		vec3D.clearVec();
		const F64 vec[3] = {x,y,z};
		vec3D.setVec(vec);
		ensure("5:setVec:Fail to initialize ", ((x == vec3D.mdV[VX]) && (y == vec3D.mdV[VY]) && (z == vec3D.mdV[VZ])));
		LLVector3d vec3Da;
		vec3Da.setVec(vec3D);
		ensure_equals("6:setVec: Fail to initialize", vec3D, vec3Da);
	}
	
	template<> template<>
	void v3dmath_object::test<6>()
	{
		F64 x = -2.32, y = 1.212, z = -.12;
		LLVector3d vec3D(x,y,z);
		vec3D.abs();
		ensure("1:abs:Fail  ", ((-x == vec3D.mdV[VX]) && (y == vec3D.mdV[VY]) && (-z == vec3D.mdV[VZ])));
		ensure("2:isNull():Fail ", (FALSE == vec3D.isNull()));	
		vec3D.clearVec();
		x =.00000001, y = .000001001, z = .000001001;
		vec3D.setVec(x,y,z);
		ensure("3:isNull():Fail ", (TRUE == vec3D.isNull()));	
		ensure("4:isExactlyZero():Fail ", (FALSE == vec3D.isExactlyZero()));	
		x =.0000000, y = .00000000, z = .00000000;
		vec3D.setVec(x,y,z);
		ensure("5:isExactlyZero():Fail ", (TRUE == vec3D.isExactlyZero()));	
	}

	template<> template<>
	void v3dmath_object::test<7>()
	{
		F64 x = -2.32, y = 1.212, z = -.12;
		LLVector3d vec3D(x,y,z);
		
		ensure("1:operator [] failed",( x ==  vec3D[0]));	
		ensure("2:operator [] failed",( y ==  vec3D[1]));
		ensure("3:operator [] failed",( z ==  vec3D[2]));
		vec3D.clearVec();
		x = 23.23, y = -.2361, z = 3.25;
		vec3D.setVec(x,y,z);
		F64 &ref1 = vec3D[0];
		ensure("4:operator [] failed",( ref1 ==  vec3D[0]));
		F64 &ref2 = vec3D[1];
		ensure("5:operator [] failed",( ref2 ==  vec3D[1]));
		F64 &ref3 = vec3D[2];
		ensure("6:operator [] failed",( ref3 ==  vec3D[2]));
	}

	template<> template<>
	void v3dmath_object::test<8>()
	{
		F32 x = 1.f, y = 2.f, z = -1.f;
		LLVector4 vec4(x,y,z);		
		LLVector3d vec3D;
		vec3D = vec4;
		ensure("1:operator=:Fail to initialize ", ((vec4.mV[VX] == vec3D.mdV[VX]) && (vec4.mV[VY] == vec3D.mdV[VY]) && (vec4.mV[VZ] == vec3D.mdV[VZ])));
	}

	template<> template<>
	void v3dmath_object::test<9>()
	{
		F64 x1 = 1.78787878, y1 = 232322.2121, z1 = -12121.121212;
		F64 x2 = 1.2, y2 = 2.5, z2 = 1.;
		LLVector3d vec3D(x1,y1,z1),vec3Da(x2,y2,z2),vec3Db;
		vec3Db = vec3Da+ vec3D;
		ensure("1:operator+:Fail to initialize ", ((x1+x2 == vec3Db.mdV[VX]) && (y1+y2 == vec3Db.mdV[VY]) && (z1+z2 == vec3Db.mdV[VZ])));
		x1 = -2.45, y1 = 2.1, z1 = 3.0;
		vec3D.clearVec();
		vec3Da.clearVec();
		vec3D.setVec(x1,y1,z1);
		vec3Da += vec3D;
		ensure_equals("2:operator+=: Fail to initialize", vec3Da,vec3D);
		vec3Da += vec3D;
		ensure("3:operator+=:Fail to initialize ", ((2*x1 == vec3Da.mdV[VX]) && (2*y1 == vec3Da.mdV[VY]) && (2*z1 == vec3Da.mdV[VZ])));
	}

	template<> template<>
	void v3dmath_object::test<10>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		F64 x2 = 1.2, y2 = 2.5, z2 = 1.;
		LLVector3d vec3D(x1,y1,z1),vec3Da(x2,y2,z2),vec3Db;
		vec3Db = vec3Da - vec3D;
		ensure("1:operator-:Fail to initialize ", ((x2-x1 == vec3Db.mdV[VX]) && (y2-y1 == vec3Db.mdV[VY]) && (z2-z1 == vec3Db.mdV[VZ])));
		x1 = -2.45, y1 = 2.1, z1 = 3.0;
		vec3D.clearVec();
		vec3Da.clearVec();
		vec3D.setVec(x1,y1,z1);
		vec3Da -=vec3D;
		ensure("2:operator-=:Fail to initialize ", ((2.45 == vec3Da.mdV[VX]) && (-2.1 == vec3Da.mdV[VY]) && (-3.0 == vec3Da.mdV[VZ])));
		vec3Da -= vec3D;
		ensure("3:operator-=:Fail to initialize ", ((-2*x1 == vec3Da.mdV[VX]) && (-2*y1 == vec3Da.mdV[VY]) && (-2*z1 == vec3Da.mdV[VZ])));
	}
	template<> template<>
	void v3dmath_object::test<11>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		F64 x2 = 1.2, y2 = 2.5, z2 = 1.;
		LLVector3d vec3D(x1,y1,z1),vec3Da(x2,y2,z2);
		F64 res = vec3D * vec3Da;
		ensure("1:operator* failed",(res == (x1*x2 + y1*y2 + z1*z2)));
		vec3Da.clearVec();
		F64 mulVal = 4.2;
		vec3Da = vec3D * mulVal;
		ensure("2:operator* failed",(x1*mulVal == vec3Da.mdV[VX]) && (y1*mulVal == vec3Da.mdV[VY])&& (z1*mulVal == vec3Da.mdV[VZ]));
		vec3Da.clearVec();
		vec3Da = mulVal * vec3D;
		ensure("3:operator* failed",(x1*mulVal == vec3Da.mdV[VX]) && (y1*mulVal == vec3Da.mdV[VY])&& (z1*mulVal == vec3Da.mdV[VZ]));
		vec3D *= mulVal;
		ensure("4:operator*= failed",(x1*mulVal == vec3D.mdV[VX]) && (y1*mulVal == vec3D.mdV[VY])&& (z1*mulVal == vec3D.mdV[VZ]));
	}

	template<> template<>
	void v3dmath_object::test<12>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		F64 x2 = 1.2, y2 = 2.5, z2 = 1.;
		F64 val1, val2, val3;
		LLVector3d vec3D(x1,y1,z1),vec3Da(x2,y2,z2), vec3Db;
		vec3Db = vec3D % vec3Da;
		val1 = y1*z2 - y2*z1;
		val2 = z1*x2 -z2*x1;
		val3 = x1*y2-x2*y1;
		ensure("1:operator% failed",(val1 == vec3Db.mdV[VX]) && (val2 == vec3Db.mdV[VY]) && (val3 == vec3Db.mdV[VZ])); 
		vec3D %= vec3Da;
		ensure_equals("2:operator%= failed",vec3D,vec3Db); 
	}

	template<> template<>
	void v3dmath_object::test<13>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1,div = 4.2;
		F64 t = 1.f / div;
		LLVector3d vec3D(x1,y1,z1), vec3Da;
		vec3Da = vec3D/div;
		ensure("1:operator/ failed",(x1*t == vec3Da.mdV[VX]) && (y1*t == vec3Da.mdV[VY])&& (z1*t == vec3Da.mdV[VZ]));
		 x1 = 1.23, y1 = 4., z1 = -2.32;
		 vec3D.clearVec();
		 vec3Da.clearVec();
		 vec3D.setVec(x1,y1,z1);
		 vec3Da = vec3D/div;
		 ensure("2:operator/ failed",(x1*t == vec3Da.mdV[VX]) && (y1*t == vec3Da.mdV[VY])&& (z1*t == vec3Da.mdV[VZ]));
		 vec3D /= div;
		 ensure("3:operator/= failed",(x1*t == vec3D.mdV[VX]) && (y1*t == vec3D.mdV[VY])&& (z1*t == vec3D.mdV[VZ]));
	}

	template<> template<>
	void v3dmath_object::test<14>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		LLVector3d vec3D(x1,y1,z1), vec3Da;
		ensure("1:operator!= failed",(TRUE == (vec3D !=vec3Da)));
		vec3Da = vec3D;
		ensure("2:operator== failed",(vec3D ==vec3Da)); 
		vec3D.clearVec();
		vec3Da.clearVec();
		x1 = .211, y1 = 21.111, z1 = 23.22;
		vec3D.setVec(x1,y1,z1);
		vec3Da.setVec(x1,y1,z1);
		ensure("3:operator== failed",(vec3D ==vec3Da)); 
		ensure("4:operator!= failed",(FALSE == (vec3D !=vec3Da)));
	}
		
	template<> template<>
	void v3dmath_object::test<15>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		LLVector3d vec3D(x1,y1,z1), vec3Da;
		std::ostringstream stream1, stream2;
		stream1 << vec3D;
		vec3Da.setVec(x1,y1,z1);
		stream2 << vec3Da;
		ensure("1:operator << failed",(stream1.str() == stream2.str()));	
	}

	template<> template<>
	void v3dmath_object::test<16>()
	{
		F64 x1 = 1.23, y1 = 2.0, z1 = 4.;
		char buf[] = "1.23 2. 4";
		LLVector3d vec3D, vec3Da(x1,y1,z1);
		LLVector3d::parseVector3d(buf, &vec3D);
		ensure_equals("1:parseVector3d: failed " , vec3D, vec3Da);	
	}

	template<> template<>
	void v3dmath_object::test<17>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		LLVector3d vec3D(x1,y1,z1), vec3Da;
		vec3Da = -vec3D;
		ensure("1:operator- failed", (vec3D == - vec3Da));	
	}

	template<> template<>
	void v3dmath_object::test<18>()
	{
		F64 x = 1., y = 2., z = -1.1;
		LLVector3d vec3D(x,y,z);
		F64 res = (x*x + y*y + z*z) - vec3D.magVecSquared();
		ensure("1:magVecSquared:Fail ", ((-F_APPROXIMATELY_ZERO <= res)&& (res <=F_APPROXIMATELY_ZERO)));
		res = fsqrtf(x*x + y*y + z*z) - vec3D.magVec();
		ensure("2:magVec: Fail ", ((-F_APPROXIMATELY_ZERO <= res)&& (res <=F_APPROXIMATELY_ZERO)));	
	}

	template<> template<>
	void v3dmath_object::test<19>()
	{
		F64 x = 1., y = 2., z = -1.1;
		LLVector3d vec3D(x,y,z);
		F64 mag = vec3D.normVec();
		mag = 1.f/ mag;
		ensure("1:normVec: Fail ", (x* mag == vec3D.mdV[VX]) && (y* mag == vec3D.mdV[VY])&& (z* mag == vec3D.mdV[VZ]));
		x = 0.000000001, y = 0.000000001, z = 0.000000001;
		vec3D.clearVec();
		vec3D.setVec(x,y,z);
		mag = vec3D.normVec();
		ensure("2:normVec: Fail ", (x* mag == vec3D.mdV[VX]) && (y* mag == vec3D.mdV[VY])&& (z* mag == vec3D.mdV[VZ]));
	}

	template<> template<>
	void v3dmath_object::test<20>()
	{
		F64 x1 = 1111.232222, y1 = 2222222222.22, z1 = 422222222222;
		char buf[] = "1111.232222 2222222222.22 422222222222";
		LLVector3d vec3Da, vec3Db(x1,y1,z1);
		LLVector3d::parseVector3d(buf, &vec3Da);
		ensure_equals("1:parseVector3 failed", vec3Da, vec3Db);	
	}

	template<> template<>
	void v3dmath_object::test<21>()
	{
		F64 x1 = 1., y1 = 2., z1 = -1.1;
		F64 x2 = 1.2, y2 = 2.5, z2 = 1.;
		F64 val = 2.3f,val1,val2,val3;
		val1 = x1 + (x2 - x1)* val;
		val2 = y1 + (y2 - y1)* val;
		val3 = z1 + (z2 - z1)* val;
		LLVector3d vec3Da(x1,y1,z1),vec3Db(x2,y2,z2);
		LLVector3d vec3d = lerp(vec3Da,vec3Db,val);
		ensure("1:lerp failed", ((val1 ==vec3d.mdV[VX])&& (val2 ==vec3d.mdV[VY]) && (val3 ==vec3d.mdV[VZ])));		
	}

	template<> template<>
	void v3dmath_object::test<22>()
	{
		F64 x = 2.32, y = 1.212, z = -.12;
		F64 min = 0.0001, max = 3.0;
		LLVector3d vec3d(x,y,z);		
		ensure("1:clamp:Fail ", (TRUE == (vec3d.clamp(min, max))));
		x = 0.000001f, z = 5.3f;
		vec3d.setVec(x,y,z);
		ensure("2:clamp:Fail ", (TRUE == (vec3d.clamp(min, max))));
	}

	template<> template<>
	void v3dmath_object::test<23>()
	{
		F64 x = 10., y = 20., z = -15.;
		F64 epsilon = .23425;
		LLVector3d vec3Da(x,y,z), vec3Db(x,y,z);
		ensure("1:are_parallel: Fail ", (TRUE == are_parallel(vec3Da,vec3Db,epsilon)));
		F64 x1 = -12., y1 = -20., z1 = -100.;
		vec3Db.clearVec();
		vec3Db.setVec(x1,y1,z1);
		ensure("2:are_parallel: Fail ", (FALSE == are_parallel(vec3Da,vec3Db,epsilon)));
	}

	template<> template<>
	void v3dmath_object::test<24>()
	{
		F64 x = 10., y = 20., z = -15.;
		F64 angle1, angle2;
		LLVector3d vec3Da(x,y,z), vec3Db(x,y,z);
		angle1 = angle_between(vec3Da, vec3Db);
		ensure("1:angle_between: Fail ", (0 == angle1));
		F64 x1 = -1., y1 = -20., z1 = -1.;
		vec3Da.clearVec();
		vec3Da.setVec(x1,y1,z1);
		angle2 = angle_between(vec3Da, vec3Db);
		vec3Db.normVec();
		vec3Da.normVec();
		F64 angle = vec3Db*vec3Da;
		angle = acos(angle);
		ensure("2:angle_between: Fail ", (angle == angle2));
	}
}