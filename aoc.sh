#!/bin/bash

# Function to create a new day directory and set up files
create_new_day() {
    day=$1

    # Create the new day directory
    mkdir $day

    # Move the template C++ file to the new day directory and rename it
    cp ./dayx.cc ./$day/$day.cc

    # Create an empty input file in the new day directory
    touch ./$day/input.txt

    echo "New day setup complete: $day"
}

# Function to compile and run the code for a specified day
compile_and_run() {
    day=$1

    # Compile the C++ file for the given day
    g++ ./$day/$day.cc -o ./$day/$day

    # Check if the compilation was successful
    if [ $? -ne 0 ]; then
        echo "Compilation failed"
        exit 1
    fi

    # Run the compiled executable with the input file
    ./$day/$day ./$day/input.txt
    rm ./$day/$day

    # Check if the execution was successful
    if [ $? -ne 0 ]; then
        echo "Execution failed"
        exit 1
    fi
}

# Main script logic
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <command> [day]"
    exit 1
fi

command=$1

case $command in
    "new")
        if [ "$#" -ne 2 ]; then
            echo "Usage: $0 new <dayN>"
            exit 1
        fi
        day=$2
        create_new_day $day
        ;;
    *)
        day=$command
        compile_and_run $day
        ;;
esac