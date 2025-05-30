#include <stdio.h>
#include <stdbool.h>


unsigned char check(char* sourse_txt, char* decompress_text) {
    if (sourse_txt && decompress_text) {
        FILE* ptr_sourse_txt = fopen(sourse_txt, "r");
        FILE* ptr_decompress_text = fopen(decompress_text, "r");
        if (ptr_sourse_txt && ptr_decompress_text) {

            char tmp1 = 0;
            char tmp2 = 0;

            while (tmp1 == tmp2 && tmp1 != EOF) {
                tmp1 = getc(ptr_sourse_txt);
                tmp2 = getc(ptr_decompress_text);
            }


            fclose(ptr_sourse_txt);
            fclose(ptr_decompress_text);
            if (tmp1 != tmp2)
            {
                return 3;
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

unsigned char compress(char* text_for_compress, char* decompress_text) {
    if (text_for_compress && decompress_text) {
        FILE* ptr_text_for_compress1 = fopen(text_for_compress, "r");//сказать про 0D(табуляция)
        //FILE* ptr_text_for_compress2 = fopen(text_for_compress, "r");// для подсчета
        FILE* ptr_decompressed_text = fopen(decompress_text, "w");//
        if (ptr_text_for_compress1 && /*ptr_text_for_compress2 &&*/ ptr_decompressed_text) {
            unsigned char set_mask = 128;
            unsigned char mask = 1;
            int pos = 0;
            char buf[8] = { 0 };
            int tmp = 0;
            bool flag = true;

            do {
                for (; ((tmp = (fscanf_s(ptr_text_for_compress1, "%c", (buf + pos), 1))) != -1) && (pos != 7); pos++);
                pos = 0;

                if (tmp == EOF) {//значит остаточные байты
                    for (int j = 0; buf[j]; j++)
                    {
                        putc(buf[j], ptr_decompressed_text);
                        buf[j] = 0;
                        flag = false;
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
            } while (flag);
            fclose(ptr_decompressed_text);
            fclose(ptr_text_for_compress1);
            _fcloseall();
            return 0;
        }
        _fcloseall();
        return 1;
    }
    _fcloseall();
    return 2;
}

unsigned char decompress(char* compressed_text, char* text_for_decompress) {
    if (compressed_text && text_for_decompress) {
        FILE* ptr_text_for_decompress1 = fopen(compressed_text, "r");
        //FILE* ptr_text_for_decompress2 = fopen(compressed_text, "r");
        FILE* ptr_decompressed_text = fopen(text_for_decompress, "w");
        if (ptr_text_for_decompress1 && /*ptr_text_for_decompress2 &&*/ ptr_decompressed_text) {
            unsigned char set_mask = 128;
            unsigned char mask = 1;
            int pos = 0;
            char buf[8] = { 0 };
            int tmp = 0;
            bool flag = true;

            do {

                for (; ((tmp = (fscanf_s(ptr_text_for_decompress1, "%c", ((buf + pos + 1)), 1))) != -1) && (pos != 6); pos++);
                pos = 0;

                if (tmp == EOF) {//значит остаточные байты
                    for (int j = 1; buf[j]; j++) {
                        putc(buf[j], ptr_decompressed_text);
                        buf[j] = 0;
                    }
                    flag = false;

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
            } while (flag);
            fclose(ptr_decompressed_text);
            fclose(ptr_text_for_decompress1);
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
    unsigned char conclusion3 = 0;



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
        break;
    default:
        printf("the pointers are wrong\n\n");
    }


    printf("Start decompressing\n");
    conclusion2 = decompress(path1, path2);
    printf("Decompressing done\n");
    printf("Decompress conclusion: ");
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
        break;
    default:
        printf("Unknown ERR\n\n");
    }

    printf("Start comparing\n");
    conclusion3 = check(path_original, path2);
    printf("Comparing done\n");
    printf("Compare conclusion: ");
    switch (conclusion3)
    {
    case 0:
        printf("Success\n\n");
        break;
    case 1:
        printf("ERR: files don't oppened or created\n\n");
        break;
    case 2:
        printf("ERR: the pointers are wrong\n\n");
        break;
    case 3:
        printf("ERR: files are different\n\n");
        break;
    default:
        printf("Unknown ERR\n\n");
    }


    return 0;
}
