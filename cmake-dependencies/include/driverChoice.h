// Copyright (C) 2009-2012 Christian Stehno
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __E_DRIVER_CHOICE_H_INCLUDED__
#define __E_DRIVER_CHOICE_H_INCLUDED__

#include <iostream>
    "bits/c++config.h"
    "bits/istream.tcc"
        "bits/istream.tcc"
            "bits/istream.tcc"
                "bits/c++config.h"
                "bits/stringfwd.h"
                "bits/postypes.h"
            "bits/istream.tcc"
                "bits/c++config.h"
                "bits/exception.h"
                    "bits/exception_ptr.h"
                    "bits/nested_exception.h"
            "bits/char_traits.h"
            "bits/localefwd.h"
            "bits/ios_base.h"
            "bits/istream.tcc"
                "bits/c++config.h"
                "bits/istream.tcc"
                "bits/localefwd.h"
                "bits/ios_base.h"
                "bits/cpp_type_traits.h"
                "ext/type_traits.h"
                "bits/streambuf.tcc"
            "bits/basic_ios.h"
        "bits/ostream_insert.h"
        "bits/ostream.tcc"
    "bits/istream.tcc"
        "bits/istream.tcc"
        "bits/istream.tcc"
        "bits/istream.tcc"
#include <cstdio>
"bits/c++config.h"
"stdio.h"
#include "EDriverTypes.h"
#include "irrTypes.h"
#include "IrrlichtDevice.h"

namespace irr
{

//! ask user for driver
static irr::video::E_DRIVER_TYPE driverChoiceConsole(bool allDrivers=true)
{
	const char* const names[] = {"NullDriver","Software Renderer","Burning's Video","Direct3D 8.1","Direct3D 9.0c","OpenGL 1.x/2.x/3.x"};
	printf("Please select the driver you want:\n");
	irr::u32 i=0;
	for (i=irr::video::EDT_COUNT; i>0; --i)
	{
		if (allDrivers || (irr::IrrlichtDevice::isDriverSupported(irr::video::E_DRIVER_TYPE(i-1))))
			printf(" (%c) %s\n", 'a'+irr::video::EDT_COUNT-i, names[i-1]);
	}

	char c;
	std::cin >> c;
	c = irr::video::EDT_COUNT+'a'-c;

	for (i=irr::video::EDT_COUNT; i>0; --i)
	{
		if (!(allDrivers || (irr::IrrlichtDevice::isDriverSupported(irr::video::E_DRIVER_TYPE(i-1)))))
			--c;
		if ((char)i==c)
			return irr::video::E_DRIVER_TYPE(i-1);
	}
	return irr::video::EDT_COUNT;
}

} // end namespace irr

#endif
