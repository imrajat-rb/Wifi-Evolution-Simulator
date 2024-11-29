#!/bin/bash

# Function to build a project using its Makefile
build_project() {
    project_dir=$1
    echo "Building project in directory: $project_dir"
    
    # Navigate to the project directory
    cd "$project_dir" || { echo "Directory $project_dir not found"; exit 1; }
    
    # Clean the build (if necessary)
    if [ -f "Makefile" ]; then
        echo "Cleaning project..."
        make clean
    fi

    # Build the project
    echo "Building project..."
    make

    # Check if the build was successful
    if [ $? -eq 0 ]; then
        echo "Build for $project_dir completed successfully."
    else
        echo "Build for $project_dir failed."
        exit 1
    fi
    
    # Go back to the root directory
    cd ..
}

# Main script execution
echo "Starting build process..."

# Build each question's project
build_project "Question_1"
build_project "Question_2"
build_project "Question_3"

echo "Build process completed."
