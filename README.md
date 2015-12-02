
BidiRenderer:

This is a test application I'm using to help me understand the Unicode bidirectional algorithm, and the process of rendering complex scripts and RTL text. It's the basis for a more complex version of the code that has been used in VLC's FreeType module for subtitles/OSD rendering.

Some options do not produce visible effects on all fonts. For example removing zero-width characters when the font can already handle them properly. The font Arial is good here since it shows zero-width spaces, Unicode control characters, etc.

See the wiki for build instructions on Windows and Linux/Unix.

I welcome any comments or corrections, particularly regarding language-specific issues.

![alt tag](https://github.com/salshaaban/BidiRenderer/blob/master/screenshot.png)
