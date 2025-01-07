#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// 基数ソート(引数が不適切であればfalseを返す)
// begin: ソートする配列の先頭要素へのポインタ
// end: ソートする配列の末尾要素の次の要素へのポインタ
// radix: 基数
bool radix_sort(item* begin, const item* end, int radix)
{
	// ToDo: 基数ソートを実装する
	if (begin == NULL || end == NULL || begin >= end || radix <= 1) {
		return false;
	}
    int max_value = 0;
    for (item* it = begin; it != end; ++it) {
        if (it->key > max_value) {
            max_value = it->key;
        }
    }

    int exp = 1;
    int n = end - begin;
    item* buffer = (item*)malloc(n * sizeof(item));
    if (buffer == NULL) {
        return false;
    }

    while (max_value / exp > 0) {
        int* count = (int*)calloc(radix, sizeof(int));
        if (count == NULL) {
            free(buffer);
            return false;
        }

        for (item* it = begin; it != end; ++it) {
            count[(it->key / exp) % radix]++;
        }

        for (int i = 1; i < radix; ++i) {
            count[i] += count[i - 1];
        }

        for (item* it = end - 1; it >= begin; --it) {
            buffer[--count[(it->key / exp) % radix]] = *it;
        }

        for (int i = 0; i < n; ++i) {
            begin[i] = buffer[i];
        }

        free(count);
        exp *= radix;
    }

    free(buffer);
    return true;
}