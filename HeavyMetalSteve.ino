/*
    rgb_display_animation.ino
    Driver for RGB LED Matrix

    Copyright (c) 2018 Seeed Technology Co., Ltd.
    Website    : www.seeed.cc
    Author     : downey
    Create Time: sep. 2018
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

/*

    Modified by Neil Devonshire (Dev255.uk)

    This version displays characters from the MineCraft game and utilises a reed switch to cycle between characters.

    This product is unofficial and not from Minecraft or approved by Minecraft.
    The idea is to create a one off gift to be just a toy, or even as a tool to get someone into coding at a later date.
    Dev255 is not associated or connected in any way with MineCraft or Mojang Studios.

*/

#include "grove_two_rgb_led_matrix.h"

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif


#define DISPLAY_COLOR    0X11

uint64_t steveNorm[] = {

  0xffffffffffffffff, // Steve Normal
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16191f17181c2020,
  0x20febb2020bbfe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveOpenMouth[] = {
 
  0xffffffffffffffff, // Steve Open Mouth
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16191f17181c2020,
  0x20febb2020bbfe20,
  0x1620201111202017,
  0x161b0cfefe0c1717,
  0x16170c0c0c0c1515
};
uint64_t steveEyesClosed[] = {
 
  0xffffffffffffffff, // Steve Eyes Closed
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16191f1718222020,
  0x2022222020222220,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveLR[] = {
 
  0xffffffffffffffff, // Steve Look Right
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16191f17181c2020,
  0x20befe2020bbfe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveLL[] = {
 
  0xffffffffffffffff, // Steve Look Left
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16191f17181c2020,
  0x20feba2020feba20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveLU[] = {
 
  0xffffffffffffffff, // Steve Look Up
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16febd1718bdfe20,
  0x20fefe2020fefe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveRE1[] = {
 
  0xffffffffffffffff, // Steve Roll Eyes 1
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16febd1718febd20,
  0x20fefe2020fefe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveRE2[] = {
 
  0xffffffffffffffff, // Steve Roll Eyes 2
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16fefe1718fefe20,
  0x20febe2020febe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveRE3[] = {
 
  0xffffffffffffffff, // Steve Roll Eyes 3
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16fefe1718fefe20,
  0x20c0fe2020c0fe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};
uint64_t steveRE4[] = {
 
  0xffffffffffffffff, // Steve Roll Eyes 4
  0xffffffffffffffff,
  0xff1b2020202020ff,
  0x16befe1718befe20,
  0x20fefe2020fefe20,
  0x1620201111202017,
  0x161b0c20200c1717,
  0x16170c0c0c0c1515
};

uint64_t tNT[] = {
 
  0x000ef4000ef4000e, // TNT
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4000ef4000c
};
uint64_t tNTEx1[] = {
 
  0x000ef4000ef4000e, // TNT Explode 1
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffe0101fefffe,
  0xfefffe0101fefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4000ef4000c
};
uint64_t tNTEx2[] = {
 
  0x000ef4000ef4000e, // TNT Explode 2
  0xfefefefefefefefe,
  0xffff01010101ffff,
  0xfeff01121201fffe,
  0xfeff01121201fffe,
  0xfefe01010101fefe,
  0x010df4010df4010d,
  0x000ef4000ef4000c
};
uint64_t tNTEx3[] = {
 
  0x000ef4000ef4000e, // TNT Explode 3
  0xfe010101010101fe,
  0xff011212121201ff,
  0xfe011224241201fe,
  0xfe011224241201fe,
  0xfe011212121201fe,
  0x010101010101010d,
  0x000ef4000ef4000c
};
uint64_t tNTEx4[] = {
 
  0x0101010101010101, // TNT Explode 4
  0x0112121212121201,
  0x0112242424241201,
  0x0112242c2c241201,
  0x0112242c2c241201,
  0x0112242424241201,
  0x0112121212121201,
  0x0101010101010101
};
uint64_t tNTEx5[] = {
 
  0x0101010101010101, // TNT Explode 5
  0x012c2c2c2c2c2c01,
  0x012c2c2c2c2c2c01,
  0x012c2c2c2c2c2c01,
  0x012c2c2c2c2c2c01,
  0x012c2c2c2c2c2c01,
  0x012c2c2c2c2c2c01,
  0x0101010101010101
};

uint64_t tNTCount1[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 1
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x7f0ef4000ef4000c
};
uint64_t tNTCount2[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 2
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x007ff4000ef4000c
};
uint64_t tNTCount3[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 3
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000e7f000ef4000c
};
uint64_t tNTCount4[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 4
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef47f0ef4000c
};
uint64_t tNTCount5[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 5
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4007ff4000c
};
uint64_t tNTCount6[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 6
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4000e7f000c
};
uint64_t tNTCount7[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 7
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4000ef47f0c
};
uint64_t tNTCount8[] = {
 
  0x000ef4000ef4000e, // TNT Countdown 8
  0xfefefefefefefefe,
  0xfffffffefeffffff,
  0xfefffefffffefffe,
  0xfefffefffffefffe,
  0xfefefefefefefefe,
  0x010df4010df4010d,
  0x000ef4000ef4007f
};

uint64_t bobaFett[] = {
 
  0x2d3a3a3a52525252, // Boba Fett
  0x0101010101010101,
  0xffffffffffffffff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl9[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 9
  0x0101010101010101,
  0xffffffffffffffff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e019cff014e4e
};
uint64_t bobaFettRefl8[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 8
  0x0101010101010101,
  0xffffffffffffffff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e019cff014e4e,
  0x4e4e01ff7f014e4e
};
uint64_t bobaFettRefl7[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 7
  0x0101010101010101,
  0xffffffffffffffff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e33019cff01334e,
  0x4e4e01ff7f014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl6[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 6
  0x0101010101010101,
  0xffffffffffffffff,
  0x010101ffff010101,
  0x3333019cff013333,
  0x4e3301ff7f01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl5[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 5
  0x0101010101010101,
  0xffffffffffffffff,
  0x0101019cff010101,
  0x333301ff7f013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl4[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 4
  0x0101010101010101,
  0xffffff9cffffffff,
  0x010101ff7f010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl3[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 3
  0x0101010101010101,
  0xffff9cffff7fffff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl2[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 2
  0x0101010101010101,
  0xff9cffffffff7fff,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t bobaFettRefl1[] = {
 
  0x2d3a3a3a52525252, // Boba Fett Reflect 1
  0x0101010101010101,
  0x9cffffffffffff7f,
  0x010101ffff010101,
  0x333301ffff013333,
  0x4e3301ffff01334e,
  0x4e4e01ffff014e4e,
  0x4e4e01ffff014e4e
};
uint64_t ironMan[] = {
 
  0x0820250000252008, // Iron Man Normal
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x18fefe2a2afefe18,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};
uint64_t ironManHalfEyes[] = {
 
  0x0820250000252008, // Iron Man Half Eyes
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x18feff2a2afffe18,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};
uint64_t ironManEyesOff[] = {
 
  0x0820250000252008, // Iron Man Eyes Off
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x18ffff2a2affff18,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};
uint64_t ironManEyesOn1[] = {
 
  0x0820250000252008, // Iron Man Eyes Turning On 1
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x18ff822a2a82ff18,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};
uint64_t ironManEyesOn2[] = {
 
  0x0820250000252008, // Iron Man Eyes Turning On 2
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x1882822a2a828218,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};
uint64_t ironManEyesOn3[] = {
 
  0x0820250000252008, // Iron Man Eyes Turning On 3
  0x0820252a2a252008,
  0x1820252a2a252018,
  0x1882fe2a2afe8218,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0800252a2a250008
};

uint64_t ironManAngry[] = {
 
  0x0820250000252008, // Iron Man Angry
  0x0820252a2a252008,
  0x181f252a2a251f18,
  0x1801012a2a010118,
  0x1820252a2a252018,
  0x0820252a2a252008,
  0x080025ffff250008,
  0x0b00252a2a25000b
};

uint64_t pigNormal[] = {
 
  0xe2e2d7d7d7d7e6d7, // Pig Normal
  0xd7d7d7d9d7d7e6d7,
  0xfffed7d7d7d7feff,
  0xd7d7d7d7d7d7d7d7,
  0xd7d71e1e1e1ed7d7,
  0xd7d7111e1e11d7d7,
  0xd7d71e1e1e1ed7e2,
  0xd7d7d7d7d7d7d7d7
};
uint64_t pigLR[] = {
 
  0xe2e2d7d7d7d7e6d7, // Pig Eyes Right
  0xd7d7d7d9d7d7e6d7,
  0xfeffd7d7d7d7feff,
  0xd7d7d7d7d7d7d7d7,
  0xd7d71e1e1e1ed7d7,
  0xd7d7111e1e11d7d7,
  0xd7d71e1e1e1ed7e2,
  0xd7d7d7d7d7d7d7d7
};
uint64_t pigLL[] = {
 
  0xe2e2d7d7d7d7e6d7, // Pig Eyes Left
  0xd7d7d7d9d7d7e6d7,
  0xfffed7d7d7d7fffe,
  0xd7d7d7d7d7d7d7d7,
  0xd7d71e1e1e1ed7d7,
  0xd7d7111e1e11d7d7,
  0xd7d71e1e1e1ed7e2,
  0xd7d7d7d7d7d7d7d7
};
uint64_t pigEyesClosed[] = {
 
  0xe2e2d7d7d7d7e6d7, // Pig Eyes Closed
  0xd7d7d7d9d7d7e6d7,
  0xffffd7d7d7d7ffff,
  0xd7d7d7d7d7d7d7d7,
  0xd7d71e1e1e1ed7d7,
  0xd7d7111e1e11d7d7,
  0xd7d71e1e1e1ed7e2,
  0xd7d7d7d7d7d7d7d7
};
uint64_t pigSnoutUp[] = {
 
  0xe2e2d7d7d7d7e6d7, // Pig Snout Up
  0xd7d7d7d9d7d7e6d7,
  0xfffed7d7d7d7feff,
  0xd7d71b1b1b1bd7d7,
  0xd7d7121e1e12d7d7,
  0xd7d71b1b1e1bd7d7,
  0xd7d7d4d4d4d4d7e2,
  0xd7d7d7d7d7d7d7d7
};
uint64_t enderMan[] = {
 
  0xffffffffffffffff, // EnderMan Normal
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xd200d2ffffd200d2,
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffffffffffffffff
};
uint64_t enderManRot1[] = {
 
  0xffffffffffffffff, // EnderMan Rotate 1
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xd2ffffffffd2ffff,
  0xff00ffffffff00ff,
  0xffffd2ffffffffd2,
  0xffffffffffffffff,
  0xffffffffffffffff
};
uint64_t enderManRot2[] = {
 
  0xffffffffffffffff, // EnderMan Rotate 2
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffd2ffffffffd2ff,
  0xff00ffffffff00ff,
  0xffd2ffffffffd2ff,
  0xffffffffffffffff,
  0xffffffffffffffff
};
uint64_t enderManRot3[] = {
 
  0xffffffffffffffff, // EnderMan Rotate 3
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xffffd2ffffffffd2,
  0xff00ffffffff00ff,
  0xd2ffffffffd2ffff,
  0xffffffffffffffff,
  0xffffffffffffffff
};
uint64_t diamond1[] = {
 
  0xffffffffffffffff,
  0xffffffffffffffff,
  0xff81fefefe81ffff,
  0x7f8181fe81fe7fff,
  0x8a92fe81fe8186ff,
  0xff8a92818186ffff,
  0xffff8a7f86ffffff,
  0xffffff86ffffffff,

  0xffffffffffffffff,
  0xffffffffffffffff,
  0xff817ffefefeffff,
  0x7f81817ffe7ffeff,
  0x8a7f90fe7ffe86ff,
  0xff8a7f908186ffff,
  0xffff8a7f86ffffff,
  0xffffff86ffffffff,

  0xffffffffffffffff,
  0xffffffffffffffff,
  0xfffe7f80fefeffff,
  0xfe81fe7f807f80ff,
  0x8afe7f967f8086ff,
  0xff8a7f7f9686ffff,
  0xffff8a7f86ffffff,
  0xffffff86ffffffff
};

uint64_t steveHelmet[] = {
 
  0x7f7f7f7f7f7f7f7f, // Steve Helmet
  0x7f7f7f7f7f7ffe7f,
  0x7f7f7f7f7f7f7f7f,
  0x7f20207ffe20207f,
  0x20fec07f7fc0fe20,
  0x2020201616202020,
  0x2020120707122020,
  0x2020121212122020
};

uint64_t hulkNormal[] = {
 
  0xffffffffffffffff, // Hulk Normal
  0xffffffffffffffff,
  0xff4fffff4fff4fff,
  0x4fffff4f4fffff4f,
  0x4ffe4f4f4f4ffe4f,
  0x4f4f4ffefe4f4f4f,
  0x4f4f4fffff4f4f4f,
  0x4f4f4f4f4f4f4f4f
};
uint64_t hulkEyesClosed[] = {
 
  0xffffffffffffffff, // Hulk Eyes Closed
  0xffffffffffffffff,
  0xff4fffff4fff4fff,
  0x4fffff4f4fffff4f,
  0x4f4e4f4f4f4f4e4f,
  0x4f4f4ffefe4f4f4f,
  0x4f4f4fffff4f4f4f,
  0x4f4f4f4f4f4f4f4f
};

uint64_t hulkMad[] = {
 
  0xffffffffffffffff, // Hulk Mad
  0xffffffffffffffff,
  0xff4fffff4fff4fff,
  0x4fffff4f4fffff4f,
  0x4f004f4f4f4f004f,
  0x4f4f4fffff4f4f4f,
  0x4f4fff1818ff4f4f,
  0x4f4f504e4e504f4f
};

uint64_t christmasTreeNoLights[] = {
 
  0xffffff2b2bffffff, // Christmas Tree No Lights
  0xffffff2b2bffffff,
  0xffffff4444ffffff,
  0xffff44444444ffff,
  0xff4d4444444d4dff,
  0xffff44444d44ffff,
  0xff444d44534444ff,
  0x44444d4d44444d44
};
uint64_t christmasTreeLights1[] = {
 
  0xffffff2b2bffffff, // Christmas Tree Lights 1
  0xffffff2b2bffffff,
  0xffffff4444ffffff,
  0xffff44444401ffff,
  0xfffe4444444dfeff,
  0xffff01444d44ffff,
  0xff444d44014444ff,
  0x44447f4d44447f44
};
uint64_t christmasTreeLights3[] = {
 
  0xffffff2b2bffffff, // Christmas Tree Lights 3
  0xffffff2b2bffffff,
  0xffffff4444ffffff,
  0xffff44440044ffff,
  0xff4d0044444d4dff,
  0xffff44444d44ffff,
  0xff444d44530044ff,
  0x447e4d7e44444d7e
};
uint64_t christmasTreeLights2[] = {
 
  0xffffff2b2bffffff, // Christmas Tree Lights 2
  0xffffff2b2bffffff,
  0xffffff4444ffffff,
  0xffff44444b44ffff,
  0xfffe4b44444dfeff,
  0xffff44444d44ffff,
  0xff444d44534b44ff,
  0xfe4b4d4b44444dfe
};

uint64_t santaHat1[] = {
 
  0xffffffffffffffff,
  0xff0000ffffffffff,
  0x00000000ffffffff,
  0xfeff000000ffffff,
  0xffff00000000ffff,
  0xffff00fefefe00ff,
  0xfffefefefefefefe,
  0xffffffffffffffff
};

uint64_t santaHat2[] = {

  0xff00ffffffffffff,
  0x000000ffffffffff,
  0xfe000000ffffffff,
  0xffff000000ffffff,
  0xff00000000ffffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat3[] = {

  0xfe0000ffffffffff,
  0xff000000ffffffff,
  0xffff000000ffffff,
  0xffff000000ffffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat4[] = {

  0xfffffffe0000ffff,
  0xffffffff0000ffff,
  0xffffff000000ffff,
  0xffff00000000ffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat5[] = {

  0xfffffffffffe01ff,
  0xffffffff000001ff,
  0xffffff000000ffff,
  0xffff00000000ffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat6[] = {

  0xffffffffffffffff,
  0xffffffff00000101,
  0xffffff00000001fe,
  0xffff00000000ffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat7[] = {
  
  0xffffffffffffffff,
  0xffffffff000001ff,
  0xffffff0000000100,
  0xffff00000000fffe,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat8[] = {

  0xffffffff01ffffff,
  0xffffff010000ffff,
  0xffff01000000feff,
  0xffff00000000ffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat9[] = {

  0xffffff01feffffff,
  0xffff010101ffffff,
  0xffff010000ffffff,
  0xffff00000000ffff,
  0xffff00000000ffff,
  0xffff01fefefe01ff,
  0xfffefefefefefefe,
  0xffffffffffffffff
};

uint64_t santaHat10[] = {
  
  0x00feffffffffffff,
  0x01000000ffffffff,
  0xffff000000ffffff,
  0xffff000000ffffff,
  0xffff00000000ffff,
  0xff00fefefe00ffff,
  0xfefefefefefefeff,
  0xffffffffffffffff
};

uint64_t santaHat11[] = {

  0xffffffffffffffff,
  0x010101ffffffffff,
  0xfe010100ffffffff,
  0xffff000000ffffff,
  0xffff00000000ffff,
  0xffff01fefefe01ff,
  0xfffefefefefefefe,
  0xffffffffffffffff
};

uint64_t sheep[] = {
  0xfefefefefefefefe, // Sheep
  0xfefefefefefefefe,
  0x2121211f1f212121,
  0xfffefe1f1ffefeff,
  0xfffefe1f1ffefeff,
  0x211f212121211f21,
  0xfe1fc7c7c7c71ffe,
  0xfe1fd2d2d2d21ffe
};

uint64_t archer[] = {
  0x3030303030303030, // Archer
  0x3030303030303030,
  0x3030303030303030,
  0x3030303030303030,
  0x30ffff3030ffff30,
  0x3030302424303030,
  0x30ffffffffffff30,
  0x3030303030303030
};

uint64_t duck[] = {
  0xfefefefefefefefe, // Duck
  0xfffffefefefeffff,
  0xfffffefefefeffff,
  0x2525252525252525,
  0x2525252525252525,
  0x1f1f1f1f1f1f1f1f,
  0xfefe00000000fefe,
  0xfefe00000000fefe
};

uint64_t alexNorm[] = {
  
  0x1717171717171718,
  0x1717171717171717,
  0x1717171720201717,
  0x1717202020202017,
  0x20fe78222078fe20,
  0x2020202020202020,
  0x202021c6c6212020,
  0x2020202020202020
};

uint64_t alexLL[] = {
  0x1717171717171718,
  0x1717171717171717,
  0x1717171720201717,
  0x1717202020202017,
  0x20fe782220fe7b20,
  0x2020202020202020,
  0x202021c6c6212020,
  0x2020202020202020
};

uint64_t alexLR[] = {
  0x1717171717171718,
  0x1717171717171717,
  0x1717171720201717,
  0x1717202020202017,
  0x207afe22207afe20,
  0x2020202020202020,
  0x202021c6c6212020,
  0x2020202020202020
};

uint64_t alexEyesClosed[] = {
  0x1717171717171718,
  0x1717171717171717,
  0x1717171720201717,
  0x1717202020202017,
  0x2021212220212120,
  0x2020202020202020,
  0x202021c6c6212020,
  0x2020202020202020
};

int reedSwitch = 2;
bool reedSwitchOff = false;
int sequence = 0;
char helloWorld[15] = "  hello world";

// Sequence Order
int sequenceMax = 19;
int steve = 0;
int alex = 1;
int iron = 2;
int boba = 3;
int hulk = 4;
int pig = 5;
int creeper = 6;
int ender = 7;
int tnt = 8;
int mineCraft = 9;
int diamond = 10;
int pokemon = 11;
int anim0 = 12;
int anim1 = 13;
int anim2 = 14;
int anim3 = 15;
int anim4 = 16;
int emoji = 17;
int christmas = 18;
int light = 19;


GroveTwoRGBLedMatrixClass matrix;
void setup() {
  pinMode(reedSwitch, INPUT_PULLUP);
  Wire.begin();
  SERIAL.begin(115200);
  delay(1000);
  uint16_t VID = 0;
  VID = matrix.getDeviceVID();
  if (VID != 0x2886) {
    SERIAL.println("Can not detect led matrix!!!");
    while (1);
  }
  SERIAL.println("Matrix init success!!!");
  matrix.displayString(helloWorld, 5000, true, 0x52);
  delay (5000);
}

void loop() {
  if (sequence == christmas){
    for (int count = 0; count < 4; count++){
      if (sequence == 0){
        matrix.displayFrames(christmasTreeNoLights, 100, true, 1);
        HeadSwitchDelay(500);
      }
      if (sequence == christmas){
        matrix.displayFrames(christmasTreeLights1, 100, true, 1);
        HeadSwitchDelay(500);
      }
      if (sequence == christmas){
        matrix.displayFrames(christmasTreeNoLights, 100, true, 1);
        HeadSwitchDelay(500);
      }
      if (sequence == christmas){
        matrix.displayFrames(christmasTreeLights2, 100, true, 1);
        HeadSwitchDelay(500);
      }
      if (sequence == christmas){
        matrix.displayFrames(christmasTreeNoLights, 100, true, 1);
        HeadSwitchDelay(500);
      }
      if (sequence == christmas){
        matrix.displayFrames(christmasTreeLights3, 100, true, 1);
        HeadSwitchDelay(500);
      }
    }
    for (int count = 0; count < 2; count++){
      if (sequence == christmas){
        matrix.displayFrames(santaHat1, 5000, true, 1);
        HeadSwitchDelay(5000);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat2, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat3, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat4, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat5, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat6, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat7, 100, true, 1);
        HeadSwitchDelay(5000);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat8, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat9, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat10, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat11, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat2, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat3, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat4, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat5, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat6, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat7, 100, true, 1);
        HeadSwitchDelay(5000);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat8, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat9, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat10, 100, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == christmas){
        matrix.displayFrames(santaHat11, 100, true, 1);
        HeadSwitchDelay(100);
      }
    }
  }

  if (sequence == steve){ // ______________________________________Steve Animation________________________________________
    
    SteveBlink();

    for (int count = 0; count < 2; count++){ // Steve Look Left, Look Right, Look Up
      if (sequence == steve){
        matrix.displayFrames(steveNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveLU, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
    }
      if (sequence == steve){
        matrix.displayFrames(steveNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == steve){
        matrix.displayFrames(steveEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      
    for (int count = 0; count < 2; count++){ // Steve Roll Eyes
      if (sequence == steve){
        matrix.displayFrames(steveRE1, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == steve){
        matrix.displayFrames(steveRE2, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == steve){
        matrix.displayFrames(steveRE3, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == steve){
        matrix.displayFrames(steveRE4, 2000, true, 1);
        HeadSwitchDelay(500);
      }
    }

    SteveBlink();
  
    if (sequence == steve){
      matrix.displayFrames(steveHelmet, 2000, true, 1);
      HeadSwitchDelay(20000);
    }
    if (sequence == steve){
      matrix.displayFrames(steveEyesClosed, 2000, true, 1);
      HeadSwitchDelay(20000);
    }
  }

  if (sequence == alex){ // ______________________________________Alex Animation________________________________________
    
    AlexBlink();

    for (int count = 0; count < 2; count++){ // Alex Look Left, Look Right
      if (sequence == alex){
        matrix.displayFrames(alexNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLL, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexLR, 2000, true, 1);
        HeadSwitchDelay(2000);
      }
    }
      if (sequence == alex){
        matrix.displayFrames(alexNorm, 2000, true, 1);
        HeadSwitchDelay(4000);
      }
      if (sequence == alex){
        matrix.displayFrames(alexEyesClosed, 2000, true, 1);
        HeadSwitchDelay(150);
      }

    AlexBlink();
  
    if (sequence == alex){
      matrix.displayFrames(alexEyesClosed, 2000, true, 1);
      HeadSwitchDelay(20000);
    }
  }
    
  if (sequence == tnt){ // ______________________________________TNT Explosion________________________________________
    if (sequence == tnt){
      matrix.displayFrames(tNT, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount8, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount7, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount6, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount5, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount4, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount3, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount2, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTCount1, 2000, true, 1);
      HeadSwitchDelay(1000);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx1, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx2, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx3, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx4, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx5, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayColorBlock(0x18, 2000, true);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx1, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx2, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx3, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx4, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx5, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayColorBlock(0x18, 2000, true);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx1, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx2, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx3, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx4, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayFrames(tNTEx5, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayColorBlock(0x18, 2000, true);
      HeadSwitchDelay(100);
    }
    if (sequence == tnt){
      matrix.displayColorAnimation(3, 5000, true);
      HeadSwitchDelay(50000);
    }
  }

  if (sequence == light){ // ______________________________________Night Light________________________________________
    if (sequence == light){
      matrix.displayColorBlock(0xffffff, 2000, true);
      HeadSwitchDelay(10000000);
    }
  }

  if (sequence == boba){ // ______________________________________Boba Fett Animation________________________________________
    if (sequence == boba){
      matrix.displayFrames(bobaFett, 2000, true, 1);
      HeadSwitchDelay(10000);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl1, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl2, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl3, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl4, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl5, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl6, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl7, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl8, 2000, true, 1);
      HeadSwitchDelay(30);
    }
    if (sequence == boba){
      matrix.displayFrames(bobaFettRefl9, 2000, true, 1);
      HeadSwitchDelay(30);
    }
  }

  if (sequence == iron){ // ______________________________________Iron Man Animation________________________________________
    
    if (sequence == iron){
      matrix.displayFrames(ironManEyesOff, 2000, true, 1);
      HeadSwitchDelay(2000);
    }
    for (int count = 0; count < 6; count++){ // Iron Man Switch On  
      if (sequence == iron){
        matrix.displayFrames(ironManEyesOn1, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == iron){
        matrix.displayFrames(ironManEyesOn2, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == iron){
        matrix.displayFrames(ironManEyesOn3, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == iron){
        matrix.displayFrames(ironMan, 2000, true, 1);
        HeadSwitchDelay(100);
      }
    }

    for (int count = 0; count < 6; count++){ // Iron Man Blink
      if (sequence == iron){
        matrix.displayFrames(ironManHalfEyes, 2000, true, 1);
        HeadSwitchDelay(50);
      }
      if (sequence == iron){
        matrix.displayFrames(ironMan, 2000, true, 1);
        HeadSwitchDelay(10000);
      }
    }
    
    if (sequence == iron){
      matrix.displayFrames(ironManAngry, 2000, true, 1);
      HeadSwitchDelay(20000);
    }
    
    for (int count = 0; count < 6; count++){ // Iron Man Blink
      if (sequence == iron){
        matrix.displayFrames(ironManHalfEyes, 2000, true, 1);
        HeadSwitchDelay(50);
      }
      if (sequence == iron){
        matrix.displayFrames(ironMan, 2000, true, 1);
        HeadSwitchDelay(10000);
      }
    }
    if (sequence == iron){
      matrix.displayFrames(ironManEyesOff, 2000, true, 1);
      HeadSwitchDelay(10000);
    }
  }


  if (sequence == pig){ // ______________________________________Pig Animation________________________________________
    if (sequence == pig){
      matrix.displayFrames(pigNormal, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == pig){
      matrix.displayFrames(pigLR, 2000, true, 1);
      HeadSwitchDelay(2000);
    }
    if (sequence == pig){
      matrix.displayFrames(pigLL, 2000, true, 1);
      HeadSwitchDelay(2000);
    }
    if (sequence == pig){
      matrix.displayFrames(pigNormal, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == pig){
      matrix.displayFrames(pigEyesClosed, 2000, true, 1);
      HeadSwitchDelay(150);
    }
    if (sequence == pig){
      matrix.displayFrames(pigNormal, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == pig){
      matrix.displayFrames(pigEyesClosed, 2000, true, 1);
      HeadSwitchDelay(150);
    }
    if (sequence == pig){
      matrix.displayFrames(pigSnoutUp, 2000, true, 1);
      HeadSwitchDelay(300);
    }
    if (sequence == pig){
      matrix.displayFrames(pigNormal, 2000, true, 1);
      HeadSwitchDelay(300);
    }
    if (sequence == pig){
      matrix.displayFrames(pigSnoutUp, 2000, true, 1);
      HeadSwitchDelay(300);
    }
    if (sequence == pig){
      matrix.displayFrames(pigNormal, 2000, true, 1);
      HeadSwitchDelay(2000);
    }
  }

  if (sequence == hulk){ // ______________________________________Hulk Animation________________________________________
    if (sequence == hulk){
      matrix.displayFrames(hulkNormal, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == hulk){
      matrix.displayFrames(hulkEyesClosed, 2000, true, 1);
      HeadSwitchDelay(100);
    }
    if (sequence == hulk){
      matrix.displayFrames(hulkNormal, 2000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == hulk){
      matrix.displayFrames(hulkMad, 2000, true, 1);
      HeadSwitchDelay(20000);
    }
  }

  if (sequence == ender){ // ______________________________________Ender Animation________________________________________
    for (int count = 0; count < 6; count++){ // EnderMan Blink
      if (sequence == ender){
        matrix.displayFrames(enderMan, 2000, true, 1);
        HeadSwitchDelay(6000);
      }
      if (sequence == ender){
        matrix.displayColorBlock(0x000000, 2000, true);
        HeadSwitchDelay(150);
      }
    }
    for (int count = 0; count < 2; count++){ // EnderMan Eye Roll
      if (sequence == ender){
        matrix.displayFrames(enderManRot1, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == ender){
        matrix.displayFrames(enderManRot2, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == ender){
        matrix.displayFrames(enderManRot3, 2000, true, 1);
        HeadSwitchDelay(100);
      }
      if (sequence == ender){
        matrix.displayFrames(enderMan, 2000, true, 1);
        HeadSwitchDelay(100);
      }
    }
  }

  if (sequence == diamond){ // ______________________________________Diamond Rotate________________________________________
    if (sequence == diamond){
      matrix.displayFrames(diamond1, 200, true, 3);
      HeadSwitchDelay(100000);
    }
    if (sequence == diamond){
      matrix.setDisplayOrientation(DISPLAY_ROTATE_90);
      HeadSwitchDelay(100);
    }
    if (sequence == diamond){
      matrix.setDisplayOrientation(DISPLAY_ROTATE_180);
      HeadSwitchDelay(100);
    }
    if (sequence == diamond){
      matrix.setDisplayOrientation(DISPLAY_ROTATE_270);
      HeadSwitchDelay(100);
    }
    if (sequence == diamond){
      matrix.setDisplayOrientation(DISPLAY_ROTATE_0);
      HeadSwitchDelay(100);
    }
    if (sequence == diamond){
      matrix.displayFrames(diamond1, 2000, true, 3);
      HeadSwitchDelay(100);
    }
    if (sequence == diamond){
      matrix.displayFrames(diamond1, 200, true, 3);
      HeadSwitchDelay(20000);
    }
  }

  if (sequence == anim0){ // ______________________________________Colour Animation 0________________________________________
    if (sequence == anim0){
      matrix.displayColorAnimation(0, 5000, true);
      HeadSwitchDelay(5000);
    }
  }

  if (sequence == anim1){ // ______________________________________Colour Animation 1________________________________________
    if (sequence == anim1){
      matrix.displayColorAnimation(1, 5000, true);
      HeadSwitchDelay(5000);
    }
  }

  if (sequence == anim2){ // ______________________________________Colour Animation 2________________________________________
    if (sequence == anim2){
      matrix.displayColorAnimation(2, 5000, true);
      HeadSwitchDelay(5000);
    }
  }

  if (sequence == anim3){ // ______________________________________Colour Animation 3________________________________________
    if (sequence == anim3){
      matrix.displayColorAnimation(3, 5000, true);
      HeadSwitchDelay(5000);
    }
  }
  
  if (sequence == anim4){ // ______________________________________Colour Animation 4________________________________________
    if (sequence == anim4){
      matrix.displayColorAnimation(4, 5000, true);
      HeadSwitchDelay(5000);
    }
  }

  if (sequence == mineCraft){ // ______________________________________MineCraft Scroll________________________________________
    if (sequence == mineCraft){
      matrix.displayEmoji(17, 5000, true);
      HeadSwitchDelay(5000);
    }
    if (sequence == mineCraft){
      matrix.displayFrames(duck, 5000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == mineCraft){
      matrix.displayEmoji(18, 5000, true);
      HeadSwitchDelay(5000);
    }
    if (sequence == mineCraft){
      matrix.displayFrames(sheep, 5000, true, 1);
      HeadSwitchDelay(5000);
    }
    if (sequence == mineCraft){
      matrix.displayEmoji(19, 5000, true);
      HeadSwitchDelay(5000);
    }
    if (sequence == mineCraft){
      matrix.displayFrames(archer, 5000, true, 1);
      HeadSwitchDelay(5000);
    }
  }

  if (sequence == creeper){  // ______________________________________Creeper / Mad Creeper________________________________________
    if (sequence == creeper){
    matrix.displayEmoji(15, 10000, true);
      HeadSwitchDelay(10000);
    }
    if (sequence == creeper){
    matrix.displayEmoji(16, 10000, true);
      HeadSwitchDelay(10000);
    }
  }
  
  if (sequence == emoji){ // ______________________________________Emoji Scroll________________________________________
    if (sequence == emoji){
    matrix.displayEmoji(0, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(1, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(2, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(3, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(4, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(5, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(6, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(7, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(8, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(9, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(20, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(21, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(22, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(23, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(24, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(25, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(26, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(27, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(28, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(29, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(30, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(31, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(32, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(33, 5000, true);
      HeadSwitchDelay(3000);
    }
    if (sequence == emoji){
    matrix.displayEmoji(34, 5000, true);
      HeadSwitchDelay(3000);
    }
  }

  if (sequence > sequenceMax){
    HeadSwitchDelay(1000);
  }
} // void loop End Curly Brace



void SteveBlink (void){
  for (int count = 0; count < 5; count++){ // Steve Blink
    if (sequence == steve){
      matrix.displayFrames(steveNorm, 2000, true, 1);
      HeadSwitchDelay(4000);
    }
    if (sequence == steve){
      matrix.displayFrames(steveEyesClosed, 2000, true, 1);
      HeadSwitchDelay(150);
    }
  }
  
  for (int count = 0; count < 3; count++){ // Steve Laughing
    if (sequence == steve){
      matrix.displayFrames(steveNorm, 2000, true, 1);
      HeadSwitchDelay(200);
    }
    if (sequence == steve){
    matrix.displayFrames(steveOpenMouth, 2000, true, 1);
      HeadSwitchDelay(200);
    }
  }
}

void AlexBlink (void){
  for (int count = 0; count < 6; count++){ // Steve Blink
    if (sequence == alex){
      matrix.displayFrames(alexNorm, 2000, true, 1);
      HeadSwitchDelay(4000);
    }
    if (sequence == alex){
      matrix.displayFrames(alexEyesClosed, 2000, true, 1);
      HeadSwitchDelay(150);
    }
  }
}

void HeadSwitchDelay(long pauseVal) {
  for (int reduceVal = 10; pauseVal > reduceVal; pauseVal = pauseVal - reduceVal){
    reedSwitchOff = digitalRead (reedSwitch);
    delay (10);
    if (reedSwitchOff == false){
      sequence++;
      if (sequence > sequenceMax){
        sequence = 0;
      }
      pauseVal = 1;
    }
  }
  while (reedSwitchOff == false){
    reedSwitchOff = digitalRead (reedSwitch);
  }
}
