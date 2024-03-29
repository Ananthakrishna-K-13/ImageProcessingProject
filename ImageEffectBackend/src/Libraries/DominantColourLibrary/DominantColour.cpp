#include "DominantColour.h"
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

// Distance is measured using the RGB values of the pixels (Formula same as for cartesian co-ordinates)
double calculateDistance(vector<double>& centroid, Pixel& pixel)
{
    double distance = (centroid[0] - pixel.r) * (centroid[0] - pixel.r) +
                      (centroid[0] - pixel.g) * (centroid[0] - pixel.g) +
                      (centroid[0] - pixel.b) * (centroid[0] - pixel.b);

    return distance;
}

void dominantColourEffect(vector<vector<Pixel>>& imageVector)
{
    srand(time(0)); // To generate random number

    int k = 6; // Number of clusters in which we segment the image
    vector<double> centroids[k]; // To store the cluster centers

    int i, j;
    int n = imageVector.size();
    int m = imageVector[0].size();

    double sum[k][3]; // Sum of RGB values of each cluster
    int freq[k] = {0}; // Know how many pixels lie in the cluster

    // Initialise sum to 0
    for (i = 0; i < k; ++i)
        sum[i][0] = sum[i][1] = sum[i][2] = 0;

    // Randomly pick k cluster centers
    for (i = 0; i < k; ++i)
    {
        int x = rand() % n;
        int y = rand() % m;

        // (x, y) is chosen as the center

        centroids[i].push_back(imageVector[x][y].r);
        centroids[i].push_back(imageVector[x][y].g);
        centroids[i].push_back(imageVector[x][y].b);
    }

    int clusterNumber[n][m]; // Store the cluster number to which the given pixel belongs

    // Iterate through each pixel
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            int cluster = 0; // To store the nearest center

            // Minimum distance of pixel from a given cluster center
            double minDistance = calculateDistance(centroids[0], imageVector[i][j]);

            // Calculate distance from each center and get the nearest one
            for (int ii = 1; ii < k; ++ii)
            {
                double distance = calculateDistance(centroids[ii], imageVector[i][j]);

                // Nearer center found
                if (distance < minDistance)
                {
                    cluster = ii;
                    minDistance = distance;
                }
            }

            clusterNumber[i][j] = cluster; // Assign a cluster to the pixel

            // Update the sum and frequency of cluster
            sum[cluster][0] += imageVector[i][j].r;
            sum[cluster][1] += imageVector[i][j].g;
            sum[cluster][2] += imageVector[i][j].b;
            ++freq[cluster];
        }
    }

    // Calculate the average values for each cluster
    for (i = 0; i < k; ++i)
    {
        double r = sum[i][0] / freq[i];
        double g = sum[i][1] / freq[i];
        double b = sum[i][2] / freq[i];

        centroids[i][0] = r;
        centroids[i][1] = g;
        centroids[i][2] = b;
    }

    // Assign the average values calculated to the pixels lying in that cluster
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            int cluster = clusterNumber[i][j];

            imageVector[i][j].r = centroids[cluster][0];
            imageVector[i][j].g = centroids[cluster][1];
            imageVector[i][j].b = centroids[cluster][2];
        }
    }
}