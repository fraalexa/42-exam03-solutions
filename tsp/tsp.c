#include <math.h>
#include <stdio.h>
#include <unistd.h>

typedef struct city
{
	float x;
	float y;
}city;


float	dist(city first, city scnd)
{
	float dx = first.x - scnd.x;
	float dy = first.y - scnd.y;

	return(sqrtf((dx * dx)+(dy * dy)));
}

float tsp(float matrix[11][11], int *visited, float total , float best, int n, int x, int count)
{
	if (count == n)
	{
		total += matrix[x][0];
		if (total < best)
			best = total;
		return best;
	}
	
	for(int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			visited[i]= 1;
			best = tsp(matrix, visited, total + matrix[x][i], best, n , i, count + 1);
			visited[i] = 0;
		}
		
	}
	return best;
}

int main()
{
	city cities[11];
	float matrix[11][11];
	int visited[11];
	int n = 0;
	float best = 1e9;
	while(fscanf(stdin, "%f, %f\n", &cities[n].x , &cities[n].y) == 2)
	 n++;
	
	for(int i = 0; i < n ; i++)
	{
		for(int j = 0; j< n; j++)
		{
			matrix[i][j] = dist(cities[i], cities[j]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		visited[i] = 0;
	}
	visited[0] = 1;
	best = tsp(matrix, visited, 0.0f, best,  n ,0, 1);
	fprintf(stdout , "%.2f\n", best);
	return 0;
}