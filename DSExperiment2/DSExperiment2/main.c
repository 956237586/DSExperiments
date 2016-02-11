//#define _DEBUG_ //ÇÐ»»µ÷ÊÔÄ£Ê½
#include "JosephRing.h"
int main() {
	JosephRing* ring = NULL;
	int i = 0;
	int k, m;
	printf("Please in put k and m:\n");
	scanf("%d %d", &k, &m);

	ring = createRing();
	for (i = 0; i < 10; i++)
		insert(ring, i);
#ifdef _DEBUG_
	printAll(ring);
#endif
	printf("the last number is %d\n", getNumber(ring, k, m));
	free(ring);

	ring = createRing();
	for (i = 0; i < 10; i++)
		insert(ring, i * 2 + 1);
#ifdef _DEBUG_
	printAll(ring);
#endif // _DEBUG_

	printf("the last number is %d\n", newGetNumber(ring, k));
	free(ring);
	system("pause");
	return 0;
}
