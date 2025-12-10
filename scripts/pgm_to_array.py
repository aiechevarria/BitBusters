#!/usr/bin/env python3
import sys
import os
from PIL import Image

# Define the fixed sprite size (12x12)
SPRITE_SIZE = 12

def pgm_to_c_array(img_path, index):
    """Convert a PGM image into a C array as part of a 2D sprite array."""
    img = Image.open(img_path)
    img = img.convert('L')  # Ensure grayscale
    
    width, height = img.size

    # Ensure image is square and fits into the SPRITE_SIZE (12x12)
    if width != SPRITE_SIZE or height != SPRITE_SIZE:
        raise ValueError(f"Image {img_path} is not the correct size ({SPRITE_SIZE}x{SPRITE_SIZE}).")

    pixels = list(img.getdata())
    
    # C array definition for a single sprite
    array_name = f"sprite_{index}"
    c_array = f"    // Sprite {index}: {os.path.basename(img_path)}\n"
    c_array += f"    {{ // {os.path.basename(img_path)}\n"

    # Format as a 2D array with one sprite per row of numbers
    for i in range(SPRITE_SIZE):
        c_array += "        { "
        for j in range(SPRITE_SIZE):
            pixel_value = pixels[i * SPRITE_SIZE + j]
            c_array += f"{pixel_value}, " if j < SPRITE_SIZE - 1 else f"{pixel_value} "
        c_array += "},\n"

    c_array += "    },\n"
    return c_array


def process_directory(directory):
    if not os.path.isdir(directory):
        print(f"Error: {directory} is not a valid directory.")
        return

    output_path = os.path.join(directory, "sprites.h")

    with open(output_path, "w") as outfile:
        outfile.write("// Auto-generated C array structure for item sprites\n\n")
        outfile.write("#define NUM_ITEMS 0\n")
        outfile.write("#define SPRITE_SIZE " + str(SPRITE_SIZE) + "\n\n")

        # Store each sprite in the itemSprites structure
        outfile.write("const char itemSprites[NUM_ITEMS][SPRITE_SIZE][SPRITE_SIZE] = {\n")

        sprite_index = 0
        for filename in os.listdir(directory):
            if filename.lower().endswith(".pgm"):
                file_path = os.path.join(directory, filename)
                print(f"Processing: {filename}")
                
                try:
                    c_data = pgm_to_c_array(file_path, sprite_index)
                    outfile.write(c_data)
                    sprite_index += 1
                except ValueError as e:
                    print(f"Skipping {filename}: {e}")

        outfile.write("};\n")

    print(f"\nDone! C arrays saved to: {output_path}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python pgm_to_sprite_struct.py <directory>")
        sys.exit(1)

    directory = sys.argv[1]
    process_directory(directory)


if __name__ == "__main__":
    main()
