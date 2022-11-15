#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int nbLigne(FILE* f) {
	int n = 0;
	char c;
	while (c != EOF) {
		c = fgetc(f);
		if (c == '\n') {
			n++;
		}
	}
	fseek(f, 0, SEEK_SET);
	return n;
}

float ** scanCoord(FILE* f) {
	int n = nbLigne(f);
	//printf("%d", n);
	float** l = malloc(n*sizeof(float*));
	for (int i=0; i<n; i++) {
		l[i] = malloc(2*sizeof(float*));
		//printf("x : %f | y : %f\n", l[i][0], l[i][1]);
	}
	
	for (int i = 0; i<n; i++) {
		fscanf(f, "%f %f", &l[i][0], &l[i][1]);
		//printf("x : %f | y : %f\n", l[i][0], l[i][1]);
	}

	/*
	for (int i = 0; i<n; i++) {
		printf("x : %f | y : %f\n", l[i][0], l[i][1]);
	}
	*/
	
	return l;
}

float perimetre(FILE* f) {
	int n = nbLigne(f);
	float** tab = scanCoord(f);
	float* dist = malloc(n*sizeof(float));
	
	float x, x2, y, y2;
	
	for (int i = 0; i<n-1; i++) {
		x = tab[i][0] - tab[i+1][0];
		x2 = x*x;
		
		y = tab[i][1] - tab[i+1][1];
		y2 = y*y;
		
		dist[i] = sqrt(x2 + y2);
	}
	
	x = tab[n-1][0] - tab[0][0];
	x2 = x*x;
	
	y = tab[n-1][1] - tab[0][1];
	y2 = y*y;
	
	dist[n-1] = sqrt(x2 + y2);
	
	float p = 0;
	
	for (int i = 0; i<n; i++) {
		p = p + dist[i];
	}
	
	return p;
}

int main() {
	FILE* f = fopen("./coordonnees.txt", "r");

	printf("%f\n", perimetre(f));
	
	fclose(f);
	return 0;
}
