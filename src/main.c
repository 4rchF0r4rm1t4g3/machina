#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[4096];
    int addr;
} label;

void nop() {}

int main(int argc, char *argv[])
{
    int c;
    int by = 0;
    unsigned char code[512];
    memset(code, 0, 512);

    if (argc < 2)
    {
        printf("usage: %s <filename> <machina code> <bios output>\n", argv[0]);
        return 1;
    }

    FILE *fptr;

    fptr = fopen(argv[1], "r");

    if(!fptr)
    {
        printf("unable to open file: %s\n", argv[1]);
        exit(1);
    }

    char buffer[4096];


    while(fgets(buffer, 4096, fptr))
    {

        char buf[4096];

        int buflen = strlen(buffer);
        if(buffer[buflen-1] == '\n')
        {
            buffer[buflen-1] = '\0';
            buffer[buflen] = '\0';
        }

        int c = 0;

        while(1)
        {
            if(buffer[c] != ' ')
            {
                break;
            }

            ++c;
        }

        int d = 0;

        while(1)
        {
            if(buffer[d+c] == ' ')
            {
                break;
            }

            if(buffer[d+c] == '\0')
            {
                break;
            }

            ++d;
        }

        strncpy(buf, buffer+c, d);
        if(buf[c+d+1] == EOF)
        {
            continue;
        }

        else
        {
            buf[c+d] = '\0';
        }

        int res = 0;

        if((res = strncmp("i10", buffer+c, 3)) == 0)
        {
            code[by] = 0xCD;
            by++;
            code[by] = 0x10;
            by++;
        }
        
        if(strncmp("ax", buf, 2) == 0)
        {
            int e = d+c;
            int emod = e;

            while(1)
            {
                if((buffer[emod] != ' ') && (buffer[emod] != '\0'))
                {
                    break;
                }

                if(buffer[emod] == '\0')
                {
                    printf("needed value for ax");
                    exit(0);
                }

                emod++;
            }

            int nemod = emod;

            while(1)
            {
                if((buffer[nemod] == '\0') || (buffer[nemod] == ' '))
                {
                    break;
                }

                nemod++;
            }

            char axbuf[4096];
            char cbuf;
            char axb1;
            char axb[2];
            int b2l;

            code[by] = 0xB8;
            by++;

            strncpy(axbuf, buffer+emod, nemod);

            if(axbuf[0] == '\'')
            {
                cbuf = axbuf[1];
                if(axbuf[2] != '\'')
                {
                    printf("ERROR: he string does not end\n");
                }

                else
                {
                    code[by] = cbuf;
                    by++;
                }
            }
            
            if(strlen(axbuf) > 4)
            {
                printf("ERROR: the value tried to be loaded on ax is greater than 0xffff\n");
                exit(1);
            }

            b2l = strlen(axbuf) - 2;

            int ax1 = strlen(axbuf);

            int b2 = 0;

            if(ax1 <= 2)
            {
                strncpy(axb, axbuf, ax1);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            if(ax1 >= 2)
            {
                strncpy(axb, axbuf, 2);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            char axb0[b2l];
            char axb2;

            if(b2l > 0)
            {
                strncpy(axb0, axbuf+2, 2);
                b2 = 1;
                axb2 = (int)strtol(axb0, NULL, 16);
            }

            if(b2 == 1)
            {
                code[by] = axb2;
                by++;
                code[by] = axb1;
                by++;
            }

            else
            {
                code[by] = axb1;
                by++;
                code[by] = 0x00;
                by++;
            }

            axend:
            nop();
        }

        if(strncmp("ah", buf, 2) == 0)
        {
            int e = d+c;
            int emod = e;

            while(1)
            {
                if((buffer[emod] != ' ') && (buffer[emod] != '\0'))
                {
                    break;
                }

                if(buffer[emod] == '\0')
                {
                    printf("needed value for ah");
                    exit(0);
                }

                emod++;
            }

            int nemod = emod;

            while(1)
            {
                if((buffer[nemod] == '\0') || (buffer[nemod] == ' '))
                {
                    break;
                }

                nemod++;
            }

            char axbuf[4096];
            char cbuf;
            char axb1;
            char axb[2];
            int b2l;

            code[by] = 0xB4;
            by++;

            strncpy(axbuf, buffer+emod, nemod);

            if(axbuf[0] == '\'')
            {
                cbuf = axbuf[1];
                if(axbuf[2] != '\'')
                {
                    printf("ERROR: the string does not end\n");
                }

                else
                {
                    code[by] = cbuf;
                    by++;
                    goto ahend;
                }
            }
            
            if(strlen(axbuf) > 4)
            {
                printf("ERROR: the value tried to be loaded on ah is greater than 0xff\n");
                exit(1);
            }

            b2l = strlen(axbuf) - 2;

            int ax1 = strlen(axbuf);

            int b2 = 0;

            if(ax1 <= 2)
            {
                strncpy(axb, axbuf, ax1);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            if(ax1 >= 2)
            {
                strncpy(axb, axbuf, 2);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            code[by] = axb1;
            by++;

            ahend:
            nop();
        }

        if(strncmp("al", buf, 2) == 0)
        {
            int e = d+c;
            int emod = e;

            while(1)
            {
                if((buffer[emod] != ' ') && (buffer[emod] != '\0'))
                {
                    break;
                }

                if(buffer[emod] == '\0')
                {
                    printf("needed value for al");
                    exit(0);
                }

                emod++;
            }

            int nemod = emod;

            while(1)
            {
                if((buffer[nemod] == '\0') || (buffer[nemod] == ' '))
                {
                    break;
                }

                nemod++;
            }

            char axbuf[4096];
            char cbuf[1];
            char axb1;
            char axb[2];
            int b2l;

            code[by] = 0xB0;
            by++;

            strncpy(axbuf, buffer+emod, nemod);

            if(axbuf[0] == '\'')
            {
                cbuf[0] = axbuf[1];
                printf("%lu", sizeof(cbuf));
                if(axbuf[2] != '\'')
                {
                    printf("ERROR: he string does not end\n");
                }

                else
                {
                    code[by] = cbuf[0];
                    by++;
                    goto aleend;
                }
            }
            
            if(strlen(axbuf) > 4)
            {
                printf("ERROR: the value tried to be loaded on al is greater than 0xff\n");
                exit(1);
            }

            b2l = strlen(axbuf) - 2;

            int ax1 = strlen(axbuf);

            int b2 = 0;

            if(ax1 == 2)
            {
                strncpy(axb, axbuf, 2);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            if(ax1 > 2)
            {
                strncpy(axb, axbuf, 1);
                axb1 = (int)strtol(axb, NULL, 16);
            }


            code[by] = axb1;
            by++;

            aleend:
            nop();
        }

        if(strncmp("bl", buf, 2) == 0)
        {
            int e = d+c;
            int emod = e;

            while(1)
            {
                if((buffer[emod] != ' ') && (buffer[emod] != '\0'))
                {
                    break;
                }

                if(buffer[emod] == '\0')
                {
                    printf("needed value for bl");
                    exit(0);
                }

                emod++;
            }

            int nemod = emod;

            while(1)
            {
                if((buffer[nemod] == '\0') || (buffer[nemod] == ' '))
                {
                    break;
                }

                nemod++;
            }

            char axbuf[4096];
            char cbuf[1];
            char axb1;
            char axb[2];
            int b2l;

            code[by] = 0xB3;
            by++;

            strncpy(axbuf, buffer+emod, nemod);

            if(axbuf[0] == '\'')
            {
                cbuf[0] = axbuf[1];
                printf("%lu", sizeof(cbuf));
                if(axbuf[2] != '\'')
                {
                    printf("ERROR: he string does not end\n");
                }

                else
                {
                    code[by] = cbuf[0];
                    by++;
                    goto bleend;
                }
            }
            
            if(strlen(axbuf) > 4)
            {
                printf("ERROR: the value tried to be loaded on bl is greater than 0xff\n");
                exit(1);
            }

            b2l = strlen(axbuf) - 2;

            int ax1 = strlen(axbuf);

            int b2 = 0;

            if(ax1 == 2)
            {
                strncpy(axb, axbuf, 2);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            if(ax1 > 2)
            {
                strncpy(axb, axbuf, 1);
                axb1 = (int)strtol(axb, NULL, 16);
            }


            code[by] = axb1;
            by++;

            bleend:
            nop();
        }

        if(strncmp("bh", buf, 2) == 0)
        {
            int e = d+c;
            int emod = e;

            while(1)
            {
                if((buffer[emod] != ' ') && (buffer[emod] != '\0'))
                {
                    break;
                }

                if(buffer[emod] == '\0')
                {
                    printf("needed value for bh");
                    exit(0);
                }

                emod++;
            }

            int nemod = emod;

            while(1)
            {
                if((buffer[nemod] == '\0') || (buffer[nemod] == ' '))
                {
                    break;
                }

                nemod++;
            }

            char axbuf[4096];
            char cbuf;
            char axb1;
            char axb[2];
            int b2l;

            code[by] = 0xB7;
            by++;

            strncpy(axbuf, buffer+emod, nemod);

            if(axbuf[0] == '\'')
            {
                cbuf = axbuf[1];
                if(axbuf[2] != '\'')
                {
                    printf("ERROR: the string does not end\n");
                    goto bhend;
                }

                else
                {
                    code[by] = cbuf;
                    goto bhend;
                    by++;
                }
            }
            
            if(strlen(axbuf) > 4)
            {
                printf("ERROR: the value tried to be loaded on bh is greater than 0xff\n");
                exit(1);
            }

            b2l = strlen(axbuf) - 2;

            int ax1 = strlen(axbuf);

            int b2 = 0;

            if(ax1 <= 2)
            {
                strncpy(axb, axbuf, ax1);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            if(ax1 >= 2)
            {
                strncpy(axb, axbuf, 2);
                axb1 = (int)strtol(axb, NULL, 16);
            }

            code[by] = axb1;
            by++;

            bhend:
            nop();
        }

    }


    code[510] = 0x55;
    code[511] = 0xAA;

    FILE* out;
    out = fopen(argv[2], "wb");
    fwrite(code, 1, 512, out);
}