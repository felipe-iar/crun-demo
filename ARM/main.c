#include <stdio.h>

typedef struct {
  int r;
  int g;
  int b;
} rgb_t;

/* ITU BT.601 */
int rgb_to_luminance(const rgb_t *color) {
   int luminance;
   luminance = (int)(0.299f * color->r + 0.587f * color->g + 0.114f * color->b);
   return luminance;
}

int main(void) {
   int luminance;
   rgb_t input;

   printf("R:");   scanf("%d", &input.r);   printf("%d\n", input.r);
   printf("G:");   scanf("%d", &input.g);   printf("%d\n", input.g);
   printf("B:");   scanf("%d", &input.b);   printf("%d\n", input.b);

   luminance = rgb_to_luminance(&input);
   printf("---\nLuminance:%d\n", luminance);

   return 0;
}