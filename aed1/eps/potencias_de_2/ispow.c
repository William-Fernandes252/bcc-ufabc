#include <stdio.h>
#include <stdlib.h>

int main() {
    int number, inputs, pow2_count = 0;

    scanf("%d", &inputs);
    for (int i = 0; i < inputs; i++) {
        scanf("%d", &number);
        if (number && !(number & (number - 1))) pow2_count += 1;
    }

    printf("%d\n", pow2_count);

    return EXIT_SUCCESS;
}