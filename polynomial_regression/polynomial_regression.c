#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pbPlots.h"
#include "supportLib.h"

int unique(double array[], int value){
    int i=0;
    while (i<100 && array[i]!=value)
    {
        i++;
    }

    return i==100;   
}

int generate_random_points(double array[], int param){         //the 'param' parameter is used to check which array is being filled
    for (int i = 0; i < 150; i++)
    {
        if (param==1)
        {
            do
            {
                array[i] = rand() % (151); //rand() % (max - min + 1) + min;
            } while (unique(array, array[i]));
        }else
        {
            array[i] = rand() % (151); //rand() % (max - min + 1) + min;
        }
    }
    
    return 0;
}

int show_points(double x_points[], double y_points[]) {
    for (int i = 0; i < 150; i++)
    {
        printf("x[%d] = %d\n",i, x_points[i]);
        printf("y[%d] = %d\n",i, y_points[i]);
    }

    return 0;
}

int polynomial_regression(double x_points[], double y_points[] , int polynomial_degree, double solution[]){
    //1st, we create a matrix, name Matrix, that contains the numbers x_points^n (all the x coord)
    double Matrix[150][polynomial_degree+1];
    for (int i = 0; i < 150; i++)
    {
        for (int j = 0; j <= polynomial_degree; j++)
        {
            Matrix[i][j] = pow(x_points[i],j);
        }  
    };

    //to determine coefficients of our polynomial, we'll use this formula : 
    //(Matrix^T * Matrix) * coeff = Matrix^T * y. Let's calculate each term:
    double Matrix_t_MAtrix[polynomial_degree+1][polynomial_degree+1];
    double Matrix_t_y[polynomial_degree+1];

    //Matrix^T * Matrix
    for (int i = 0; i <= polynomial_degree+1; i++) {
        for (int j = 0; j <= polynomial_degree+1; j++) {
            for (int k = 0; k < 150; k++) {
                Matrix_t_MAtrix[i][j] += Matrix[k][i] * Matrix[k][j];
            }
        }
    }

    //Matrix^T * y
    for (int i = 0; i <= polynomial_degree; i++) {
        for (int k = 0; k < 150; k++) {
            Matrix_t_y[i] += Matrix[k][i] * y_points[k];
        }
    }

    //coeff
    for (int i = 0; i <= polynomial_degree; i++) {
        solution[i] = Matrix_t_y[i] / Matrix_t_MAtrix[i][i];
    }

    // Print coefficients
    printf("Polynomial coefficients: ");
    for (int i = 0; i <= polynomial_degree; i++) {
        printf("%f ", solution[i]);
    }
    printf("\n");
    
    return 0;
}


