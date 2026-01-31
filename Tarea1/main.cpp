#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

int main() {
    int array_size;
    int num_threads;
    
    // Ask the user for the size of the arrays
    std::cout << "Enter the size of the arrays: ";
    std::cin >> array_size;
    
    if (array_size <= 0) {
        std::cerr << "Error: Array size must be greater than 0." << std::endl;
        return 1;
    }
    
    // Ask the user for the number of threads
    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;
    
    if (num_threads <= 0) {
        std::cerr << "Error: Number of threads must be greater than 0." << std::endl;
        return 1;
    }
    
    // Initialize arrays A, B, and C
    std::vector<int> A(array_size);
    std::vector<int> B(array_size);
    std::vector<int> C(array_size, 0); // Result array
    
    // Ask the user how they want to fill the arrays
    char choice;
    std::cout << "\nHow do you want to fill the arrays?" << std::endl;
    std::cout << "Enter 'm' for manual input or 'r' for random generation: ";
    std::cin >> choice;
    
    switch (choice) {
        case 'r':
        case 'R': {
            // Random generation
            int min_val, max_val;
            std::cout << "Enter minimum value for random numbers: ";
            std::cin >> min_val;
            std::cout << "Enter maximum value for random numbers: ";
            std::cin >> max_val;
            
            if (min_val > max_val) {
                std::cerr << "Error: Minimum value must be less than or equal to maximum value." << std::endl;
                return 1;
            }
            
            // Initialize random number generator
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(min_val, max_val);
            
            // Generate random values for array A
            std::cout << "\nGenerating random values for array A..." << std::endl;
            for (int i = 0; i < array_size; i++) {
                A[i] = dis(gen);
            }
            
            // Generate random values for array B
            std::cout << "Generating random values for array B..." << std::endl;
            for (int i = 0; i < array_size; i++) {
                B[i] = dis(gen);
            }
            break;
        }
        case 'm':
        case 'M': {
            // Manual input
            std::cout << "\nEnter " << array_size << " values for array A:" << std::endl;
            for (int i = 0; i < array_size; i++) {
                std::cout << "A[" << i << "] = ";
                std::cin >> A[i];
            }
            
            std::cout << "\nEnter " << array_size << " values for array B:" << std::endl;
            for (int i = 0; i < array_size; i++) {
                std::cout << "B[" << i << "] = ";
                std::cin >> B[i];
            }
            break;
        }
        default: {
            std::cerr << "Error: Invalid choice. Please enter 'm' or 'r'." << std::endl;
            return 1;
        }
    }
    
    std::cout << std::endl;
    
    std::cout << "Array A: ";
    for (int i = 0; i < array_size; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Array B: ";
    for (int i = 0; i < array_size; i++) {
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;
    
    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);
    
    // Use OpenMP to parallelize the sum operation with user-specified number of threads
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int actual_num_threads = omp_get_num_threads();
        
        // Calculate the range for each thread
        int elements_per_thread = array_size / actual_num_threads;
        int start = thread_id * elements_per_thread;
        int end = (thread_id == actual_num_threads - 1) ? array_size : start + elements_per_thread;
        
        std::cout << "Thread " << thread_id << " processing indixes " 
                  << start << " to " << (end - 1) << std::endl;
        
        // Each thread sums its assigned portion
        for (int i = start; i < end; i++) {
            C[i] = A[i] + B[i];
            std::cout << "Thread " << thread_id << ": C[" << i << "] = " 
                      << A[i] << " + " << B[i] << " = " << C[i] << std::endl;
        }
    }
    
    // Display the final result
    std::cout << "\nResult Array C: ";
    for (int i = 0; i < array_size; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
