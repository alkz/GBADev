#include <stdio.h>

typedef  unsigned short u16; 

u16 rgb_gba(u16 c)
{
    return ( ( (c << 10) & (0x7c00) ) | (c & 0x03e0) | ( (c >> 10) & (0x001f) ) );
}

int
main(int argc, char** argv)
{
    if(argc < 5)  {
        fprintf(stderr, "Usage : %s <file source> <width> <height> <file dest>\n", argv[0]);

        return -1;
    }

    FILE* f = fopen(argv[1], "rb");
    FILE* out = fopen(argv[4], "wb");

    unsigned short word;
    int i = 0;
    fseek(f, sizeof(unsigned short)*27, SEEK_SET);  /* salto l'header bitmap */ 

    fprintf(out, "const u16 img[][%d] = {\n", atoi(argv[2]));
    int j = 0;

    while( j++ < ( atoi(argv[2]) * atoi(argv[3]) ) )  {
        fread(&word, sizeof(unsigned short), 1, f);

        fprintf(out, "%#06x, ", rgb_gba(word));

        if(++i == atoi(argv[2]))  {
            fprintf(out, "\n");
            i = 0;
        }
    }
    fprintf(out, "\n};\n");

    fclose(f);
    fclose(out);
}
