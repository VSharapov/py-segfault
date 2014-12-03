Segfault module for python
==========================

This is mostly a demo of mixing C into python, just a little more fun than the typicall "hello world" and "spam" example modules. There is [actual documentation][1] for this, and don't worry, I won't make you read the whole thing, just sections 1.1, 1.3 only if you're confused, 1.4, then click [the first link in 1.5][2] but only read up through the second code block unless you're a total nerd.

C can do lots of stuff that python can't, mainly it's pretty fast, which is nice if you have some bottleneck in your python scripts.

Of course speed isn't all that C offers, you can do other amazing things, like access whatever memory you want. Damn the torpedoes!

So next time some snobby systems developer points to a segfault and asks "[Can your python do this?!][3]" show them what's up.

Installation
------------

    python setup.py install; \
    echo lol, always forget; \
    sudo python setup.py install

The `segfault` module
---------------------

The `segfault` module provides only one method:

    segfault.segfault(startString)

This method reads the string passed to it, but doesn't heed to silly things like null terminators that deter inferior string-reading methods. This one stops for nothing! It will print the byte index and the character there with verbose expansions for special and non-printable characters.

Passing an empty string supresses this output and memory bytes will only be copied into a buffer with no output.

Examples
--------

Generate a segfault quietly:

    python -c "import segfault; segfault.segfault('')"

Scroll through over 400KB at one line per byte, there's a surprise at the end:

    python -c "import segfault; segfault.segfault('lol')"

Just a taste of the fun:

    python -c "import segfault; segfault.segfault('lol')" | head; \
    echo "..."; \
    echo "$(python -c "import segfault; segfault.segfault('lol')"; exit="$(echo $?)"; echo; man 7 signal | grep $(($exit-128));)" | tail

[1]: https://docs.python.org/2/extending/extending.html
[2]: https://docs.python.org/2/extending/building.html#building
[3]: https://www.google.com/search?q=can+your+mac+do+this&tbm=isch
