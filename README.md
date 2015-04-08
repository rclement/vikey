# Description

**vikey** (pronounce "*vicky*") is a virtual MIDI keyboard allowing to simulate
sending MIDI events as a real MIDI keyboard would.

It is particularly useful when playing with a digital instrument requiring a
MIDI input connection and not having a MIDI instrument at hand.
It can also be used as a minimal C++ mock module when developing software
requiring MIDI events to be received.

# Features

Supported MIDI events (according to the [official MIDI specifications](http://www.midi.org/techspecs/midimessages.php)):

* Note-off
* Note-on
* Control change
* Program change
* Pitch-bend change
* Polyphonic key pressure (after-touch)
* Change pressure (after-touch)

# Using the C++ API

The C++ module ``VirtualKeyboard`` can be found under the ``src`` directory.

The only dependence is the [RtMidi](http://www.music.mcgill.ca/~gary/rtmidi/index.html) library, available along side.
Please refer to the [official documentation](http://www.music.mcgill.ca/~gary/rtmidi/index.html#compiling)
for compilation instructions.

You can import the corresponding C++ files into your project and start using
the C++ API:

```
#include <VirtualKeyboard.h>

...

vikey::VirtualKeyboard vk;

...

vk.noteOn(60, 127);
vk.noteOff(60);
```

# Notes

**vikey** uses the [RtMidi](http://www.music.mcgill.ca/~gary/rtmidi) library
to perform MIDI I/O operations, and most notably opening a virtual MIDI port.
For now, only the MacOSX and Linux platforms support this feature.

# Contact

Any questions or comments about **vikey**? Let me know at [contact@romainclement.com](mailto:contact@romainclement.com).

# License

The MIT License (MIT)

Copyright (c) 2015 Romain Clement

