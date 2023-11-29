# rngmp3
Generates random MP3 files with a voice rifling off numbers from 1 to N to aid in shuffling large decks of cards.

Usage: ./main.py \<buckets\> \<cards\> \<silence\>

* Buckets should average about 20 cards each, so if you are shuffling 250 cards buckets should be about 12 or 13.
* Cards are how many cards you are shuffling, so in the previous example you'd set this to 250.
* Silence adds some additional silence after each number providing you with more time to place a card in a bucket.

This uses the same technique large databases use to shuffle their data around. It takes place in 2 steps:

Step 1) Add the card to a random bucket, until all cards have been added to randomly chosen buckets

Step 2) Shuffle each bucket by itself. A traditional method can be used (https://en.wikipedia.org/wiki/Shuffling)

After each bucket is well shuffled combine all of the cards together into 1 or more large decks. The order of combining does not matter.

With this bucket shuffling method each card is equally likely to be in every possible location providing a perfect shuffle every time.

Written to use Python 3.

This requires FFMPEG binaries to be installed on your computer AND the PATH variable is set to the bin directory. If you do not know how to change your PATH environment variable then edit line #63 in the Python script to include the full path to the 'ffmpeg' binary file.

https://ffmpeg.org/download.html

# c_src

The original utility was written in C and that can be found in the c_src folder. It isn't needed however and was added for reference only.