int main(){
/*
    double x_points[150]; 
    double y_points[150];
    //these two calls can be made simultaneously by using two threads
    srand(time(NULL));

    generate_random_points(x_points,1);
    generate_random_points(y_points,2);

    show_points(x_points, y_points);
*/

    double x_points[150] = {
        0.0, 1.0067, 2.0134, 3.0201, 4.0268, 5.0336, 6.0403, 7.0470, 8.0537, 9.0604,
        10.0671, 11.0738, 12.0805, 13.0872, 14.0939, 15.1007, 16.1074, 17.1141, 18.1208, 19.1275,
        20.1342, 21.1409, 22.1477, 23.1544, 24.1611, 25.1678, 26.1745, 27.1812, 28.1879, 29.1946,
        30.2013, 31.2081, 32.2148, 33.2215, 34.2282, 35.2349, 36.2416, 37.2483, 38.2550, 39.2617,
        40.2685, 41.2752, 42.2819, 43.2886, 44.2953, 45.3020, 46.3087, 47.3154, 48.3221, 49.3289,
        50.3356, 51.3423, 52.3490, 53.3557, 54.3624, 55.3691, 56.3758, 57.3826, 58.3893, 59.3960,
        60.4027, 61.4094, 62.4161, 63.4228, 64.4295, 65.4362, 66.4429, 67.4497, 68.4564, 69.4631,
        70.4698, 71.4765, 72.4832, 73.4899, 74.4966, 75.5034, 76.5101, 77.5168, 78.5235, 79.5302,
        80.5369, 81.5436, 82.5503, 83.5570, 84.5638, 85.5705, 86.5772, 87.5839, 88.5906, 89.5973,
        90.6040, 91.6107, 92.6174, 93.6242, 94.6309, 95.6376, 96.6443, 97.6510, 98.6577, 99.6644,
        100.6711, 101.6779, 102.6846, 103.6913, 104.6980, 105.7047, 106.7114, 107.7181, 108.7248, 109.7315,
        110.7383, 111.7450, 112.7517, 113.7584, 114.7651, 115.7718, 116.7785, 117.7852, 118.7919, 119.7987,
        120.8054, 121.8121, 122.8188, 123.8255, 124.8322, 125.8389, 126.8456, 127.8523, 128.8591, 129.8658,
        130.8725, 131.8792, 132.8859, 133.8926, 134.8993, 135.9060, 136.9128, 137.9195, 138.9262, 139.9329,
        140.9396, 141.9463, 142.9530, 143.9597, 144.9664, 145.9732, 146.9799, 147.9866, 148.9933, 150.0
    };

    /*
    double y_points[150] = {
    -3567.89,  2048.67,  15423.45, -872.12,  9348.24, -12475.38,  18765.98, -5623.44,  24678.23, -13987.50,
    31234.12,  5483.67, -24789.64,  37548.92, -1256.89,  43876.34, -18954.76,  51784.23,  6123.78,  59876.89,
    -8745.21,  69348.67, -12634.98,  78923.56, -15423.78,  89456.23, -19567.89, 101348.67,  21678.45, -112345.89,
    123456.78, -24567.89, 134678.90,  27689.12, -145678.56,  156789.34, -28765.67,  178654.12,  31578.23, -189654.78,
    201345.67, -34876.12,  213678.45, -39876.89,  227890.34, -45678.12,  243789.45, -51678.78,  259876.56, -58976.23,
    276789.12, -67345.89,  295678.34, -76234.45,  315678.78, -86345.12,  336789.67, -97345.78,  359876.45, -109876.23,
    384789.12, -123678.45,  410678.89, -138765.12,  437678.34, -154678.56,  465789.67, -171876.23,  494789.12, -190678.78,
    524678.34, -210789.67,  555678.23, -232789.45,  587789.12, -255678.78,  620678.34, -279678.56,  654789.23, -304789.67,
    689789.12, -330678.34,  725678.56, -357789.78,  762789.12, -385678.34,  800789.45, -414789.67,  839789.12, -444789.78,
    879789.34, -475789.23,  920789.56, -507789.67,  962789.78, -540789.89, 1005789.12, -574789.34, 1050789.56, -609789.78,
    1096789.34, -645789.45, 1144789.12, -682789.56, 1194789.34, -720789.67, 1246789.45, -759789.12, 1300789.34, -799789.45,
    1356789.12, -840789.23, 1414789.34, -882789.45, 1474789.12, -925789.23, 1536789.34, -969789.45, 1600789.12, -1014789.34,
    1666789.23, -1060789.45, 1734789.12, -1108789.34, 1804789.23, -1158789.45, 1876789.12, -1210789.34, 1950789.23, -1264789.45
    };*/

/*
    double y_points[150];
    srand(time(NULL));

    generate_random_points(y_points, 2);
*/


    // Generate chaotic y values
    double y_points[150];
    for (int i = 0; i < 150; i++) {
        double noise = (rand() % 10000) + 1000;
        y_points[i] = 3 * x_points[i] * x_points[i] - 20 * x_points[i] + 4 + noise;
    }

    //plot the points on a graph
    RGBABitmapImageReference * imgRef = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    DrawScatterPlot(imgRef, 1280, 720, x_points, 150, y_points, 150, errorMessage);

    //creating png img of the graph
    ByteArray *pngData = ConvertToPNG(imgRef->image);
    WriteToFile(pngData, "plot.png");

    //polynomial regression
    int polynomial_degree = -1;
    do
    {
        printf("enter degree of plynomial : ");
        scanf("%d",&polynomial_degree);
    } while (polynomial_degree<0);
    
    double solution[polynomial_degree+1];
    polynomial_regression(x_points, y_points , polynomial_degree, solution);

    //polynomial graph
    double y_graph[150];
    for (int i = 0; i < 150; i++)
    {
        y_graph[i] = 0;
        for (int j = 0; j <= polynomial_degree; j++) {
            y_graph[i] += solution[j] * pow(x_points[i], j);
        }
    }
    
    //plot the points on a graph
    RGBABitmapImageReference * imgPolyRegRef = CreateRGBABitmapImageReference();
    DrawScatterPlot(imgPolyRegRef, 1280, 720, x_points, 150, y_graph, 150, errorMessage);

    //creating png img of the graph
    ByteArray *pngPolyRegData = ConvertToPNG(imgPolyRegRef->image);
    WriteToFile(pngPolyRegData, "polyRegression.png");
    
    return 0;
}
