#include <stdio.h>
#include <stdlib.h>

int iteration_number() {
    int iter;
    do {
        printf("Enter number of iterations: ");
        scanf("%d", &iter);
    } while (iter < 0);
    
    return iter;
}

int get_array_length() {
    int n;
    do {
        printf("Enter array length: ");
        scanf("%d", &n);
    } while (n < 0);
    
    return n;
}

void get_user_points(float* table_X, float* table_Y, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter X-COORDINATES of %d element: ", i);
        scanf("%f", &table_X[i]);
        
        printf("Enter Y-COORDINATES of %d element: ", i);
        scanf("%f", &table_Y[i]);
    }
}

void gradient_descent(float* table_X, float* table_Y, int n, float* m, float* b, float learning_rate, float error_threshold) {
    for (int iter = 0; iter < 1000; iter++) {
        float m_grad = 0.0;
        float b_grad = 0.0;
        
        // Calculate gradients for each point
        for (int i = 0; i < n; i++) {
            float prediction = (*m) * table_X[i] + (*b);
            float error = prediction - table_Y[i];
            // Partial derivatives
            m_grad += 2 * table_X[i] * error;
            b_grad += 2 * error;
        }
        
        // Average gradients
        m_grad /= n;
        b_grad /= n;
        
        // Update parameters
        *m -= learning_rate * m_grad;
        *b -= learning_rate * b_grad;
        
        // Debug output
        if (iter % 100 == 0) {
            printf("iter %d: m = %.5f, b = %.4f\n", iter, *m, *b);
        }
    }
}

int main() {
    // Get user inputs
    int n = get_array_length();
    
    // tables containing points coords
    float* table_X = (float*)malloc(n * sizeof(float));
    float* table_Y = (float*)malloc(n * sizeof(float));
    
    if (table_X == NULL || table_Y == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Get iteration count and points' coords
    int iteration = iteration_number();
    get_user_points(table_X, table_Y, n);
    
    // Initializing parameters
    float m = 0.0;
    float b = 0.0;
    float learning_rate = 0.001;
    float error_threshold = 0.0001;
    
    // Train the 'model'
    gradient_descent(table_X, table_Y, n, &m, &b, learning_rate, error_threshold);
    
    // Show results
    printf("EXACT FUNCTION: y = %.5fx + %.5f\n", m, b);
    
    // Free allocated memory
    free(table_X);
    free(table_Y);
    
    return 0;
}