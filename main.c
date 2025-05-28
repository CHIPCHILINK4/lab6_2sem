#include <stdio.h>









unsigned char compress(char* text_for_compress, char* decompress_text) {
    if (text_for_compress && decompress_text) {
        FILE* ptr_text_for_compress1 = fopen(text_for_compress, "r");
        FILE* ptr_text_for_compress2 = fopen(text_for_compress, "r");// для подсчета
        FILE* ptr_decompressed_text = fopen(decompress_text, "w");//
        if (ptr_text_for_compress1 && ptr_text_for_compress2 && ptr_decompressed_text) {
            {
                unsigned char set_mask = 128;
                unsigned char mask = 1;
                int i = 0, ix = 0, pos = 0;

                for (; fscanf(ptr_text_for_compress2, "%c") != -1; pos++);



            }
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
        FILE* ptr_text_for_decompress = fopen(text_for_decompress, "r");
        FILE* ptr_compressed_text = fopen(compressed_text, "w");
        if (ptr_text_for_decompress && ptr_compressed_text) {






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
        printf("success\n\n");
        break;
    case 1:
        printf("ERR: files don't oppened or created\n\n");
        break;
    default:
        printf("Unknown ERR\n\n");
    }


    printf("Start decompressing\n");
    //conclusion2 = decompress(path1, path2);
    printf("Decompressing done\n");
    printf("Deompress conclusion: ");
    switch (conclusion1)
    {
    case 0:
        printf("success\n\n");
        break;
    default:
        printf("Unknown ERR\n\n");
    }
//дописать функцию сравнения

    return 0;
}
