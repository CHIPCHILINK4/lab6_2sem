#include <stdio.h>
#include <stdbool.h>


bool check(char* text_for_compress, char* decompress_text);

unsigned char compress(char* text_for_compress, char* decompress_text) {
    if (text_for_compress && decompress_text) {
        FILE* ptr_text_for_compress1 = fopen(text_for_compress, "rb");
        FILE* ptr_text_for_compress2 = fopen(text_for_compress, "rb");// для подсчета
        FILE* ptr_decompressed_text = fopen(decompress_text, "wb");//
        if (ptr_text_for_compress1 && ptr_text_for_compress2 && ptr_decompressed_text) {
            unsigned char set_mask = 128;
            unsigned char mask = 1;
            int pos = 0;
            char buf[8] = { 0 };
            int tmp = 0;

            while (getc(ptr_text_for_compress2) != EOF) {
                for (; ((tmp = (fscanf_s(ptr_text_for_compress1, "%c", (buf + (pos % 8)), 1))) != -1) && (pos % 8 != 7); pos++);
                pos = 0 ;

                if (tmp == EOF) {//значит остаточные байты
                    for (int j = 0; buf[j]; j++)
                    {
                        putc(buf[j], ptr_decompressed_text);
                        buf[j] = 0;
                    }
                }
                else {
                    mask = 64;
                    for (size_t j = 1; j < 8; j++) {
                        if (buf[0] & mask) {
                            buf[j] = buf[j] | set_mask;
                        }
                        mask >>= 1;
                    }
                    for (size_t j = 1; j < 8; j++) {
                        putc(buf[j], ptr_decompressed_text);
                    }
                    for (size_t j = 0; j < 8; j++) {
                        buf[j] = 0;
                    }
                }
            }
            fclose(ptr_text_for_compress2);
            fclose(ptr_text_for_compress1);
            _fcloseall();
            return 0;
        }
        _fcloseall();
        return 1;
    }
    _fcloseall();
    return 3;
}

unsigned char decompress(char* compressed_text, char* text_for_decompress) {
    if (compressed_text && text_for_decompress) {
        FILE* ptr_text_for_decompress1 = fopen(compressed_text, "rb");
        FILE* ptr_text_for_decompress2 = fopen(compressed_text, "rb");
        FILE* ptr_decompressed_text = fopen(text_for_decompress, "wb");
        if (ptr_text_for_decompress1 && ptr_text_for_decompress2 && ptr_decompressed_text) {
            unsigned char set_mask = 128;
            unsigned char mask = 1;
            int pos = 0;
            char buf[8] = { 0 };
            int tmp = 0;

            while (getc(ptr_text_for_decompress2) != EOF) {

                for (; ((tmp = (fscanf_s(ptr_text_for_decompress1, "%c", ((buf + (pos % 8) + 1)), 1))) != -1) && (pos % 7 != 6); pos++);
                pos = 0;

                if (tmp == EOF) {//значит остаточные байты
                    for (int j = 1; buf[j]; j++) {
                        putc(buf[j], ptr_decompressed_text);
                        buf[j] = 0;
                    }
                }
                else {
                    mask = 64;
                    for (size_t j = 1; j < 8; j++) {
                        if (buf[j] & set_mask) {
                            buf[0] = buf[0] | mask;
                        }
                        buf[j] = buf[j] & ~set_mask;
                        mask >>= 1;
                    }
                    for (size_t j = 0; j < 8; j++) {
                        putc(buf[j], ptr_decompressed_text);

                    }
                    for (size_t j = 0; j < 8; j++) {
                        buf[j] = 0;
                    }

                }
            }
            _fcloseall();
            return 0;
        }
        _fcloseall();
        return 1;
    }
    _fcloseall();
    return 2;
}

int main() {
    char path_original[] = "sourse/original.txt";
    char path1[] = "before_decompress.txt";
    char path2[] = "after_decompress.txt";
    unsigned char conclusion1 = 0;
    unsigned char conclusion2 = 0;


    printf("Start compressing\n");
    conclusion1 = compress(path_original, path1);
    printf("Compressing done\n");
    printf("Compress conclusion: ");
    switch (conclusion1)
    {
    case 0:
        printf("Success\n\n");
        break;
    case 1:
        printf("ERR: files don't oppened or created\n\n");
        break;
    case 2:
        printf("the pointers are wrong\n\n");
    default:
        printf("the pointers are wrong\n\n");
    }


    printf("Start decompressing\n");
    conclusion2 = decompress(path1, path2);
    printf("Decompressing done\n");
    printf("Deompress conclusion: ");
    switch (conclusion2)
    {
    case 0:
        printf("Success\n\n");
        break;
    case 1:
        printf("ERR: files don't oppened or created\n\n");
        break;
    case 2:
        printf("ERR: the pointers are wrong\n\n");
    default:
        printf("Unknown ERR\n\n");
    }




    //дописать функцию сравнения
    return 0;
}
