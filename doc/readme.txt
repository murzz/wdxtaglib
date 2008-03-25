WDXTagLib
Content plugin for Total Commander (http://www.ghisler.com/)
by Dmitrie Murzaikin


Description --------------------------------------------------------------------
	This is a content plugin for Total Commander that allows you to show audio
file tags in columns, edit tags and search in tags. Supported file formats:
MP3, MPC, FLAC, Ogg FLAC, Ogg Vorbis and Speex.


Functionality ------------------------------------------------------------------
Tags supported for reading and writing:
	• title;
	• artist;
	• album;
	• year;
	• tracknumber;
	• comment;
	• genre.

Readonly tags:
	• bitrate;
	• samplerate;
	• channels;
	• length;
	• tag type.

It has been tested with Total Commander 7.02a under Windows XP.


Known issues -------------------------------------------------------------------
• National characters are not supported yet.


License Agreement --------------------------------------------------------------
	This software is distributed under the GNU General Public License (GPL)
version 3 or later and GNU Lesser General Public License (LGPL) version 3 or later.


Requirements -------------------------------------------------------------------
• Total Commander 7.02 or higher.
• libtag.dll (included).
• msvcrt.dll (included).


Installation -------------------------------------------------------------------
	Firstly place the libtag.dll and msvcrt.dll in the totalcmd.exe folder or
somewhere in the %PATH%. Then add wdxtaglib.wdx as content plugin.


Version history ----------------------------------------------------------------
25.03.2008	WDXTagLib 1.0.1
+ New field Tag Type. It shows all tags types file has (ID3v1, APE etc).
+ Speed improvement on tag saving.
+ Double licensing scheme used now GPL and LGPL.
+ Detect string used.

05.03.2008	WDXTagLib 1.0.0
First public version.


Special thanks -----------------------------------------------------------------
• Christian Ghisler, author of Total Commander (http://www.ghisler.com).
• TagLib project (http://developer.kde.org/~wheeler/taglib.html).
• Andrey "Ergo" Pyasetskiy (http://www.wincmd.ru and http://totalcmd.net).


Support ------------------------------------------------------------------------
• author's e-mail: murzzz@gmail.com
• plugin's homepage (en): http://www.totalcmd.net/plugring/wdxtaglib.html
• plugin's homepage (ru): http://wincmd.ru/plugring/wdxtaglib.html
• plugin's support (en): http://ghisler.ch/board/viewtopic.php?p=145149
