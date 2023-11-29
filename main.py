#!/usr/bin/python3
#-----------------------------------------------------------------------------------------------------------------------
import os
import sys
import time
import secrets
#-----------------------------------------------------------------------------------------------------------------------
def main():

    # Get the command line arguments and verify they are correct

    if (len(sys.argv) != 4):
        print("\nusage: %s <buckets> <cards> <silence>" % sys.argv[0])
        print("buckets: how many buckets the cards are placed inside; a reasonable number is 1 bucket per 20 cards")
        print("cards: how many cards to be shuffled; make this number higher in case a number is skipped by mistake")
        print("silence: how many milliseconds of silence added between each number; a reasonable amount of time is 250ms\n")
        os._exit(0)

    buckets = int(sys.argv[1])
    cards   = int(sys.argv[2])
    silence = int(sys.argv[3])

    if (buckets < 2 or buckets > 20):
        print("usage: %s <buckets> <cards>\nbuckets must be 2 - 20" % sys.argv[0])
        os._exit(0)

    if (cards < 10 or cards > 10000):
        print("usage: %s <buckets> <cards>\ncards must be 10 - 10000" % sys.argv[0])
        os._exit(0)

    if (silence < 10 or silence > 2500):
        print("usage: %s <buckets> <cards>\nsilence must be 10 - 2500" % sys.argv[0])
        os._exit(0)

    # Start to output a raw audio file of randomly chosen numbers between 1 and 'buckets'

    print("Starting...")

    delfile("input.raw")
    delfile("output.mp3")
    delfile("silence.raw")

    output_silence(silence)

    files = ["1_one.raw", "2_two.raw", "3_three.raw", "4_four.raw", "5_five.raw", "6_six.raw", "7_seven.raw",
    "8_eight.raw", "9_nine.raw", "10_ten.raw", "11_eleven.raw", "12_twelve.raw", "13_thirteen.raw", "14_forteen.raw",
    "15_fifteen.raw", "16_sixteen.raw", "17_seventeen.raw", "18_eighteen.raw", "19_nineteen.raw", "20_twenty.raw"]

    prog_tick = time.time()

    for i in range(0, cards):
        buf = "cat %s silence.raw >> input.raw" % files[secrets.randbelow(buckets)]
        os.system(buf)

        if ((time.time() - prog_tick) >= 1):
            prog_tick += 1
            print("Progress: %.1f%%" % ((i * 100.0) / cards))

    print("Encoding MP3...")

    # Signed 16-bit PCM, LE, 48kHz, Mono

    os.system("ffmpeg -loglevel error -stats -f s16le -ar 48000 -ac 1 -i input.raw -acodec libmp3lame -aq 6 output.mp3")

    delfile("input.raw")
    delfile("silence.raw")

    print("All Done")

    os._exit(0)

#-----------------------------------------------------------------------------------------------------------------------
def delfile(filename):

    try:
        os.remove(filename)
    except:
        pass

    return

#-----------------------------------------------------------------------------------------------------------------------
def output_silence(milliseconds):

    bytes = int(48000 * (milliseconds / 1000.0))

    f = open("silence.raw", "w")

    for i in range(0, bytes):
        f.write("\0")

    f.close()

    return

#-----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':

    main()

#-----------------------------------------------------------------------------------------------------------------------