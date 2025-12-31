# Licenses
Any modifications are licensed under the MIT license.

## MIT Licnese
Copyright 2025 bananapizzuh

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## PopCap Games Framework License

Version 1.1

� Copyright  2005-2009 PopCap Games, Inc. All rights reserved.

Redistribution and use of this software in source or binary forms, with or 
without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code or derived libraries, whether source code or binary, must include a copy of this PopCap Games Framework License in its entirety.

2. The end-user documentation included with a work that contains any portion of this software must include the following acknowledgment:

"This product includes portions of the PopCap Games Framework, � 2005-2009 PopCap Games, Inc.  All rights reserved. (http://popcapframework.sourceforge.net/).

Alternatively, this acknowledgment may appear in the work itself, wherever such third-party acknowledgments normally appear.

3. The names "PopCap" and "PopCap Games" (and the PopCap logos)
may not be used to endorse or promote products that contain any portion of this software or are otherwise derived from this software.  The name
"PopCap" may not appear in any way in the name of such products.

4. The right to redistribute and/or use the software, whether in its original or modified form, terminates automatically in the event of a breach of this license, without further notice from PopCap.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGMENT AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL POPCAP GAMES, OR ANY OF ITS DIRECTORS, OFFICERS, EMPLOYEES, AGENTS, AFFILIATES, SUCCESSORS OR ASSIGNS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## BASS Audio Library
The BASS Audio Library is the default library used by the Framework 
to decompress sounds and to play music.  Licenses to the BASS Audio 
Library can be purchased at http://www.un4seen.com/bass.html#license.
You can avoid using the BASS Audio Library by setting 
SexyAppBase::mWantFMod before application initialization to use the 
FMOD Music Library or by setting SexyAppBase::mNoSoundNeeded if you 
do not need to load compressed audio or play tracked music.
				
## FMOD Audio Library
The FMOD library is a popular alternative to the BASS Audio Library.
Licenses to FMOD can be purchased at http://www.fmod.org/. Although 
the BASS Audio Library is the default sound library in the Framework, 
you can use FMOD instead by setting SexyAppBase::mWantFMod before 
application initialization.

## MP3 Compressed Audio
The Framework supports both MP3 and OGG decompression through either 
BASS or FMOD.  The OGG format can be used for free, but if you must 
use MP3 in your product, you will have to contact Thompson Multimedia 
and arrange to pay for an MP3 license.  Game developers can get a 
'game license' to use MP3 for $2500.  See 
http://www.mp3licensing.com/royalty/games.html.

## Macromedia Flash
The Framework supports Flash through FlashWidget, but you must sign 
up for a license to redistribute the Flash ActiveX control if you 
use FlashWidget in your application.  You can get a Flash license 
from Macromedia at 
http://www.macromedia.com/support/shockwave/info/licensing/main_2.html.
Make sure you actually read the license, particularly the 
"Consideration" section.

## J2K-Codec Library
The framework supports loading j2k images through the j2k-codec library.
This library is NOT free and you must purchase your own copy if you want
to use it in registered (non-demo) mode. You may obtain a copy from 
Alex Saveliev at http://j2k-codec.com. We do not distribute our key,
so the library will run in demo mode with the following restrictions,
as taken from the readme.txt file:
  * beeps at the end of each decoding 
  * open the ordering page once in about 30 decoded images 
  * on the rare occasions do several other little nags

The price of the j2k codec is between $49 and $399, depending on use.