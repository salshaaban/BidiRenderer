
BidiRenderer:

This is a test application I'm using to help me understand the Unicode bidirectional algorithm, and the process of rendering complex scripts and RTL text.

Some options do not produce visible effects on all fonts. For example removing zero-width characters when the font can already handle them properly. The font Arial is good here since it shows zero-width spaces, Unicode control characters, etc.

This is a work in progress. I hope to figure out how to implement font fallback, and to create a wiki page about the various issues usually encountered in bi-directional text rendering, once I understand the process well enough.
