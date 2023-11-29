#include "main.h"
//----------------------------------------------------------------------------------------------------------------------
si main(si argc, s8 ** argv)
{
    // Get the command line arguments and verify they are sane

    if (argc != 4)
    {
        printf("\nusage: %s <buckets> <cards> <silence>\n", argv[0]);
        printf("buckets: how many buckets the cards are placed inside; a reasonable number is 1 bucket per 20 cards\n");
        printf("cards: how many cards to be shuffled; make this number higher in case a number is skipped by mistake\n");
        printf("silence: how many milliseconds of silence added between each number; a reasonable amount of time is 250ms\n\n");
        return EXIT_FAILURE;
    }

    const si buckets = atoi(argv[1]);
    const si cards   = atoi(argv[2]);
    const si silence = atoi(argv[3]);

    if (buckets < 2 || buckets > 20)
    {
        printf("usage: %s <buckets> <cards>\nbuckets must be 2 - 20\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (cards < 10 || cards > 10000)
    {
        printf("usage: %s <buckets> <cards>\ncards must be 10 - 10000\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (silence < 100 || silence > 2500)
    {
        printf("usage: %s <buckets> <cards>\nsilence must be 100 - 2500\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Start to output a raw audio file of randomly chosen numbers between 1 and 'buckets'

    printf("Starting...\n");

    remove("input.raw");
    remove("output.mp3");
    remove("silence.raw");

    output_silence(silence);

    u64 prog_tick = tick();

    for (ui i=0;i<cards;i++)
    {
        // Append a randomly chosen raw audio input file to the output file along with some silence

        sprintf(buf, "cat %s silence.raw >> input.raw", files[rng(buckets - 1)]);
        system(buf);

        // Print some progress to the screen every 1000 milliseconds

        if ((tick() - prog_tick) >= 1000)
        {
            prog_tick += 1000;
            printf("Progress: %.1f%%\n", (i * 100.) / cards);
        }
    }

    printf("Encoding MP3...\n");

    // Signed 16-bit PCM, LE, 48kHz, Mono

    system("ffmpeg -loglevel error -stats -f s16le -ar 48000 -ac 1 -i input.raw -acodec libmp3lame -aq 6 output.mp3");

    remove("input.raw");
    remove("silence.raw");

    printf("All Done\n");

    return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------------------------------------------------
static u8 rng(u8 buckets)
{
    u8 mask = buckets - 1;

    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;

    mask |= mask + 1;

    u8 r;
    do r = rng8() & mask;
    while (r > buckets);

    return r;
}
//----------------------------------------------------------------------------------------------------------------------
static u8 rng8(void)
{
    static si p = -1;
    static u8 buf[64];

    if (p == -1)
    {
        p = 0;

        FILE * f = fopen("/dev/random", "rb");
        if (!f) exit(EXIT_FAILURE);
        if (fread(buf, 1, 64, f) != 64) exit(EXIT_FAILURE);
        fclose(f);

        u64 temp_buf;
        memcpy(&temp_buf, buf, 8);
        temp_buf ^= tick();
        memcpy(buf, &temp_buf, 8);

        blake2b_mod(buf, buf);
    }

    if (p >= 64)
    {
        p = 0;
        blake2b_mod(buf, buf);
    }

    return buf[p++];
}
//----------------------------------------------------------------------------------------------------------------------
static u64 tick(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return ((u64)now.tv_sec * 1000) + ((u64)now.tv_nsec / 1000000);
}
//----------------------------------------------------------------------------------------------------------------------
static void output_silence(const ul milliseconds)
{
    const ul bytes = 48000 * (milliseconds / 1000.);

    FILE * f = fopen("silence.raw", "w");

    if (!f) exit(EXIT_FAILURE);

    for (ul i=0;i<bytes;i++)
    {
        u8 n = 0;
        fwrite(&n, 1, 1, f);
    }

    fclose(f);
}
//----------------------------------------------------------------------------------------------------------------------