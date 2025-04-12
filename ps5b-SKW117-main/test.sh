binary=build/image_calc

make clean; make

if [[ ! -a $binary ]]; then
    echo "FAIL: $binary not made"
    echo "SCORE:"
    echo "0/3"
    exit -1
fi
score=0
# Function to run the image operation and compare the output with the reference
check_image_operation() {
    local input_image=$1
    local width=$2
    local height=$3
    local operation=$4
    local output_image=$5
    local reference_image=$6

    # Run the operation
    echo "./build/image_calc $input_image $width $height $operation $output_image"
    ./build/image_calc "$input_image" "$width" "$height" "$operation" "$output_image" > /dev/null
    


    if [[ ! -a $output_image ]]; then
        echo "FAIL: $output_image not made"
        return
    fi
    # Compare the output with the reference
    local diff_result=$(diff "$output_image" "$reference_image" | wc -l)

    # Check if the diff result is non-zero (meaning there's a mismatch)
    if [ "$diff_result" -ne 0 ]; then
        echo "$operation Image Operation FAIL: Produced image does not match reference."
    else
        echo "$operation Image Operation PASS"
        score=$((score+1))
    fi
}

# Check grayscale operation
check_image_operation "images/sky.bmp" 640 426 "grayscale" "grayscale.bmp" "reference/grayscale.bmp"

# Check reflect operation
check_image_operation "images/sky.bmp" 640 426 "reflect" "reflect.bmp" "reference/reflect.bmp"

# Check greenscreen operation
check_image_operation "images/green-person.bmp" 350 350 "greenscreen" "green.bmp" "reference/green.bmp"


echo "SCORE:"
echo "$score/3"
