import sys
import os
from PIL import Image

def bmp_to_pgm_directory(directory):
    # Ensure directory exists
    if not os.path.isdir(directory):
        print(f"Error: '{directory}' is not a valid directory.")
        return

    # Loop through files in the directory
    for filename in os.listdir(directory):
        if filename.lower().endswith(".bmp"):
            bmp_path = os.path.join(directory, filename)
            pgm_path = os.path.join(directory, os.path.splitext(filename)[0] + ".pgm")

            try:
                img = Image.open(bmp_path)
                gray_img = img.convert('L')
                gray_img.save(pgm_path, format="PPM")  # PGM uses the PPM saver in Pillow
                print(f"Converted: {filename} → {os.path.basename(pgm_path)}")

            except Exception as e:
                print(f"Failed to convert {filename}: {e}")

def main():
    if len(sys.argv) != 2:
        print("Usage: python bmp_to_pgm_batch.py <directory>")
        sys.exit(1)

    directory = sys.argv[1]
    bmp_to_pgm_directory(directory)

if __name__ == "__main__":
    main()
